/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      config_parameter.c
*
* @author    FPT Software
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include "config_parameter.h"
#include "rls_app.h"
#include "eeprom.h"
#include "lin.h"
#include "lin_cfg.h"
#include "lin_diagnostic_service.h"
#include "lin_app.h"


tMlx75308_Config const Mlx75308_Config_Parameter[1] =
{
    {
       0x0b, //np
       0x02, //t_dem
       0x02, //t_dc
       0x00, //bw_adj_a
       0x00, //bw_adj_b
       0x00, //gain_adj_a
       0x00, //gain_adj_b
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
    }
} ;

tRain_Stastegy_Config const  Rain_Stastegy_Parameter[1] =
{
    {
    		8400, //dc_stage1
			8600, //dc_stage2
			8900, //dc_stage3
			9100, //dc_stage4
			
			80,  //stage_intensity1
			100,  //stage_intensity2
			120,  //stage_intensity3
			150,  //stage_intensity4
			200,  //stage_intensity5
			
			8, // meas_avg_cnt
			
			4,//park position  high_speed meas timer
			13,//park position high_speed meas timer
			4,// park position low_speed meas timer
			20,//park position low_speed meas timer
		
			80, // park_timer(u8_Rain_Sensitivity = 4)
			2,  // park_enter_low_th;
			4,  // park_enter_high_th;

			60, // int_delay_timer;
			
			3,  // int_enter_period_cnt;
			50, // int_enter_low_cnt; 
			 
			15,  //period_enter_low_cnt;
			4,  //period_enter_low_th;
			
			60, //low_delaytimer41;    (u8_Rain_Sensitivity = 4)
			55, //low_enter_high_cnt41;
			140, //low_delaytimer42;
			45, //low_enter_high_cnt42;
			180, //low_delaytimer43;
			35, //low_enter_high_cnt43;
			
			60, //low_delaytimer31;    (u8_Rain_Sensitivity = 3)
			55, //low_enter_high_cnt31;
			140, //low_delaytimer32;
			45, //low_enter_high_cnt32;
			180, //low_delaytimer33;
			35, //low_enter_high_cnt33;
			
			60, //low_delaytimer21;    (u8_Rain_Sensitivity = 2)
			55, //low_enter_high_cnt21;
			140, //low_delaytimer22;
			45, //low_enter_high_cnt22;
			180, //low_delaytimer23;
			35, //low_enter_high_cnt23;
			
			60, //low_delaytimer11;    (u8_Rain_Sensitivity = 1)
			55, //low_enter_high_cnt11;
			140, //low_delaytimer12;
			45, //low_enter_high_cnt12;
			180, //low_delaytimer13;
			35, //low_enter_high_cnt13;
			
			60, //high_delaytimer41;    (u8_Rain_Sensitivity = 4)
			5, //high_hold_th41;
			120,//120, //high_delaytimer42;
			3, //high_hold_th42;
			140, //high_delaytimer43;
			3, //high_hold_th43;
			
			60, //high_delaytimer31;    (u8_Rain_Sensitivity = 3)
			5, //high_hold_th431;
			120, //high_delaytimer32;
			3, //high_hold_th32;
			140, //high_delaytimer33;
			3, //high_hold_th33;
			
			60, //high_delaytimer21;    (u8_Rain_Sensitivity = 2)
			5, //high_hold_th21;
			120, //high_delaytimer22;
			3, //high_hold_th22;
			140, //high_delaytimer23;
			3,//high_hold_th23;
			
			60,// high_delaytimer11;    (u8_Rain_Sensitivity = 1)
			5,// high_hold_th11;
			120,// high_delaytimer12;
			3,// high_hold_th12;
			140,// high_delaytimer13;
			3,// high_hold_th13; 
    }
} ;


tLight_Stastegy_Config const  Light_Stastegy_Parameter[1] =
{
    {
        55,  //off_timer
        166, //Lowbean_on_th
        233, //Lowbean_off_th
        166, //PositionLamp_on_th
        233  //PositionLamp_off_th
    }
} ;


void Globle_parameter_Init(void)
{
	uint8 temp_data[1],i;
	read_data_from_EEPROM(EEPROM_BR_LIG_PER_ADDR,Brightness_Light_Percentage,1,ENABLE);
	if(Brightness_Light_Percentage[0] == 0xFF) 
	{
		Brightness_Light_Percentage[0] = 100;
	}
	
	read_data_from_EEPROM(EEPROM_IR_PER_ADDR,Brightness_Infrared_Percentage,1,ENABLE);
	if(Brightness_Infrared_Percentage[0] == 0xFF) 
	{
		Brightness_Infrared_Percentage[0] = 100;
	}
	
	/**************Set ProType and Param****************************/
	   
	read_data_from_EEPROM(EEPROM_A_DAC_ADDR,temp_data,EEPROM_A_DAC_ADDR_LENTH,ENABLE);   /****_DAC********/
   
	if(temp_data[0] == 0xFF)
	{
		MLX75308_A_Adc = Mlx75308_Config_Parameter[0].dac_a_default;
	}
	
	else
	{
		MLX75308_A_Adc = (uint8)(temp_data[0]);
	}
  
   
	read_data_from_EEPROM(EEPROM_B_DAC_ADDR,temp_data,EEPROM_B_DAC_ADDR_LENTH,ENABLE);  
   
	if(temp_data[0] == 0xFF)
	{
		MLX75308_B_Adc = Mlx75308_Config_Parameter[0].dac_b_default ;
	}
	
	else
	{
		MLX75308_B_Adc =  (uint8)(temp_data[0]);
	}
  
	    	
	for (i = 0;i < LIGHT_TYPE ; i++)
	{
		Light_on_cnt[i] = 0; 
		Light_off_cnt[i] = 0;  
	}
			
	u8_light_on_req = 0;     
	u8_light_on_invent_req = 1; 
	u8_twilight_on_req = 0;     
	u8_twilight_on_invent_req = 1; 
	
	//l_bool_wr_LI0_Light_On(u8_light_on_req);
	//l_bool_wr_LI0_Light_On_Invers(u8_light_on_invent_req);
	
	//l_bool_wr_LI0_Twilight_On(u8_twilight_on_req);
	//l_bool_wr_LI0_Twilight_On_Invers(u8_twilight_on_invent_req);
	
	//l_bool_wr_LI0_LS_Error(0);
	//l_bool_wr_LI0_LIN_Error(0);	
	
	Lin_BCM_MOTOR.ParkPosition = 1;
	Lin_BCM_WIPSW.SCS_Automatic = 1;
	Lin_BCM_WIPSW.S_Sens = 4;
	u8_Wipe_Automatic_On_Pre = 1;
	u8_Window_Flg = 0;
	
	Lin_BCM_WIPSW.Ignition = 2;
	Lin_BCM_MOTOR.SPD_Vehicle =  0;
	
	u8_G_FW_Config = 90;
	u8_G_IR_Config = 90;
	
	u8_MsgCounter = 0;
	
	diagnostic_Session = DIAGSRV_SESSION_DEFAULT;
    diagnostic_Session_timer = 0 ;
    diagnostic_Session_flg = 0;
    
    RLS_RunMode = SLEFADAPT;
    
    Lin_Busy_Flag = 0;
    u16_window_cnt = 0;
    
    u8_Rain_Delta =  RAIN_DELTA;
    
    Rain_Sensitivity = 4;
    u8_Rain_SensitivityPre = 4;
    
	u8_IntSpeedCnt = 0;
	u8_IntSpeedEnterCnt = 0;	
	
	u8_polling_mode_enter = 0 ;
	u8_wakeup_bcm_timer = 0;
	u8_wakeup_cnt = 0;
	u8_wakeup_timer = 0;
	
	u8_lin_cmd_sleep = 0;
	u8_auto_roof_rain_measure_sleep_flg = 0;
	u8_wakeup_bcm_cnt_sleep_flg = 0;
}
