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
   BCM_Nomal_Mode           = 0,
   BCM_Polling_Mode         = 1,
   BCM_Sleep_Mode           = 2,
   BCM_Reserved             = 3  
}BCM_ModReq_t;

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
  
  RainSensitivity_t                Pre_BCM_RainSensitivity  ;
   
  RainSensitivity_t                BCM_RainSensitivity  ;
    
  uint8                            BCM_VehicleSpeed     ;
  
  BCM_ModReq_t                     BCM_ModReq ;
      
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


typedef enum
{
   RLS_Nomal1_ModeReq              = 0,
   RLS_Polling_ModeReq             = 1,
   RLS_Sleep_ModeReq               = 2,
   RLS_Reserved_ModeReq            = 3  
}RLS_ModeReq_t;



typedef enum
{
   RLS_No_Request           = 0,
   RLS_Rain_Closed          = 1,
   RLS_Time_Closed          = 2,
   RLS_Closed_Reserved      = 3  
}RLS_ClosedWind_t;


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
 RLS_ModeReq_t                     RLS_ModReq;
 RLS_ClosedWind_t                  RLS_ClosedWind;
}RLS1_Frame_t;

extern void Lin_Var_Init(void);
extern void Lin_Sys_Init(void);
extern void Lin_Busy_Process(void);
extern void RLS_Analysis_Master_Data(void);
extern void RLS_APP_Send_data(void);
extern void Lin_RLS_data(void);
extern void RLS_APP_Get_Data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);

#endif    /* _ADC_H_ */
