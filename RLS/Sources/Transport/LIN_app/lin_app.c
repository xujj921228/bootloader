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
#include "lin_app.h"
#include "lin.h"
#include "lin_cfg.h"
#include "ftm.h"
#include "spi.h"
#include "auto_humid.h"
#include "battery.h"
#include "auto_wiper.h"

/**************************
 * extern var  from battery
 * ************************/
extern Battery_status_t  Battery_status;;

extern uint16 u16_Brightness_FW,u16_Brightness_UP;
extern uint8  u8_Solar_r_value;
extern uint8  u8_Solar_l_value;

extern bool_t  Lin_Diag_Enable;
extern  MLX75308_Mnrval_t      Mnrval;

bool_t Lin_Busy_Flag;

RLS1_Frame_t        Lin_RLS1_frame;
BCM_Frame_t         Lin_BCM_Frame;



//this frame is for APP 
RLS_APP_Value_t     RLS_APP_Value;
BCM_APP_Value_t     BCM_APP_Value;

void Lin_Var_Init(void)
{
	BCM_APP_Value.u16_SPD_Vehicle =  0;
	Lin_Busy_Flag = FALSE;
	
	RLS_APP_Value.APP_Reset = FALSE;
	
	
}
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
	Lin_Busy_Flag = TRUE;	
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
	
	Lin_BCM_Frame.BCM_Status_IGN = l_u8_rd_LI0_BCM_Status_IGN();  
	Lin_BCM_Frame.BCM_CMD_AutoWiper = l_bool_rd_LI0_BCM_CMD_AutoWiper();
	Lin_BCM_Frame.BCM_RQ_FrontWash =  l_bool_rd_LI0_BCM_RQ_FrontWash();
	Lin_BCM_Frame.BCM_ParkPosition =  l_bool_rd_LI0_BCM_ParkPosition();
	Lin_BCM_Frame.BCM_RainSensitivity =  l_u8_rd_LI0_BCM_RainSensitivity();
	Lin_BCM_Frame.BCM_CMD_AutoLight =  l_bool_rd_LI0_BCM_CMD_AutoLight();
	Lin_BCM_Frame.BCM_BladesTurningPoint = l_bool_rd_LI0_BCM_BladesTurningPoint();
	Lin_BCM_Frame.BCM_RoofStatus =  l_bool_rd_LI0_BCM_RoofStatus();
	Lin_BCM_Frame.BCM_SPD_Vehicle = l_u16_rd_LI0_BCM_SPD_Vehicle();
	Lin_BCM_Frame.LI0_BCM_OutsideTemp = l_u8_rd_LI0_BCM_OutsideTemp();
	
	RLS_APP_Get_Data();
}
/*******************************************************
 * FUNCTION NAME : RLS_APP_Get_Data()
 *   DESCRIPTION :   
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_APP_Get_Data(void)
{
	/***************************************
	 * 
	 * APP  get WiperPosition from bcm
	 * *************************************/
	
	if(Lin_BCM_Frame.BCM_ParkPosition == WiperPosition_Parked)
	{
		BCM_APP_Value.BCM_WiperPosition = APP_WiperPosition_Parked;
	}
	else
	{
		BCM_APP_Value.BCM_WiperPosition =APP_WiperPosition_Not_Parked;
	}

	RLS_Wipe_Park_Process();
	
	/****************************
	 * 
	 * APP  Get 
	 * RainSensitivity  and 
	 * Automatic_On flag
	 * from bcm
	 * *************************************/
	switch(Lin_BCM_Frame.BCM_RainSensitivity)
	{
	
		case RainSensitivity_LV0:                        ;break;
		case RainSensitivity_LV1: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV1;break;                                 
		case RainSensitivity_LV2: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV1;break;
		case RainSensitivity_LV3: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV2;break;
		case RainSensitivity_LV4: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV2;break;
		case RainSensitivity_LV5: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV3;break;
		case RainSensitivity_LV6: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV3;break;
		default:
         BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV4;break;               
	}
	BCM_APP_Value.Single_Wipe_flag = FALSE;
	if(Lin_BCM_Frame.BCM_RainSensitivity > BCM_APP_Value.Pre_BCM_RainSensitivity)
	{
		BCM_APP_Value.Single_Wipe_flag = TRUE;
	}
	BCM_APP_Value.Pre_BCM_RainSensitivity = Lin_BCM_Frame.BCM_RainSensitivity;
	/****************************
	 * 
	 * APP  Get VehicleSpeed  from bcm
	 * *************************************/
	BCM_APP_Value.u16_SPD_Vehicle =  Lin_BCM_Frame.BCM_SPD_Vehicle ;
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
	//RLS_Single_Wipe_Function();
	RLS_APP_Send_data();	
}

/*******************************************************
 * FUNCTION NAME : RLS_APP_Send_Data()
 *   DESCRIPTION : Lin_RLS_data  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_APP_Send_data(void)
{
	/**********************************************************
	 * RLS_MsgCounter
	 * ********************************************************/
	Lin_RLS1_frame.RLS_MsgCounter =  1;
	/**********************************************************
	 * Diagnnostic  Req
	 * *******************************************************/
	/*if(RLS_APP_Value.APP_DiagnnosticReq == APP_Diagnnostic_Req)
	{
		Lin_RLS1_frame = Diagnnostic_Req;
	}
	else
	{
		Lin_RLS1_frame.RLS_DiagnnosticReq = NO_Diagnnostic_Req;
	}*/
	/**********************
	 * DATA for WIPE
	 * *****************************/
	if( RLS_APP_Value.RLS_APP_WiperSpeed == WiperSpeed_Off)
	{
		Lin_RLS1_frame.RLS_RQ_WiperSPD = Wiper_Request_Off;
	}
	else if ((RLS_APP_Value.RLS_APP_WiperSpeed == WiperSpeed_Low)||
			(RLS_APP_Value.RLS_APP_WiperSpeed == WiperSpeed_Single))
	{
		Lin_RLS1_frame.RLS_RQ_WiperSPD = Wiper_Request_Low;
	}
	else
	{
		Lin_RLS1_frame.RLS_RQ_WiperSPD = Wiper_Request_High;
	}
	if((Mnrval.IR_[0] >= 0xFFFF) ||
			(RLS_APP_Value.Battery_status == VOLTAGE_LOW)||
			(Lin_Diag_Enable == 0) ||
			(Lin_BCM_Frame.BCM_RQ_FrontWash == BCM_Washering))
	{
		Lin_RLS1_frame.RLS_RQ_WiperSPD = Wiper_Request_Off;
	}

	
	/************************
	 * DATA_OF_LIGHT
	 * ******************************************/
	if(RLS_APP_Value.light_on_req == Light_On)
	{
		Lin_RLS1_frame.RLS_RQ_LowBeam = RLS_RQ_LowBeam_On;	
		Lin_RLS1_frame.RLS_RQ_PositionLamp = RLS_RQ_LowBeam_On;
	}
	else
	{
		Lin_RLS1_frame.RLS_RQ_LowBeam = RLS_RQ_LowBeam_Off;
		Lin_RLS1_frame.RLS_RQ_PositionLamp = RLS_RQ_LowBeam_Off;
	}
	
	/************************
	 * rain_ERR
	 * ******************************************/
	Lin_RLS1_frame.RLS_Fault_Rain =  RainSensor_Normal;
	
	/************************
	 * light_err
	 * ******************************************/
	Lin_RLS1_frame.RLS_Fault_Light =  LightSensor_Normal;
	/************************
	 * lin_ERR
	 * ******************************************/
	Lin_RLS1_frame.RLS_REP_Error =  RLS_REP_Normal;
	
	/************************
	 * battery_ERR
	 * ******************************************/
	Lin_RLS1_frame.RLS_VOLT_Error = RLS_VOLT_Normal;
	
	/************************
	 * Humid_Temp_err
	 * ******************************************/
	Lin_RLS1_frame.RLS_Humid_Temp_Error = RLS_Humid_Temp_Normal;
	
	/************************
	 * IR_L
	 * ******************************************/
	Lin_RLS1_frame.RLS_Brightness_IR_L = u16_Brightness_UP >>4;
	
	
	/************************ 
	 * FW
	 * ******************************************/
	Lin_RLS1_frame.RLS_Brightness_FW = u16_Brightness_FW>>2;
	
	
	/************************ 
	 * RLS_Rain_Intensity
	 * ******************************************/
	Lin_RLS1_frame.RLS_Rain_Intensity= 0x5;
	
	/************************ 
	 * RLS_Brightness_IR_R
	 * ******************************************/
	Lin_RLS1_frame.RLS_Brightness_IR_R = 0x5;
	
	/************************ 
	 * RLS_Temperature
	 * ******************************************/
	Lin_RLS1_frame.RLS_Temperature = 0x5;
	
	/************************ 
	 * RLS_Humid
	 * ******************************************/
	Lin_RLS1_frame.RLS_Humid = 0x5;
	
	
	
	//send  data to BCM
	l_u8_wr_LI0_RLS_MsgCounter(Lin_RLS1_frame.RLS_MsgCounter);
	l_u8_wr_LI0_RLS_RQ_WiperSPD(Lin_RLS1_frame.RLS_RQ_WiperSPD);
	l_bool_wr_LI0_RLS_RQ_LowBeam(Lin_RLS1_frame.RLS_RQ_LowBeam);
	l_bool_wr_LI0_RLS_RQ_PositionLamp(Lin_RLS1_frame.RLS_RQ_PositionLamp);
	l_bool_wr_LI0_RLS_Fault_Rain(Lin_RLS1_frame.RLS_Fault_Rain);
	l_bool_wr_LI0_RLS_Fault_Light(Lin_RLS1_frame.RLS_Fault_Light);
	l_bool_wr_LI0_RLS_REP_Error(Lin_RLS1_frame.RLS_REP_Error);
	l_u8_wr_LI0_RLS_VOLT_Error(Lin_RLS1_frame.RLS_VOLT_Error);
	l_bool_wr_LI0_RLS_Humid_Temp_Error(Lin_RLS1_frame.RLS_Humid_Temp_Error);
	l_u8_wr_LI0_RLS_Brightness_IR_L(Lin_RLS1_frame.RLS_Brightness_IR_L);
	l_u16_wr_LI0_RLS_Brightness_FW(Lin_RLS1_frame.RLS_Brightness_FW);
	l_u8_wr_LI0_RLS_Rain_Intensity(Lin_RLS1_frame.RLS_Rain_Intensity);
	l_u8_wr_LI0_RLS_Brightness_IR_R(Lin_RLS1_frame.RLS_Brightness_IR_R);
	l_u8_wr_LI0_RLS_Temperature(Lin_RLS1_frame.RLS_Temperature);
	l_u8_wr_LI0_RLS_Humid(Lin_RLS1_frame.RLS_Humid);
	
}

void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}
