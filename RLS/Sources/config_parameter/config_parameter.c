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
* @author    xujun
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


const uint8 lin_Spare_Part_Number[LIN_SPARE_PART_NUMBER_LENTH]= {0x38,0x30,0x33,0x30,0x30,0x30,0x30,0x32,0x39,0x41,0x41,0x20,0x20};
const uint8 lin_Vehicle_Soft_Version[LIN_VEHICLE_SOFT_VERSION_LENTH]= {0x30,0x30,0x2E,0x30,0x33,0x2E,0x30,0x32};
const uint8 lin_Vehicle_Hard_Version[LIN_VEHICLE_HARD_VERSION_LENTH]= {0x30,0x2E,0x32,0x2E,0x30};
const uint8 lin_Supplier_ID[LIN_SUPPLIER_ID_LENTH]= {0x39,0x48,0x48};
const uint8 lin_Manufact_Data[LIN_MANUFACT_DATA_LENTH]= {0x20,0x20,0x20};
const uint8 lin_Ecu_Serial[LIN_ECU_SERIAL_LENTH]= {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
const uint8 lin_Supplier_Soft_Version[LIN_SUPPLIER_SOFT_VERSION_LENTH]= {0x32,0x2E,0x30,0x20,0x20,0x20,0x20,0x20,0x20};
const uint8 lin_Supplier_Hard_Version[LIN_SUPPLIER_HARD_VERSION_LENTH]= {0x31,0x2E,0x30,0x20,0x20,0x20,0x20,0x20,0x20};

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
			12,//park position high_speed meas timer
			4,// park position low_speed meas timer
			20,//park position low_speed meas timer
		
			80, // park_timer(u8_Rain_Sensitivity = 4)
			3,  // park_enter_low_th;
			4,  // park_enter_high_th;

			60, // int_delay_timer;
			
			3,  // int_enter_period_cnt;
			50, // int_enter_low_cnt; 
			 
			10,  //period_enter_low_cnt; //25
			5,  //period_enter_low_th;
			
			40, //low_delaytimer41;    (u8_Rain_Sensitivity = 4)
			40, //low_enter_high_cnt41;
			80, //low_delaytimer42;
			38, //low_enter_high_cnt42;
			100, //low_delaytimer43;
			35, //low_enter_high_cnt43;
			
			40, //low_delaytimer31;    (u8_Rain_Sensitivity = 3)
			45, //low_enter_high_cnt31;
			80, //low_delaytimer32;
			40, //low_enter_high_cnt32;
			100, //low_delaytimer33;
			38, //low_enter_high_cnt33;
			
			40, //low_delaytimer21;    (u8_Rain_Sensitivity = 2)
			50, //low_enter_high_cnt21;
			80, //low_delaytimer22;
			45, //low_enter_high_cnt22;
			100, //low_delaytimer23;
			40, //low_enter_high_cnt23;
			
			40, //low_delaytimer11;    (u8_Rain_Sensitivity = 1)
			55, //low_enter_high_cnt11;
			80, //low_delaytimer12;
			50, //low_enter_high_cnt12;
			100, //low_delaytimer13;
			45, //low_enter_high_cnt13;
			
			40, //high_delaytimer41;    (u8_Rain_Sensitivity = 4)
			5, //high_hold_th41;
			80, //high_delaytimer42;
			5, //high_hold_th42;
			100, //high_delaytimer43;
			5, //high_hold_th43;
			
			40, //high_delaytimer31;    (u8_Rain_Sensitivity = 3)
			5, //high_hold_th431;
			80, //high_delaytimer32;
			5, //high_hold_th32;
			100, //high_delaytimer33;
			5, //high_hold_th33;
			
			40, //high_delaytimer21;    (u8_Rain_Sensitivity = 2)
			5, //high_hold_th21;
			80, //high_delaytimer22;
			5, //high_hold_th22;
			100, //high_delaytimer23;
			5,//high_hold_th23;
			
			40,// high_delaytimer11;    (u8_Rain_Sensitivity = 1)
			5,// high_hold_th11;
			80,// high_delaytimer12;
			5,// high_hold_th12;
			100,// high_delaytimer13;
			5,// high_hold_th13; 
    }
} ;


tLight_Stastegy_Config const  Light_Stastegy_Parameter[1] =
{
    {
        55,  //off_timer
        166, //Lowbean_on_th
        266, //Lowbean_off_th
        166, //PositionLamp_on_th
        266  //PositionLamp_off_th
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
	u8_twilight_on_req = 0;     
	

	
	Lin_BCM3_Frame.FrontWiperPosition = 0;
	Lin_BCM3_Frame.FrontWiperSwitch = 1;
	u8_Wipe_Automatic_On_Pre = 1;
	
	Lin_BCM1_Frame.STAT_Terminal = 2;
	Lin_BCM2_Frame.RoofStatus = 1;
	Lin_BCM1_Frame.remote = 0;
	u16_SPD_Vehicle =  0;
	u8_AmbientTemp = 120;
	
	
	diagnostic_Session = DIAGSRV_SESSION_DEFAULT;
    diagnostic_Session_timer = 0 ;
    diagnostic_Session_flg = 0;
    
    RLS_RunMode = SLEFADAPT;
       
    u8_Rain_Delta =  RAIN_DELTA;
    
    Rain_Sensitivity = 4;
    u8_Rain_SensitivityPre = 4;
    
	u8_IntSpeedCnt = 0;
	u8_IntSpeedEnterCnt = 0;	
	
	u8_Sleep_16h_flg = 0;
	u16_wakeup_16h_cnt = 0;
	u8_polling_mode_enter = 0 ;
	u8_wakeup_bcm_timer = 0;
	u8_wakeup_cnt = 0;
	u8_wakeup_timer = 0;
	
	u8_rain_state_exit_polling_flg = 0;
	
	u8_lin_cmd_sleep = 0;
	u8_auto_roof_rain_measure_sleep_flg = 0;
	u8_wakeup_bcm_1min_flg = 0;
	
	u8_Tunnel_Detect_pre_flg = 0;
	u8_Tunnel_Detect_flg = 0;
	u8_LightOnReason = 0;
	u8_LightMode = 0;
	u8_RainDayGlobalCloseCmd = 0;
	u8_WiperSpeed = 0 ;
	u8_hud_factor = 0;
	u8_hud_value = 0;
	
	u16_RainWindow_Cnt = 0;
	u8_enter_period_cnt = 0;
	u8_enter_period_flg = 0;
	u8_Rain_Flg = 0;
	
	u8_Vehicle_State = 0;
	u8_Vehicle_State_Pre = 0;
	u16_IntWindow_Cnt = 0;
	u8_Int_Cnt = 0;

	/* add intia*/	
	l_u8_wr_LI0_WiperSpeed(u8_WiperSpeed);
	l_bool_wr_LI0_STAT_RS(1);
	l_bool_wr_LI0_STAT_RSError(0);
	l_bool_wr_LI0_LightOnReq(u8_light_on_req);
	l_u8_wr_LI0_STAT_DayNightMode(u8_LightMode);
	l_bool_wr_LI0_STAT_LS(1);
	l_bool_wr_LI0_STAT_LSError(0);
	l_u8_wr_LI0_LightOnReason(u8_LightOnReason);
	l_u8_wr_LI0_HUDBrightnessUnit(u8_hud_factor);
	l_u8_wr_LI0_HUDBrightnessRawValue(u8_hud_value);
	l_bool_wr_LI0_RainDayGlobalClose(u8_RainDayGlobalCloseCmd);
	
}
