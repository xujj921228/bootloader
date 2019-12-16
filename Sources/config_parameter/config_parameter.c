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
    }
} ;

tRain_Stastegy_Config const  Rain_Stastegy_Parameter[1] =
{
    {
        7900, //dc_stage1
        8500, //dc_stage2
        8900, //dc_stage3
        9100, //dc_stage4
        
        80,  //stage_intensity1
        100,  //stage_intensity2
        150,  //stage_intensity3
        200,  //stage_intensity4
        250,  //stage_intensity5
        
        16, // meas_avg_cnt
        
        4,//park position  high_speed meas timer
        16,//park position high_speed meas timer
        4,// park position low_speed meas timer
        26,//park position low_speed meas timer

        40, // park_timer(u8_Rain_Sensitivity = 4)
        2,  // park_enter_low_th;
        11,  // park_enter_high_th;

        30, // int_delay_timer;
        
        3,  // int_enter_period_cnt;
        30, // int_enter_low_cnt; 
         
        5, //period_enter_low_cnt;
        2,  //period_enter_low_th;
        
        20, //low_delaytimer41;    (u8_Rain_Sensitivity = 4)
        30, //low_enter_high_cnt41;
        70, //low_delaytimer42;
        30, //low_enter_high_cnt42;
        90, //low_delaytimer43;
        20, //low_enter_high_cnt43;
        
        20, //low_delaytimer31;    (u8_Rain_Sensitivity = 3)
        40, //low_enter_high_cnt31;
        70, //low_delaytimer32;
        30, //low_enter_high_cnt32;
        90, //low_delaytimer33;
        20, //low_enter_high_cnt33;
        
        20, //low_delaytimer21;    (u8_Rain_Sensitivity = 2)
        40, //low_enter_high_cnt21;
        70, //low_delaytimer22;
        30, //low_enter_high_cnt22;
        90, //low_delaytimer23;
        20, //low_enter_high_cnt23;
        
        20, //low_delaytimer11;    (u8_Rain_Sensitivity = 1)
        40, //low_enter_high_cnt11;
        70, //low_delaytimer12;
        30, //low_enter_high_cnt12;
        90, //low_delaytimer13;
        20, //low_enter_high_cnt13;
        
        30, //high_delaytimer41;    (u8_Rain_Sensitivity = 4)
        5, //high_hold_th41;
        60, //high_delaytimer42;
        3, //high_hold_th42;
        70, //high_delaytimer43;
        3, //high_hold_th43;
        
        30, //high_delaytimer31;    (u8_Rain_Sensitivity = 3)
        5, //high_hold_th431;
        60, //high_delaytimer32;
        3, //high_hold_th32;
        70, //high_delaytimer33;
        3, //high_hold_th33;
        
        30, //high_delaytimer21;    (u8_Rain_Sensitivity = 2)
        5, //high_hold_th21;
        60, //high_delaytimer22;
        3, //high_hold_th22;
        70, //high_delaytimer23;
        3,//high_hold_th23;
        
        30,// high_delaytimer11;    (u8_Rain_Sensitivity = 1)
        5,// high_hold_th11;
        60,// high_delaytimer12;
        3,// high_hold_th12;
        70,// high_delaytimer13;
        3,// high_hold_th13; 
    }
} ;


tLight_Stastegy_Config const  Light_Stastegy_Parameter[1] =
{
    {
        55,  //off_timer
        100, //Lowbean_on_th
        120, //Lowbean_off_th
        130, //PositionLamp_on_th
        150  //PositionLamp_off_th
    }
} ;


void Globle_parameter_Init(void)
{
	uint8 temp_data[1];
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
  
	    	
	Light_cnt[LIGHT] = 0;
	Light_cnt[TWILIGHT] = 0;
			
	u8_light_on_req = 0;     
	u8_light_on_invent_req = 1; 
	u8_twilight_on_req = 0;     
	u8_twilight_on_invent_req = 1; 
	
	l_bool_wr_LI0_Light_On(u8_light_on_req);
	l_bool_wr_LI0_Light_On_Invers(u8_light_on_invent_req);
	
	l_bool_wr_LI0_Twilight_On(u8_twilight_on_req);
	l_bool_wr_LI0_Twilight_On_Invers(u8_twilight_on_invent_req);
	
	l_bool_wr_LI0_LS_Error(0);
	l_bool_wr_LI0_LIN_Error(0);	
	
	Lin_BCM_02_Frame.ParkPosition = 1;
	Lin_BCM_01_Frame.SCS_Automatic = 1;
	u8_Wipe_Automatic_On_Pre = 1;
	
	Lin_BCM_01_Frame.Ignition = 1;
	Lin_BCM_01_Frame.SCS_Automatic = 1;
	Lin_BCM_01_Frame.SPD_Vehicle =  0;
	
	u8_MsgCounter = 0;
	
	diagnostic_Session = DIAGSRV_SESSION_DEFAULT;
    diagnostic_Session_timer = 0 ;
    diagnostic_Session_flg = 0;
    
    RLS_RunMode = SLEFADAPT;
    
    Lin_Busy_Flag = 0;
    
    u8_Rain_Delta =  RAIN_DELTA;
    
    Rain_Sensitivity = 9;
    u8_Rain_SensitivityPre = 9;
    
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
