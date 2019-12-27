/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      lin_app.c
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
#include "rls_app.h"
#include "lin_app.h"
#include "lin.h"
#include "lin_cfg.h"
#include "ftm.h"
#include "spi.h"
#include "humid.h"

uint8 u8_MsgCounter;

/*******************************************************
 * FUNCTION NAME : Lin_Busy_Process()
 *   DESCRIPTION : Lin_Busy_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Lin_Sys_Init(void)
{
	uint8 ret = 0 ;
	uint8 vector_number = 0;
	
    ret = l_sys_init();
	ret = l_ifc_init(LI0);
	
	vector_number = INT_UART0 -16;
	
	NVIC_ICPR |= 1 << (vector_number%32);
	NVIC_ISER |= 1 << (vector_number%32);
}

/*******************************************************
 * FUNCTION NAME : Lin_Busy_Process()
 *   DESCRIPTION : Lin_Busy_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Lin_Busy_Process(void)
{	
	G_4sFlag = 0;       //当接收到外界中断时则清除4s标志
	G_4s_counter = 0;   //当接收到外界中断时则清除4s计数			
}


/*******************************************************
 * FUNCTION NAME : LS_Analysis_Master_Data()
 *   DESCRIPTION : LS_Analysis_Master_Data  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 

void RLS_Analysis_Master_Data(void)
{ 	
	uint32 tempspd;
	
	Lin_BCM1_Frame.STAT_Terminal = l_u8_rd_LI0_STAT_Terminal();	
	Lin_BCM1_Frame.VehicleSpeedValid = l_u8_rd_LI0_VehicleSpeedValid();	
	
	tempspd =  l_u16_rd_LI0_vehicleSpeed() ;
	u16_SPD_Vehicle =  (tempspd * 3) /40 ;
	
	Lin_BCM3_Frame.FrontWasherSwitch = l_u8_rd_LI0_FrontWasherSwitch();
	Lin_BCM3_Frame.FrontWiperInterval = l_u8_rd_LI0_FrontWiperInterval();
	Lin_BCM3_Frame.FrontWiperPosition = l_bool_rd_LI0_FrontWiperPosition();
	Lin_BCM3_Frame.FrontWiperSwitch = l_u8_rd_LI0_FrontWiperSwitch();
	Lin_BCM3_Frame.MasterLightSwitch = l_u8_rd_LI0_MasterLightSwitch();
	
	Lin_BCM2_Frame.RoofStatus = l_u8_rd_LI0_WindowSunroofPosition();
	Lin_BCM2_Frame.remote =  l_bool_rd_LI0_STAT_RemoteControl();
	u8_AmbientTemp = l_u8_rd_LI0_AmbientTemp();

	switch(Lin_BCM3_Frame.FrontWiperInterval)
	{
		case 0: u8_Rain_Sensitivity = 1;break;
		case 1: u8_Rain_Sensitivity = 2;break;                                 
		case 2: u8_Rain_Sensitivity = 3;break;
		case 3: u8_Rain_Sensitivity = 4;break;

		default:u8_Rain_Sensitivity = 4;break;                
	}

	u8_Rain_Delta =  RAIN_DELTA;
}
/*******************************************************
 * FUNCTION NAME : Lin_RLS_data()
 *   DESCRIPTION : Lin_RLS_data  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Lin_RLS_data(void)
{	
	if((Mnrval.IR_A == 0xFFFF) || (Mnrval.IR_B == 0xFFFF)||(u8_Battery_status == VOLTAGE_LOW))
	{
		u8_WiperSpeed = 0;
	}
	
	if((Lin_BCM2_Frame.RoofStatus == 1)&&(Lin_BCM1_Frame.STAT_Terminal <= 3)&&(Lin_BCM1_Frame.STAT_Terminal >= 1))
	{
		u8_RainDayGlobalCloseCmd = 0;
	}
	
	RLS_Wipe_Auto_On_Function();
	RLS_Wipe_Sensitivity_Up_Function();
	RLS_Wash_Function();
	
	l_u8_wr_LI0_WiperSpeed(u8_WiperSpeed);
	l_bool_wr_LI0_STAT_RS(App_Rls_Error.RS_State);
	l_bool_wr_LI0_STAT_RSError(0);
	l_bool_wr_LI0_LightOnReq(u8_light_on_req);
	l_u8_wr_LI0_STAT_DayNightMode(u8_LightMode);
	l_bool_wr_LI0_STAT_LS(App_Rls_Error.LS_State);
	l_bool_wr_LI0_STAT_LSError(0);
	l_u8_wr_LI0_LightOnReason(u8_LightOnReason);
	l_u8_wr_LI0_HUDBrightnessUnit(u8_hud_factor);
	l_u8_wr_LI0_HUDBrightnessRawValue(u8_hud_value);
	l_bool_wr_LI0_RainDayGlobalClose(u8_RainDayGlobalCloseCmd);
	
	l_u8_wr_LI0_SolarIrradianceLeft(u8_Solar_l_value);
	l_u8_wr_LI0_SolarIrradianceRight(u8_Solar_r_value);
}

void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}
