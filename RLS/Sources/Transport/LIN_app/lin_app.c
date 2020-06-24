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

extern uint8  u8_Solar_r_value;
extern uint8  u8_Solar_l_value;

extern bool_t  Lin_Diag_Enable;
extern  MLX75308_Mnrval_t      Mnrval;

bool_t Lin_Busy_Flag;

RLS1_Frame_t        Lin_RLS1_frame;
BCM_Frame_t         Lin_BCM_Frame;
RLHS_Frame_t        Lin_RLHS_frame;
RLHS01_Frame_t      Lin_RLHS01_frame;


//this frame is for APP 
RLS_APP_Value_t     RLS_APP_Value;
BCM_APP_Value_t     BCM_APP_Value;

void Lin_Var_Init(void)
{
	BCM_APP_Value.u16_SPD_Vehicle =  0;
	Lin_Busy_Flag = FALSE;
	
	RLS_APP_Value.APP_Reset = FALSE;
	vehicle_start_Flag = FALSE;
	
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
	
	Lin_BCM_Frame.BCM_WiperPosition = (WiperPosition_t)l_bool_rd_LI0_BCM_WiperPosition();    
	Lin_BCM_Frame.BCM_Washer  = (BCM_Washer_t)l_bool_rd_LI0_BCM_Washer();		    
	Lin_BCM_Frame.BCM_Amb_LV = (BCM_Amb_LV_t)l_u8_rd_LI0_BCM_Amb_LV();
	Lin_BCM_Frame.BCM_RainSensitivity  = (RainSensitivity_t)l_u8_rd_LI0_BCM_RainSensitivity();	    
	Lin_BCM_Frame.BCM_VehicleSpeed = l_u8_rd_LI0_BCM_VehicleSpeed();
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
	
	if(Lin_BCM_Frame.BCM_WiperPosition == WiperPosition_Parked)
	{
		BCM_APP_Value.BCM_WiperPosition = APP_WiperPosition_Parked;
	}
	else
	{
		BCM_APP_Value.BCM_WiperPosition =APP_WiperPosition_Not_Parked;
	}

	/****************************
	 * 
	 * APP  Get 
	 * RainSensitivity  and 
	 * Automatic_On flag
	 * from bcm
	 * *************************************/
	switch(Lin_BCM_Frame.BCM_RainSensitivity)
	{
	
		case RainSensitivity_Off:                        ;break;
		case RainSensitivity_LV1: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV1;break;                                 
		case RainSensitivity_LV2: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV1;break;
		case RainSensitivity_LV3: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV2;break;
		case RainSensitivity_LV4: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV2;break;
		case RainSensitivity_LV5: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV3;break;
		case RainSensitivity_Low: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV3;break;
		default:
		case RainSensitivity_High: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV4;break;               
	}
	if(Lin_BCM_Frame.BCM_RainSensitivity > BCM_APP_Value.Pre_BCM_RainSensitivity)
	{
		BCM_APP_Value.Single_Wipe_flag = TRUE;
	}
	BCM_APP_Value.Pre_BCM_RainSensitivity = Lin_BCM_Frame.BCM_RainSensitivity;
	/****************************
	 * 
	 * APP  Get VehicleSpeed  from bcm
	 * *************************************/
	BCM_APP_Value.u16_SPD_Vehicle =  (uint16)(Lin_BCM_Frame.BCM_VehicleSpeed) * 2 ;
	
	if((BCM_APP_Value.u16_SPD_Vehicle < 2 )&&
		(Lin_BCM_Frame.BCM_SPD_Vehicle >= 2)&&
		(RLS_APP_Value.vehicle_start_Flag == TRUE))
	{
		RLS_APP_Value.vehicle_start_Flag = FALSE;
		BCM_APP_Value.Single_Wipe_flag = TRUE;
	}
	
	if(Wiper_State_Fsm != PARK_MODE)
	{
		BCM_APP_Value.Single_Wipe_flag = FALSE;
	}
	
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
	RLHS_APP_Send_data();
	RLHS01_APP_Send_data();	
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
	 * rain  continue
	 * ********************************************************/
	Lin_RLS1_frame.RLS_ContinuteReq =  Continue_Req;
	/**********************************************************
	 * Diagnnostic  Req
	 * *******************************************************/
	if(RLS_APP_Value.APP_DiagnnosticReq == APP_Diagnnostic_Req)
	{
		Lin_RLS1_frame.RLS_DiagnnosticReq = Diagnnostic_Req;
	}
	else
	{
		Lin_RLS1_frame.RLS_DiagnnosticReq = NO_Diagnnostic_Req;
	}
	/**********************************
	 * APP_Reset
	 * ********************************/
	if(RLS_APP_Value.APP_Reset == TRUE)
	{
		Lin_RLS1_frame.RLS_AppResetStatus = TRUE;
	}
	else
	{
		Lin_RLS1_frame.RLS_AppResetStatus = FALSE;
	}
	/**********************************
	 * APP_Configrationstatus 
	 * ********************************/
	Lin_RLS1_frame.RLS_AppConfigurationStatus = App_ConfigurationStatus;
	/************************************
	 * AppStatus
	 * **********************************/
	Lin_RLS1_frame.RLS_AppStatus = AppStatus_OK;
	
	/************************************
	 * lin_COM_STATUS
	 * **********************************/

	/**********************
	 * DATA for WIPE
	 * *****************************/
	if( RLS_APP_Value.RLS_APP_WiperSpeed == WiperSpeed_Off)
	{
		Lin_RLS1_frame.RLS_WiperRequest = Wiper_Request_Off;
	}
	else if ((RLS_APP_Value.RLS_APP_WiperSpeed == WiperSpeed_Low)||
			(RLS_APP_Value.RLS_APP_WiperSpeed == WiperSpeed_Single))
	{
		Lin_RLS1_frame.RLS_WiperRequest = Wiper_Request_Low;
	}
	else
	{
		Lin_RLS1_frame.RLS_WiperRequest = Wiper_Request_High;
	}
	if((Mnrval.IR_[0] >= 0xFFFF) ||
			(Mnrval.IR_[1] >= 0xFFFF)||
			(RLS_APP_Value.Battery_status == VOLTAGE_LOW)||
			(Lin_Diag_Enable == 0) ||
			(Lin_BCM_Frame.BCM_Washer == BCM_Washering))
	{
		Lin_RLS1_frame.RLS_WiperRequest = Wiper_Request_Off;
	}
	/************************
	 * DATA_OF_LIGHT
	 * ******************************************/
	if(RLS_APP_Value.light_on_req == Light_On)
	{
		Lin_RLS1_frame.RLS_Amb_LV = RLS_Amb_LV_Night;	
	}
	else
	{
		Lin_RLS1_frame.RLS_Amb_LV = RLS_Amb_LV_Day;
	}
	/************************
	 * RLS_ERR
	 * ******************************************/
	Lin_RLS1_frame.RLS_RainSensorError =  RainSensor_Normal;
	
	/************************
	 * light_Installed
	 * ******************************************/
	Lin_RLS1_frame.RLS_LightSensorInstalled =  LightSensor_Installed;
	/************************
	 * light_ERR
	 * ******************************************/
	Lin_RLS1_frame.RLS_LightSensorError =  LightSensor_Normal;
	
	/************************
	 * light_ERR
	 * ******************************************/
	Lin_RLS1_frame.RLS_HumiditySensorInstalled = HumiditySensor_Not_Installed;
	
	/************************
	 * LIGHT_Value
	 * ******************************************/
	Lin_RLS1_frame.RLS_Amb_Value =124;
	Lin_RLS1_frame.RLS_Amb_Value =125;
	
	
	
	//send  data to BCM
	l_bool_wr_LI0_RLS_ContinuteReq(Lin_RLS1_frame.RLS_ContinuteReq);
	l_bool_wr_LI0_RLS_DiagnnosticReq(Lin_RLS1_frame.RLS_DiagnnosticReq);
	l_bool_wr_LI0_RLS_AppResetStatus(Lin_RLS1_frame.RLS_AppResetStatus);
	l_bool_wr_LI0_RLS_AppConfigurationStatus(Lin_RLS1_frame.RLS_AppConfigurationStatus);
	l_bool_wr_LI0_RLS_AppStatus(Lin_RLS1_frame.RLS_AppStatus);
	l_u8_wr_LI0_RLS_LinComStatus((uint8)(Lin_RLS1_frame.RLS_LinComStatus));
	l_u8_wr_LI0_RLS_WiperRequest((uint8)(Lin_RLS1_frame.RLS_WiperRequest));
	l_u8_wr_LI0_RLS_Amb_LV((uint8)(Lin_RLS1_frame.RLS_Amb_LV));
	l_bool_wr_LI0_RLS_RainSensorError(Lin_RLS1_frame.RLS_RainSensorError);
	l_bool_wr_LI0_RLS_LightSensorInstalled(Lin_RLS1_frame.RLS_LightSensorInstalled);
	l_bool_wr_LI0_RLS_LightSensorError(Lin_RLS1_frame.RLS_LightSensorError);
	l_bool_wr_LI0_RLS_HumiditySensorInstalled(Lin_RLS1_frame.RLS_HumiditySensorInstalled);
	l_u8_wr_LI0_RLS_Amb_Value((uint8)(Lin_RLS1_frame.RLS_Amb_Value));
	l_u8_wr_LI0_RLS_FW_Value((uint8)(Lin_RLS1_frame.RLS_FW_Value));
	
	
}
void RLHS_APP_Send_data(void)
{
	
	/****************RLHS_COM_Continue_req*********/
	Lin_RLHS_frame.RLHS_COM_Continue_req = Continue_Req;
	/****************RLHS_Diagnostic_Req***********/
	if(RLS_APP_Value.APP_DiagnnosticReq == APP_Diagnnostic_Req)
	{
		Lin_RLHS_frame.RLHS_Diagnostic_Req = Diagnnostic_Req;
	}
	else
	{
		Lin_RLHS_frame.RLHS_Diagnostic_Req = NO_Diagnnostic_Req;
	}
	/****************RLHS_APP_Reset_Atatus*********/
	Lin_RLHS_frame.RLHS_APP_Reset_Atatus = NO_AppResetStatus_Req;
	/****************RLHS_APP_Configuration********/
	Lin_RLHS_frame.RLHS_APP_Configuration = App_ConfigurationStatus;
	/****************RLHS_APP_Status;**************/
	Lin_RLHS_frame.RLHS_APP_Status = AppStatus_OK;
	/****************RLHS_Comunicate_Status********/
	Lin_RLHS_frame.RLHS_Comunicate_Status = LinComStatus_No_detected_Fault;
	/****************RLHS_Humidity_Temp************/
	Lin_RLHS_frame.RLHS_Humidity_Temp = 0xffff;
	/****************RLHS_Humidity_Temp_Validity***/
	Lin_RLHS_frame.RLHS_Humidity_Temp_Validity = Validity;
	/****************RLHS_Sensor_Fault*************/
	Lin_RLHS_frame.RLHS_Sensor_Fault = RainSensor_Normal;
	/****************RLHS_Unused_bit***************/
	Lin_RLHS_frame.RLHS_Unused_bit = 0;
	/****************RLHS_Sensor_Humidity_Validity*/
	Lin_RLHS_frame.RLHS_Sensor_Humidity_Validity = Validity;
	/****************RLHS_Humindity_Value**********/
	Lin_RLHS_frame.RLHS_Humindity_Value = 0xff;
	
	

	l_bool_wr_LI0_RLHS_COM_Continue_req(Lin_RLHS_frame.RLHS_COM_Continue_req);
	l_bool_wr_LI0_RLHS_Diagnostic_Req(Lin_RLHS_frame.RLHS_Diagnostic_Req);
	l_bool_wr_LI0_RLHS_APP_Reset_Atatus(Lin_RLHS_frame.RLHS_APP_Reset_Atatus);
	l_bool_wr_LI0_RLHS_APP_Configuration(Lin_RLHS_frame.RLHS_APP_Configuration);
	l_bool_wr_LI0_RLHS_APP_Status(Lin_RLHS_frame.RLHS_APP_Status);
	l_u8_wr_LI0_RLHS_Comunicate_Status(Lin_RLHS_frame.RLHS_Comunicate_Status);
	l_u16_wr_LI0_RLHS_Humidity_Temp(Lin_RLHS_frame.RLHS_Humidity_Temp);
	l_bool_wr_LI0_RLHS_Humidity_Temp_Validity(Lin_RLHS_frame.RLHS_Humidity_Temp_Validity);
	l_bool_wr_LI0_RLHS_Sensor_Fault(Lin_RLHS_frame.RLHS_Sensor_Fault);
	l_u8_wr_LI0_RLHS_Unused_bit(Lin_RLHS_frame.RLHS_Unused_bit);
	l_bool_wr_LI0_RLHS_Sensor_Humidity_Validity(Lin_RLHS_frame.RLHS_Sensor_Humidity_Validity);
	l_u8_wr_LI0_RLHS_Humindity_Value(Lin_RLHS_frame.RLHS_Humindity_Value);
	
}
void RLHS01_APP_Send_data(void)
{
	/*RLHS01_Continue_Req*/
	Lin_RLHS01_frame.RLHS01_Continue_Req = Continue_Req;
	/*RLHS01_Diagnostic_Req*/
	if(RLS_APP_Value.APP_DiagnnosticReq == APP_Diagnnostic_Req)
	{
		Lin_RLHS01_frame.RLHS01_Diagnostic_Req = Diagnnostic_Req;
	}
	else
	{
		Lin_RLHS01_frame.RLHS01_Diagnostic_Req = NO_Diagnnostic_Req;
	}
	/*RLHS01_APP_Reset*/
	Lin_RLHS01_frame.RLHS01_APP_Reset =  NO_AppResetStatus_Req;
	/*RLHS01_APP_configuration*/
	Lin_RLHS01_frame.RLHS01_APP_configuration = App_ConfigurationStatus;
	/*RLHS01_APP_Status*/
	Lin_RLHS01_frame.RLHS01_APP_Status = AppStatus_OK;
	/*RLHS01_Comunication_Status*/
	Lin_RLHS01_frame.RLHS01_Comunication_Status = LinComStatus_No_detected_Fault;
	/*RLHS01_Temp01*/
	Lin_RLHS01_frame.RLHS01_Temp01 = 0xffff;
	/*RLHS01_Sensor_Vaility*/
	Lin_RLHS01_frame.RLHS01_Sensor_Vaility = Validity;
	/*RLHS01_Unused*/
	Lin_RLHS01_frame.RLHS01_Unused = 0;
	
	
	l_bool_wr_LI0_RLHS01_Continue_Req(Lin_RLHS01_frame.RLHS01_Continue_Req);
	l_bool_wr_LI0_RLHS01_Diagnostic_Req(Lin_RLHS01_frame.RLHS01_Diagnostic_Req);
	l_bool_wr_LI0_RLHS01_APP_Reset(Lin_RLHS01_frame.RLHS01_APP_Reset);
	l_bool_wr_LI0_RLHS01_APP_configuration(Lin_RLHS01_frame.RLHS01_APP_configuration);
	l_bool_wr_LI0_RLHS01_APP_Status(Lin_RLHS01_frame.RLHS01_APP_Status);
	l_u8_wr_LI0_RLHS01_Comunication_Status(Lin_RLHS01_frame.RLHS01_Comunication_Status);
	l_u16_wr_LI0_RLHS01_Temp01(Lin_RLHS01_frame.RLHS01_Temp01);
	l_bool_wr_LI0_RLHS01_Sensor_Vaility(Lin_RLHS01_frame.RLHS01_Sensor_Vaility);
	l_u8_wr_LI0_RLHS01_Unused(Lin_RLHS01_frame.RLHS01_Unused);
}

void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}
