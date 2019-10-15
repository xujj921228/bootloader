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
* @author    FPT Software
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
uint8 Lin_Busy_Flag;
uint8 Enter_Sleep_Flag;


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
	Lin_Busy_Flag = 1;
	G_4sFlag = 0;       //当接收到外界中断时则清除4s标志
	G_4s_counter = 0;   //当接收到外界中断时则清除4s计数	
	u16_window_cnt = 0; //当接收到外界中断时，24h计时器清零
}


/*******************************************************
 * FUNCTION NAME : message_cnt()
 *   DESCRIPTION : message_cnt  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void message_cnt(void)
{
	if(u8_MsgCounter >= 0x0f)
	{
		u8_MsgCounter = 0;
	}
	else
	{
		u8_MsgCounter++;
	}
	//l_u8_wr_LI0_RLS_MsgCounter(u8_MsgCounter);
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
	
	//修改：协议修改，灵敏度划分
	
	
	
	//uint8 temp;
	uint16 tempspd;
	
	Lin_BCM_WIPSW.Ignition 		 = l_u8_rd_LI0_Ignition();
	Lin_BCM_WIPSW.SCS_Automatic  = l_bool_rd_LI0_SCS_Automatic();
	Lin_BCM_WIPSW.S_Sens		 = l_u8_rd_LI0_S_SENS();
	Lin_BCM_WIPSW.Status_SMA     = l_u8_rd_LI0_Status_SMA();
	Lin_BCM_WIPSW.S_Wash		 = l_bool_rd_LI0_S_WASH();
	Lin_BCM_WIPSW.S_LOW          = l_bool_rd_LI0_S_LOW();
	Lin_BCM_WIPSW.S_High         = l_bool_rd_LI0_S_HIGH();
	Lin_BCM_WIPSW.S_Trans_550nm  = l_u8_rd_LI0_S_Trans_550nm();
	Lin_BCM_WIPSW.S_Trans_880nm  = l_u8_rd_LI0_S_Trans_880nm();
			
			
	Lin_BCM_MOTOR.ParkPosition   = l_bool_rd_LI0_ParkPosition();
	Lin_BCM_MOTOR.SPD_Vehicle    = l_u16_rd_LI0_VehicleSpeed();
	
	tempspd = Lin_BCM_MOTOR.SPD_Vehicle;
	u16_SPD_Vehicle = tempspd / 16;	
	
	u8_G_FW_Config = Lin_BCM_WIPSW.S_Trans_550nm;
	if(u8_G_FW_Config > 100 || u8_G_FW_Config == 0)
	{
		u8_G_FW_Config = 90;
	}
	u8_G_IR_Config = Lin_BCM_WIPSW.S_Trans_880nm;
	if(u8_G_IR_Config > 100 || u8_G_IR_Config == 0)
	{
		u8_G_IR_Config = 90;
	}
	
	
	u8_Rain_Sensitivity = Lin_BCM_WIPSW.S_Sens;
	Rain_Sensitivity = u8_Rain_Sensitivity;
	
	//RLS_Wipe_Park_Process();

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
	//修改：赋值部分，雨刮传出方式，标志位。
	
	uint8 RainIntensity_Temp ;
	
	if((Mnrval.IR_A >= 0xFFFF) || (Mnrval.IR_B >= 0xFFFF))
	{
		u8_WiperSpeed = 0;
	}
	
	RLS_Wipe_Auto_On_Function();
	RLS_Wipe_Sensitivity_Up_Function();
	
	if(Lin_BCM_WIPSW.Ignition >= 1)
	{
		if(u8_WiperSpeed == 0)
		{
			u8_Wip_low  = 0;
			u8_Wip_High = 0;
			//u8_Rain_Flg = 0;
			u8_Window_Flg = 0;
			u8_Window_CTL = 0;
		}
		else if(u8_WiperSpeed == 1)
		{
			u8_Wip_low  = 1;
			u8_Wip_High = 0;
			//u8_Rain_Flg = 1;
			u8_Window_Flg = 0;
			u8_Window_CTL = 0;
		}
		else if(u8_WiperSpeed == 2)
		{
			u8_Wip_low  = 0;
			u8_Wip_High = 1;
			//u8_Rain_Flg = 1;
			u8_Window_Flg = 0;
			u8_Window_CTL = 0;
		}		
		else 
		{
			u8_Wip_low  = 0;
			u8_Wip_High = 0;
			//u8_Rain_Flg = 0;
			u8_Window_Flg = 0;
			u8_Window_CTL = 0;
		}
	}
	
	else 
	{
		if(u8_Window_Flg == 1 && u8_WiperSpeed >= 1)
		{
			u8_Window_CTL = 1;
		}
	}
	
	if((Lin_BCM_WIPSW.SCS_Automatic == 0) && (Lin_BCM_WIPSW.S_Wash == 0) 
			&& (Lin_BCM_WIPSW.S_LOW == 0) && (Lin_BCM_WIPSW.S_High == 0))
	{
		u8_Wip_low  = 0;
		u8_Wip_High = 0;
		u8_Rain_Flg = 0;
	}
	

	
	if(App_Rls_Error.IR_Error == 1 || App_Rls_Error.LS_Error == 1 || App_Rls_Error.RS_Error == 1)
	{
		u8_Err_Flg = 1;
	}
	else 
	{
		u8_Err_Flg = 0;
	}
	
	l_bool_wr_LI0_S_COMMFAULT(0);
	l_bool_wr_LI0_S_Window_CMD(u8_Window_CTL);
	l_bool_wr_LI0_S_AUTO_Panel(u8_twilight_on_req);
	l_bool_wr_LI0_S_Auto_Lamp(u8_light_on_req);
	l_bool_wr_LI0_S_RS_FAULT(u8_Err_Flg);
	l_bool_wr_LI0_S_RAIN(u8_Rain_Flg);
	l_bool_wr_LI0_S_AUTO_H(u8_Wip_High);
	l_bool_wr_LI0_S_AUTO_L(u8_Wip_low);
	l_u8_wr_LI0_S_TRANS_550nm_RSP(u8_G_FW_Config);	
	//l_u8_wr_LI0_S_TRANS_550nm_RSP(u8_Brightness_IR);
	//l_u8_wr_LI0_S_TRANS_550nm_RSP(u8_MeasureSureTime);
	//l_u8_wr_LI0_S_TRANS_550nm_RSP((uint8)(Mnrval.IR_A));
	
	l_u8_wr_LI0_S_TRANS_880nm_RSP(u8_G_IR_Config);
	//l_u8_wr_LI0_S_TRANS_880nm_RSP((u16_Brightness_FW / 256));
	//l_u8_wr_LI0_S_TRANS_880nm_RSP((uint8)(Mnrval.IR_A >> 8));
	
	l_u8_wr_LI0_RLS_VotalgeError(u8_Battery_status);
	l_u8_wr_LI0_RLS_HumidSensorValue(Humid_Avg);	
	l_u8_wr_LI0_RLS_TempSensorValue(Temp_Avg);
	if(Dew_Point >= 1000) Dew_Point = 1000;
	l_u16_wr_LI0_RLS_TempDewPoint(Dew_Point);
	l_bool_wr_LI0_RLS_Humid_Temp_Error(Humid_Temp_Error);	
}

void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}
