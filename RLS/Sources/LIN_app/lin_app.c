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
	l_u8_wr_LI0_RLS_MsgCounter(u8_MsgCounter);
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
	
	Lin_BCM_Frame.Status_IGN = l_u8_rd_LI0_BCM_Status_IGN();
	Lin_BCM_Frame.CMD_AutoWiper = l_bool_rd_LI0_BCM_CMD_AutoWiper();
	Lin_BCM_Frame.RQ_FrontWash =  l_bool_rd_LI0_BCM_RQ_FrontWash();
	Lin_BCM_Frame.ParkPosition =  l_bool_rd_LI0_BCM_ParkPosition();
	Lin_BCM_Frame.RainSensitivity =  l_u8_rd_LI0_BCM_RainSensitivity();
	Lin_BCM_Frame.CMD_AutoLight =  l_bool_rd_LI0_BCM_CMD_AutoLight();
	Lin_BCM_Frame.BladesTurningPoint =  l_bool_rd_LI0_BCM_BladesTurningPoint();
	Lin_BCM_Frame.RoofStatus =  l_bool_rd_LI0_BCM_RoofStatus();
	Lin_BCM_Frame.OutsideTemp =  l_u8_rd_LI0_BCM_OutsideTemp();
	
	tempspd =  l_u16_rd_LI0_BCM_SPD_Vehicle() ;
	u16_SPD_Vehicle =  (tempspd * 9) /160 ;
	RLS_Wipe_Park_Process();
	
	switch(Lin_BCM_Frame.RainSensitivity)
	{
		case 0: u8_Rain_Sensitivity = 1;break;
		case 1: u8_Rain_Sensitivity = 1;break;                                 
		case 2: u8_Rain_Sensitivity = 2;break;
		case 3: u8_Rain_Sensitivity = 2;break;
		case 4: u8_Rain_Sensitivity = 3;break;
		case 5: u8_Rain_Sensitivity = 3;break;
		case 6: u8_Rain_Sensitivity = 4;break;

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
	uint8 RainIntensity_Temp ;
	
	
	
	//RLS_Wipe_Auto_On_Function();
	//RLS_Wipe_Sensitivity_Up_Function();
	
	if((Mnrval.IR_A >= 0xFFFF) || (Mnrval.IR_B >= 0xFFFF)||(u8_Battery_status == VOLTAGE_LOW)||(u8_Lin_Diag_Enable == 0))
	{
		u8_WiperSpeed = 0;
	}
	
	l_u8_wr_LI0_RLS_RQ_WiperSPD(u8_WiperSpeed);

	l_bool_wr_LI0_RLS_RQ_LowBeam(u8_light_on_req);
	l_bool_wr_LI0_RLS_RQ_PositionLamp(u8_twilight_on_req);
		
	l_u16_wr_LI0_RLS_Brightness_FW(u16_Brightness_FW);
	l_u8_wr_LI0_RLS_Brightness_IR_L(u8_Brightness_IR);
	l_u8_wr_LI0_RLS_Brightness_IR_R((uint8)(Mnrval.DC_bre_A>>8));
	
	if(u8_Rain_Value >= 10)  RainIntensity_Temp = 10 ;
	else                     RainIntensity_Temp = u8_Rain_Value ;
	l_u8_wr_LI0_RLS_Rain_Intensity(RainIntensity_Temp);
	
	l_bool_wr_LI0_RLS_Fault_Rain(App_Rls_Error.RS_Error);
	l_bool_wr_LI0_RLS_Fault_Light((App_Rls_Error.LS_Error)|(App_Rls_Error.IR_Error));
	l_u8_wr_LI0_RLS_VOLT_Error(u8_Battery_status);
	l_bool_wr_LI0_RLS_Humid_Temp_Error(u8_Rain_Valid);
	
	l_u8_wr_LI0_RLS_Temperature(Mnrval.IR_A);
	l_u8_wr_LI0_RLS_Humid(Mnrval.IR_A>>8);
}

void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}
