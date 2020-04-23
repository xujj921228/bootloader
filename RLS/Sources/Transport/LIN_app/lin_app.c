/******************************************************************************
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
extern uint8 u8_RLS_WindowCloseReq;
extern uint8  u8_Solar_r_value;
extern uint8  u8_Solar_l_value;
extern struct BCM_Frame         Lin_BCM_Frame;
/*******************************************************
 * FUNCTION NAME : Lin_Sys_Init()
 *   DESCRIPTION : Lin_Sys_Init  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Lin_Sys_Init(void)
{
	uint8 vector_number = 0;
	
        l_sys_init();
	l_ifc_init(LI0);
	
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
	
	Lin_BCM_Frame.BCM_WiperPosition =  l_bool_rd_LI0_BCM_WiperPosition();
	Lin_BCM_Frame.BCM_WiperSwitch = l_u8_rd_LI0_BCM_WiperSwitch();
	Lin_BCM_Frame.BCM_Washer = l_bool_rd_LI0_BCM_Washer();
	Lin_BCM_Frame.BCM_WindowStatus = l_bool_rd_LI0_BCM_WindowStatus();
	Lin_BCM_Frame.BCM_Ignition = l_bool_rd_LI0_BCM_Ignition();
	Lin_BCM_Frame.BCM_RainSensitivity =  l_u8_rd_LI0_BCM_RainSensitivity();
	Lin_BCM_Frame.BCM_Transmision550nm = l_u8_rd_LI0_BCM_Transmision550nm();
	Lin_BCM_Frame.BCM_Transmision880nm = l_u8_rd_LI0_BCM_Transmision880nm();
	Lin_BCM_Frame.BCM_VehicleSpeed = l_u16_rd_LI0_BCM_VehicleSpeed();
	
	u16_SPD_Vehicle =  Lin_BCM_Frame.BCM_VehicleSpeed /100 ;
	
	RLS_Wipe_Park_Process();
	
	switch(Lin_BCM_Frame.BCM_RainSensitivity)
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
	RLS_Wipe_Auto_On_Function();
	RLS_Wipe_Sensitivity_Up_Function();
	
	if((Mnrval.IR_A >= 0xFFFF) || (Mnrval.IR_B >= 0xFFFF)||(u8_Battery_status == VOLTAGE_LOW)||(u8_Lin_Diag_Enable == 0))
	{
		u8_WiperSpeed = 0;
	}
	
	l_u8_wr_LI0_RLS_WiperRequest(u8_WiperSpeed);
	l_bool_wr_LI0_RLS_RainSensorError(0);
	l_bool_wr_LI0_RLS_WindowCloseReq(u8_RLS_WindowCloseReq);
	l_bool_wr_LI0_RLS_LightSensorError(0);
	l_bool_wr_LI0_RLS_LightRequest(u8_light_on_req);
	l_u8_wr_LI0_RLS_VotalgeError(u8_Battery_status);
	//here lost one lin error
	l_u16_wr_LI0_RLS_FW_value(u16_Brightness_FW);
	l_u16_wr_LI0_RLS_Amb_value(u16_Brightness_UP);
	
	l_u8_wr_LI0_RLS_Solar_Left(u8_Solar_l_value);
	l_u8_wr_LI0_RLS_Solar_Right(u8_Solar_r_value);
	
}

void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}