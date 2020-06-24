#include "mlx75308.h"
#include "auto_wiper.h"
#include "spi.h"
#include "watchdog.h"
#include "gpio.h"
#include "clock.h"
#include "local_eep_data.h"

extern Main_Fsm_t  RLS_RunMode;
extern local_info_t local_info;
extern uint8  u8_IntSpeedEnterCnt;

tMlx75308_Config const Mlx75308_Config_Parameter =
{
       0x0b, //np
       0x02, //t_dem
       0x02, //t_dc
       0x00, //bw_adj_a
       0x00, //bw_adj_b
       0x01, //gain_adj_a
       0x01, //gain_adj_b
       0x03, //bw_sel_lp_a
       0x03, //bw_sel_lp_b
       0x04, //rf
       0x03, //dc_comp_ic1
       0x05, //dc_comp_ic2
       0x04, //dc_comp_ic3
       0x02, //dc_comp_ic4
       0x01, //dc_comp_ic5
       0x01, //dc_comp_en
       0xA8, //dac_a_default
       0xA8  //dac_b_default
} ;

MLX75308_Frame_t       MLX75308_RxFrame;
MLX75308_Mnrval_t      Mnrval;

uint8  MLX75308_A_Gain,MLX75308_B_Gain;
uint16 u16_DC_comp_value;
uint16 u16_Save_DC_bre_[2],u16_Save_DC_aft_[2];
uint16 u16_Delta_DC_bre_[2],u16_Delta_DC_aft_[2];

/*******************************************************
 * FUNCTION NAME : RLS_Rain_Get_Measure()
 *   DESCRIPTION : RLS_Rain_Get_Measure function 
 *         INPUT : PD_chan ,n ,DC_cancel_th
 *        OUTPUT : NONE  
 *        RETURN : rain_adc              
 *        OTHERS : NONE
 *******************************************************/
uint16 RLS_Rain_Get_Measure(uint8 PD_chan,uint8 n,uint16 DC_cancel_th)
{   
   uint32 sum,sum_DC[2];
   uint16 DC_chk;
   uint8 i,mtime;
   uint8 Chan_Temp = CHAN_A;
   uint16 temp_th1,temp_th2;
   
   if(PD_chan == PDB) Chan_Temp = CHAN_B;
   
   mtime = 0;
   sum = 0;
   sum_DC[0]= 0;
   sum_DC[1]= 0;
   
   for(i = 0; i < n;)
   {
	  WDOG_Feed();
      MLX75308_Meansure(PD_chan);
      
      if(MLX75308_RxFrame.data_field[0] > MLX75308_RxFrame.data_field[2])
         DC_chk = MLX75308_RxFrame.data_field[0] - MLX75308_RxFrame.data_field[2]; 
      else 
         DC_chk = MLX75308_RxFrame.data_field[2] - MLX75308_RxFrame.data_field[0];
     

      if((RLS_RunMode == MAIN_SLEFADAPT)||(DC_chk < DC_cancel_th))
	  {
		if(MLX75308_RxFrame.data_field[1] > 34000) 
		{
		  sum_DC[0] += MLX75308_RxFrame.data_field[0];
		  sum_DC[1] += MLX75308_RxFrame.data_field[2];  
		  sum += MLX75308_RxFrame.data_field[1];
		  mtime ++;
		  i ++;
		}
		else
		{
		   return 0; 
		}
	  }
   }
   
   if(u8_IntSpeedEnterCnt > 2)
   {
	   temp_th1 =  DC_bef_dtTH_RAIN;
	   temp_th2 =  DC_aft_dtTH_RAIN;
   }
   else
   {
	   temp_th1 =  DC_bef_dtTH;
	   temp_th2 =  DC_aft_dtTH;
   }
   

	Mnrval.DC_bre_[Chan_Temp] = (uint16)(sum_DC[0]/mtime);
	Mnrval.DC_aft_[Chan_Temp] = (uint16)(sum_DC[1] / mtime);
	
	u16_Delta_DC_bre_[Chan_Temp]=  (u16_Save_DC_bre_[Chan_Temp] >= Mnrval.DC_bre_[Chan_Temp])?(u16_Save_DC_bre_[Chan_Temp] - Mnrval.DC_bre_[Chan_Temp]):(Mnrval.DC_bre_[Chan_Temp] - u16_Save_DC_bre_[Chan_Temp]);
	u16_Delta_DC_aft_[Chan_Temp] =  (u16_Save_DC_aft_[Chan_Temp] >= Mnrval.DC_aft_[Chan_Temp])?(u16_Save_DC_aft_[Chan_Temp] - Mnrval.DC_aft_[Chan_Temp]):(Mnrval.DC_aft_[Chan_Temp]- u16_Save_DC_aft_[Chan_Temp]);
	
	u16_Save_DC_bre_[Chan_Temp]  =  Mnrval.DC_bre_[Chan_Temp];
	u16_Save_DC_aft_[Chan_Temp]  =  Mnrval.DC_aft_[Chan_Temp];
	
	if((u16_Delta_DC_bre_[Chan_Temp] > temp_th1) ||
			(u16_Delta_DC_aft_[Chan_Temp]> temp_th2))    return 0; 

    
    sum = sum / mtime;
   
    //-----------DC SOFT compensation ---------------//


    return ((uint16) (sum)); 
}



/*******************************************************
 * FUNCTION NAME : MLX75308_Init()
 *   DESCRIPTION : MLX75308_Init function 
 *         INPUT : NONE
 *        OUTPUT : NONE  
 *        RETURN : calc value              
 *        OTHERS : NONE
 *******************************************************/
void MLX75308_Init(void)
{
    
    (void)SPI_Wr_Cmd(CR);
    WDOG_Feed();
    while(!DR);
                                             
    Delay_Ms(2);
   
    SPI_Wr_Reg(0xFF,addr_EnChan); //Ê¹ÄÜPDA B C D E
    Delay_Ms(5);

    MLX75308_SetPara(NP, Mlx75308_Config_Parameter.np);   //24pluss
    MLX75308_SetPara(Tdem, Mlx75308_Config_Parameter.t_dem); //the demodulator delay time in the rain channel 0.8us
    MLX75308_SetPara(Tdc, Mlx75308_Config_Parameter.t_dc); //200us  default value
    
    /*****************anti-aliasing filter ****************/
    MLX75308_SetPara(BW_ADJ_AA_A,Mlx75308_Config_Parameter.bw_adj_a);//4
    MLX75308_SetPara(BW_ADJ_AA_B,Mlx75308_Config_Parameter.bw_adj_b);//4
    /*****************************************************/
    MLX75308_SetPara(BW_SEL_LP_A,Mlx75308_Config_Parameter.bw_sel_lp_a);//2
    MLX75308_SetPara(DACA, local_info.DAC_EEPdtata[0]);
    MLX75308_SetPara(GAIN_ADJ_AA_A,Mlx75308_Config_Parameter.gain_adj_a);

    MLX75308_SetPara(BW_SEL_LP_B,Mlx75308_Config_Parameter.bw_sel_lp_b);//2              
    MLX75308_SetPara(DACB, local_info.DAC_EEPdtata[1]);
    MLX75308_SetPara(GAIN_ADJ_AA_B,Mlx75308_Config_Parameter.gain_adj_b);

    MLX75308_SetPara(RF,Mlx75308_Config_Parameter.rf);  //69.4khz default value
    /*****************************************************/

    MLX75308_SetPara(DC_COMP_IC1,Mlx75308_Config_Parameter.dc_comp_ic1);         
    MLX75308_SetPara(DC_COMP_IC2,Mlx75308_Config_Parameter.dc_comp_ic2);
    MLX75308_SetPara(DC_COMP_IC3,Mlx75308_Config_Parameter.dc_comp_ic3);  
    MLX75308_SetPara(DC_COMP_IC4,Mlx75308_Config_Parameter.dc_comp_ic4); 
    MLX75308_SetPara(DC_COMP_IC5,Mlx75308_Config_Parameter.dc_comp_ic5);

    MLX75308_SetPara(EN_DCCOMP,Mlx75308_Config_Parameter.dc_comp_en);
   
}



