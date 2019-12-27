/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      ls_app.c
*
* @author    xujun
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"
#include "adc.h"
#include "rls_app.h"
#include "lin_app.h"
#include "lin.h"
#include "lin_cfg.h"
#include "spi.h"
#include "gpio.h"
#include "eeprom.h"
#include "clock.h"
#include "rtc.h"
#include "ftm.h"
#include "watchdog.h"


uint8  u8_Lin_Diag_Enable;
uint8  u8_Lin_Diag_Enable_Cnt;

uint8  u8_Rain_Sensitivity,Rain_Sensitivity;
uint16 u16_SPD_Vehicle;

uint8  u8_cnt_choose;
uint8  u8_cnt_choose_pre;
uint8  u8_Int_Time;
uint8  u8_Int_Time_pre;

uint8 u8_enter_period_cnt;
uint8 u8_enter_period_flg;
uint16 u16_Brightness_FW;
uint8  u8_Brightness_IR,u8_Brightness_IR_Right;

uint8  u8_Cmd_Execution;
uint16 u16_Pd_Measure_Value;
uint8  u8_Wiper_State,u8_Wiper_StatePre;
uint8  u8_Vehicle_State,u8_Vehicle_State_Pre;
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
uint8  u8_Juge_Rain_Cnt[CHAN_NUM] ;

uint16 u16_DC_Comp_Value[CHAN_NUM];


uint8  u8_RainIntensity[CHAN_NUM];
uint8  u8_RainIntensityPre[CHAN_NUM];

uint8  u8_RainIntensity_Max;
uint8  u8_Rain_Invalid_Cnt;

uint8  u8_MeasureSureTime,u8_RLS_StopMsureFlg;

uint8  u8_ClearEnternIntSpeedCnt;
uint8  u8_IntSpeedEnterCnt,u8_LowSpeedCnt;

uint8  u8_ExitLowSpeedCnt,u8_IntSpeedCnt,u8_IntDelayTimer,u8_HighHoldCnt;
uint8  u8_HighSpeedHoldCnt;

uint8  u8_EnterLowSpeedCnt;
uint16 u16_ExitLowSpeedTimer;

uint8  u8_Splash_cnt;

uint8  u8_Rain_Valid;
uint8  u8_Rain_Value,u8_WiperSpeed_Expert,u8_WiperSpeed;
uint8  u8_Rain_Flg;
uint16 u16_RainWindow_Cnt;
uint16 u16_IntWindow_Cnt;
uint8  u8_Int_Cnt;

uint16 u16_DC_checkValue,u16_DC_comp_value,u16_Ref_Adc_A,u16_Ref_Adc_B;
uint8  RLS_RunMode;
uint8  u8_Rain_Delta;

uint8  u8_LightOnTimer;

uint8  Light_on_cnt[LIGHT_TYPE];
uint8  Light_off_cnt[LIGHT_TYPE];

uint32 u32_light_value;

uint8 u8_Wipe_Automatic_On_Flg;
uint8 u8_Wipe_Automatic_On_Pre;
uint8 u8_Automatic_On_Cnt;

uint8 u8_SensitivityUpCnt;   
uint8 u8_SensitivityUpFlg;
uint8 u8_Rain_SensitivityPre; 

uint8 u8_IntSpeedFlgCnt;
uint8 u8_IntSpeedFlg;

uint8 u8_low_enter_high_timer;

uint16 u16_Battery_Volt;
uint8  u8_Battery_Low_Cnt;
uint8  u8_Battery_High_Cnt;
uint8  u8_Battery_status;

uint8 Brightness_Light_Percentage[1];
uint8 Brightness_Infrared_Percentage[1];

uint8 u8_low_voltage_cnt;
uint8 u8_high_voltage_cnt;

uint8 u8_ls_error_cnt;

uint8 u8_light_on_req,u8_light_on_invent_req,u8_twilight_on_req,u8_twilight_on_invent_req;

uint8 u8_polling_mode_enter,u8_wakeup_timer,u8_wakeup_bcm_timer,u8_wakeup_cnt,Mcu_wakeup_state,u8_rain_state_polling_flg;
uint8 u8_lin_cmd_sleep,u8_auto_roof_rain_measure_sleep_flg,u8_wakeup_bcm_cnt_sleep_flg;


struct BCM_Frame            Lin_BCM_Frame;
struct MLX75308_Frame       MLX75308_RxFrame;
struct MLX75308_Mnrval      Mnrval;
struct Rls_Error            App_Rls_Error;


/*****NEW PCB**x37*********/
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
    WDOG_Feed();
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
	  WDOG_Feed();
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
 * FUNCTION NAME : RLS_AutoLightControl()
 *   DESCRIPTION : RLS_AutoLightControl function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_AutoLightControl(void)
{
    uint32 temp,temp_light_on_th,temp_light_off_th;
    uint8 temp_on_ir,temp_off_ir;
    if(u16_SPD_Vehicle == 0)   
    {
        u8_LightOnTimer  =  4 ;        
    }
    else if(u16_SPD_Vehicle <= 40)
    {
        u8_LightOnTimer  =  10;           
    }    
    else if(u16_SPD_Vehicle <= 80)
    {
        u8_LightOnTimer  =  9;         
    }    
    else 
    {
        u8_LightOnTimer  =  7; 
    }
    
	
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
				 u8_light_on_req = 1;     
			 }
			 else
			 {
				Light_on_cnt[LIGHT]++ ;
			 }
		} 		
		else if(((u16_Brightness_FW > temp_light_off_th )&&(u8_Brightness_IR > 4))||(u16_Brightness_FW > 500))
		{	
			 Light_on_cnt[LIGHT] = 0;
			 if(Light_off_cnt[LIGHT] >= Light_Stastegy_Parameter[0].off_timer)
			 {
				 u8_light_on_req = 0;     
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
	else
	{
		if(u16_Brightness_FW <= temp_light_on_th )
		{
			 Light_off_cnt[LIGHT] = 0;
			 if(Light_on_cnt[LIGHT] >= u8_LightOnTimer)
			 {
				 u8_light_on_req = 1;     
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
				 u8_light_on_req = 0;     
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
				 u8_twilight_on_req = 1;     
			 }
			 else
			 {
				Light_on_cnt[TWILIGHT]++ ;
			 }
		} 			
		else if(((u16_Brightness_FW > temp_light_off_th)&&(u8_Brightness_IR > 4))||(u16_Brightness_FW > 500))
		{	
			 Light_on_cnt[TWILIGHT] = 0;
			 if(Light_off_cnt[TWILIGHT] >= Light_Stastegy_Parameter[0].off_timer)
			 {
				 u8_twilight_on_req = 0;      
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
				 u8_twilight_on_req = 1;     
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
				 u8_twilight_on_req = 0;     
			 }
			 else
			 {
				Light_off_cnt[TWILIGHT]++ ;
			 }
		}		
		else
		{
			Light_on_cnt[TWILIGHT] = 0;
			Light_off_cnt[TWILIGHT] = 0;
		}
	}
}

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
	
	/*if(Mnrval.Amb_E < 2000)  //IR
	{
		App_Rls_Error.IR_Error_Cnt[1]++;
		if(App_Rls_Error.IR_Error_Cnt[1] >= 20)
		{
			App_Rls_Error.IR_Error = 1;
		}
	}
	else
	{
		App_Rls_Error.IR_Error_Cnt[1] = 0;
	}*/
	
	if(App_Rls_Error.IR_Error_Cnt[0] < 50)
	{
		App_Rls_Error.IR_Error = 0;
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
    uint32 avg_fw = 0, avg_ir = 0 , avg_ir_right = 0;
    uint8 i;
    
    for(i = 0; i < AVG_N; i++)
    {
#if 0
        MLX75308_Meansure(PDC | PDD |PDE);
        avg_fw +=  MLX75308_RxFrame.data_field[0];
        avg_ir +=  MLX75308_RxFrame.data_field[1];
        avg_ir_right +=  MLX75308_RxFrame.data_field[2];
#endif
        MLX75308_Meansure(PDC | PDD);
		avg_fw +=  MLX75308_RxFrame.data_field[0];
		avg_ir +=  MLX75308_RxFrame.data_field[1];
    }
    
    avg_fw = avg_fw / AVG_N;
    avg_ir = avg_ir / AVG_N;
    avg_ir_right = avg_ir_right / AVG_N;
    
    Mnrval.Amb_C = (uint16)(avg_fw);
    Mnrval.Amb_D = (uint16)(avg_ir);
    Mnrval.Amb_E = (uint16)(avg_ir_right);
    
    avg_ir = Search_Table(avg_ir,Tab_AWG_IR, Tab_Brightness_IR, 16);
    //avg_ir = (avg_ir * Brightness_Infrared_Percentage[0])/100;
    
    if(avg_ir > 253)         u8_Brightness_IR = 253;
    else                     u8_Brightness_IR = avg_ir;
    
    avg_ir_right = Search_Table(avg_ir_right,Tab_AWG_IR, Tab_Brightness_IR, 16);   
    //avg_ir_right = (avg_ir_right * Brightness_Infrared_Percentage[0])/100;
    		
	if(avg_ir_right > 253)   u8_Brightness_IR_Right = 253;
	else                     u8_Brightness_IR_Right = avg_ir_right;
        
    avg_fw = Search_Table(avg_fw,Tab_AWG_FW, Tab_Brightness_FW, 16);
    if(avg_fw > 1021)     
    {
    	u16_Brightness_FW = 1021;
    }
    else                 
    {
    	u16_Brightness_FW = avg_fw;
    }
    
    RLS_Light_Module_Fault_Process();
    RLS_AutoLightControl();                
}


void RLS_Rain_Module_Fault_Process(uint8 chan)
{
	if(chan == PDA) 
	{
	    if (u16_Pd_Measure_Value == 0) 
		{
			App_Rls_Error.RS_Error_Cnt[0]++;
			if(App_Rls_Error.RS_Error_Cnt[0] >= 100)   
			{
				App_Rls_Error.RS_Error_Cnt[0] = 100;
				App_Rls_Error.RS_Error = 1 ;
			}
		} 
		else 
		{
			App_Rls_Error.RS_Error_Cnt[0] = 0;
		}
	}
	else if(chan == PDB) 
	{
	    if (u16_Pd_Measure_Value == 0) 
		{
			App_Rls_Error.RS_Error_Cnt[1]++;
			if(App_Rls_Error.RS_Error_Cnt[1] >= 100)   
			{
				App_Rls_Error.RS_Error_Cnt[1] = 100;
				App_Rls_Error.RS_Error = 1 ;
			}
		} 
		else 
		{
			App_Rls_Error.RS_Error_Cnt[1] = 0;
		}
	}
	
	if((App_Rls_Error.RS_Error_Cnt[0] < 100)&&(App_Rls_Error.RS_Error_Cnt[1] < 100))
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
        	temp = 3000;
        }
        
        if(Lin_BCM_Frame.ParkPosition == 1)
        { 
            PD_Meas_Comp_Ref[CHAN_A] =  PD_WIN_AVG[CHAN_A][0] ;            
        }
        else
        {
            
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
        	temp = 3000;
        }
        
        if(Lin_BCM_Frame.ParkPosition == 1)
        { 
            PD_Meas_Comp_Ref[CHAN_B] =  PD_WIN_AVG[CHAN_B][0] ;
            
        }
        else
        {
            
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
        else if((Rain_temp_B >= 1)&&(Rain_temp_B <= 3))   u8_RainIntensity[CHAN_B]  = 1;
        else if((Rain_temp_B >= 4)&&(Rain_temp_B <= 5))   u8_RainIntensity[CHAN_B]  = 2;
        else if((Rain_temp_B >= 6)&&(Rain_temp_B <= 7))   u8_RainIntensity[CHAN_B]  = 3;
        else if((Rain_temp_B >= 8)&&(Rain_temp_B <= 9))   u8_RainIntensity[CHAN_B]  = 4;
        else if((Rain_temp_B >= 10)&&(Rain_temp_B <= 10)) u8_RainIntensity[CHAN_B]  = 5;
        else if((Rain_temp_B >= 11)&&(Rain_temp_B <= 14)) u8_RainIntensity[CHAN_B]  = 6;
        else if((Rain_temp_B >= 15)&&(Rain_temp_B <= 17)) u8_RainIntensity[CHAN_B]  = 7;
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
        else if((Rain_temp_A >= 1)&&(Rain_temp_A <= 3))   u8_RainIntensity[CHAN_A]  = 1;
        else if((Rain_temp_A >= 4)&&(Rain_temp_A <= 5))   u8_RainIntensity[CHAN_A]  = 2;
        else if((Rain_temp_A >= 6)&&(Rain_temp_A <= 7))   u8_RainIntensity[CHAN_A]  = 3;
        else if((Rain_temp_A >= 8)&&(Rain_temp_A <= 9))   u8_RainIntensity[CHAN_A]  = 4;
        else if((Rain_temp_A >= 10)&&(Rain_temp_A <= 10)) u8_RainIntensity[CHAN_A]  = 5;
        else if((Rain_temp_A >= 11)&&(Rain_temp_A <= 14)) u8_RainIntensity[CHAN_A]  = 6;
        else if((Rain_temp_A >= 15)&&(Rain_temp_A <= 17)) u8_RainIntensity[CHAN_A]  = 7;
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
 * FUNCTION NAME : RLS_Invalid_DataProcess()
 *   DESCRIPTION : RLS_Rain_State_Mchaine function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
uint8 RLS_Period_Mode(uint8 Int_Timer, uint8 Wiper_Timer)
{
	if((Wiper_Timer >= 0) && (Wiper_Timer < (Int_Timer - 10)))
	{
		u8_WiperSpeed = 0;
	}
	else if((Wiper_Timer >= (Int_Timer - 10)) && (Wiper_Timer <= Int_Timer))
	{
		u8_WiperSpeed = 1;
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

void RLS_Rain_State_Mchaine(void)
{
    uint8  u8_Delaytimer,i,u8_rain_state_th,u8_rain_cnt;
    uint8  temp,tempcnt;
    uint8  temp_period_low_th;
    uint8  temp_period_low_cnt;
    uint8  u8_temp_rcv;
    uint8  temp_period_low_timer;
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
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer + 20;
            }            
            else if(u8_Rain_Sensitivity == 4)
            {
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer + 20; 
            }
            else
            {
                u8_Delaytimer = Rain_Stastegy_Parameter[0].park_timer + 20;
            }
                       
            
            if(u8_Wiper_StatePre != PARK_MODE)
            {
                u8_Wiper_StatePre_Int  = 1;
            }
            
            if(u8_Wiper_StatePre_Int  == 1)
            {
            	u8_WiperSpeed = 0;
                
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
                
                if(u8_Wiper_StatePre_Int_Cnt >= 20)//1s
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
            	u8_Splash_cnt = 0;
            	u8_ClearEnternIntSpeedCnt = 0;
                u8_IntSpeedEnterCnt = 0;
            }
            else
            {
                u8_ClearEnternIntSpeedCnt++;
            }
            if(u8_enter_period_flg == 1)
            {
            	u8_WiperSpeed = 1;
            	if(u8_enter_period_cnt >= 10)
            	{
            		u8_enter_period_cnt = 0;
            		u8_enter_period_flg = 0;
            		u8_Wiper_State = PERIOD_SPEED_MODE;
            	}
            	else
            	{
            		u8_enter_period_cnt++;
            	}            	
            }
            else
            {
            	u8_WiperSpeed = 0;
            }
            u8_IntDelayTimer = 0;
            u8_EnterLowSpeedCnt = 0;           
            
            if(u8_WiperSpeed_Expert != 0)
            {
                u8_ClearEnternIntSpeedCnt = 0;
                u8_IntSpeedCnt = 0;
                if(u8_Rain_Flg == 0)
                {
                	u8_Wiper_State = INT_SPEED_MODE;
                }
                else 
                {                	
                	u16_RainWindow_Cnt = 0;
                	u8_enter_period_flg = 1;
                }
                
                if(u8_Rain_Sensitivity == 4)
                {
                    temp =  Rain_Stastegy_Parameter[0].park_enter_low_th + 4;
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
                    tempcnt = 2;
                }
                else
                {
                    temp =  Rain_Stastegy_Parameter[0].park_enter_low_th + 4 ;
                    tempcnt = 2;
                }
                
                if((u8_RainIntensity[CHAN_A] >= temp)&&(u8_RainIntensity[CHAN_B]>= temp)&&(u8_IntSpeedEnterCnt > tempcnt))
				{
					u8_Wiper_State = LOW_SPEED_MODE;
					u8_Rain_Flg = 1;
					u16_RainWindow_Cnt = 0;
					u16_IntWindow_Cnt = 0;
					u8_Int_Cnt = 0;
					u8_low_enter_high_timer = 0;
				}								
            }
            else
            {  
            
            }
            
            if((u8_RainIntensity[CHAN_A] >= Rain_Stastegy_Parameter[0].park_enter_high_th)&&(u8_RainIntensity[CHAN_B]>= Rain_Stastegy_Parameter[0].park_enter_high_th)) 
			{
				if(u8_Splash_cnt >= 20)
				{
					u8_Splash_cnt = 0;
					u8_Rain_Flg = 1;
					u16_RainWindow_Cnt = 0;
					u16_IntWindow_Cnt = 0;
					u8_Int_Cnt = 0;
					u8_Wiper_State = HIGH_SPEED_MODE;
				}
				else
				{
					u8_Splash_cnt++;
				}										
			}
            
            if(u16_SPD_Vehicle == 0)
            {
            	u8_Vehicle_State = 0;
            }
            else
            {
            	u8_Vehicle_State = 1;
            }
            
            if((u8_Vehicle_State > u8_Vehicle_State_Pre)&&(u8_Rain_Flg == 1))
            {
            	u8_Wiper_State =  INT_SPEED_MODE ;
            	u8_IntSpeedEnterCnt = 0;
            }
            if(u16_RainWindow_Cnt >= 800)
            {
            	u16_RainWindow_Cnt = 0;
            	u8_Rain_Flg = 0;
				u16_IntWindow_Cnt = 0;
				u8_Int_Cnt = 0;
            }
            else 
            {
            	u16_RainWindow_Cnt++;
            }
            
            if((u16_IntWindow_Cnt <= 800) && (u8_Int_Cnt >= 3))
            {
            	u16_IntWindow_Cnt = 0;
            	u8_Int_Cnt = 0;
            	u16_RainWindow_Cnt = 0;
            	u8_Rain_Flg = 1;
            }
            else 
            {
            	u16_IntWindow_Cnt++;
            	if(u16_IntWindow_Cnt > 800)
            	{
            		u16_IntWindow_Cnt = 0;
            		u8_Int_Cnt = 0;
            	}
            }
            u8_Wiper_StatePre = PARK_MODE;
            u8_Vehicle_State_Pre =  u8_Vehicle_State;
            
        } break;
        
        case INT_DELAY_MODE:
        {
            u8_IntSpeedEnterCnt = 0;
            u8_ClearEnternIntSpeedCnt = 0;
            u8_LowSpeedCnt = 0;
            u8_HighHoldCnt = 0; 
            u8_EnterLowSpeedCnt = 0;
            
            u8_IntDelayTimer++;
            
            if((u8_IntDelayTimer >= 0)&&(u8_IntDelayTimer < Rain_Stastegy_Parameter[0].int_delay_timer))
            {
            	u8_WiperSpeed = 0;
            }
            
            else if((u8_IntDelayTimer >= Rain_Stastegy_Parameter[0].int_delay_timer)&&(u8_IntDelayTimer < (Rain_Stastegy_Parameter[0].int_delay_timer + 10))) 
            {
            	u8_WiperSpeed = 1;
            }
            
            else if((u8_IntDelayTimer >= 70)&&(u8_IntDelayTimer < 130)) 
            {
            	u8_WiperSpeed = 0;
            }
            
            else if((u8_IntDelayTimer >= 130)&&(u8_IntDelayTimer < 140)) 
            {
            	u8_WiperSpeed = 1;
            }           
            else
            {
            	u8_WiperSpeed = 0;
                u8_Wiper_State = PARK_MODE;
            }

            u8_Wiper_StatePre = INT_DELAY_MODE;
        } break;
        
        case INT_SPEED_MODE:
        {
        	u16_RainWindow_Cnt = 0;
        	u8_low_enter_high_timer = 0;
            u8_IntDelayTimer = 0;
            u8_HighHoldCnt = 0;   
            u8_ExitLowSpeedCnt = 0;
            u8_WiperSpeed = 1;
            u8_IntSpeedCnt++;
            u8_EnterLowSpeedCnt = 0;
                                          
            if(u8_IntSpeedCnt >= 10)
            {
            	u8_enter_period_cnt = 0;
            		u8_enter_period_flg = 0;
            	u8_WiperSpeed = 0;
                u8_Wiper_State = PARK_MODE;
                u8_IntSpeedEnterCnt++;
                u8_Int_Cnt++;
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
                	u8_Splash_cnt = 0;
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
                	u8_Splash_cnt = 0;
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
                	u8_Splash_cnt = 0;
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
                	u8_Splash_cnt = 0;
                    u8_IntSpeedEnterCnt = 0;
                    u8_Wiper_State = PERIOD_SPEED_MODE;
                    u8_IntDelayTimer = 0;
                }
            }
            
            u8_Wiper_StatePre = INT_SPEED_MODE;
        } break;
        case PERIOD_SPEED_MODE:
        {
        	u8_Rain_Flg = 1;
            u8_LowSpeedCnt = 0;
            u8_HighHoldCnt = 0;
            u8_IntSpeedEnterCnt = 0;
            u8_IntDelayTimer++; 
            u8_ExitLowSpeedCnt = 0; 
            u8_low_enter_high_timer = 0;
			u16_RainWindow_Cnt = 0;
			u8_enter_period_cnt = 0;
			u8_enter_period_flg = 0;
			u16_IntWindow_Cnt = 0;
			u8_Int_Cnt = 0;
                  	
        	//灵敏度选择时间间隔

        	if(u8_Rain_Sensitivity == 4)
        	{
        		if( u16_SPD_Vehicle < 10)
				{
					u8_cnt_choose = 3;
				}
				else if(u16_SPD_Vehicle < 80)
				{
					u8_cnt_choose = 4;
				}
				else
				{
					u8_cnt_choose = 5;
				}
        		
        		if( u16_SPD_Vehicle < 10)
				{
					u8_Int_Time = 48;
				}
				else if(u16_SPD_Vehicle < 50)
				{
					u8_Int_Time = 80;
				}
				else if(u16_SPD_Vehicle < 80)
				{
					u8_Int_Time = 60;
				}
				else
				{
					u8_Int_Time = 40;
				}
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt;
        	}
        	else if(u8_Rain_Sensitivity == 3)
        	{
				if( u16_SPD_Vehicle < 10)
				{
					u8_cnt_choose = 3;
				}
				else if(u16_SPD_Vehicle < 80)
				{
					u8_cnt_choose = 4;
				}
				else
				{
					u8_cnt_choose = 4;
				}
				
				if( u16_SPD_Vehicle < 10)
				{					
					u8_Int_Time = 48;
				}
				else if(u16_SPD_Vehicle < 50)
				{
					u8_Int_Time = 100;
				}
				else if(u16_SPD_Vehicle < 80)
				{
					u8_Int_Time = 80;
				}
				else
				{
					u8_Int_Time = 60;
				}
				
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt + 5;
        	}
        	else if(u8_Rain_Sensitivity == 2)
        	{
				if( u16_SPD_Vehicle < 10)
				{
					u8_cnt_choose = 3;
				}
				else
				{
					u8_cnt_choose = 4;
				}
				
				if( u16_SPD_Vehicle < 10)
				{					
					u8_Int_Time = 60;
				}
				else if(u16_SPD_Vehicle < 50)
				{
					u8_Int_Time = 110;
				}
				else if(u16_SPD_Vehicle < 80)
				{
					u8_Int_Time = 90;
				}
				else
				{
					u8_Int_Time = 70;
				}
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt + 10;
        	}
        	else 
        	{
				if( u16_SPD_Vehicle < 10)
				{
					u8_cnt_choose = 3;
				}
				else
				{
					u8_cnt_choose = 3;
				}
				
				if( u16_SPD_Vehicle < 10)
				{					
					u8_Int_Time = 60;
				}
				else if(u16_SPD_Vehicle < 50)
				{
					u8_Int_Time = 120;
				}
				else if(u16_SPD_Vehicle < 80)
				{
					u8_Int_Time = 100;
				}
				else
				{
					u8_Int_Time = 80;
				}
				
        		temp_period_low_th = Rain_Stastegy_Parameter[0].period_enter_low_th ;
        		temp_period_low_cnt = Rain_Stastegy_Parameter[0].period_enter_low_cnt + 15;
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
        			u8_Splash_cnt = 0;
            		u8_WiperSpeed = 0;
            		u8_cnt_choose_pre = 0;
            		u8_Int_Time_pre = 0;
            		u8_Int_Time = 0;
            		u8_cnt_choose = 0;
            		u8_Wiper_State = PARK_MODE;
        		}
        	}
        	else
        	{
				if(u8_WiperSpeed_Expert > 3)
        		{
        			if(u16_SPD_Vehicle >= 5)
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
                	        	
        	if(u8_Rain_Sensitivity == 4)
        	{
        		temp_period_low_timer = 120 ;   
        	}
        	else if(u8_Rain_Sensitivity == 3)
        	{
        		temp_period_low_timer = 125 ; 
        	}
        	else if(u8_Rain_Sensitivity == 2)
			{
        		temp_period_low_timer = 140 ; 
			}
        	else 
			{
        		temp_period_low_timer = 160 ; 
			}
        	if(u8_WiperSpeed_Expert >= temp_period_low_th)
            {
                u8_EnterLowSpeedCnt++;
                u16_ExitLowSpeedTimer = 0;
                if(u8_EnterLowSpeedCnt >= temp_period_low_cnt)
                {
					u8_cnt_choose_pre = 0;
					u8_Int_Time_pre = 0;
					u8_Int_Time = 0;
					u8_cnt_choose = 0;
					u8_IntDelayTimer = 0;
					u8_EnterLowSpeedCnt = 0;                    
					u8_Wiper_State = LOW_SPEED_MODE;					
                }
            }
        	else
        	{
        		u16_ExitLowSpeedTimer++;
        		if(u16_ExitLowSpeedTimer >= temp_period_low_timer)
        		{
        			u16_ExitLowSpeedTimer = 0;
        			u8_EnterLowSpeedCnt = 0;
        		}
        	}
        	
        	if((u8_RainIntensity[CHAN_A] >= Rain_Stastegy_Parameter[0].park_enter_high_th)&&(u8_RainIntensity[CHAN_B]>= Rain_Stastegy_Parameter[0].park_enter_high_th)) 
			{
				if(u8_Splash_cnt >= 40)
				{
					u8_cnt_choose_pre = 0;
					u8_Int_Time_pre = 0;
					u8_Int_Time = 0;
					u8_cnt_choose = 0;
					u8_Splash_cnt = 0;
					u8_Wiper_State = HIGH_SPEED_MODE;
				}
				else
				{
					u8_Splash_cnt++;
				}								
			}
            u8_Wiper_StatePre = PERIOD_SPEED_MODE;  
        } break;
        
        case LOW_SPEED_MODE:
        {
        	u8_Rain_Flg = 1;
        	u8_Splash_cnt = 0;
            u8_IntSpeedCnt = 0;
            u8_IntDelayTimer = 0;
            u8_IntSpeedEnterCnt = 0;
            u8_HighSpeedHoldCnt = 0;
            u8_WiperSpeed = 1;
            
            if(u8_low_enter_high_timer >= 200)
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
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer41;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt41;
                }
                else if(u16_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer42;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt42;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer43;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt43;
                }
                
                if(u8_WiperSpeed_Expert < 4)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer) 
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  PERIOD_SPEED_MODE;
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
                else if(u8_WiperSpeed_Expert >= 4)
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
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer31;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt31;
                }
                else if(u16_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer32;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt32;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer33;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt33;
                }
                 
                if(u8_WiperSpeed_Expert < 4)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer) 
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  PERIOD_SPEED_MODE;
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
                else if(u8_WiperSpeed_Expert >= 4)
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
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer21;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt21;
                }
                else if(u16_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer22;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt22;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer23;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt23;
                }
                
                if(u8_WiperSpeed_Expert < 4)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer) //6s
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  PERIOD_SPEED_MODE;
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
                else if(u8_WiperSpeed_Expert >= 4)
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
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer11;//40
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt11;
                }
                else if(u16_SPD_Vehicle < 80)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer12;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt12;
                }
                else 
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].low_delaytimer13;
                     u8_rain_cnt = Rain_Stastegy_Parameter[0].low_enter_high_cnt13;
                }
                
                if(u8_WiperSpeed_Expert < 4)
                {              
                    if(u8_ExitLowSpeedCnt >= u8_Delaytimer)
                    {
                        u8_ExitLowSpeedCnt = 0;
                        u8_IntDelayTimer = 0;
                        u8_Wiper_State =  PERIOD_SPEED_MODE;
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
                else if(u8_WiperSpeed_Expert >= 4)
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
        	u8_Rain_Flg = 1;
        	u8_WiperSpeed = 2;
        	u8_low_enter_high_timer = 0;
            if(u8_Rain_Sensitivity == 4)
            {
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer41;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th41;
                }
                else if(u16_SPD_Vehicle < 80)
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
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer31;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th31;
                }
                else if(u16_SPD_Vehicle < 80)
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
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer21;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th21;
                }
                else if(u16_SPD_Vehicle < 80)
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
                if(u16_SPD_Vehicle < 5)
                {
                     u8_Delaytimer = Rain_Stastegy_Parameter[0].high_delaytimer11;
                     u8_rain_state_th = Rain_Stastegy_Parameter[0].high_hold_th11;
                }
                else if(u16_SPD_Vehicle < 80)
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
                	u8_WiperSpeed = 2;
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
            if((u8_MeasureSureTime <= Rain_Stastegy_Parameter[0].park_high_meas_timer1))//||((u8_MeasureSureTime >= Rain_Stastegy_Parameter[0].park_high_meas_timer2)))//&&(u8_MeasureSureTime <= 20)))
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
            if((u8_MeasureSureTime <= Rain_Stastegy_Parameter[0].park_low_meas_timer1))//||((u8_MeasureSureTime >= Rain_Stastegy_Parameter[0].park_low_meas_timer2)))//&&(u8_MeasureSureTime <= 30)))
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
    uint8   temp_data[2] ;

   /* add intia*/

    u8_WiperSpeed = 0 ;
    l_u8_wr_LI0_RLS_RQ_WiperSPD(u8_WiperSpeed);
    l_bool_wr_LI0_RLS_RQ_LowBeam(0);
    l_bool_wr_LI0_RLS_RQ_PositionLamp(0);
/******************Chanl A*********************/   
    for(i = 0; i < 20; i++)
    {
    	WDOG_Feed();
        u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDA, 1, 600);
        if(0 != u16_Pd_Measure_Value) 
            break;
    }

    if(u16_Pd_Measure_Value < CALI_PARAM_LOW)
    {
        for(i = 0; i < 254; i++)
        {
        	WDOG_Feed();
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
        	WDOG_Feed();
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
    
    write_data_from_EEPROM(EEPROM_A_DAC_ADDR,temp_data,EEPROM_A_DAC_ADDR_LENTH,1);

/******************Chanl B*********************/ 
   
    for(i = 0 ;i < 20;i++)
    {
    	WDOG_Feed();
        u16_Pd_Measure_Value =  RLS_Rain_Get_Measure(PDB, 1, 600);
        if(0 != u16_Pd_Measure_Value) 
            break;
    }
      
    if(u16_Pd_Measure_Value < CALI_PARAM_LOW)
    {
        for(i = 0;i < 254;i++)
        {
        	WDOG_Feed();
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
        	WDOG_Feed();
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
    write_data_from_EEPROM(EEPROM_B_DAC_ADDR,temp_data,EEPROM_B_DAC_ADDR_LENTH,1);
   
/*********MODE CHANGE TO NORMAL*******************/
    for(i = 0;i < Rain_WINDOW ;i ++) 
    {
        u8_RainIntensity_Win[i] = 0;
    }
    
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
    
    if((u8_Wipe_Automatic_On_Pre == 0)&&(Lin_BCM_Frame.CMD_AutoWiper == 1))
    {
        u8_Wipe_Automatic_On_Flg = 1;
    } 
    
    u8_Wipe_Automatic_On_Pre = Lin_BCM_Frame.CMD_AutoWiper;  
    
    if((u8_Wipe_Automatic_On_Flg == 1)&&(u8_Lin_Diag_Enable == 1))
    {
    	u8_WiperSpeed = 1;
        u8_IntSpeedEnterCnt = 0;
        u8_Automatic_On_Cnt++;
        
        if(u8_Automatic_On_Cnt > 10)
        {
            u8_Automatic_On_Cnt = 0;
            u8_Wipe_Automatic_On_Flg = 0;
            u8_WiperSpeed = 0;
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
    
    if((u8_SensitivityUpFlg == 1)&&((u8_Wiper_State == PARK_MODE)||(u8_Wiper_State == INT_SPEED_MODE))&&(u8_Lin_Diag_Enable == 1))
    {
    	u8_WiperSpeed = 1;
        u8_IntSpeedEnterCnt = 0;
        u8_SensitivityUpCnt++;
        
        if(u8_SensitivityUpCnt > 10)
        {
            u8_SensitivityUpFlg = 0;
            u8_WiperSpeed = 0;
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
 * FUNCTION NAME : LS_Battery_Measurement()
 *   DESCRIPTION : LS_Battery_Measurement  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Battery_Measurement(void)
{
    uint32 temp;
    temp = get_adc_times(VOLT_CH,MEAS_NUM); //V_VCC/1024 = x*(13/113)/3.3 
    u16_Battery_Volt = ((temp*113*33/13)>>12) + 8;
}

/*******************************************************
 * FUNCTION NAME : LS_Battery_Measurement()
 *   DESCRIPTION : LS_Battery_Measurement  
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
		if(u8_low_voltage_cnt >= 20) //1s
		{
			u8_Battery_status = VOLTAGE_LOW;
		}
	}
	else if((u16_Battery_Volt >= 80)&&(u16_Battery_Volt <= 180))
	{
		u8_low_voltage_cnt = 0;
		u8_high_voltage_cnt = 0;
		u8_Battery_status = VOLTAGE_NORMAL;
	}
	else if(u16_Battery_Volt > 185)
	{
		u8_low_voltage_cnt = 0;
		u8_high_voltage_cnt++;
		if(u8_high_voltage_cnt >= 20) //1s
		{
			u8_Battery_status = VOLTAGE_HIGH;
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
void RLS_Lin_Diag_Fucntion(void)
{
    if(u8_Lin_Diag_Enable_Cnt >= 15) //1500ms
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
 * FUNCTION NAME : Auto_Roof_Process()
 *   DESCRIPTION : Auto_Roof_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Auto_Roof_Process(void)
{   
	if(Mcu_wakeup_state == 1)
	{
		u8_wakeup_timer = 0;
		u8_polling_mode_enter = 0;
	}
	
	if(u8_WiperSpeed != 0)
	{
		u8_rain_state_polling_flg = 1;		
	}	
	else
	{
	   u8_wakeup_timer++;
	   if(u8_wakeup_timer >= 6) //600ms
	   {   
		   u8_wakeup_timer = 0;
		   u8_auto_roof_rain_measure_sleep_flg = 1;
	   }
	}
   		
	
	if(u8_rain_state_polling_flg == 1)
	{
		u8_WiperSpeed = 1 ;
		u8_wakeup_timer = 0;
		u8_wakeup_bcm_timer++;
		if(u8_wakeup_bcm_timer >= 2) //200ms
		{			
			u8_wakeup_bcm_timer = 0;
			Lin_RLS_Wakeup_BCM();
			
			if(u8_wakeup_cnt >= 2)
			{
				u8_wakeup_cnt = 0;
				u8_wakeup_bcm_cnt_sleep_flg = 1;
			}
			else
			{
				u8_wakeup_cnt++;
			}	
			
			if(Mcu_wakeup_state == 1) 
			{
				u8_rain_state_polling_flg = 0 ;
			}
		}					
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
	uint8 i;
		
	DISABLE_INTERRUPT;
	
	UART0_S2 |=  UART_S2_RXEDGIF_MASK;   //去掉会产生错误帧
	UART0_BDH  |=  UART_BDH_RXEDGIE_MASK; //去掉会产生错误帧
	/******关闭LIN发送***********/ 
	LIN_DISABLE ;// LIN_EN
	
	/******MLX75308进入休眠***********/
	(void)SPI_Wr_Cmd(RSLP);    
	(void)SPI_Wr_Cmd(CSLP);
	SPI_Disable();
#ifdef ENABLE_AUTO_ROOF
		
	if(Lin_BCM_Frame.RoofStatus >= 1)
	{
		RTC_EnableInt();
		u8_polling_mode_enter = 1 ;
		u8_rain_state_polling_flg = 0;   //休眠前将有雨判断标志置0,有雨时置1
	}
	else
	{
		u8_polling_mode_enter = 0 ;
		RTC_DisableInt();
	}
#endif
	
	for (i = 0;i < LIGHT_TYPE ; i++)
	{
		Light_on_cnt[i] = 0; 
		Light_off_cnt[i] = 0;  
	}
			
	u8_light_on_req = 0;     
	u8_twilight_on_req = 0;
		
	Mcu_wakeup_state = 0;
	u16_RainWindow_Cnt = 0;
	u8_enter_period_cnt = 0;
	u8_enter_period_flg = 0;
	u8_Rain_Flg = 0;
	u16_IntWindow_Cnt = 0;
	u8_Int_Cnt = 0;
	Lin_RLS_data();
	
	/* disable LVD in stop mode */
	PMC_SPMSC1 &= ~(PMC_SPMSC1_LVDE_MASK | PMC_SPMSC1_LVDRE_MASK | PMC_SPMSC1_LVDSE_MASK);
	/* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
	SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK;
	/* Not using KEIL's uVision, so use the standard assembly command */
	ENABLE_INTERRUPT;	
	asm("WFI");
	
	RTC_DisableInt();
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
	LIN_ENABLE ;// LIN_EN
	u8_Lin_Diag_Enable = 0;
	u8_Lin_Diag_Enable_Cnt = 0;
	l_sys_init();
	l_ifc_init(LI0);
	SPI_Enable();
	FTM0_Init();
	
	G_4s_counter = 0;
	G_4sFlag = FALSE ;
    (void)SPI_Wr_Cmd(NRM); 
}
