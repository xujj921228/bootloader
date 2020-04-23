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
#include "lin.h"
#include "lin_cfg.h"
#include "lin_diagnostic_service.h"
#include "lin_app.h"
#include "local_eep_data.h"

extern Main_Fsm_t  RLS_RunMode;
extern local_info_t local_info;
extern struct BCM_Frame         Lin_BCM_Frame;

const  uint8 Software_Versions[3] = {0x00, 0x01, 0x03};
const  uint8 Hardware_Versions[3] = {0x00, 0x01, 0x00};

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
    	8400, //dc_stage1
        8600, //dc_stage2
        8900, //dc_stage3
        9100, //dc_stage4
        
        100,  //stage_intensity1
        120,  //stage_intensity2
        160,  //stage_intensity3
        250,  //stage_intensity4
        300,  //stage_intensity5
        
        8, // meas_avg_cnt
        
        6,//park position  high_speed meas timer
        12,//park position high_speed meas timer
        6,// park position low_speed meas timer
        20,//park position low_speed meas timer

        80, // park_timer(u8_Rain_Sensitivity = 4)
        3,  // park_enter_low_th;
        4,  // park_enter_high_th;

        60, // int_delay_timer;
        
        3,  // int_enter_period_cnt;
        50, // int_enter_low_cnt; 
         
        10,  //period_enter_low_cnt; //25
        4,  //period_enter_low_th;
        
        40, //low_delaytimer41;    (u8_Rain_Sensitivity = 4)
        25, //low_enter_high_cnt41;
        100, //low_delaytimer42;
        30, //low_enter_high_cnt42;
        120, //low_delaytimer43;
        25, //low_enter_high_cnt43;
        
        40, //low_delaytimer31;    (u8_Rain_Sensitivity = 3)
        25, //low_enter_high_cnt31;
        100, //low_delaytimer32;
        30, //low_enter_high_cnt32;
        120, //low_delaytimer33;
        28, //low_enter_high_cnt33;
        
        40, //low_delaytimer21;    (u8_Rain_Sensitivity = 2)
        28, //low_enter_high_cnt21;
        100, //low_delaytimer22;
        32, //low_enter_high_cnt22;
        120, //low_delaytimer23;
        30, //low_enter_high_cnt23;
        
        40, //low_delaytimer11;    (u8_Rain_Sensitivity = 1)
        28, //low_enter_high_cnt11;
        100, //low_delaytimer12;
        35, //low_enter_high_cnt12;
        120, //low_delaytimer13;
        32, //low_enter_high_cnt13;
        
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
} ;


tLight_Stastegy_Config const  Light_Stastegy_Parameter[1] =
{
        55,  //off_timer
        350, //Lowbean_on_th
        1000, //Lowbean_off_th
        350, //PositionLamp_on_th
        1000  //PositionLamp_off_th
} ;


void Globle_parameter_Init(void)
{
	uint8 temp_data[1],i;
	 
 	Get_All_data_From_EEPROM();
 	while(local_info.mark != FMARK)
 	{
 		local_info.NUMBER0 = 0xF185;                         //0.1.2
 		local_info.NUMBER1 = xF186;                         //3.4.5
 		local_info.NUMBER2 = xF187;                        //6.7.8
 		local_info.NUMBER3 = xF188;                        //9.10.11
 		local_info.Brightness_Light_Percentage = 100;;         //12
 		local_info.Brightness_Infrared_Percentage = 100;      //13
 		local_info.A_DAC_EEPdtata = Mlx75308_Config_Parameter[0].dac_a_default;                     //14
 		local_info.B_DAC_EEPdtata = Mlx75308_Config_Parameter[0].dac_b_default;                      //15
 		local_info.A_RAIN_ADC_EEPdtata;                //16.17
 		local_info.B_RAIN_ADC_EEPdtata;                //18.19
 		local_info.EEPmark;                            //20.21
 		
 		Set_Data_To_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,local_info.array,LOCAL_SIZE);
 		Get_All_data_From_EEPROM();
 	}
	
	/**************Set ProType and Param****************************/
	    	
	for (i = 0;i < LIGHT_TYPE ; i++)
	{
		Light_on_cnt[i] = 0; 
		Light_off_cnt[i] = 0;  
	}
			
	u8_light_on_req = 0;     
	//l_bool_wr_LI0_RLS_LightRequest(u8_light_on_req);
	
	l_bool_wr_LI0_RLS_RainSensorError(0);
	l_bool_wr_LI0_RLS_LightSensorError(0);
	//l_u8_wr_LI0_RLS_VotalgeError(0);
	
	Lin_BCM_Frame.BCM_WiperSwitch = 4;
	u8_Wipe_Automatic_On_Pre = 1;
	
	Lin_BCM_Frame.BCM_Ignition = 1;
	u16_SPD_Vehicle =  0;
	
	u8_MsgCounter = 0;
	
	diagnostic_Session = DIAGSRV_SESSION_DEFAULT;
        diagnostic_Session_timer = 0 ;
        diagnostic_Session_flg = 0;
    
        RLS_RunMode = MAIN_SLEFADAPT;
    
        Lin_Busy_Flag = 0;
    
        u8_Rain_Delta =  RAIN_DELTA;
    
        Rain_Sensitivity = 7;
        u8_Rain_SensitivityPre = 7;
    
	u8_IntSpeedCnt = 0;
	u8_IntSpeedEnterCnt = 0;	
	
	u8_wakeup_timer = 0;
	
	u8_lin_cmd_sleep = 0;
	u8_auto_roof_rain_measure_sleep_flg = 0;
	u8_wakeup_bcm_cnt_sleep_flg = 0;
	u16_RainWindow_Cnt = 0;
	u8_enter_period_cnt = 0;
	u8_enter_period_flg = 0;
	u8_Rain_Flg = 0;
	u8_Vehicle_State = 0;
	u8_Vehicle_State_Pre = 0;
	u16_IntWindow_Cnt = 0;
	u8_Int_Cnt = 0;
	
	u8_Lin_Diag_Enable = 0;
	u8_Lin_Diag_Enable_Cnt = 0;
}
