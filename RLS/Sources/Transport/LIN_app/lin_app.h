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
   RainSensitivity_LV0       = 0,
   RainSensitivity_LV1       = 1,   
   RainSensitivity_LV2       = 2,
   RainSensitivity_LV3       = 3,
   RainSensitivity_LV4       = 4,
   RainSensitivity_LV5       = 5,
   RainSensitivity_LV6       = 6
}RainSensitivity_t;


typedef enum
{
   BCM_IG_Statu_Off       = 0,
   BCM_IG_Statu_ACC       = 1,   
   BCM_IG_Statu_On       = 2,
   BCM_IG_Statu_Start       = 3
}BCM_IGON_Status_t;



typedef enum
{
   BCM_CMD_AutoWiper_Off       = 0,   
   BCM_CMD_AutoWiper_On        = 1
}BCM_CMD_AutoWiper_t;


typedef enum
{
   BCM_CMD_AutoLight_Off       = 0,   
   BCM_CMD_AutoLight_On        = 1
}BCM_CMD_AutoLight_t;


typedef enum
{
   BCM_CMD_RoofStatus_Off       = 0,   
   BCM_CMD_RoofStatus_On        = 1
}BCM_RoofStatus_t;

typedef struct  
{
  BCM_IGON_Status_t  BCM_Status_IGN;

  BCM_CMD_AutoWiper_t BCM_CMD_AutoWiper;
 
  BCM_Washer_t BCM_RQ_FrontWash;
 
  WiperPosition_t  BCM_ParkPosition;
 
  RainSensitivity_t  BCM_RainSensitivity;
 
  BCM_CMD_AutoLight_t BCM_CMD_AutoLight;
 
  bool_t BCM_BladesTurningPoint;
 
  BCM_RoofStatus_t BCM_RoofStatus;
 
  uint16 BCM_SPD_Vehicle;
 
  uint8 LI0_BCM_OutsideTemp;
      
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
  NO_Diagnnostic_Req   = 0,
  Diagnnostic_Req      = 1
}DiagnnosticReq_t;


typedef enum
{
   Wiper_Request_Off               = 0,
   Wiper_Request_Low               = 1,
   Wiper_Request_High              = 2,
   Wiper_Request_NOT_Use           = 3  
}WiperRequest_t;


typedef enum
{
   RainSensor_Normal               = 0,
   RainSensor_Fault                = 1
}RainSensorError_t;


typedef enum
{
   LightSensor_Normal              = 0,
   LightSensor_Fault               = 1
}LightSensorError_t;

typedef enum
{
   RLS_RQ_LowBeam_Off    = 0,
   RLS_RQ_LowBeam_On     = 1
}RLS_RQ_LowBeam_t;


typedef enum
{
   RLS_REP_Normal              = 0,
   RLS_REP_Fault               = 1
}RLS_REP_Error_t;

typedef enum
{
   RLS_VOLT_Normal              = 0,
   RLS_VOLT_Fault               = 1
}RLS_VOLT_Error_t;

typedef enum
{
	RLS_Humid_Temp_Normal              = 0,
	RLS_Humid_Temp_Fault               = 1
}RLS_Humid_Temp_Error_t;

typedef struct  
{
 uint8 RLS_MsgCounter;

 WiperRequest_t RLS_RQ_WiperSPD;

 RLS_RQ_LowBeam_t RLS_RQ_LowBeam;

 RLS_RQ_LowBeam_t RLS_RQ_PositionLamp;

 RainSensorError_t RLS_Fault_Rain;

 LightSensorError_t RLS_Fault_Light;

 RLS_REP_Error_t RLS_REP_Error;

 RLS_VOLT_Error_t RLS_VOLT_Error;

 RLS_Humid_Temp_Error_t RLS_Humid_Temp_Error;

 uint8 RLS_Brightness_IR_L;

 uint16 RLS_Brightness_FW;

 uint8 RLS_Rain_Intensity;
 
 
 

 uint8 RLS_Brightness_IR_R;

 uint8 RLS_Temperature;

 uint8 RLS_Humid;
}RLS1_Frame_t;



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
  uint8  IR_Error_Cnt ;
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
extern void Lin_RLS_data(void);
extern void RLS_APP_Get_Data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);

#endif    /* _ADC_H_ */
