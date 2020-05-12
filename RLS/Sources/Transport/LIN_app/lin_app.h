/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      adc.h 
* 
* @author    xujun
*  
* @version   1.0 
*  
* @date      Sat Aug 04 10:53:51 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _LIN_APP_H_  
#define    _LIN_APP_H_  

#include "config_parameter.h"

/*****************************
 * config of BCM
 * * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * ***********************/
typedef enum
{
   WiperPosition_Not_Parked             = 0,
   WiperPosition_Parked                 = 1
}WiperPosition_t;

typedef enum
{
   BCM_Not_Washering                 = 0,
   BCM_Washering                     = 1
}BCM_Washer_t;

typedef enum
{
   BCM_Amb_LV_Unknown       = 0,
   BCM_Amb_LV_Night         = 1,
   BCM_Amb_LV_Day           = 2,
   BCM_Amb_LV_NOT_Use       = 3  
}BCM_Amb_LV_t;

typedef enum
{
   RainSensitivity_Off       = 0,
   RainSensitivity_LV1       = 1,   
   RainSensitivity_LV2       = 2,
   RainSensitivity_LV3       = 3,
   RainSensitivity_LV4       = 4,
   RainSensitivity_LV5       = 5,
   RainSensitivity_Low       = 6,
   RainSensitivity_High      = 7
}RainSensitivity_t;

typedef struct  
{
	   
  WiperPosition_t                  BCM_WiperPosition ;
    
  BCM_Washer_t                     BCM_Washer ;
    
  BCM_Amb_LV_t                     BCM_Amb_LV ;
   
  RainSensitivity_t                BCM_RainSensitivity  ;
    
  uint8                            BCM_VehicleSpeed     ;
      
}BCM_Frame_t;












/*****************************
 * config of RLS
 * * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * ***********************/

typedef enum
{
  NO_Continue_Req   = 0,
  Continue_Req      = 1
}ContinuteReq_t;

typedef enum
{
  NO_Diagnnostic_Req   = 0,
  Diagnnostic_Req      = 1
}DiagnnosticReq_t;

typedef enum
{
  NO_AppResetStatus_Req   = 0,
  AppResetStatus_Req      = 1
}AppResetStatus_t;

typedef enum
{
  App_ConfigurationStatus       = 0,
  NO_App_ConfigurationStatus    = 1
}AppConfigurationStatus_t;

typedef enum
{
   AppStatus_OK        = 0,
   AppStatus_Failed    = 1
}AppStatus_t;

typedef enum
{
   LinComStatus_No_detected_Fault            = 0,
   LinComStatus_Reset                        = 1,
   LinComStatus_Reserved0                    = 2,
   LinComStatus_Reserved1                    = 3,
   LinComStatus_Data_Error                   = 4,
   LinComStatus_Checksum_error               = 5,
   LinComStatus_Byte_field_framing           = 6,
   LinComStatus_ID_parity_error              = 7
}LinComStatus_t;

typedef enum
{
   Wiper_Request_Off               = 0,
   Wiper_Request_Low               = 1,
   Wiper_Request_High              = 2,
   Wiper_Request_NOT_Use           = 3  
}WiperRequest_t;

typedef enum
{
   RLS_Amb_LV_Unknown              = 0,
   RLS_Amb_LV_Night                = 1,
   RLS_Amb_LV_Day                  = 2,
   RLS_Amb_LV_NOT_Use              = 3  
}RLS_Amb_LV_t;

typedef enum
{
   RainSensor_Normal               = 0,
   RainSensor_Fault                = 1
}RainSensorError_t;

typedef enum
{
   LightSensor_Not_Installed       = 0,
   LightSensor_Installed           = 1
}LightSensorInstalled_t;

typedef enum
{
   LightSensor_Normal              = 0,
   LightSensor_Fault               = 1
}LightSensorError_t;

typedef enum
{
   HumiditySensor_Not_Installed    = 0,
   HumiditySensor_Installed        = 1
}HumiditySensorInstalled_t;

typedef struct  
{
 ContinuteReq_t	                   RLS_ContinuteReq ;
 DiagnnosticReq_t	               RLS_DiagnnosticReq ;
 AppResetStatus_t	               RLS_AppResetStatus ;
 AppConfigurationStatus_t	       RLS_AppConfigurationStatus ;
 AppStatus_t                       RLS_AppStatus ;
 LinComStatus_t                    RLS_LinComStatus ;
 WiperRequest_t	                   RLS_WiperRequest ;
 RLS_Amb_LV_t	                   RLS_Amb_LV ;
 RainSensorError_t	               RLS_RainSensorError ;
 LightSensorInstalled_t	           RLS_LightSensorInstalled ;
 LightSensorError_t	               RLS_LightSensorError ;
 HumiditySensorInstalled_t   	   RLS_HumiditySensorInstalled ;
 uint8	                           RLS_Amb_Value ;
 uint8	                           RLS_FW_Value ;	       
}RLS1_Frame_t;















/*****************************
 * config of RLHS
 * * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * ***********************/

typedef enum
{
   Validity    = 0,
   Invalidity  = 1
}Validity_t;


typedef struct  
{
	ContinuteReq_t                 RLHS_COM_Continue_req;
	DiagnnosticReq_t               RLHS_Diagnostic_Req;
	AppResetStatus_t               RLHS_APP_Reset_Atatus;
	AppConfigurationStatus_t       RLHS_APP_Configuration;
	AppStatus_t                    RLHS_APP_Status;
	LinComStatus_t                 RLHS_Comunicate_Status;
	uint16                         RLHS_Humidity_Temp;
	Validity_t                     RLHS_Humidity_Temp_Validity;
	RainSensorError_t              RLHS_Sensor_Fault;
	uint8                          RLHS_Unused_bit;
	Validity_t                     RLHS_Sensor_Humidity_Validity;
	uint8                          RLHS_Humindity_Value;
}RLHS_Frame_t;









/*****************************
 * config of RLHS01
 * * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * ***********************/

typedef struct  
{
	ContinuteReq_t                 RLHS01_Continue_Req;
	DiagnnosticReq_t               RLHS01_Diagnostic_Req;
	AppResetStatus_t               RLHS01_APP_Reset;
	AppConfigurationStatus_t       RLHS01_APP_configuration;
	AppStatus_t                    RLHS01_APP_Status;
	LinComStatus_t                 RLHS01_Comunication_Status;
	uint16                         RLHS01_Temp01;
	Validity_t                     RLHS01_Sensor_Vaility;
	uint8                          RLHS01_Unused;
}RLHS01_Frame_t;













/*****************************
 * config of lin_error
 * * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * ***********************/
typedef struct
{
  uint8  RS_Error              :1;
  uint8  LS_Error              :1;
  uint8  IR_Error              :1;
  uint8  rsv0                  :5;
  
  uint8  RS_Error_Cnt[2];
  uint8  LS_Error_Cnt ;
  uint8  IR_Error_Cnt[2] ;
} Rls_Error_t;










/******************************RLS_APP_SET_DATA_TO_BCM
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *************************************************************/

typedef enum
{
    WiperSpeed_Off         = 0,
    WiperSpeed_Low         = 1,
    WiperSpeed_Single      = 2,
    WiperSpeed_High        = 3
}WiperSpeed_t;

typedef enum
{
	VOLTAGE_NORMAL              = 0,
	VOLTAGE_LOW                 = 1,
	VOLTAGE_HIGH                = 2
}Battery_status_t;

typedef enum
{
	Light_Off              = 0,
	Light_On                 = 1
}APP_Light_t;

typedef enum
{
  APP_NO_Diagnnostic_Req   = 0,
  APP_Diagnnostic_Req      = 1
}APP_DiagnnosticReq_t;

typedef enum
{
  APP_LinComStatus_No_detected_Fault            = 0,
  APP_LinComStatus_Reset                        = 1,
  APP_LinComStatus_Reserved0                    = 2,
  APP_LinComStatus_Reserved1                    = 3,
  APP_LinComStatus_Data_Error                   = 4,
  APP_LinComStatus_Checksum_error               = 5,
  APP_LinComStatus_Byte_field_framing           = 6,
  APP_LinComStatus_ID_parity_error              = 7
}APP_LinComStatus_t;

typedef enum
{
	APP_Rain_Invalid   = 0,
    APP_Rain_Valid      = 1
}APP_Rain_Valid_t;

typedef struct  
{
  WiperSpeed_t	  RLS_APP_WiperSpeed ;
  Battery_status_t  Battery_status;
  APP_Light_t light_on_req;
  APP_Light_t  twilight_on_req;
  uint8  u8_Solar_l_value;
  uint8 u8_Solar_r_value;
  APP_DiagnnosticReq_t  APP_DiagnnosticReq;
  bool_t  APP_Reset;
  APP_Rain_Valid_t  Rain_Valid;
}RLS_APP_Value_t;











/******************************RLS_APP_GET_DATA_FROM_BCM
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *******************************************************************************
 * *************************************************************/


typedef enum
{
   APP_RainSensitivityAPP__default       = 0,
   APP_RainSensitivityAPP_LV1       = 1,   
   APP_RainSensitivityAPP_LV2       = 2,
   APP_RainSensitivityAPP_LV3       = 3,
   APP_RainSensitivityAPP_LV4       = 4

}APP_RainSensitivity_t;


typedef enum
{
	BCM_Window_All_closed         = 0,
	BCM_Window_Not_All_closed         = 1,
	BCM_Window_All_On      = 2
}APP_WindowStatus_t;


typedef enum
{
   APP_WiperPosition_Not_Parked             = 0,
   APP_WiperPosition_Parked                 = 1
}APP_WiperPosition_t;

typedef struct  
{
  APP_WindowStatus_t	                 BCM_WindowStatus ;
  uint16                                 u16_SPD_Vehicle;
  RainSensitivity_t                      Pre_BCM_RainSensitivity;
  APP_RainSensitivity_t                  BCM_RainSensitivity  ;
  APP_WiperPosition_t                    BCM_WiperPosition ; 
  bool_t                                 Single_Wipe_flag;
  
}BCM_APP_Value_t;










extern void Lin_Var_Init(void);
extern void Lin_Sys_Init(void);
extern void Lin_Busy_Process(void);
extern void RLS_Analysis_Master_Data(void);
extern void message_cnt(void);
extern void RLS_APP_Send_data(void);
extern void RLHS_APP_Send_data(void);
extern void RLHS01_APP_Send_data(void);
extern void Lin_RLS_data(void);
extern void RLS_APP_Get_Data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);

#endif    /* _ADC_H_ */
