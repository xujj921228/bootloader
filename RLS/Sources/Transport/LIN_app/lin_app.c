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
#include "app_data.h"
#include "local_eep_data.h"

/**************************
 * extern var  from battery
 * ************************/
extern bool_t  Lin_Diag_Enable;
extern  MLX75308_Mnrval_t      Mnrval;

extern RLS_Wiper_State_FSM_t  Wiper_State_Fsm;
extern local_info_t local_info;

bool_t Lin_Busy_Flag;

Rls_Error_t       App_Rls_Error;

RLS1_Frame_t        Lin_RLS1_frame;
BCM_Frame_t         Lin_BCM_Frame;


//this frame is for APP 
RLS_APP_Value_t     RLS_APP_Value;
BCM_APP_Value_t     BCM_APP_Value;

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

void Lin_Var_Init(void)
{
	BCM_APP_Value.u16_SPD_Vehicle =  0;
	BCM_APP_Value.Pre_BCM_Auto_Active = FALSE;
	BCM_APP_Value.BCM_Auto_Active = FALSE;
	Lin_Busy_Flag = FALSE;
	
	Lin_BCM_Frame.BCM_RainSensitivity = RainSensitivity_LV4;
	Lin_BCM_Frame.Pre_BCM_RainSensitivity = Lin_BCM_Frame.BCM_RainSensitivity;
	
	RLS_APP_Value.APP_Reset = FALSE;
	RLS_APP_Value.vehicle_start_Flag = FALSE;
	
	Lin_RLS1_frame.RLS_ModReq = RLS_Nomal1_ModeReq;
	
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
	Lin_BCM_Frame.BCM_ModReq = l_u8_rd_LI0_BCM_ModReq();
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
	BCM_APP_Value.BCM_Auto_Active = TRUE;
	switch(Lin_BCM_Frame.BCM_RainSensitivity)
	{
	
		case RainSensitivity_Off: BCM_APP_Value.BCM_Auto_Active = FALSE;break;
		case RainSensitivity_LV1: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV1;break;                                 
		case RainSensitivity_LV2: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV1;break;
		case RainSensitivity_LV3: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV2;break;
		case RainSensitivity_LV4: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV2;break;
		case RainSensitivity_LV5: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV3;break;
		case RainSensitivity_Low: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV3;break;
		default:
		case RainSensitivity_High: BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV4;break;               
	}
	if(Lin_BCM_Frame.BCM_RainSensitivity > Lin_BCM_Frame.Pre_BCM_RainSensitivity)
	{
		BCM_APP_Value.Single_Wipe_flag = TRUE;
	}
	if((BCM_APP_Value.Pre_BCM_Auto_Active == FALSE)&&(BCM_APP_Value.BCM_Auto_Active == TRUE))
	{
		BCM_APP_Value.Single_Wipe_flag = TRUE;
	}
	Lin_BCM_Frame.Pre_BCM_RainSensitivity = Lin_BCM_Frame.BCM_RainSensitivity;
	BCM_APP_Value.Pre_BCM_Auto_Active = BCM_APP_Value.BCM_Auto_Active;
	/****************************
	 * 
	 * APP  Get VehicleSpeed  from bcm
	 * *************************************/
	
	
	if((BCM_APP_Value.u16_SPD_Vehicle < 2 )&&
		(Lin_BCM_Frame.BCM_VehicleSpeed >= 1)&&
		(RLS_APP_Value.vehicle_start_Flag == TRUE))
	{
		RLS_APP_Value.vehicle_start_Flag = FALSE;
		BCM_APP_Value.Single_Wipe_flag = TRUE;
	}
	BCM_APP_Value.u16_SPD_Vehicle =  (uint16)(Lin_BCM_Frame.BCM_VehicleSpeed) * 2 ;
	
	/***根据车速分辨车速挡位****/
	
	if(BCM_APP_Value.u16_SPD_Vehicle <= local_info.Vehicle_Speed_Gear0)   
	{
		BCM_APP_Value.SPD_Vehicle_Gear  =  APP_SPD_Gear0;        
	}
	else if(BCM_APP_Value.u16_SPD_Vehicle <= local_info.Vehicle_Speed_Gear1)
	{
		BCM_APP_Value.SPD_Vehicle_Gear  =  APP_SPD_Gear1;           
	}    
	else if(BCM_APP_Value.u16_SPD_Vehicle <= local_info.Vehicle_Speed_Gear2)
	{
		BCM_APP_Value.SPD_Vehicle_Gear  =  APP_SPD_Gear2;         
	}    
	else if(BCM_APP_Value.u16_SPD_Vehicle <= local_info.Vehicle_Speed_Gear3) 
	{
		BCM_APP_Value.SPD_Vehicle_Gear  =  APP_SPD_Gear3; 
	}
	else
	{
		BCM_APP_Value.SPD_Vehicle_Gear  =  APP_SPD_Gear4;
	}
	
	
	
	BCM_APP_Value.BCM_APP_ModReq = Lin_BCM_Frame.BCM_ModReq;
	
	/*if(RLS_RunMode != MAIN_SLEFADAPT)
	{
		if(BCM_APP_Value.BCM_APP_ModReq == APP_Nomal_Mode)
		{
			RLS_RunMode =  MAIN_NORMAL;
		}
		else
		{
			RLS_RunMode =  MAIN_SLEEP_Mode;
		}
	}*/
	
	
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
	uint16 up_out,fw_out;
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
			(Lin_BCM_Frame.BCM_Washer == BCM_Washering))//清洗抑制
	{
		Lin_RLS1_frame.RLS_WiperRequest = Wiper_Request_Off;
	}
	/************************
	 * DATA_OF_LIGHT
	 * ******************************************/
	
	Lin_RLS1_frame.RLS_Amb_LV = Lin_BCM_Frame.BCM_Amb_LV;
	/*if(RLS_APP_Value.light_on_req == Light_On)
	{
		Lin_RLS1_frame.RLS_Amb_LV = RLS_Amb_LV_Night;	
	}
	else
	{
		Lin_RLS1_frame.RLS_Amb_LV = RLS_Amb_LV_Day;
	}*/
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
	up_out = RLS_APP_Value.u16_Brightness_UP/15;
	if(up_out > 0xff) up_out = 0xFF;
	fw_out = RLS_APP_Value.u16_Brightness_FW /13;
	if(fw_out > 0xff) fw_out = 0xFF;
	
	Lin_RLS1_frame.RLS_Amb_Value =(uint8)up_out;
	Lin_RLS1_frame.RLS_FW_Value =(uint8)fw_out ;
	/************************
	 * change_mode
	 * ******************************************/
	
	Lin_RLS1_frame.RLS_ModReq = BCM_APP_Value.BCM_APP_ModReq;
	
	Lin_RLS1_frame.RLS_ClosedWind = RLS_APP_Value.RLS_APP_ClosedWind;
		
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
	l_u8_wr_LI0_RLS_ModReq((uint8)(Lin_RLS1_frame.RLS_ModReq));
	l_u8_wr_LI0_RLS_ClosedWind((uint8)(Lin_RLS1_frame.RLS_ClosedWind));
	
}
void Lin_RLS_Wakeup_BCM(void)
{
	UART0_C2 |= UART_C2_SBK_MASK  ;
	UART0_C2 &= ~UART_C2_SBK_MASK ;
}
