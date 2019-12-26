/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           rls_app.c
** Last modified Date:  2017-12-19
** Last Version:        V1.00
** Descriptions:        全局参数声明。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          xujun
** Created date:        2017-12-19
** Version:             V1.00
** Descriptions:        创建文件
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"
#include "spi.h"
#include "api.h"
#include "clock.h"
#include "gpio.h"
#include "adc.h"
#include "rls_app.h"
#include "lin_app.h"
#include "HCS12EEPROM.h"
#include "config_parameter.h"



uint8 u8_receive_data_flg ;
uint8 u8_rain_detect_flg;


uint16 API_6h_Cnt;
uint8  u8_send_break_cnt;
uint8  u8_rls_wake_up_bcm_flg,u8_receive_break_flag;
uint8  u8_lin_cmd_sleep_flg ;
       
uint16 u16_Pd_Measure_Value;
uint8  u8_Wiper_State,u8_Wiper_StatePre;
uint8  u8_Rain_SensitivityLowValue;

uint8  u8_Wiper_StatePre_Int,u8_Wiper_StatePre_Int_Cnt;


uint8  MLX75308_A_Gain,MLX75308_B_Gain,MLX75308_A_Adc,MLX75308_B_Adc;
uint16 u16_Delta_DC_bre_A,u16_Delta_DC_aft_A,u16_Delta_DC_bre_B,u16_Delta_DC_aft_B;
uint16 u16_Save_DC_bre_A,u16_Save_DC_aft_A,u16_Save_DC_bre_B,u16_Save_DC_aft_B;

uint16 PD_WIN_AVG[CHAN_NUM][PD_WINDOW];
uint16 DC_WIN_BUFF[CHAN_NUM][DC_WINDOW];
uint16 u16_DC_PD_dt[CHAN_NUM];

uint8  u8_RainIntensity_Win[Rain_WINDOW];
uint16 u16_PD_Win_Max[CHAN_NUM]; 
uint8  u8_PD_State[CHAN_NUM];
uint16 u16_Dt_PD[CHAN_NUM];

uint16 u16_PDA_Wmax,u16_PDB_Wmax;

uint16 PD_Meas_Comp_Ref[CHAN_NUM] ;
uint16 PD_Meas_Comp_Ref_Pre[CHAN_NUM];
uint8 u8_Juge_Rain_Cnt[CHAN_NUM] ;

uint16 u16_DC_Comp_Value[CHAN_NUM];


uint8  u8_RainIntensity[CHAN_NUM];
uint8  u8_RainIntensityPre[CHAN_NUM];

uint8  u8_RainIntensity_Max;
uint8  u8_Rain_Invalid_Cnt;

uint8 u8_MeasureSureTime,u8_RLS_StopMsureFlg;

uint8  u8_ClearEnternIntSpeedCnt;
uint8  u8_IntSpeedEnterCnt,u8_LowSpeedCnt;

uint8  u8_ExitLowSpeedCnt,u8_IntSpeedCnt,u8_IntDelayTimer,u8_HighHoldCnt;
uint8  u8_HighSpeedHoldCnt,u8_low_enter_high_timer;
uint8  u8_cnt_choose;
uint8  u8_cnt_choose_pre;
uint8  u8_Int_Time;
uint8  u8_Int_Time_pre;

uint8  u8_EnterLowSpeedCnt;

uint8  u8_Rain_Valid;
uint8  u8_Rain_Value,u8_WiperSpeed_Expert;

uint16 u16_DC_checkValue,u16_DC_comp_value,u16_Ref_Adc_A,u16_Ref_Adc_B;
uint8  RLS_RunMode;
uint8  u8_Rain_Delta;

uint8  u8_LightOnTimer;

uint8  Light_On_Flag[LIGHT_TYPE];
uint8  Light_cnt[LIGHT_TYPE];

uint8  u8_Wipe_Automatic_On_Flg;
uint8  u8_Wipe_Automatic_On_Pre;
uint8  u8_Automatic_On_Cnt;

uint8  u8_SensitivityUpCnt;   
uint8  u8_SensitivityUpFlg;
uint8  u8_Rain_SensitivityPre; 

uint8  u8_IntSpeedFlgCnt;
uint8  u8_IntSpeedFlg;

uint16 u16_Battery_Volt;
uint8  u8_low_voltage_cnt;
uint8  u8_high_voltage_cnt;
uint8  u8_Lin_Diag_Enable;
uint8  u8_Lin_Diag_Enable_Cnt;

uint16  u16_Brightness_FW;
uint8   u8_Brightness_IR;
uint8   Light_on_cnt[LIGHT_TYPE];
uint8   Light_off_cnt[LIGHT_TYPE];

struct MLX75308_Frame    MLX75308_RxFrame;
struct MLX75308_Mnrval   Mnrval;
struct Rls_Error         App_Rls_Error;
 
/*****NEW PCB**X37*********/
const uint32 Tab_AWG_FW[Tab_FW_NUM]        = {5018,11019, 12317, 13687, 15252, 16290, 16500, 16750,17000,17500,18000,18500,19000,19250,19500,19750};
const uint16 Tab_Brightness_FW[Tab_FW_NUM] = {0,    40,    150,   220,   300,  350,    400,   500,  550, 600, 659 , 700,  750,  800,  866,  1021};

const uint32 Tab_AWG_IR[Tab_IR_NUM]        = {21062,26277 ,29680,30642,31246,32353,33035,33673,34084,34296,34780,35000,35220,  35420,   35700,  36000};
const uint16 Tab_Brightness_IR[Tab_IR_NUM] = { 0   ,  9,     21,    29,   35,  51,   60,   75  , 80,  85,  90,   95,    100,    150,    200,    253}; 


/*******************************************************
 * FUNCTION NAME : Search_Table()
 *   DESCRIPTION : line table 
 *         INPUT : in_x ,*Tabx ,*Taby, Tab_NUM
 *        OUTPUT : NONE  
 *        RETURN : calc value              
 *        OTHERS : NONE
 *******************************************************/
uint16 Search_Table(uint32 in_x,uint32 *Tabx,uint16 *Taby,uint8 Tab_NUM)
{
    uint8 Search_Inx;
    uint8 Lit_Inx,Big_Inx;
    uint16 Result;
    
    Search_Inx = Tab_NUM/2;
    
    if(in_x < *(Tabx)) 
    {   
        return *(Taby);
    }
    else
    {
        if(in_x == *(Tabx + Search_Inx)) 
        {
            return *(Taby + Search_Inx);
        } 
    
        else if(in_x > *(Tabx + Search_Inx))
        {

            for(Search_Inx ++; Search_Inx <= (Tab_NUM - 1); Search_Inx ++)
            {
                if((Search_Inx == (Tab_NUM - 1)) || (in_x <= *(Tabx + Search_Inx))) 
                {
                    
                    Lit_Inx = Search_Inx - 1;
                    Big_Inx = Search_Inx;
                    Result = (uint16) ((*(Taby + Big_Inx) - *(Taby + Lit_Inx)) * (in_x - *(Tabx + Lit_Inx))/(*(Tabx + Big_Inx) - *(Tabx + Lit_Inx)) + *(Taby + Lit_Inx));
                    return Result;
                }
            }
        } 
        else 
        {
            for(Search_Inx --; Search_Inx >= 0; Search_Inx --)
            {
                if((Search_Inx == 0) || (in_x >= *(Tabx + Search_Inx))) 
                {
                    Lit_Inx = Search_Inx;
                    Big_Inx = Search_Inx + 1;
                    Result = (uint16) ((*(Taby + Big_Inx) - *(Taby + Lit_Inx)) * (in_x - *(Tabx + Lit_Inx))/(*(Tabx + Big_Inx) - *(Tabx + Lit_Inx)) + *(Taby + Lit_Inx));
                    return Result;
                }
            }        
        }
    }
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
    uint8 i;
    
    (void)SPI_Wr_Cmd(CR);
    while(!DR);
                                             
    Delay_Ms(2);
   
    SPI_Wr_Reg(0xFF,addr_EnChan); //使能PDA B C D E
    Delay_Ms(5);

    MLX75308_SetPara(NP, Mlx75308_Config_Parameter[0].np);   //24pluss
    MLX75308_SetPara(Tdem, Mlx75308_Config_Parameter[0].t_dem); //the demodulator delay time in the rain channel 0.8us
    MLX75308_SetPara(Tdc, Mlx75308_Config_Parameter[0].t_dc); //200us  default value
    
    /*****************anti-aliasing filter ****************/
    MLX75308_SetPara(BW_ADJ_AA_A,Mlx75308_Config_Parameter[0].bw_adj_a);//4
    MLX75308_SetPara(BW_ADJ_AA_B,Mlx75308_Config_Parameter[0].bw_adj_b);//4
    /*****************************************************/
    MLX75308_SetPara(BW_SEL_LP_A,Mlx75308_Config_Parameter[0].bw_sel_lp_a);//2
    MLX75308_SetPara(DACA, MLX75308_A_Adc);
    MLX75308_SetPara(GAIN_ADJ_AA_A,Mlx75308_Config_Parameter[0].gain_adj_a);

    MLX75308_SetPara(BW_SEL_LP_B,Mlx75308_Config_Parameter[0].bw_sel_lp_b);//2              
    MLX75308_SetPara(DACB, MLX75308_B_Adc);
    MLX75308_SetPara(GAIN_ADJ_AA_B,Mlx75308_Config_Parameter[0].gain_adj_b);

    MLX75308_SetPara(RF,Mlx75308_Config_Parameter[0].rf);  //69.4khz default value
    /*****************************************************/

    MLX75308_SetPara(DC_COMP_IC1,Mlx75308_Config_Parameter[0].dc_comp_ic1);         
    MLX75308_SetPara(DC_COMP_IC2,Mlx75308_Config_Parameter[0].dc_comp_ic2);
    MLX75308_SetPara(DC_COMP_IC3,Mlx75308_Config_Parameter[0].dc_comp_ic3);  
    MLX75308_SetPara(DC_COMP_IC4,Mlx75308_Config_Parameter[0].dc_comp_ic4); 
    MLX75308_SetPara(DC_COMP_IC5,Mlx75308_Config_Parameter[0].dc_comp_ic5);

    MLX75308_SetPara(EN_DCCOMP,Mlx75308_Config_Parameter[0].dc_comp_en);
   
   //------------------------------------------
    for(i = 0 ;i < PD_WINDOW; i++)   
    {
        PD_WIN_AVG[CHAN_A][i] =  RLS_Rain_Get_Measure(PDA,3,600); 
        PD_WIN_AVG[CHAN_B][i] =  RLS_Rain_Get_Measure(PDB,3,600);
    }
}

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
   uint16 PDavage,DC_chk,temp;
   uint8 i,mtime;
   
   mtime = 0;
   sum = 0;
   sum_DC[0]= 0;
   sum_DC[1]= 0;
   
   for(i = 0; i < n;)
   {
      _FEED_COP(); /* feeds the dog */
      MLX75308_Meansure(PD_chan);
      
      if(MLX75308_RxFrame.data_field[0] > MLX75308_RxFrame.data_field[2])
         DC_chk = MLX75308_RxFrame.data_field[0] - MLX75308_RxFrame.data_field[2]; 
      else 
         DC_chk = MLX75308_RxFrame.data_field[2] - MLX75308_RxFrame.data_field[0];
     
      u16_DC_checkValue =  DC_chk;

      if(RLS_RunMode == NORMAL)
      {
          if((DC_chk < DC_cancel_th) && (MLX75308_RxFrame.data_field[1] > 34000)) 
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
      else if(RLS_RunMode == SLEFADAPT)
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
   
   if(PD_chan == PDA) 
   {
        sum_DC[0] = sum_DC[0] / mtime;
        Mnrval.DC_bre_A = (uint16)(sum_DC[0]);
        Mnrval.DC_aft_A = (uint16)(sum_DC[1] / mtime);
        
        u16_Delta_DC_bre_A =  (u16_Save_DC_bre_A >= Mnrval.DC_bre_A)?(u16_Save_DC_bre_A - Mnrval.DC_bre_A):(Mnrval.DC_bre_A - u16_Save_DC_bre_A);
        u16_Delta_DC_aft_A =  (u16_Save_DC_aft_A >= Mnrval.DC_aft_A)?(u16_Save_DC_aft_A - Mnrval.DC_aft_A):(Mnrval.DC_aft_A - u16_Save_DC_aft_A);
        
        u16_Save_DC_bre_A  =  Mnrval.DC_bre_A;
        u16_Save_DC_aft_A  =  Mnrval.DC_aft_A;
        
        if((u16_Delta_DC_bre_A > DC_bef_dtTH) || (u16_Delta_DC_aft_A > DC_aft_dtTH))    return 0; 
   }
   else if(PD_chan == PDB) 
   {  
        sum_DC[0] = sum_DC[0] / mtime;
        Mnrval.DC_bre_B = (uint16)(sum_DC[0]);
        Mnrval.DC_aft_B = (uint16)(sum_DC[1] / mtime);
        
        u16_Delta_DC_bre_B =  (u16_Save_DC_bre_B >= Mnrval.DC_bre_B)?(u16_Save_DC_bre_B - Mnrval.DC_bre_B):(Mnrval.DC_bre_B - u16_Save_DC_bre_B);
        u16_Delta_DC_aft_B =  (u16_Save_DC_aft_B >= Mnrval.DC_aft_B)?(u16_Save_DC_aft_B - Mnrval.DC_aft_B):(Mnrval.DC_aft_B - u16_Save_DC_aft_B);
       
        u16_Save_DC_bre_B  =  Mnrval.DC_bre_B;
        u16_Save_DC_aft_B  =  Mnrval.DC_aft_B;
        
        if((u16_Delta_DC_bre_B > DC_bef_dtTH) || (u16_Delta_DC_aft_B > DC_aft_dtTH))   return 0;
    }
    
    sum = sum / mtime;
   
    //-----------DC SOFT compensation ---------------//
   
    if(RLS_RunMode == SLEFADAPT)
    {
        PDavage = (uint16) (sum);
    }
    else if(RLS_RunMode == NORMAL)
    {
        if(PD_chan == PDA)
        {
            if(Mnrval.DC_aft_A <= DC_COMP_TH0)
            {   
                PDavage = sum ; 
            }
            else
            {
                temp =  Mnrval.DC_aft_A - DC_COMP_TH0 ;
                u16_DC_Comp_Value[0] = temp*10/ SOFT_DC_COMP_VALUE0;
                PDavage = sum - u16_DC_Comp_Value[0];
            }
        }
        else if(PD_chan == PDB)
        {
            if(Mnrval.DC_aft_B <= DC_COMP_TH0)
            {   
                PDavage = sum ; 
            }        
            else 
            {   
                temp =  Mnrval.DC_aft_B - DC_COMP_TH0 ;
                u16_DC_Comp_Value[1] = temp*10/ SOFT_DC_COMP_VALUE0; 
                PDavage = sum - u16_DC_Comp_Value[1];   
            }
        }
        else
        {
        }
    }
   
    return (PDavage); 
}

/*******************************************************
 * FUNCTION NAME : RLS_Light_Module_Fault_Process()
 *   DESCRIPTION : RLS_Light_Module_Fault_Process function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
 
void RLS_Light_Module_Fault_Process(void)
{
	if(Mnrval.Amb_C == 0xFFFF)    //light
	{
		App_Rls_Error.LS_Error_Cnt++;
		if(App_Rls_Error.LS_Error_Cnt >= 50)
		{
			App_Rls_Error.LS_Error = 1;
		}
	}
	else
	{
		App_Rls_Error.LS_Error_Cnt = 0;
	}
	
	if(App_Rls_Error.LS_Error_Cnt < 50)
	{
		App_Rls_Error.LS_Error = 0;
	}
				
	if(Mnrval.Amb_D == 0)  //IR
	{
		App_Rls_Error.IR_Error_Cnt[0]++;
		if(App_Rls_Error.IR_Error_Cnt[0] >= 50)
		{
			App_Rls_Error.IR_Error = 1;
		}
	}
	else
	{
		App_Rls_Error.IR_Error_Cnt[0] = 0;
	}
		
	if(App_Rls_Error.IR_Error_Cnt[0] < 50)
	{
		App_Rls_Error.IR_Error = 0;
	}
	
	
	if((App_Rls_Error.IR_Error == 1)||(App_Rls_Error.LS_Error == 1))
	{
    	Lin_RLS_Frame.Fault_Light = 1;
	}
	else
	{
	    Lin_RLS_Frame.Fault_Light = 0;
	}
	
}

/*******************************************************
 * FUNCTION NAME : RLS_AutoLightControl()
 *   DESCRIPTION : RLS_AutoLightControl function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_AutoLightControl(void)
{
    uint16 temp,temp_light_on_th,temp_light_off_th;
    uint8 temp_on_ir,temp_off_ir;

    if(u8_SPD_Vehicle == 0)   
    {
        u8_LightOnTimer  =  5 ;        
    }
    else if(u8_SPD_Vehicle <= 40)
    {
        u8_LightOnTimer  =  10;           
    }    
    else if(u8_SPD_Vehicle <= 80)
    {
        u8_LightOnTimer  =  9;         
    }    
    else 
    {
        u8_LightOnTimer  =  7; 
    }
    
    
    temp =  Lin_RLS_Frame.Brightness_FW_H;
    u16_Brightness_FW =  (temp <<8| Lin_RLS_Frame.Brightness_FW_L) ;
    u8_Brightness_IR =  Lin_RLS_Frame.Brightness_IR;

    if(u8_Brightness_IR <= 5)
    {
        temp_light_on_th =  Light_Stastegy_Parameter[0].Lowbean_on_th;
        temp_light_off_th =  Light_Stastegy_Parameter[0].Lowbean_off_th; 
    }
    else if (u8_Brightness_IR <= 10)
    {
        temp_light_on_th =  Light_Stastegy_Parameter[0].Lowbean_on_th + 16;
        temp_light_off_th =  Light_Stastegy_Parameter[0].Lowbean_off_th + 16;
    }
    else 
    {
        temp_light_on_th =  Light_Stastegy_Parameter[0].Lowbean_on_th + 33;
        temp_light_off_th =  Light_Stastegy_Parameter[0].Lowbean_off_th + 33;
    }
	
        
    if(App_Rls_Error.IR_Error == 0)
    {
        if((u16_Brightness_FW <= temp_light_on_th )&&(u8_Brightness_IR <= 2))
        {
            Light_off_cnt[LIGHT] = 0;
            if(Light_on_cnt[LIGHT] >= u8_LightOnTimer)
            {
                Lin_RLS_Frame.RQ_LowBeam = 1;     
                Lin_RLS_Frame.RQ_LowBeam_Invers = 0;
            }
            else
            {
                Light_on_cnt[LIGHT]++ ;
            }
        } 
		
        else if((u16_Brightness_FW > temp_light_off_th )&&(u8_Brightness_IR > 4)||(u16_Brightness_FW >= 500))
        {
            Light_on_cnt[LIGHT] = 0;
            if(Light_off_cnt[LIGHT] >= Light_Stastegy_Parameter[0].off_timer)
            {
                Lin_RLS_Frame.RQ_LowBeam = 0;     
                Lin_RLS_Frame.RQ_LowBeam_Invers = 1;
            }
            else
            {
                Light_off_cnt[LIGHT]++ ;
            }
        }
        else
        {
           Light_off_cnt[LIGHT] = 0;
           Light_on_cnt[LIGHT] = 0;
        }
    }
	
    else
    {
        if(u16_Brightness_FW <= temp_light_on_th )
        {
            Light_off_cnt[LIGHT] = 0;
            if(Light_on_cnt[LIGHT] >= u8_LightOnTimer)
            {
                Lin_RLS_Frame.RQ_LowBeam = 1;     
                Lin_RLS_Frame.RQ_LowBeam_Invers = 0;
            }
            else
            {
                Light_on_cnt[LIGHT]++ ;
            }
        } 
        else if(u16_Brightness_FW > temp_light_off_th )
        {
            Light_on_cnt[LIGHT] = 0;
            if(Light_off_cnt[LIGHT] >= Light_Stastegy_Parameter[0].off_timer)
            {
                Lin_RLS_Frame.RQ_LowBeam = 0;     
                Lin_RLS_Frame.RQ_LowBeam_Invers = 1;
            }
            else
            {
                Light_off_cnt[LIGHT]++ ;
            }
        }
        else
        {
            Light_on_cnt[LIGHT] = 0;
            Light_off_cnt[LIGHT] = 0;
        }
    }
	
	
    if(u8_Brightness_IR <= 5)
    {
        temp_light_on_th =  Light_Stastegy_Parameter[0].PositionLamp_on_th;
        temp_light_off_th =  Light_Stastegy_Parameter[0].PositionLamp_off_th; 
    }
    else if (u8_Brightness_IR <= 10)
    {
        temp_light_on_th =  Light_Stastegy_Parameter[0].PositionLamp_on_th + 16;
        temp_light_off_th =  Light_Stastegy_Parameter[0].PositionLamp_off_th + 16;
    }
    else 
    {
        temp_light_on_th =  Light_Stastegy_Parameter[0].PositionLamp_on_th + 33;
        temp_light_off_th =  Light_Stastegy_Parameter[0].PositionLamp_off_th + 33;
    }
		
    if(App_Rls_Error.IR_Error == 0)
    {
        if((u16_Brightness_FW <=  temp_light_on_th)&&(u8_Brightness_IR <= 2))
        {
            Light_off_cnt[TWILIGHT] = 0;
            if(Light_on_cnt[TWILIGHT] >= u8_LightOnTimer)
            {
                Lin_RLS_Frame.RQ_PositionLamp = 1;     
                Lin_RLS_Frame.RQ_PositionLamp_Invers = 0;
            }
            else
            {
                Light_on_cnt[TWILIGHT]++ ;
            }
        } 
        else if((u16_Brightness_FW > temp_light_off_th)&&(u8_Brightness_IR > 4)||(u16_Brightness_FW >= 500))
        {
            Light_on_cnt[TWILIGHT] = 0;
            if(Light_off_cnt[TWILIGHT] >= Light_Stastegy_Parameter[0].off_timer)
            {
                Lin_RLS_Frame.RQ_PositionLamp = 0;     
                Lin_RLS_Frame.RQ_PositionLamp_Invers = 1; 
            }
            else
            {
                Light_off_cnt[TWILIGHT]++ ;
            }
        }
        else
        {
            Light_off_cnt[TWILIGHT] = 0;
            Light_on_cnt[TWILIGHT] = 0;
        }
    }
    else
    {
        if(u16_Brightness_FW <=  temp_light_on_th)
        {
            Light_off_cnt[TWILIGHT] = 0;
            if(Light_on_cnt[TWILIGHT] >= u8_LightOnTimer)
            {
                Lin_RLS_Frame.RQ_PositionLamp = 1;     
                Lin_RLS_Frame.RQ_PositionLamp_Invers = 0; 
            }
            else
            {
                Light_on_cnt[TWILIGHT]++ ;
            }
        } 
        else if(u16_Brightness_FW > temp_light_off_th)
        {
            Light_on_cnt[TWILIGHT] = 0;
            if(Light_off_cnt[TWILIGHT] >= Light_Stastegy_Parameter[0].off_timer)
            {
                Lin_RLS_Frame.RQ_PositionLamp = 0;     
                Lin_RLS_Frame.RQ_PositionLamp_Invers = 1;  
            }
            else
            {
                Light_off_cnt[TWILIGHT]++ ;
            }
        }
        else
        {
            Light_off_cnt[TWILIGHT] = 0;
            Light_on_cnt[TWILIGHT] = 0;
        }
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Auto_Light_Task()
 *   DESCRIPTION : RLS_Auto_Light_Task function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Auto_Light_Task(void)
{
    uint32 avg_fw = 0, avg_ir = 0;
    uint8 i;
    
    for(i = 0; i < AVG_N; i++)
    {
        MLX75308_Meansure(PDC | PDD);
        avg_fw +=  MLX75308_RxFrame.data_field[0];
        avg_ir +=  MLX75308_RxFrame.data_field[1];
    }
    
    avg_fw = avg_fw / AVG_N;
    avg_ir = avg_ir / AVG_N;
    
    Mnrval.Amb_C = (uint16)(avg_fw);
    Mnrval.Amb_D = (uint16)(avg_ir);
    
    avg_ir = Search_Table(avg_ir,Tab_AWG_IR, Tab_Brightness_IR, 16);
    if(avg_ir > 250)         Lin_RLS_Frame.Brightness_IR = 250;
    else                     Lin_RLS_Frame.Brightness_IR = avg_ir;
    
    avg_fw = Search_Table(avg_fw,Tab_AWG_FW, Tab_Brightness_FW, 16);
    if(avg_fw > 1021)     
    {
        Lin_RLS_Frame.Brightness_FW_L = (uint8)1021;
        Lin_RLS_Frame.Brightness_FW_H = (uint8)(1021>>8);
    }
    else                 
    {
        Lin_RLS_Frame.Brightness_FW_L = (uint8)avg_fw;
        Lin_RLS_Frame.Brightness_FW_H = (uint8)(avg_fw>>8);
    }
    
    RLS_Light_Module_Fault_Process();
    RLS_AutoLightControl();                
}

/*******************************************************
 * FUNCTION NAME : RLS_Rain_Module_Fault_Process()
 *   DESCRIPTION : RLS_Rain_Module_Fault_Process function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Rain_Module_Fault_Process(uint8 PD_chan)
{
    if(PD_chan == PDA) 
    {
        if(u16_Pd_Measure_Value == 0) 
        {
            App_Rls_Error.RS_Error_Cnt[0]++;
            if(App_Rls_Error.RS_Error_Cnt[0] >= 50)   
            {
                App_Rls_Error.RS_Error_Cnt[0] = 50;
            }
        } 
        else 
        {
            App_Rls_Error.RS_Error_Cnt[0] = 0;
        }
    }
    
    if(PD_chan == PDB) 
    {
        if(u16_Pd_Measure_Value == 0) 
        {
            App_Rls_Error.RS_Error_Cnt[1]++;
            if(App_Rls_Error.RS_Error_Cnt[1] >= 50) 
            {
                App_Rls_Error.RS_Error_Cnt[1] = 50;
            }
        } 
        else 
        {
            App_Rls_Error.RS_Error_Cnt[1] = 0;
        }
    }
    
    if((App_Rls_Error.RS_Error_Cnt[0] == 50) || (App_Rls_Error.RS_Error_Cnt[1] == 50)) 
    {
        App_Rls_Error.RS_Error = 1;
    } 
    else if((App_Rls_Error.RS_Error_Cnt[0] == 0) && (App_Rls_Error.RS_Error_Cnt[1] == 0))
    {
        App_Rls_Error.RS_Error = 0;
    }
}




/*******************************************************
 * FUNCTION NAME : RLS_Get_Rain_State()
 *   DESCRIPTION : RLS_Get_Rain_State function 
 *         INPUT : PD_chan
 *        OUTPUT : Rain_State  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
uint8 RLS_Get_Rain_State(uint8 PD_chan)
{
    uint8 i; 
    uint16 temp;
    
    u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PD_chan,Rain_Stastegy_Parameter[0].meas_avg_cnt,600);
    
    RLS_Rain_Module_Fault_Process(PD_chan);
    
    
    if((PD_chan == PDA)&&(u16_Pd_Measure_Value!=0)) 
    {
        Mnrval.IR_A = u16_Pd_Measure_Value;
        
        DC_WIN_BUFF[CHAN_A][DC_WINDOW - 1] = Mnrval.DC_bre_A ;
        
        for(i = 1;i <= DC_WINDOW;i++)
        {
             DC_WIN_BUFF[CHAN_A][DC_WINDOW - 1] = Mnrval.DC_bre_A ;
            
            if(i < DC_WINDOW)
            {
                DC_WIN_BUFF[CHAN_A][i - 1] = DC_WIN_BUFF[CHAN_A][i];
               
            }
        }
        
        if( u8_RLS_StopMsureFlg == 0 )
        {
            for(i = 1;i <= PD_WINDOW;i++)
            {
                PD_WIN_AVG[CHAN_A][PD_WINDOW - 1] = Mnrval.IR_A ;
                if(i < PD_WINDOW)
                {
                     PD_WIN_AVG[CHAN_A][i - 1] = PD_WIN_AVG[CHAN_A][i];
                }
            }
            
        } 
        else
        {
           /* for(i = 0;i < PD_WINDOW;i++)
            {
                PD_WIN_AVG[CHAN_A][i] =  PD_Meas_Comp_Ref[CHAN_A];
            } */
        }
        
        if(Lin_BCM_Frame.ParkPosition == 1)
        { 
            PD_Meas_Comp_Ref[CHAN_A] =  PD_WIN_AVG[CHAN_A][0] ;
            if(Mnrval.DC_bre_A < Rain_Stastegy_Parameter[0].dc_stage1)
            {
                temp =  Rain_Stastegy_Parameter[0].stage_intensity1;
            }
            else if(Mnrval.DC_bre_A < Rain_Stastegy_Parameter[0].dc_stage2)
            {
                temp =   Rain_Stastegy_Parameter[0].stage_intensity2;
            }
            else if(Mnrval.DC_bre_A < Rain_Stastegy_Parameter[0].dc_stage3)
            {
                temp =   Rain_Stastegy_Parameter[0].stage_intensity3;
            }
            else if(Mnrval.DC_bre_A < Rain_Stastegy_Parameter[0].dc_stage4)
            {
                temp =   Rain_Stastegy_Parameter[0].stage_intensity4;
            }
            else
            {
                temp =   Rain_Stastegy_Parameter[0].stage_intensity5;
            }
        }
        else
        {
            temp =  Rain_Stastegy_Parameter[0].stage_intensity4;
        }
        
        u16_PDA_Wmax = PD_WIN_AVG[CHAN_A][0];                        //A通道最大值赋值
        if(Mnrval.IR_A >= u16_PDA_Wmax) 
        {                           //当前值大于前PD_WINDOW-1个采集值时，返回无雨量
            u8_PD_State[CHAN_A] = 0;
            if((Mnrval.IR_A - u16_PDA_Wmax) > DtABS_MAX) PD_WIN_AVG[CHAN_A][PD_WINDOW - 1] = PD_WIN_AVG[CHAN_A][PD_WINDOW - 2];
        }
        else
        {
            u16_Dt_PD[CHAN_A] = u16_PDA_Wmax - Mnrval.IR_A;
            if((u16_Dt_PD[CHAN_A] > DtABS_MAX)||(u16_Dt_PD[CHAN_A] < temp)) 
            {                  
              PD_WIN_AVG[CHAN_A][PD_WINDOW - 1] = PD_WIN_AVG[CHAN_A][PD_WINDOW - 2];
              u8_PD_State[CHAN_A] = 0;          
            }
            else 
            {
                u8_PD_State[CHAN_A] = (u16_Dt_PD[CHAN_A] / u8_Rain_Delta);
            }
        }

        
        PD_Meas_Comp_Ref_Pre[CHAN_A] =  PD_Meas_Comp_Ref[CHAN_A];
        
        return (u8_PD_State[CHAN_A]);
    }
    else if((PD_chan == PDB)&&(u16_Pd_Measure_Value!=0))
    {
        Mnrval.IR_B = u16_Pd_Measure_Value;
        
        DC_WIN_BUFF[CHAN_B][DC_WINDOW - 1] = Mnrval.DC_bre_B ;
        
        for(i = 1;i <= DC_WINDOW;i++)
        {
             DC_WIN_BUFF[CHAN_B][DC_WINDOW - 1] = Mnrval.DC_bre_B ;
            
            if(i < DC_WINDOW)
            {
                DC_WIN_BUFF[CHAN_B][i - 1] = DC_WIN_BUFF[CHAN_B][i];
               
            }
        }
        
        if(u8_RLS_StopMsureFlg == 0 )
        {
            for(i = 1;i <= PD_WINDOW;i++)
            {
                PD_WIN_AVG[CHAN_B][PD_WINDOW - 1] = Mnrval.IR_B ;
                if(i < PD_WINDOW)
                {
                     PD_WIN_AVG[CHAN_B][i - 1] = PD_WIN_AVG[CHAN_B][i];
                }
            }
            
        } 
        else
        {
            
            /*for(i = 0;i < PD_WINDOW;i++)
            {
                PD_WIN_AVG[CHAN_B][i] =  PD_Meas_Comp_Ref[CHAN_B];
            }*/
        }
        
        if(Lin_BCM_Frame.ParkPosition == 1)
        { 
            PD_Meas_Comp_Ref[CHAN_B] =  PD_WIN_AVG[CHAN_B][0] ;
            if(Mnrval.DC_bre_B <  Rain_Stastegy_Parameter[0].dc_stage1)
            {
                temp =  Rain_Stastegy_Parameter[0].stage_intensity1;
            }
            else if(Mnrval.DC_bre_B <  Rain_Stastegy_Parameter[0].dc_stage2)
            {
                temp =  Rain_Stastegy_Parameter[0].stage_intensity2;
            }
            else if(Mnrval.DC_bre_B <  Rain_Stastegy_Parameter[0].dc_stage3)
            {
                temp =  Rain_Stastegy_Parameter[0].stage_intensity3;
            }
            else if(Mnrval.DC_bre_B <  Rain_Stastegy_Parameter[0].dc_stage4)
            {
                temp =  Rain_Stastegy_Parameter[0].stage_intensity4;
            }
            else
            {
                temp =  Rain_Stastegy_Parameter[0].stage_intensity5;
            }
        }
        else
        {
            temp =  Rain_Stastegy_Parameter[0].stage_intensity4;
        }
        
         
        u16_PDB_Wmax = PD_WIN_AVG[CHAN_B][0];                        //A通道最大值赋值
        if(Mnrval.IR_B >= u16_PDB_Wmax) 
        {                           //当前值大于前PD_WINDOW-1个采集值时，返回无雨量
            u8_PD_State[CHAN_B] = 0;
            if((Mnrval.IR_B - u16_PDB_Wmax) > DtABS_MAX) PD_WIN_AVG[CHAN_B][PD_WINDOW - 1] = PD_WIN_AVG[CHAN_B][PD_WINDOW - 2];
        }
        else
        {
            u16_Dt_PD[CHAN_B] = u16_PDB_Wmax - Mnrval.IR_B;
            if((u16_Dt_PD[CHAN_B] > DtABS_MAX)||(u16_Dt_PD[CHAN_B] < temp)) 
            {                  
              PD_WIN_AVG[CHAN_B][PD_WINDOW - 1] = PD_WIN_AVG[CHAN_B][PD_WINDOW - 2];
              u8_PD_State[CHAN_B] = 0;          
            }
            else 
            {
                u8_PD_State[CHAN_B] = (u16_Dt_PD[CHAN_B] / u8_Rain_Delta);
            }
        }
        
        PD_Meas_Comp_Ref_Pre[CHAN_B] =  PD_Meas_Comp_Ref[CHAN_B];

        
        return (u8_PD_State[CHAN_B]);
    }
    else
    {
    	return 0 ;
    }
}


/*******************************************************
 * FUNCTION NAME : RLS_Get_Rain_ExpectStage()
 *   DESCRIPTION : RLS_Get_Rain_ExpectStage function 
 *         INPUT : PD_chan
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Get_Rain_ExpectStage(uint8 PD_chan)
{
    uint8  Rain_temp_A = 0, Rain_temp_B = 0;
    
    if((PD_chan & PDB) == PDB) 
    {
                        
        Rain_temp_B = RLS_Get_Rain_State(PDB);
        
        if(Rain_temp_B == 0)                              u8_RainIntensity[CHAN_B]  = 0;
        else if((Rain_temp_B >= 1)&&(Rain_temp_B <= 4))   u8_RainIntensity[CHAN_B]  = 1;
        else if((Rain_temp_B >= 5)&&(Rain_temp_B <= 7))   u8_RainIntensity[CHAN_B]  = 2;
        else if((Rain_temp_B >= 8)&&(Rain_temp_B <= 9))   u8_RainIntensity[CHAN_B]  = 3;
        else if((Rain_temp_B >= 10)&&(Rain_temp_B <= 11)) u8_RainIntensity[CHAN_B]  = 4;
        else if((Rain_temp_B >= 12)&&(Rain_temp_B <= 12)) u8_RainIntensity[CHAN_B]  = 5;
        else if((Rain_temp_B >= 13)&&(Rain_temp_B <= 13)) u8_RainIntensity[CHAN_B]  = 6;
        else if((Rain_temp_B >= 14)&&(Rain_temp_B <= 17)) u8_RainIntensity[CHAN_B]  = 7;
        else if((Rain_temp_B >= 18)&&(Rain_temp_B <= 18)) u8_RainIntensity[CHAN_B]  = 8;
        else if((Rain_temp_B >= 19)&&(Rain_temp_B <= 19)) u8_RainIntensity[CHAN_B]  = 9;
        else if((Rain_temp_B >= 20)&&(Rain_temp_B <= 35)) u8_RainIntensity[CHAN_B]  = 10;
        else                                              u8_RainIntensity[CHAN_B]  = 11;

        u8_RainIntensityPre[CHAN_B] = u8_RainIntensity[CHAN_B];
    }
           
    if((PD_chan & PDA) == PDA)
    {

        Rain_temp_A = RLS_Get_Rain_State(PDA);    
        
        if(Rain_temp_A == 0)                              u8_RainIntensity[CHAN_A]  = 0;
        else if((Rain_temp_A >= 1)&&(Rain_temp_A <= 4))   u8_RainIntensity[CHAN_A]  = 1;
        else if((Rain_temp_A >= 5)&&(Rain_temp_A <= 7))   u8_RainIntensity[CHAN_A]  = 2;
        else if((Rain_temp_A >= 8)&&(Rain_temp_A <= 9))   u8_RainIntensity[CHAN_A]  = 3;
        else if((Rain_temp_A >= 10)&&(Rain_temp_A <= 11)) u8_RainIntensity[CHAN_A]  = 4;
        else if((Rain_temp_A >= 12)&&(Rain_temp_A <= 12)) u8_RainIntensity[CHAN_A]  = 5;
        else if((Rain_temp_A >= 13)&&(Rain_temp_A <= 13)) u8_RainIntensity[CHAN_A]  = 6;
        else if((Rain_temp_A >= 14)&&(Rain_temp_A <= 17)) u8_RainIntensity[CHAN_A]  = 7;
        else if((Rain_temp_A >= 18)&&(Rain_temp_A <= 18)) u8_RainIntensity[CHAN_A]  = 8;
        else if((Rain_temp_A >= 19)&&(Rain_temp_A <= 19)) u8_RainIntensity[CHAN_A]  = 9;
        else if((Rain_temp_A >= 20)&&(Rain_temp_A <= 35)) u8_RainIntensity[CHAN_A]  = 10;
        else                                              u8_RainIntensity[CHAN_A]  = 11;


        u8_RainIntensityPre[CHAN_A] = u8_RainIntensity[CHAN_A];
    }   
} 

/*******************************************************
 * FUNCTION NAME : RLS_Mask_False_Operation()
 *   DESCRIPTION : RLS_Mask_False_Operation function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Mask_False_Operation(void)
{
    uint8 i;
    if(Mnrval.DC_bre_A > Mnrval.DC_aft_A) 
        u16_DC_PD_dt[CHAN_A] =  Mnrval.DC_bre_A  - Mnrval.DC_aft_A; 
    
    else                                  
        u16_DC_PD_dt[CHAN_A] =  Mnrval.DC_aft_A  - Mnrval.DC_bre_A;
    
    if(Mnrval.DC_bre_B > Mnrval.DC_aft_B) 
        u16_DC_PD_dt[CHAN_B] =  Mnrval.DC_bre_B  - Mnrval.DC_aft_B; 
    
    else                                  
        u16_DC_PD_dt[CHAN_B] =  Mnrval.DC_aft_B  - Mnrval.DC_bre_B;
    
    if((u16_Delta_DC_bre_A > DC_bef_dtTH) || (u16_Delta_DC_aft_A > DC_aft_dtTH)\
        ||(u16_Delta_DC_bre_B > DC_bef_dtTH) || (u16_Delta_DC_aft_B > DC_aft_dtTH))
    {
        u8_Rain_Valid = 0;
    }
    else
    {
        u8_Rain_Valid = 1;
    }
    
    for(i = 0;i < DC_WINDOW;i++)  //  CHAN_A
    {
        if(DC_WIN_BUFF[CHAN_A][0] > DC_WIN_BUFF[CHAN_A][i])
        {
            if((DC_WIN_BUFF[CHAN_A][0] - DC_WIN_BUFF[CHAN_A][i]) >  DC_CHANGE_TH)
            {
                u8_Rain_Valid = 0;
            }
        }
        else
        {
            if((DC_WIN_BUFF[CHAN_A][i] - DC_WIN_BUFF[CHAN_A][0]) >  DC_CHANGE_TH)
            {
                u8_Rain_Valid = 0;
            }
        }
    }
    
    for(i = 0;i < DC_WINDOW  ;i++)  //  CHAN_B
    {
        if(DC_WIN_BUFF[CHAN_B][0] > DC_WIN_BUFF[CHAN_B][i])
        {
            if((DC_WIN_BUFF[CHAN_B][0] - DC_WIN_BUFF[CHAN_B][i]) >  DC_CHANGE_TH)
            {
                u8_Rain_Valid = 0;
            }
        }
        else
        {
            if((DC_WIN_BUFF[CHAN_B][i] - DC_WIN_BUFF[CHAN_B][0]) >  DC_CHANGE_TH)
            {
                u8_Rain_Valid = 0;
            }
        }
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Invalid_DataProcess()
 *   DESCRIPTION : RLS_Invalid_DataProcess function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Invalid_DataProcess(void)
{
    uint8 i;
    if(u8_Rain_Valid == 1)
    {
        u8_Rain_Value = u8_RainIntensity_Win[0];
        
        for(i = 0;i < (Rain_WINDOW - 1) ;i ++) 
        {
            u8_RainIntensity_Win[i] = u8_RainIntensity_Win[i + 1];
        }  

        if(u8_RainIntensity[CHAN_B] > u8_RainIntensity[CHAN_A]) 
            u8_RainIntensity_Win[Rain_WINDOW - 1] = u8_RainIntensity[CHAN_B];
        else  
            u8_RainIntensity_Win[Rain_WINDOW - 1] = u8_RainIntensity[CHAN_A];
        
        if(u8_Cmd_Execution == 0) 
        {
            if(u8_Rain_Value < 5)
            {
                u8_WiperSpeed_Expert = u8_Rain_Value;
            }
            else
            {
                switch(u8_Rain_Value)
                {
                    case 5:
                    case 6: 
                    case 7:
                        u8_WiperSpeed_Expert   = 5;                     
                    case 8:
                    case 9: 
                        u8_WiperSpeed_Expert   = 6;
                    break;
                    
                    case 10:
                        u8_WiperSpeed_Expert   = 6;
                    break;                    
                    default: 
                        u8_WiperSpeed_Expert   = 6;
                    break;
                }
            }
            
            u8_RainIntensity_Max = u8_Rain_Value; 
            u8_Cmd_Execution = 1;
        
        }
        else if(u8_Rain_Value > u8_RainIntensity_Max)
        {
            if(u8_Rain_Value < 5)
            {
                u8_WiperSpeed_Expert = u8_Rain_Value;
            }
            else
            {
                switch(u8_Rain_Value)
                {
                    case 5:
                    case 6: 
                    case 7:
                        u8_WiperSpeed_Expert   = 5;                     
                    case 8:
                    case 9: 
                        u8_WiperSpeed_Expert   = 6;
                    break;
                    
                    case 10:
                        u8_WiperSpeed_Expert   = 6;
                    break;                    
                    default: 
                        u8_WiperSpeed_Expert   = 6;
                    break;
                }
            }
            u8_RainIntensity_Max = u8_Rain_Value;
        }
    }
    else
    {
        for(i = 0;i < (PD_WINDOW - 1); i++) 
        {                   
            //将窗口中的历史数据全部刷成当前采集值
            PD_WIN_AVG[CHAN_A][i] = PD_WIN_AVG[CHAN_A][PD_WINDOW - 1];
            PD_WIN_AVG[CHAN_B][i] = PD_WIN_AVG[CHAN_B][PD_WINDOW - 1];
        }

        u8_Cmd_Execution = 0;
        u8_RainIntensity_Max = 0;
        
        for(i = 0;i < Rain_WINDOW ;i++) 
        {
            u8_RainIntensity_Win[i] = 0;
            if(u8_Rain_Invalid_Cnt >= RAIN_INVALID_NUM) 
            {
                u8_Rain_Invalid_Cnt = 0;

                if(u8_WiperSpeed_Expert >= 2)
                {
                    u8_WiperSpeed_Expert = u8_WiperSpeed_Expert - 2;      
                }
                else if(u8_WiperSpeed_Expert > 0) //当雨量数据无效时，将雨刮速度降低一级，直至降到0
                {
                    u8_WiperSpeed_Expert--;
                }        
            } 
            else 
            {
                u8_Rain_Invalid_Cnt ++;        
            }
        }
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Period_Mode(uint8 Int_Timer, uint8 Wiper_Timer)
 *   DESCRIPTION : RLS_Period_Mode function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
uint8 RLS_Period_Mode(uint8 Int_Timer, uint8 Wiper_Timer)
{
	if((Wiper_Timer >= 0) && (Wiper_Timer < (Int_Timer - 7)))
	{
		Lin_RLS_Frame.RQ_WiperSPD = 0;
	}
	else if((Wiper_Timer >= (Int_Timer - 7)) && (Wiper_Timer <= Int_Timer))
	{
		Lin_RLS_Frame.RQ_WiperSPD = 1;
	}
	
	if(Wiper_Timer >= (Int_Timer - 1))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

/*******************************************************
 * FUNCTION NAME : RLS_Invalid_DataProcess()
 *   DESCRIPTION : RLS_Rain_State_Mchaine function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Rain_State_Mchaine(void)
{
    uint8  u8_Delaytimer,i,u8_rain_state_th,u8_rain_cnt;
    uint16 temp_rain_value;
    uint8  temp,tempcnt;
    uint8  temp_period_low_th;
    uint8  temp_period_low_cnt;
    uint8  u8_temp_rcv;
    
    switch(u8_Wiper_State)
    {
        case PARK_MODE:
        {
            if(u8_Rain_Sensitivity == 1)
            {
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer ;
            }
            else if(u8_Rain_Sensitivity == 2)
            {
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer ;
            }
            else if(u8_Rain_Sensitivity == 3)
            {
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer + 10;
            }            
            else if(u8_Rain_Sensitivity == 4)
            {
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer + 10; 
            }
            else
            {
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer + 10;
            }
                       
            
            if(u8_Wiper_StatePre != PARK_MODE)
            {
                u8_Wiper_StatePre_Int  = 1;
            }
            
            if(u8_Wiper_StatePre_Int  == 1)
            {
                Lin_RLS_Frame.RQ_WiperSPD = 0;
                
                for(i = 0;i < (PD_WINDOW - 1); i++) 
                {                   
                    //将窗口中的历史数据全部刷成当前采集值
                    PD_WIN_AVG[CHAN_A][i] = Mnrval.IR_A ;//PD_WIN_AVG[CHAN_A][0];
                    PD_WIN_AVG[CHAN_B][i] = Mnrval.IR_B ;//PD_WIN_AVG[CHAN_B][0];
                } 
                
                for(i = 0;i < Rain_WINDOW ;i++) 
                {
                    u8_RainIntensity_Win[i] = 0;
                }
                u8_WiperSpeed_Expert = 0;
                
                if(u8_Wiper_StatePre_Int_Cnt >= 10)//1s
                {                    
                    u8_Wiper_StatePre_Int_Cnt = 0;
                    u8_Wiper_StatePre_Int = 0;
                }
                else
                {
                    u8_Wiper_StatePre_Int_Cnt++;
                }    
            }
            
            if(u8_ClearEnternIntSpeedCnt >= u8_Delaytimer) 
            {
                u8_ClearEnternIntSpeedCnt = 0;
                u8_IntSpeedEnterCnt = 0;
            }
            else
            {
                u8_ClearEnternIntSpeedCnt++;
            }
            
            Lin_RLS_Frame.RQ_WiperSPD = 0;
            u8_IntDelayTimer = 0;
            u8_EnterLowSpeedCnt = 0; 
            
            
            if(u8_WiperSpeed_Expert != 0)
            {
                u8_ClearEnternIntSpeedCnt = 0;
                u8_Wiper_State = INT_SPEED_MODE;
                u8_IntSpeedCnt = 0;
                if(u8_Rain_Sensitivity == 4)
                {
                    temp =  Rain_Stastegy_Parameter[0].park_enter_low_th + 1;
                    tempcnt = 1;
                }
                else if(u8_Rain_Sensitivity == 3)
                {
                    temp =  Rain_Stastegy_Parameter[0].park_enter_low_th + 4;
                    tempcnt = 2;
                }
                else if(u8_Rain_Sensitivity == 2)
                {
                    temp =  Rain_Stastegy_Parameter[0].park_enter_low_th + 4;
                    tempcnt = 2;
                }
                else if(u8_Rain_Sensitivity == 1)
                {
                    temp =  Rain_Stastegy_Parameter[0].park_enter_low_th + 4;
                    tempcnt = 3;
                }
                else
                {
                    temp =  Rain_Stastegy_Parameter[0].park_enter_low_th + 4 ;
                    tempcnt = 1;
                }
                
                if((u8_WiperSpeed_Expert >= temp + 1)&&(u8_IntSpeedEnterCnt >= tempcnt + 2))
                {
                    u8_Wiper_State = LOW_SPEED_MODE;
                	u8_low_enter_high_timer = 0;
                }
                
                if((u8_Rain_Value >= (Rain_Stastegy_Parameter[0].park_enter_high_th))&&(u8_IntSpeedEnterCnt >= tempcnt)) 
                {
                    u8_Wiper_State = HIGH_SPEED_MODE;
                }
            }
            else
            {  
            
            }
            u8_Wiper_StatePre = PARK_MODE;
            
        } break;
        
        case INT_DELAY_MODE:
        {
            u8_IntSpeedEnterCnt = 0;
            u8_ClearEnternIntSpeedCnt = 0;
            u8_LowSpeedCnt = 0;
            u8_HighHoldCnt = 0; 
            
            u8_IntDelayTimer++;
            
            if((u8_IntDelayTimer >= 0)&&(u8_IntDelayTimer < Rain_Stastegy_Parameter[0].int_delay_timer))
            {
                Lin_RLS_Frame.RQ_WiperSPD = 0;
            }
            
            else if((u8_IntDelayTimer >= Rain_Stastegy_Parameter[0].int_delay_timer)&&(u8_IntDelayTimer < (Rain_Stastegy_Parameter[0].int_delay_timer + 5))) 
            {
                Lin_RLS_Frame.RQ_WiperSPD = 1;
            }
            
            else if((u8_IntDelayTimer >= 35)&&(u8_IntDelayTimer < 65)) 
            {
                Lin_RLS_Frame.RQ_WiperSPD = 0;
            }
            
            else if((u8_IntDelayTimer >= 65)&&(u8_IntDelayTimer < 70)) 
            {
                Lin_RLS_Frame.RQ_WiperSPD = 1;
            }
            
            else if((u8_IntDelayTimer >= 70)&&(u8_IntDelayTimer < 100)) 
            {
            	Lin_RLS_Frame.RQ_WiperSPD = 0;
            }
            
            else if((u8_IntDelayTimer >= 100)&&(u8_IntDelayTimer < 105)) 
            {
            	Lin_RLS_Frame.RQ_WiperSPD = 1;
            }
            else
            {
                Lin_RLS_Frame.RQ_WiperSPD = 0;
                u8_Wiper_State = PARK_MODE;
            }

            u8_Wiper_StatePre = INT_DELAY_MODE;
        } break;
        
        case INT_SPEED_MODE:
        {
        	u8_low_enter_high_timer = 0;
            u8_IntDelayTimer = 0;
            u8_HighHoldCnt = 0;   
            u8_ExitLowSpeedCnt = 0;
            Lin_RLS_Frame.RQ_WiperSPD = 1;
            u8_IntSpeedCnt++;
                                          
            if(u8_IntSpeedCnt >= 5)
            {
                Lin_RLS_Frame.RQ_WiperSPD = 0;
                u8_Wiper_State = PARK_MODE;
                u8_IntSpeedEnterCnt++;
            } 
            
            if(u8_Rain_Sensitivity == 4)
            {
                if(u8_WiperSpeed_Expert > 4)
                {
                    u8_LowSpeedCnt++;
                    
                    if(u8_LowSpeedCnt > Rain_Stastegy_Parameter[0].int_enter_low_cnt)
                    {
                        u8_LowSpeedCnt = 0;
                        u8_Wiper_State = LOW_SPEED_MODE; 
                    }
                }
                
                if(u8_IntSpeedEnterCnt >= Rain_Stastegy_Parameter[0].int_enter_period_cnt)
                {
                    u8_IntSpeedEnterCnt = 0;
                    u8_Wiper_State = PERIOD_SPEED_MODE;
                    u8_IntDelayTimer = 0;
                }
            }
            else if(u8_Rain_Sensitivity == 3)
            {
                if(u8_WiperSpeed_Expert > 4)
                {
                    u8_LowSpeedCnt++;
                    
                    if(u8_LowSpeedCnt > Rain_Stastegy_Parameter[0].int_enter_low_cnt)
                    {
                        u8_LowSpeedCnt = 0;
                        u8_Wiper_State = LOW_SPEED_MODE; 
                    }
                }
                
                if(u8_IntSpeedEnterCnt >= Rain_Stastegy_Parameter[0].int_enter_period_cnt)
                {
                    u8_IntSpeedEnterCnt = 0;
                    u8_Wiper_State = PERIOD_SPEED_MODE;
                    u8_IntDelayTimer = 0;
                }
            }
            else if (u8_Rain_Sensitivity == 2 ) 
            {
                
                if(u8_WiperSpeed_Expert > 4)
                {
                    u8_LowSpeedCnt++;
                    
                    if(u8_LowSpeedCnt > Rain_Stastegy_Parameter[0].int_enter_low_cnt)
                    {
                        u8_LowSpeedCnt = 0;
                        u8_Wiper_State = LOW_SPEED_MODE; 
                    }
                }
                
                if(u8_IntSpeedEnterCnt >= Rain_Stastegy_Parameter[0].int_enter_period_cnt)
                {
                    u8_IntSpeedEnterCnt = 0;
                    u8_Wiper_State = PERIOD_SPEED_MODE;
                    u8_IntDelayTimer = 0;
                }
            }
            else
            {
                if(u8_WiperSpeed_Expert > 4)
                {
                    u8_LowSpeedCnt++;
                    
                    if(u8_LowSpeedCnt > Rain_Stastegy_Parameter[0].int_enter_low_cnt)
                    {
                        u8_LowSpeedCnt = 0;
                        u8_Wiper_State = LOW_SPEED_MODE; 
                    }
                }
                
                if(u8_IntSpeedEnterCnt >= (Rain_Stastegy_Parameter[0].int_enter_period_cnt + 1))
                {
                    u8_IntSpeedEnterCnt = 0;
                    u8_Wiper_State = PERIOD_SPEED_MODE;
                    u8_IntDelayTimer = 0;
                }
            }
            
            u8_Wiper_StatePre = INT_SPEED_MODE;
        } break;
        
        case PERIOD_SPEED_MODE:
        {
            u8_LowSpeedCnt = 0;
            u8_HighHoldCnt = 0;
            u8_IntSpeedEnterCnt = 0;
            u8_ExitLowSpeedCnt = 0; 
            u8_low_enter_high_timer = 0;
        	u8_IntDelayTimer++;
        	
            
            //速度选择次数
        	if(u8_SPD_Vehicle >= 0 && u8_SPD_Vehicle < 5)
        	{
        		u8_cnt_choose = 4;
        	}
        	else if(u8_SPD_Vehicle >= 5 && u8_SPD_Vehicle < 80)
        	{
        		u8_cnt_choose = 5;
        	}
        	else if(u8_SPD_Vehicle >= 80 && u8_SPD_Vehicle < 120)
        	{
        		u8_cnt_choose = 6;
        	}
        	else 
        	{
        		u8_cnt_choose = 4;
        	}
        	          
            //灵敏度选择时间间隔
        	if(u8_Rain_Sensitivity == 4)
        	{
        		u8_Int_Time = 17;
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt;
        	}
        	else if(u8_Rain_Sensitivity == 3)
        	{
        		u8_Int_Time = 20;
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt + 2;
        	}
        	else if(u8_Rain_Sensitivity == 2)
        	{
        		u8_Int_Time = 24;
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt + 6;
        	}
        	else 
        	{
        		u8_Int_Time = 30;
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt + 8;
        	}
        	
           	//一个周期为单位 清零
			if(u8_Int_Time_pre <= u8_IntDelayTimer)
			{
				u8_IntDelayTimer = 0;
			}
        	
        	if(u8_cnt_choose_pre)
        	{
        		u8_temp_rcv = RLS_Period_Mode(u8_Int_Time_pre, u8_IntDelayTimer);
        		u8_Wiper_State = PERIOD_SPEED_MODE;
        	}
        	else 
        	{
        		u8_cnt_choose_pre = u8_cnt_choose;
        		u8_Int_Time_pre   = u8_Int_Time;
        	}
        	
        	if(u8_temp_rcv)
        	{
        		u8_cnt_choose_pre--;
        		if(u8_cnt_choose_pre == 0)
        		{
            		Lin_RLS_Frame.RQ_WiperSPD = 0;
            		u8_cnt_choose_pre = 0;
            		u8_Int_Time_pre = 0;
            		u8_Wiper_State = PARK_MODE;
        		}
        	}
        	else
        	{
        		//if(u8_WiperSpeed_Expert > 0 && u8_WiperSpeed_Expert <= 2)
        		if(u8_WiperSpeed_Expert == 2)
        		{
        			if(u8_SPD_Vehicle >= 5)
        			{
						u8_cnt_choose_pre = u8_cnt_choose;
						u8_Int_Time_pre   = u8_Int_Time;
        			}
        			else 
        			{
        				u8_Int_Time_pre   = u8_Int_Time;
        			}
        		}
        		u8_Wiper_State = PERIOD_SPEED_MODE;
        	}
          
            
            if(u8_WiperSpeed_Expert >= temp_period_low_th)
            {
                u8_EnterLowSpeedCnt++;
                if(u8_EnterLowSpeedCnt >= temp_period_low_cnt)
                {
                    u8_IntDelayTimer = 0;
                    u8_EnterLowSpeedCnt = 0;                    
                    
                    if(u8_SPD_Vehicle > 5)
                    {
                    	u8_Wiper_State = LOW_SPEED_MODE;
                    }
                    else 
                    {
                    	u8_Wiper_State = PERIOD_SPEED_MODE;
                    }
                }
            }
            u8_Wiper_StatePre = PERIOD_SPEED_MODE;  
        } break;
        
        case LOW_SPEED_MODE:
        {
            u8_IntSpeedCnt = 0;
            u8_IntDelayTimer = 0;
            u8_IntSpeedEnterCnt = 0;
            u8_HighSpeedHoldCnt = 0;
            Lin_RLS_Frame.RQ_WiperSPD = 3;
            
            if(u8_low_enter_high_timer >= 100)
			{
				u8_low_enter_high_timer = 0;
				u8_HighHoldCnt = 0;
			}
			else
			{
				u8_low_enter_high_timer++;
			}
            if(u8_Rain_Sensitivity == 4)
            {
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer41;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt41;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer42;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt42;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer43;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt43;
                }
                
                if(u8_WiperSpeed_Expert <= 3)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer) 
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  INT_DELAY_MODE;
                    }
                    else
                    {
                        u8_ExitLowSpeedCnt++;
                    }

                    if(u8_WiperSpeed_Expert >= 2)
                    {
                        u8_ExitLowSpeedCnt = 0;
                    }
                }
                else if(u8_WiperSpeed_Expert >= 5)
                {   
                    u8_HighHoldCnt++;
                    u8_ExitLowSpeedCnt = 0;
                    
                    if(u8_HighHoldCnt >= u8_rain_cnt)   
                    {                
                       u8_HighHoldCnt = 0;
                       u8_Wiper_State =  HIGH_SPEED_MODE;               
                    } 
                } 
            }
            else if(u8_Rain_Sensitivity == 3)
            {   
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer31;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt31;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer32;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt32;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer33;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt33;
                }
                 
                if(u8_WiperSpeed_Expert <= 3)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer) 
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  INT_DELAY_MODE;
                    }
                    else
                    {
                        u8_ExitLowSpeedCnt++;
                    }

                    if(u8_WiperSpeed_Expert >= 2)
                    {
                        u8_ExitLowSpeedCnt = 0;
                    }
                }
                else if(u8_WiperSpeed_Expert >= 5)
                {   
                    u8_HighHoldCnt++;
                    u8_ExitLowSpeedCnt = 0;
                    
                    if(u8_HighHoldCnt >= u8_rain_cnt)   
                    {                
                       u8_HighHoldCnt = 0;
                       u8_Wiper_State =  HIGH_SPEED_MODE;               
                    } 
                } 
            }
            else if(u8_Rain_Sensitivity == 2)
            {   
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer21;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt21;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer22;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt22;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer23;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt23;
                }
                
                if(u8_WiperSpeed_Expert <= 3)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer) //6s
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  INT_DELAY_MODE;
                    }
                    else
                    {
                        u8_ExitLowSpeedCnt++;
                    }

                    if(u8_WiperSpeed_Expert >= 2)
                    {
                        u8_ExitLowSpeedCnt = 0;
                    }
                }
                else if(u8_WiperSpeed_Expert >= 5)
                {   
                    u8_HighHoldCnt++;
                    u8_ExitLowSpeedCnt = 0;
                    
                    if(u8_HighHoldCnt >= u8_rain_cnt)   
                    {                
                       u8_HighHoldCnt = 0;
                       u8_Wiper_State =  HIGH_SPEED_MODE;               
                    } 
                } 
            }
            else
            {
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer11;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt11;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer12;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt12;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer13;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt13;
                }
                
                if(u8_WiperSpeed_Expert <= 3)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer)
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  INT_DELAY_MODE;
                    }
                    else
                    {
                        u8_ExitLowSpeedCnt++;
                    }
                    
                    if(u8_WiperSpeed_Expert >= 2)
                    {
                        u8_ExitLowSpeedCnt = 0;
                    }
                    
                }
                else if(u8_WiperSpeed_Expert >= 5)
                {   
                    u8_HighHoldCnt++;
                    u8_ExitLowSpeedCnt = 0;
                    
                    if(u8_HighHoldCnt >= u8_rain_cnt)   
                    {                
                        u8_HighHoldCnt = 0;
                        u8_Wiper_State =  HIGH_SPEED_MODE;               
                    } 
                }
            }
          
            u8_Wiper_StatePre =  u8_Wiper_State;
        } break;
        
        case HIGH_SPEED_MODE:
        {
            Lin_RLS_Frame.RQ_WiperSPD  = 6;
        	u8_low_enter_high_timer = 0;
            if(u8_Rain_Sensitivity == 4)
            {
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer41;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th41;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer42;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th42;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer43;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th43;    
                }
            }
            else if(u8_Rain_Sensitivity == 3)
            {
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer31;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th31;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer32;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th32;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer33;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th33;    
                }
            }
            else if(u8_Rain_Sensitivity == 2)
            {
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer21;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th21;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer22;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th22;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer23;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th23;    
                }
            }
            else
            {
                if(u8_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer11;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th11;
                }
                else if(u8_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer12;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th12;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer13;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th13;    
                }
            }           
          
            u8_ExitLowSpeedCnt = 0;
            u8_HighHoldCnt = 0;
            u8_HighSpeedHoldCnt++;
            
            if(u8_HighSpeedHoldCnt >= u8_Delaytimer)
            {             
                u8_Wiper_State = LOW_SPEED_MODE;
                u8_HighSpeedHoldCnt = 0;                     
            }
            else
            {
                if(u8_WiperSpeed_Expert >= u8_rain_state_th) 
                {
                    Lin_RLS_Frame.RQ_WiperSPD = 6;
                    u8_HighSpeedHoldCnt = 0;
                }
            }
            
            u8_Wiper_StatePre = u8_Wiper_State;
        } break;
        
        default:  
            u8_Wiper_State = PARK_MODE; 
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Wipe_Park_Process()
 *   DESCRIPTION : RLS_Wipe_Park_Process function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Wipe_Park_Process(void)
{
    if(Lin_BCM_Frame.ParkPosition == 0)   //1为park点
    {
        u8_MeasureSureTime++;
        if(u8_Wiper_State == HIGH_SPEED_MODE)
        {            
            if((u8_MeasureSureTime <= Rain_Stastegy_Parameter[0].park_high_meas_timer1)||((u8_MeasureSureTime >= Rain_Stastegy_Parameter[0].park_high_meas_timer2)))
            {
                u8_RLS_StopMsureFlg = 0;
            }
            else
            {
                u8_RLS_StopMsureFlg = 1;
            }
        }
        else
        {
            if((u8_MeasureSureTime <= Rain_Stastegy_Parameter[0].park_low_meas_timer1)||((u8_MeasureSureTime >= Rain_Stastegy_Parameter[0].park_low_meas_timer2)))
            {
                u8_RLS_StopMsureFlg = 0;
            }
            else
            {
                u8_RLS_StopMsureFlg = 1;
            }
        }
    }
    else
    {
        u8_RLS_StopMsureFlg = 0;
        u8_MeasureSureTime = 0;
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Auto_Rain_Task()
 *   DESCRIPTION : RLS_Auto_Rain_Task function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/                      
void RLS_Auto_Rain_Task(void)
{
    RLS_Get_Rain_ExpectStage(PDB|PDA);
    RLS_Mask_False_Operation();
    RLS_Invalid_DataProcess(); 
    RLS_Rain_State_Mchaine();   
}

/*******************************************************
 * FUNCTION NAME : RLS_SelfAdaptTask()
 *   DESCRIPTION : RLS_SelfAdaptTask function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/       
void RLS_SelfAdaptTask(void)
{
    uint8   i;
    uint16  temp_data[2] ;

   /* add intia*/

    Lin_RLS_Frame.RQ_WiperSPD     = 0;
    Lin_RLS_Frame.RQ_LowBeam      = 0;
    Lin_RLS_Frame.RQ_PositionLamp = 0;
/******************Chanl A*********************/   
    for(i = 0; i < 20; i++)
    {
        u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDA, 1, 600);
        if(0 != u16_Pd_Measure_Value) 
            break;
    }

    if(u16_Pd_Measure_Value < CALI_PARAM_LOW)
    {
        for(i = 0; i < 254; i++)
        {
            MLX75308_A_Adc = MLX75308_A_Adc + 1;
                                                           
            MLX75308_SetPara(DACA, MLX75308_A_Adc);
            Delay_Ms(5);
            u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDA,ADAPT_MEAS_CNT, 600);
             
            if(((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH)) || (MLX75308_A_Adc >=ADAPT_VALUE_DAC_HIGH)) 
                break;
        }
        
        if(MLX75308_A_Adc >= ADAPT_VALUE_DAC_HIGH)    
            MLX75308_A_Adc = ADAPT_VALUE_DAC_HIGH;
    
        MLX75308_SetPara(DACA, MLX75308_A_Adc);
    }
    
    else if(u16_Pd_Measure_Value > CALI_PARAM_HIGH)
    {
        for(i = 0;i < 254;i++)
        {
            MLX75308_A_Adc = MLX75308_A_Adc - 1;
            MLX75308_SetPara(DACA, MLX75308_A_Adc);
            Delay_Ms(5);
            u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDA,ADAPT_MEAS_CNT, 600);
             
            if(((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH)) || (MLX75308_A_Adc <= ADAPT_VALUE_DAC_LOW))  
                break;
        }
        
        if(MLX75308_A_Adc <= ADAPT_VALUE_DAC_LOW)   
            MLX75308_A_Adc = ADAPT_VALUE_DAC_LOW;
        
        MLX75308_SetPara(DACA, MLX75308_A_Adc);
    }
    
    u16_Ref_Adc_A = u16_Pd_Measure_Value;
    
    for(i = 0;i < PD_WINDOW;i++) 
    {                   
        //将最新的数据压入滑动窗口             
        PD_WIN_AVG[CHAN_A][i] = u16_Pd_Measure_Value;            
    }
    
    temp_data[0] = MLX75308_A_Adc;
    HCS12_EE_Write_2Word(EEPROM_A_DAC_ADDR, temp_data);

/******************Chanl B*********************/ 
   
    for(i = 0 ;i < 20;i++)
    {
        u16_Pd_Measure_Value =  RLS_Rain_Get_Measure(PDB, 1, 600);
        if(0 != u16_Pd_Measure_Value) 
            break;
    }
      
    if(u16_Pd_Measure_Value < CALI_PARAM_LOW)
    {
        for(i = 0;i < 254;i++)
        {
            MLX75308_B_Adc = MLX75308_B_Adc + 1;
            MLX75308_SetPara(DACB, MLX75308_B_Adc);
            Delay_Ms(5);
            u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDB,ADAPT_MEAS_CNT,600);
             
            if(((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH)) || (MLX75308_B_Adc >= ADAPT_VALUE_DAC_HIGH)) 
                break;         
        }
        
        if(MLX75308_B_Adc >= ADAPT_VALUE_DAC_HIGH)  
            MLX75308_B_Adc = ADAPT_VALUE_DAC_HIGH;                                     
        
        MLX75308_SetPara(DACB, MLX75308_B_Adc);
    }
    
    else if(u16_Pd_Measure_Value > CALI_PARAM_HIGH)
    {
        for(i = 0;i < 254;i++)
        {
            MLX75308_B_Adc  = MLX75308_B_Adc - 1;
            MLX75308_SetPara(DACB, MLX75308_B_Adc);
            Delay_Ms(5);
            u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDB,ADAPT_MEAS_CNT,600);
             
            if(((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH)) || (MLX75308_B_Adc <= ADAPT_VALUE_DAC_LOW)) 
                break;
        }
        
        if(MLX75308_B_Adc <= ADAPT_VALUE_DAC_LOW)  
            MLX75308_B_Adc = ADAPT_VALUE_DAC_LOW;
        
        MLX75308_SetPara(DACB, MLX75308_B_Adc);
    }
       
    u16_Ref_Adc_B = u16_Pd_Measure_Value ;
    
    for(i = 0;i < PD_WINDOW;i++) 
    {   
        //将最新的数据压入滑动窗口             
        PD_WIN_AVG[CHAN_B][i] = u16_Pd_Measure_Value;            
    }
    
    temp_data[0] = MLX75308_B_Adc;
    HCS12_EE_Write_2Word(EEPROM_B_DAC_ADDR, temp_data);
   
/*********MODE CHANGE TO NORMAL*******************/
    for(i = 0;i < Rain_WINDOW ;i ++) 
    {
        u8_RainIntensity_Win[i] = 0;
    }
/******************watch dog init******************************/
    COP_Init();
/****************************************************/
    RLS_RunMode = NORMAL;
    u8_IntSpeedEnterCnt = 0;
    u8_LowSpeedCnt = 0;
      
}

/*******************************************************
 * FUNCTION NAME : RLS_Wipe_Auto_On_Function()
 *   DESCRIPTION : RLS_Wipe_Auto_On_Function  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/  
void RLS_Wipe_Auto_On_Function(void)
{
    uint8 i;
    
    if((Lin_BCM_Frame.Status_IGN == 1))
    {
        for(i = 0; i < Rain_WINDOW; ++i) 
        {
            u8_RainIntensity_Win[i] = 0;
        }
        
        u8_Rain_Value = 0x0E;
        Lin_RLS_Frame.RQ_WiperSPD = 0;
    }
    
    if((u8_Wipe_Automatic_On_Pre == 0)&&(Lin_BCM_Frame.CMD_AutoWiper == 1))
    {
        u8_Wipe_Automatic_On_Flg = 1;
    } 
    
    u8_Wipe_Automatic_On_Pre = Lin_BCM_Frame.CMD_AutoWiper;  
    
    if(u8_Wipe_Automatic_On_Flg == 1)
    {
        Lin_RLS_Frame.RQ_WiperSPD = 1;
        u8_IntSpeedEnterCnt = 0;
        u8_Automatic_On_Cnt++;
        
        if(u8_Automatic_On_Cnt > 5)
        {
            u8_Automatic_On_Cnt = 0;
            u8_Wipe_Automatic_On_Flg = 0;
            Lin_RLS_Frame.RQ_WiperSPD = 0;
        }

        for(i = 0;i < Rain_WINDOW ;i ++) 
        {
            u8_RainIntensity_Win[i] = 0;
        }
        u8_Wiper_StatePre = INT_SPEED_MODE;
        u8_Wiper_State = PARK_MODE;
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Wipe_Sensitivity_Up_Function()
 *   DESCRIPTION : RLS_Wipe_Sensitivity_Up_Function  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/  
                   
void RLS_Wipe_Sensitivity_Up_Function(void)
{
    uint8 i;
    if(Lin_BCM_Frame.RainSensitivity > u8_Rain_SensitivityPre)
    {
        u8_SensitivityUpFlg = 1;
    }
    u8_Rain_SensitivityPre = Lin_BCM_Frame.RainSensitivity;
    
    if((u8_SensitivityUpFlg == 1)&&((u8_Wiper_State == PARK_MODE)||(u8_Wiper_State == INT_SPEED_MODE)))
    {
        Lin_RLS_Frame.RQ_WiperSPD = 1 ;
        u8_IntSpeedEnterCnt = 0;
        u8_SensitivityUpCnt++;
        
        if(u8_SensitivityUpCnt > 5)
        {
            u8_SensitivityUpFlg = 0;
            Lin_RLS_Frame.RQ_WiperSPD = 0;
        }
        
        for(i = 0;i < Rain_WINDOW ;i ++) 
        {
            u8_RainIntensity_Win[i] = 0;
        }
        u8_Wiper_StatePre = INT_SPEED_MODE;
        u8_Wiper_State = PARK_MODE;
    }
    
    else
    {
        u8_SensitivityUpCnt = 0; 
    }    
}

/*******************************************************
 * FUNCTION NAME : RLS_Battery_Measurement()
 *   DESCRIPTION : RLS_Battery_Measurement  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Battery_Measurement(void)
{
    uint32 temp;
    temp = get_adc_times(VOLT_CH,MEAS_NUM); //V_VCC/1024 = x*(5/46)/3.3 
    u16_Battery_Volt = ((temp*113*33/13)>>10) + 5;
}

/*******************************************************
 * FUNCTION NAME : RLS_Battery_State()
 *   DESCRIPTION : RLS_Battery_State  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Battery_State(void)
{
    RLS_Battery_Measurement();

    if(u16_Battery_Volt <= 75) //7.5v
	{
		u8_high_voltage_cnt = 0;
		u8_low_voltage_cnt++;
		if(u8_low_voltage_cnt >= 60) //3s
		{
			Lin_RLS_Frame.VOLT_Error = VOLTAGE_LOW;
		}
	}
	else if((u16_Battery_Volt >= 80)&&(u16_Battery_Volt <= 180))
	{
		u8_low_voltage_cnt = 0;
		u8_high_voltage_cnt = 0;
		Lin_RLS_Frame.VOLT_Error = VOLTAGE_NORMAL;
	}
	else if(u16_Battery_Volt > 185)
	{
		u8_low_voltage_cnt = 0;
		u8_high_voltage_cnt++;
		if(u8_high_voltage_cnt >= 60) //3s
		{
			Lin_RLS_Frame.VOLT_Error = VOLTAGE_HIGH;
		}
	}
}
/*******************************************************
 * FUNCTION NAME : RLS_Lin_Diag_Fucntion()
 *   DESCRIPTION : RLS_Lin_Diag_Fucntion  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Lin_Diag_Fucntion(void) //50ms
{
    if(u8_Lin_Diag_Enable_Cnt >= 30) //1500ms
    {
        u8_Lin_Diag_Enable = 1;
    }
    else
    {
        u8_Lin_Diag_Enable = 0;
        u8_Lin_Diag_Enable_Cnt++;
    }
}
/*******************************************************
 * FUNCTION NAME : Sleep_Process()
 *   DESCRIPTION : Sleep_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Sleep_Process(void)
{    
    /******MLX75308进入休眠***********/
    (void)SPI_Wr_Cmd(RSLP);
     while(!DR);     
    (void)SPI_Wr_Cmd(CSLP);
     while(!DR);
     
    u8_receive_data_flg = 0;

    if((API_6h_Cnt < API_OVERTIME_CNT) &&
    (((Lin_Window_Frame.roof_status != 9) && (Lin_Window_Frame.roof_status != 0))|| //open
    (Lin_Window_Frame.flw_status != 0 || Lin_Window_Frame.frw_status != 0 || Lin_Window_Frame.blw_status != 0 || Lin_Window_Frame.brw_status != 0)))  //天窗、车窗未关并且12小时未到，启动API自动醒功能
    {
         API_init();
    }
    
    Lin_RLS_Frame.RQ_WiperSPD     = 0;
    Lin_RLS_Frame.RQ_LowBeam      = 0;
    Lin_RLS_Frame.RQ_LowBeam_Invers = 1;
    Lin_RLS_Frame.RQ_PositionLamp = 0;
    Lin_RLS_Frame.RQ_PositionLamp_Invers = 1;
    Lin_RLS_Frame.Fault_Light = 0;
    Lin_RLS_Frame.Fault_Rain = 0;
    Lin_RLS_Frame.VOLT_Error = 0;   
    
    Lin_RLS_data();
      
    /******关闭LIN发送***********/ 
    LIN_EN = 0;
    SCI0SR2 = 0x80;    
    SCI0ACR1 = 0x83;                   //休眠前将SCI设置为检测电平触发退出休眠
    /******检测RX脚***********/ 
    if(PTS_PTS0 == 1 ) 
    {
        CPMUPROT = 0x26U;

        CPMUCLKS_PSTP = 1;                  /* Make sure PSTP bit is clear to enable Stop Mode */
        CPMUPROT = 0x00U;
        asm ANDCC #0x7F;                    /* Clear S-bit in the CCR to enable STOP instruction */
        asm STOP;                           /* Enter Stop mode */  
    }
    else
    {
        LIN_EN = 1;
        G_4sFlag = 0;
        G_4s_counter = 0;
    }
}
/*******************************************************
 * FUNCTION NAME : Recover_Process()
 *   DESCRIPTION : Recover_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Recover_Process(void)
{
   u8_Lin_Diag_Enable = 0;
   u8_Lin_Diag_Enable_Cnt = 0;
   
   App_Rls_Error.RS_Error_Cnt[0] = 0;
   App_Rls_Error.RS_Error_Cnt[1] = 0;
   App_Rls_Error.IR_Error_Cnt[0] = 0;
   u8_low_voltage_cnt = 0;
   u8_high_voltage_cnt = 0;
   
   /******重新初始化LIN***********/
   LinConfig();
   TIM_Init() ;     //定时器初始化
   rx.error = 0;
   G_4sFlag = 0;
   G_4s_counter = 0;
   /******低电平唤醒MLX75398***********/
   WAKE_UP = 0;
   while(!DR); 
   (void)SPI_Wr_Cmd(NRM); 
   while(!DR);                
} 
    
void RLS_Roof_Task (void)
{   
    uint8 i; 
    if(API_10s_Flag == 1) //休眠后定时10s醒
    {
        RLS_Auto_Rain_Task();
        if(Lin_RLS_Frame.RQ_WiperSPD != 0)
        {
            u8_rain_detect_flg = 1;
        }
        
        
        if((((Lin_Window_Frame.roof_status != 9) && (Lin_Window_Frame.roof_status != 0)) \
        || Lin_Window_Frame.flw_status != 0 || Lin_Window_Frame.frw_status != 0 || Lin_Window_Frame.blw_status != 0 || Lin_Window_Frame.brw_status != 0)\
        &&(u8_rain_detect_flg == 1) 
        ||(Lin_RLS_Frame.VOLT_Error == 1 )
        ||(Lin_RLS_Frame.Fault_Rain == 1 || Lin_RLS_Frame.Fault_Light == 1)
        ||(API_6h_Cnt >= API_OVERTIME_CNT-1))                               //监控模式下有雨或电压异常或传感器故障或超时且 天窗、车窗未关
        
        {	
            Lin_RLS_Frame.RQ_WiperSPD = 1 ;
            u8_rain_detect_flg = 0;
            
            for(i=0;i<=2;i++)
            {            
                Lin_send_break();
                 _FEED_COP(); /* feeds the dog */
                Delay_Ms(120);
                if(u8_receive_data_flg == 1) break;
            }
        }
        else
        {
            
        }


        if(G_600msFlag == 1) //监控模式下醒来，查看定时有没有到1s
        {
            u8_rain_detect_flg = 0;
            API_10s_Flag = 0;
            G_600msFlag = 0;
            G_4sFlag = 0;
            G_4s_counter = 0;  
            API_6h_Cnt++;
            Sleep_Process();   //进入伪停止模式
            Recover_Process();
        }
    } 

}

