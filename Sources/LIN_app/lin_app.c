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
	l_u8_wr_LI0_SensorMsgCounter(u8_MsgCounter);
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
	uint8 temp;
	uint16 tempspd;
	Lin_BCM_01_Frame.Ignition = l_bool_rd_LI0_Ignition();
	Lin_BCM_01_Frame.SCS_Automatic = l_bool_rd_LI0_SCS_Automatic();
	Lin_BCM_01_Frame.SPD_Vehicle =  l_u8_rd_LI0_VehicleSpeed();
	
	tempspd =  Lin_BCM_01_Frame.SPD_Vehicle ;
	u16_SPD_Vehicle =  (tempspd * 64) /25 ;
	
	Lin_BCM_01_Frame.Status_SMA =   l_u8_rd_LI0_Status_SMA();
	Lin_BCM_01_Frame.SCS_FrontWash = l_bool_rd_LI0_SCS_FrontWash();
	Lin_BCM_01_Frame.LS_Sensitivity = l_u8_rd_LI0_LS_Sensitivity();
	Lin_BCM_01_Frame.RS_Deactivation = l_bool_rd_LI0_RS_Deactivation();
	Lin_BCM_01_Frame.SCS_IntervalLevel = l_u8_rd_LI0_SCS_IntervalLeve();
	Lin_BCM_01_Frame.RS_Sensitivity =  l_u8_rd_LI0_RS_Sensitivity();
	
	Lin_BCM_02_Frame.BladesTurningPoint = l_bool_rd_LI0_BladesTurningPoint();
	Lin_BCM_02_Frame.ParkPosition =  l_bool_rd_LI0_ParkPosition();
	Lin_BCM_02_Frame.Wiper_running =  l_bool_rd_LI0_Wiper_running();
	
	RLS_Wipe_Park_Process();
	
	/************************************************************
	            SCS_IntervalLeve  |  RS_Sensitivity  |   Rain_Sensitivity
	                   1          |        1         |         1
	                   1          |        3         |         2
	                   5          |        2         |         3
	                   5          |        3         |         4
	                   9          |        5         |         5
	                   13         |        2         |         6
	                   13         |        3         |         7
	                   13         |        5         |         8
	                   13         |        6         |         9                  
	    **************************************************************/
	    temp =  ((Lin_BCM_01_Frame.SCS_IntervalLevel << 4) & 0xF0) | (Lin_BCM_01_Frame.RS_Sensitivity & 0x07); 
	        
	    switch(temp)
	    {
			  case 0x11:
			  {
				Rain_Sensitivity = 1;
				u8_Rain_Sensitivity = 1;
			  }break;
			  case 0x13:
			  {
				Rain_Sensitivity = 2;
				u8_Rain_Sensitivity = 1;
			  }break;
			  case 0x52:
			  {
				Rain_Sensitivity = 3;
				u8_Rain_Sensitivity = 1;
			  }break;                                 
			  case 0x53:
			  {
				Rain_Sensitivity = 4;
				u8_Rain_Sensitivity = 2;
			  }break;
			  case 0x95:
			  {
				Rain_Sensitivity = 5;
				u8_Rain_Sensitivity = 3;
			  }break;
			  case 0xD2:
			  {
				Rain_Sensitivity = 6;
				u8_Rain_Sensitivity = 3;
			  }break;
			  case 0xD3:
			  {
				Rain_Sensitivity = 7;
				u8_Rain_Sensitivity = 3;
			  }break;
			  case 0xD5:
			  {
				Rain_Sensitivity = 8;
				u8_Rain_Sensitivity = 4;
			  }break;
			  case 0xD6:
			  {
				Rain_Sensitivity = 9;
				u8_Rain_Sensitivity = 4;
			  }break;
			  default:
			  {
				Rain_Sensitivity = 9;
				u8_Rain_Sensitivity = 4;
			  }break;             
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
	
	if((Mnrval.IR_A >= 0xFFFF) || (Mnrval.IR_B >= 0xFFFF))
	{
		u8_WiperSpeed = 0;
	}
	
	RLS_Wipe_Auto_On_Function();
	RLS_Wipe_Sensitivity_Up_Function();
	
	
	l_u8_wr_LI0_WiperSpeed(u8_WiperSpeed);

	l_bool_wr_LI0_Light_On(u8_light_on_req);
	l_bool_wr_LI0_Light_On_Invers(u8_light_on_invent_req);
	
	l_bool_wr_LI0_Twilight_On(u8_twilight_on_req);
	l_bool_wr_LI0_Twilight_On_Invers(u8_twilight_on_invent_req);
	
	l_u16_wr_LI0_Brightness_FW(u16_Brightness_FW);
	l_u8_wr_LI0_Brightness_IR_L(u8_Brightness_IR_Right);
	l_u8_wr_LI0_Brightness_IR_R(u8_Brightness_IR);
	
	if(u8_Rain_Value >= 10)  RainIntensity_Temp = 10 ;
	else                     RainIntensity_Temp = u8_Rain_Value ;
	l_u8_wr_LI0_RainIntensity(RainIntensity_Temp);
	
	l_bool_wr_LI0_RS_Error(App_Rls_Error.RS_Error);
	l_bool_wr_LI0_LS_Error((App_Rls_Error.LS_Error)|(App_Rls_Error.IR_Error));
}

void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}
