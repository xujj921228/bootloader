/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2019 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      lin_cfg.h 
* 
* @author    xujun
*  
* @version   1.0 
*  
* @date      Mon Dec 30 14:53:07 CST 2019
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _LIN_CFG_H_  
#define    _LIN_CFG_H_  
#include "lin_hw_cfg.h" 
/* Define operating mode */
#define _MASTER_MODE_     0 
#define _SLAVE_MODE_      1 
#define LIN_MODE   _SLAVE_MODE_
/* Define protocol version */
#define PROTOCOL_21       0  
#define PROTOCOL_J2602    1  
#define PROTOCOL_20       2 
#define LIN_PROTOCOL    PROTOCOL_21

#define UART_ADDR        UART0_ADDR    /* For slave */ 


#define LIN_BAUD_RATE    10417    	 /*For slave*/ 
/**********************************************************************/
/***************          Diagnostic class selection  *****************/
/**********************************************************************/
#define _DIAG_CLASS_I_          0
#define _DIAG_CLASS_II_         1
#define _DIAG_CLASS_III_        2

#define _DIAG_CLASS_SUPPORT_    _DIAG_CLASS_II_

#define MAX_LENGTH_SERVICE 8

#define MAX_QUEUE_SIZE 2

#define DIAGSRV_SESSION_DEFAULT 1
#define DIAGSRV_SESSION_PROGRAM 2
#define DIAGSRV_SESSION_EXTERN  3

#define _DIAG_NUMBER_OF_SERVICES_    9

#define DIAGSRV_READ_BY_IDENTIFIER_ORDER    0

#define DIAGSRV_ASSIGN_FRAME_ID_RANGE_ORDER    1

#define DIAGSRV_READ_DATA_BY_IDENTIFIER_ORDER    2

#define DIAGSRV_CONDITIONAL_CHANGE_NAD_ORDER    3

#define DIAGSRV_ASSIGN_NAD_ORDER    4

#define DIAGSRV_WRITE_DATA_BY_IDENTIFIER_ORDER    5

#define DIAGSRV_SAVE_CONFIGURATION_ORDER    6

#define DIAGSRV_DATA_DUMP_ORDER    7

#define DIAGSRV_ASSIGN_FRAME_IDENTIFIER_ORDER    8


/**************** FRAME SUPPORT DEFINITION ******************/
#define _TL_SINGLE_FRAME_       0
#define _TL_MULTI_FRAME_        1

#define _TL_FRAME_SUPPORT_      _TL_MULTI_FRAME_

/* frame buffer size */
#define LIN_FRAME_BUF_SIZE			8
#define LIN_FLAG_BUF_SIZE			4

/**********************************************************************/
/***************               Interfaces           *******************/
/**********************************************************************/
typedef enum { 
   LI0
}l_ifc_handle; 

/**********************************************************************/
/***************               Signals              *******************/
/**********************************************************************/
/* Number of signals */
#define LIN_NUM_OF_SIGS  22
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_BCM_WiperPosition

   , LI0_BCM_Washer
  
   , LI0_BCM_Amb_LV
  
   , LI0_BCM_RainSensitivity
  
   , LI0_BCM_VehicleSpeed
  
   , LI0_RLS_ContinuteReq
  
   , LI0_RLS_DiagnnosticReq
  
   , LI0_RLS_AppResetStatus
  
   , LI0_RLS_AppConfigurationStatus
  
   , LI0_RLS_AppStatus
  
   , LI0_RLS_LinComStatus
  
   , LI0_RLS_WiperRequest
  
   , LI0_RLS_Amb_LV
  
   , LI0_RLS_RainSensorError
  
   , LI0_RLS_LightSensorInstalled
  
   , LI0_RLS_LightSensorError
  
   , LI0_RLS_HumiditySensorInstalled
  
   , LI0_RLS_Amb_Value
  
   , LI0_RLS_FW_Value
  
   , LI0_BCM_ModReq
  
   , LI0_RLS_ModReq
  
   , LI0_RLS_ClosedWind
  
  
} l_signal_handle; 
/**********************************************************************/
/*****************               Frame             ********************/
/**********************************************************************/
/* Number of frames */
#define LIN_NUM_OF_FRMS  4 
/* List of frames */
typedef enum {
/* All frames for master node */

   /* Interface_name = LI0 */

   LI0_BCM_01

   , LI0_RLS_01
  
   , LI0_MasterReq
  
   , LI0_SlaveResp
  
  
} l_frame_handle; 
 
/**********************************************************************/
/***************             Configuration          *******************/
/**********************************************************************/
/* Size of configuration in ROM and RAM used for interface: LI1 */
#define LIN_SIZE_OF_CFG  6 
#define LIN_CFG_FRAME_NUM  2 
/*********************************************************************
 * global macros
 *********************************************************************/
#define l_bool_rd(SIGNAL) l_bool_rd_##SIGNAL()
#define l_bool_wr(SIGNAL, A) l_bool_wr_##SIGNAL(A)
#define l_u8_rd(SIGNAL) l_u8_rd_##SIGNAL()
#define l_u8_wr(SIGNAL, A) l_u8_wr_##SIGNAL(A)
#define l_u16_rd(SIGNAL) l_u16_rd_##SIGNAL()
#define l_u16_wr(SIGNAL, A) l_u16_wr_##SIGNAL(A)
#define l_bytes_rd(SIGNAL, start, count, data)  l_bytes_rd_##SIGNAL(start, count, data)
#define l_bytes_wr(SIGNAL, start, count, data) l_bytes_wr_##SIGNAL(start, count, data)
#define l_flg_tst(FLAG) l_flg_tst_##FLAG()
#define l_flg_clr(FLAG) l_flg_clr_##FLAG()
#define LIN_TEST_BIT(A,B) ((l_bool)((((A) & (1U << (B))) != 0U) ? 1U : 0U))
#define LIN_SET_BIT(A,B)                      ((A) |= (l_u8) (1U << (B)))
#define LIN_CLEAR_BIT(A,B)               ((A) &= ((l_u8) (~(1U << (B)))))
#define LIN_BYTE_MASK  ((l_u16)(((l_u16)((l_u16)1 << CHAR_BIT)) - (l_u16)1))
#define LIN_FRAME_LEN_MAX                                             10U

/* Returns the low byte of the 32-bit value    */
#define BYTE_0(n)                              ((l_u8)((n) & (l_u8)0xFF))
/* Returns the second byte of the 32-bit value */
#define BYTE_1(n)                        ((l_u8)(BYTE_0((n) >> (l_u8)8)))
/* Returns the third byte of the 32-bit value  */
#define BYTE_2(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)16)))
/* Returns high byte of the 32-bit value       */
#define BYTE_3(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)24)))

/*
 * defines for signal access
 */


#define LIN_BYTE_OFFSET_LI0_BCM_WiperPosition    0
#define LIN_BIT_OFFSET_LI0_BCM_WiperPosition    0
#define LIN_SIGNAL_SIZE_LI0_BCM_WiperPosition    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperPosition    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperPosition    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_WiperPosition    0

#define LIN_BYTE_OFFSET_LI0_BCM_Washer    0
#define LIN_BIT_OFFSET_LI0_BCM_Washer    1
#define LIN_SIGNAL_SIZE_LI0_BCM_Washer    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_Washer    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_Washer    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Washer    0

#define LIN_BYTE_OFFSET_LI0_BCM_Amb_LV    0
#define LIN_BIT_OFFSET_LI0_BCM_Amb_LV    2
#define LIN_SIGNAL_SIZE_LI0_BCM_Amb_LV    2
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_Amb_LV    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_Amb_LV    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Amb_LV    0

#define LIN_BYTE_OFFSET_LI0_BCM_RainSensitivity    0
#define LIN_BIT_OFFSET_LI0_BCM_RainSensitivity    4
#define LIN_SIGNAL_SIZE_LI0_BCM_RainSensitivity    3
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_RainSensitivity    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_RainSensitivity    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RainSensitivity    0

#define LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed    1
#define LIN_BIT_OFFSET_LI0_BCM_VehicleSpeed    0
#define LIN_SIGNAL_SIZE_LI0_BCM_VehicleSpeed    8
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_VehicleSpeed    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_VehicleSpeed    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_VehicleSpeed    0

#define LIN_BYTE_OFFSET_LI0_RLS_ContinuteReq    3
#define LIN_BIT_OFFSET_LI0_RLS_ContinuteReq    0
#define LIN_SIGNAL_SIZE_LI0_RLS_ContinuteReq    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_ContinuteReq    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_ContinuteReq    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ContinuteReq    1

#define LIN_BYTE_OFFSET_LI0_RLS_DiagnnosticReq    3
#define LIN_BIT_OFFSET_LI0_RLS_DiagnnosticReq    2
#define LIN_SIGNAL_SIZE_LI0_RLS_DiagnnosticReq    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_DiagnnosticReq    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_DiagnnosticReq    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_DiagnnosticReq    1

#define LIN_BYTE_OFFSET_LI0_RLS_AppResetStatus    3
#define LIN_BIT_OFFSET_LI0_RLS_AppResetStatus    1
#define LIN_SIGNAL_SIZE_LI0_RLS_AppResetStatus    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppResetStatus    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_AppResetStatus    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_AppResetStatus    1

#define LIN_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus    3
#define LIN_BIT_OFFSET_LI0_RLS_AppConfigurationStatus    3
#define LIN_SIGNAL_SIZE_LI0_RLS_AppConfigurationStatus    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_AppConfigurationStatus    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus    1

#define LIN_BYTE_OFFSET_LI0_RLS_AppStatus    3
#define LIN_BIT_OFFSET_LI0_RLS_AppStatus    4
#define LIN_SIGNAL_SIZE_LI0_RLS_AppStatus    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppStatus    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_AppStatus    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_AppStatus    1

#define LIN_BYTE_OFFSET_LI0_RLS_LinComStatus    3
#define LIN_BIT_OFFSET_LI0_RLS_LinComStatus    5
#define LIN_SIGNAL_SIZE_LI0_RLS_LinComStatus    3
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_LinComStatus    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_LinComStatus    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LinComStatus    1

#define LIN_BYTE_OFFSET_LI0_RLS_WiperRequest    4
#define LIN_BIT_OFFSET_LI0_RLS_WiperRequest    0
#define LIN_SIGNAL_SIZE_LI0_RLS_WiperRequest    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_WiperRequest    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_WiperRequest    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_WiperRequest    1

#define LIN_BYTE_OFFSET_LI0_RLS_Amb_LV    4
#define LIN_BIT_OFFSET_LI0_RLS_Amb_LV    2
#define LIN_SIGNAL_SIZE_LI0_RLS_Amb_LV    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_LV    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_LV    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Amb_LV    1

#define LIN_BYTE_OFFSET_LI0_RLS_RainSensorError    4
#define LIN_BIT_OFFSET_LI0_RLS_RainSensorError    4
#define LIN_SIGNAL_SIZE_LI0_RLS_RainSensorError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_RainSensorError    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_RainSensorError    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RainSensorError    1

#define LIN_BYTE_OFFSET_LI0_RLS_LightSensorInstalled    4
#define LIN_BIT_OFFSET_LI0_RLS_LightSensorInstalled    5
#define LIN_SIGNAL_SIZE_LI0_RLS_LightSensorInstalled    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorInstalled    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorInstalled    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LightSensorInstalled    1

#define LIN_BYTE_OFFSET_LI0_RLS_LightSensorError    4
#define LIN_BIT_OFFSET_LI0_RLS_LightSensorError    6
#define LIN_SIGNAL_SIZE_LI0_RLS_LightSensorError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorError    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorError    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LightSensorError    1

#define LIN_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled    4
#define LIN_BIT_OFFSET_LI0_RLS_HumiditySensorInstalled    7
#define LIN_SIGNAL_SIZE_LI0_RLS_HumiditySensorInstalled    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_HumiditySensorInstalled    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled    1

#define LIN_BYTE_OFFSET_LI0_RLS_Amb_Value    5
#define LIN_BIT_OFFSET_LI0_RLS_Amb_Value    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Amb_Value    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_Value    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_Value    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Amb_Value    1

#define LIN_BYTE_OFFSET_LI0_RLS_FW_Value    6
#define LIN_BIT_OFFSET_LI0_RLS_FW_Value    0
#define LIN_SIGNAL_SIZE_LI0_RLS_FW_Value    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_FW_Value    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_FW_Value    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_FW_Value    1

#define LIN_BYTE_OFFSET_LI0_BCM_ModReq    2
#define LIN_BIT_OFFSET_LI0_BCM_ModReq    0
#define LIN_SIGNAL_SIZE_LI0_BCM_ModReq    2
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_ModReq    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_ModReq    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_ModReq    0

#define LIN_BYTE_OFFSET_LI0_RLS_ModReq    7
#define LIN_BIT_OFFSET_LI0_RLS_ModReq    0
#define LIN_SIGNAL_SIZE_LI0_RLS_ModReq    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_ModReq    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_ModReq    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ModReq    1

#define LIN_BYTE_OFFSET_LI0_RLS_ClosedWind    7
#define LIN_BIT_OFFSET_LI0_RLS_ClosedWind    2
#define LIN_SIGNAL_SIZE_LI0_RLS_ClosedWind    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_ClosedWind    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_ClosedWind    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ClosedWind    1




#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_01             0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_01             1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_01              0


/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */


/* static access macros for signal LI0_BCM_WiperPosition */
#define l_bool_rd_LI0_BCM_WiperPosition() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WiperPosition], \
   	LIN_BIT_OFFSET_LI0_BCM_WiperPosition))
#define l_bool_wr_LI0_BCM_WiperPosition(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WiperPosition], \
  	LIN_BIT_OFFSET_LI0_BCM_WiperPosition)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WiperPosition], \
  	LIN_BIT_OFFSET_LI0_BCM_WiperPosition));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_WiperPosition] = 1;}

/* static access macros for signal LI0_BCM_Washer */
#define l_bool_rd_LI0_BCM_Washer() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Washer], \
   	LIN_BIT_OFFSET_LI0_BCM_Washer))
#define l_bool_wr_LI0_BCM_Washer(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Washer], \
  	LIN_BIT_OFFSET_LI0_BCM_Washer)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Washer], \
  	LIN_BIT_OFFSET_LI0_BCM_Washer));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Washer] = 1;}

/* static access macros for signal LI0_BCM_Amb_LV */
#define l_u8_rd_LI0_BCM_Amb_LV() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Amb_LV] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_Amb_LV) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_Amb_LV )) >> LIN_BIT_OFFSET_LI0_BCM_Amb_LV))
#define l_u8_wr_LI0_BCM_Amb_LV(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Amb_LV] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Amb_LV] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_Amb_LV) - 1) << LIN_BIT_OFFSET_LI0_BCM_Amb_LV)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_Amb_LV) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_Amb_LV))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Amb_LV] = 1;}

/* static access macros for signal LI0_BCM_RainSensitivity */
#define l_u8_rd_LI0_BCM_RainSensitivity() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RainSensitivity] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_RainSensitivity) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_RainSensitivity )) >> LIN_BIT_OFFSET_LI0_BCM_RainSensitivity))
#define l_u8_wr_LI0_BCM_RainSensitivity(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RainSensitivity] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RainSensitivity] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_RainSensitivity) - 1) << LIN_BIT_OFFSET_LI0_BCM_RainSensitivity)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_RainSensitivity) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_RainSensitivity))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RainSensitivity] = 1;}

/* static access macros for signal LI0_BCM_VehicleSpeed */
#define l_u8_rd_LI0_BCM_VehicleSpeed() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_VehicleSpeed) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_VehicleSpeed )) >> LIN_BIT_OFFSET_LI0_BCM_VehicleSpeed))
#define l_u8_wr_LI0_BCM_VehicleSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_VehicleSpeed) - 1) << LIN_BIT_OFFSET_LI0_BCM_VehicleSpeed)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_VehicleSpeed) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_VehicleSpeed))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_VehicleSpeed] = 1;}

/* static access macros for signal LI0_RLS_ContinuteReq */
#define l_bool_rd_LI0_RLS_ContinuteReq() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ContinuteReq], \
   	LIN_BIT_OFFSET_LI0_RLS_ContinuteReq))
#define l_bool_wr_LI0_RLS_ContinuteReq(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ContinuteReq], \
  	LIN_BIT_OFFSET_LI0_RLS_ContinuteReq)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ContinuteReq], \
  	LIN_BIT_OFFSET_LI0_RLS_ContinuteReq));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ContinuteReq] = 1;}

/* static access macros for signal LI0_RLS_DiagnnosticReq */
#define l_bool_rd_LI0_RLS_DiagnnosticReq() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_DiagnnosticReq], \
   	LIN_BIT_OFFSET_LI0_RLS_DiagnnosticReq))
#define l_bool_wr_LI0_RLS_DiagnnosticReq(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_DiagnnosticReq], \
  	LIN_BIT_OFFSET_LI0_RLS_DiagnnosticReq)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_DiagnnosticReq], \
  	LIN_BIT_OFFSET_LI0_RLS_DiagnnosticReq));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_DiagnnosticReq] = 1;}

/* static access macros for signal LI0_RLS_AppResetStatus */
#define l_bool_rd_LI0_RLS_AppResetStatus() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppResetStatus], \
   	LIN_BIT_OFFSET_LI0_RLS_AppResetStatus))
#define l_bool_wr_LI0_RLS_AppResetStatus(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppResetStatus], \
  	LIN_BIT_OFFSET_LI0_RLS_AppResetStatus)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppResetStatus], \
  	LIN_BIT_OFFSET_LI0_RLS_AppResetStatus));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_AppResetStatus] = 1;}

/* static access macros for signal LI0_RLS_AppConfigurationStatus */
#define l_bool_rd_LI0_RLS_AppConfigurationStatus() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus], \
   	LIN_BIT_OFFSET_LI0_RLS_AppConfigurationStatus))
#define l_bool_wr_LI0_RLS_AppConfigurationStatus(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus], \
  	LIN_BIT_OFFSET_LI0_RLS_AppConfigurationStatus)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus], \
  	LIN_BIT_OFFSET_LI0_RLS_AppConfigurationStatus));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus] = 1;}

/* static access macros for signal LI0_RLS_AppStatus */
#define l_bool_rd_LI0_RLS_AppStatus() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppStatus], \
   	LIN_BIT_OFFSET_LI0_RLS_AppStatus))
#define l_bool_wr_LI0_RLS_AppStatus(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppStatus], \
  	LIN_BIT_OFFSET_LI0_RLS_AppStatus)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_AppStatus], \
  	LIN_BIT_OFFSET_LI0_RLS_AppStatus));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_AppStatus] = 1;}

/* static access macros for signal LI0_RLS_LinComStatus */
#define l_u8_rd_LI0_RLS_LinComStatus() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LinComStatus] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_LinComStatus) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_LinComStatus )) >> LIN_BIT_OFFSET_LI0_RLS_LinComStatus))
#define l_u8_wr_LI0_RLS_LinComStatus(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LinComStatus] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LinComStatus] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_LinComStatus) - 1) << LIN_BIT_OFFSET_LI0_RLS_LinComStatus)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_LinComStatus) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_LinComStatus))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LinComStatus] = 1;}

/* static access macros for signal LI0_RLS_WiperRequest */
#define l_u8_rd_LI0_RLS_WiperRequest() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_WiperRequest] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_WiperRequest) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_WiperRequest )) >> LIN_BIT_OFFSET_LI0_RLS_WiperRequest))
#define l_u8_wr_LI0_RLS_WiperRequest(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_WiperRequest] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_WiperRequest] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_WiperRequest) - 1) << LIN_BIT_OFFSET_LI0_RLS_WiperRequest)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_WiperRequest) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_WiperRequest))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_WiperRequest] = 1;}

/* static access macros for signal LI0_RLS_Amb_LV */
#define l_u8_rd_LI0_RLS_Amb_LV() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_LV] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Amb_LV) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Amb_LV )) >> LIN_BIT_OFFSET_LI0_RLS_Amb_LV))
#define l_u8_wr_LI0_RLS_Amb_LV(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_LV] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_LV] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Amb_LV) - 1) << LIN_BIT_OFFSET_LI0_RLS_Amb_LV)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Amb_LV) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Amb_LV))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Amb_LV] = 1;}

/* static access macros for signal LI0_RLS_RainSensorError */
#define l_bool_rd_LI0_RLS_RainSensorError() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RainSensorError], \
   	LIN_BIT_OFFSET_LI0_RLS_RainSensorError))
#define l_bool_wr_LI0_RLS_RainSensorError(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RainSensorError], \
  	LIN_BIT_OFFSET_LI0_RLS_RainSensorError)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RainSensorError], \
  	LIN_BIT_OFFSET_LI0_RLS_RainSensorError));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RainSensorError] = 1;}

/* static access macros for signal LI0_RLS_LightSensorInstalled */
#define l_bool_rd_LI0_RLS_LightSensorInstalled() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightSensorInstalled], \
   	LIN_BIT_OFFSET_LI0_RLS_LightSensorInstalled))
#define l_bool_wr_LI0_RLS_LightSensorInstalled(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightSensorInstalled], \
  	LIN_BIT_OFFSET_LI0_RLS_LightSensorInstalled)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightSensorInstalled], \
  	LIN_BIT_OFFSET_LI0_RLS_LightSensorInstalled));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LightSensorInstalled] = 1;}

/* static access macros for signal LI0_RLS_LightSensorError */
#define l_bool_rd_LI0_RLS_LightSensorError() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightSensorError], \
   	LIN_BIT_OFFSET_LI0_RLS_LightSensorError))
#define l_bool_wr_LI0_RLS_LightSensorError(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightSensorError], \
  	LIN_BIT_OFFSET_LI0_RLS_LightSensorError)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightSensorError], \
  	LIN_BIT_OFFSET_LI0_RLS_LightSensorError));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LightSensorError] = 1;}

/* static access macros for signal LI0_RLS_HumiditySensorInstalled */
#define l_bool_rd_LI0_RLS_HumiditySensorInstalled() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled], \
   	LIN_BIT_OFFSET_LI0_RLS_HumiditySensorInstalled))
#define l_bool_wr_LI0_RLS_HumiditySensorInstalled(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled], \
  	LIN_BIT_OFFSET_LI0_RLS_HumiditySensorInstalled)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled], \
  	LIN_BIT_OFFSET_LI0_RLS_HumiditySensorInstalled));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled] = 1;}

/* static access macros for signal LI0_RLS_Amb_Value */
#define l_u8_rd_LI0_RLS_Amb_Value() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_Value] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Amb_Value) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Amb_Value )) >> LIN_BIT_OFFSET_LI0_RLS_Amb_Value))
#define l_u8_wr_LI0_RLS_Amb_Value(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_Value] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_Value] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Amb_Value) - 1) << LIN_BIT_OFFSET_LI0_RLS_Amb_Value)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Amb_Value) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Amb_Value))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Amb_Value] = 1;}

/* static access macros for signal LI0_RLS_FW_Value */
#define l_u8_rd_LI0_RLS_FW_Value() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_Value] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_FW_Value) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_FW_Value )) >> LIN_BIT_OFFSET_LI0_RLS_FW_Value))
#define l_u8_wr_LI0_RLS_FW_Value(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_Value] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_Value] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_FW_Value) - 1) << LIN_BIT_OFFSET_LI0_RLS_FW_Value)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_FW_Value) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_FW_Value))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_FW_Value] = 1;}

/* static access macros for signal LI0_BCM_ModReq */
#define l_u8_rd_LI0_BCM_ModReq() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_ModReq] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_ModReq) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_ModReq )) >> LIN_BIT_OFFSET_LI0_BCM_ModReq))
#define l_u8_wr_LI0_BCM_ModReq(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_ModReq] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_ModReq] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_ModReq) - 1) << LIN_BIT_OFFSET_LI0_BCM_ModReq)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_ModReq) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_ModReq))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_ModReq] = 1;}

/* static access macros for signal LI0_RLS_ModReq */
#define l_u8_rd_LI0_RLS_ModReq() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ModReq] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_ModReq) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_ModReq )) >> LIN_BIT_OFFSET_LI0_RLS_ModReq))
#define l_u8_wr_LI0_RLS_ModReq(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ModReq] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ModReq] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_ModReq) - 1) << LIN_BIT_OFFSET_LI0_RLS_ModReq)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_ModReq) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_ModReq))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ModReq] = 1;}

/* static access macros for signal LI0_RLS_ClosedWind */
#define l_u8_rd_LI0_RLS_ClosedWind() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ClosedWind] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_ClosedWind) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_ClosedWind )) >> LIN_BIT_OFFSET_LI0_RLS_ClosedWind))
#define l_u8_wr_LI0_RLS_ClosedWind(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ClosedWind] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ClosedWind] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_ClosedWind) - 1) << LIN_BIT_OFFSET_LI0_RLS_ClosedWind)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_ClosedWind) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_ClosedWind))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ClosedWind] = 1;}



/* Signal flag APIs */


#define l_flg_tst_LI0_BCM_WiperPosition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperPosition)
#define l_flg_clr_LI0_BCM_WiperPosition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperPosition)

#define l_flg_tst_LI0_BCM_Washer_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Washer],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Washer)
#define l_flg_clr_LI0_BCM_Washer_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Washer],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Washer)

#define l_flg_tst_LI0_BCM_Amb_LV_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Amb_LV],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Amb_LV)
#define l_flg_clr_LI0_BCM_Amb_LV_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Amb_LV],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Amb_LV)

#define l_flg_tst_LI0_BCM_RainSensitivity_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RainSensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RainSensitivity)
#define l_flg_clr_LI0_BCM_RainSensitivity_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RainSensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RainSensitivity)

#define l_flg_tst_LI0_BCM_VehicleSpeed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_VehicleSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_VehicleSpeed)
#define l_flg_clr_LI0_BCM_VehicleSpeed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_VehicleSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_VehicleSpeed)

#define l_flg_tst_LI0_RLS_ContinuteReq_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ContinuteReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ContinuteReq)
#define l_flg_clr_LI0_RLS_ContinuteReq_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ContinuteReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ContinuteReq)

#define l_flg_tst_LI0_RLS_DiagnnosticReq_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_DiagnnosticReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_DiagnnosticReq)
#define l_flg_clr_LI0_RLS_DiagnnosticReq_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_DiagnnosticReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_DiagnnosticReq)

#define l_flg_tst_LI0_RLS_AppResetStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppResetStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_AppResetStatus)
#define l_flg_clr_LI0_RLS_AppResetStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppResetStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_AppResetStatus)

#define l_flg_tst_LI0_RLS_AppConfigurationStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_AppConfigurationStatus)
#define l_flg_clr_LI0_RLS_AppConfigurationStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppConfigurationStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_AppConfigurationStatus)

#define l_flg_tst_LI0_RLS_AppStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_AppStatus)
#define l_flg_clr_LI0_RLS_AppStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_AppStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_AppStatus)

#define l_flg_tst_LI0_RLS_LinComStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LinComStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LinComStatus)
#define l_flg_clr_LI0_RLS_LinComStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LinComStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LinComStatus)

#define l_flg_tst_LI0_RLS_WiperRequest_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_WiperRequest],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_WiperRequest)
#define l_flg_clr_LI0_RLS_WiperRequest_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_WiperRequest],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_WiperRequest)

#define l_flg_tst_LI0_RLS_Amb_LV_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_LV],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_LV)
#define l_flg_clr_LI0_RLS_Amb_LV_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_LV],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_LV)

#define l_flg_tst_LI0_RLS_RainSensorError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RainSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RainSensorError)
#define l_flg_clr_LI0_RLS_RainSensorError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RainSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RainSensorError)

#define l_flg_tst_LI0_RLS_LightSensorInstalled_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorInstalled],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorInstalled)
#define l_flg_clr_LI0_RLS_LightSensorInstalled_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorInstalled],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorInstalled)

#define l_flg_tst_LI0_RLS_LightSensorError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorError)
#define l_flg_clr_LI0_RLS_LightSensorError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorError)

#define l_flg_tst_LI0_RLS_HumiditySensorInstalled_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_HumiditySensorInstalled)
#define l_flg_clr_LI0_RLS_HumiditySensorInstalled_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_HumiditySensorInstalled],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_HumiditySensorInstalled)

#define l_flg_tst_LI0_RLS_Amb_Value_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_Value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_Value)
#define l_flg_clr_LI0_RLS_Amb_Value_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_Value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_Value)

#define l_flg_tst_LI0_RLS_FW_Value_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_FW_Value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_FW_Value)
#define l_flg_clr_LI0_RLS_FW_Value_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_FW_Value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_FW_Value)

#define l_flg_tst_LI0_BCM_ModReq_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_ModReq],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_ModReq)
#define l_flg_clr_LI0_BCM_ModReq_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_ModReq],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_ModReq)

#define l_flg_tst_LI0_RLS_ModReq_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ModReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ModReq)
#define l_flg_clr_LI0_RLS_ModReq_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ModReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ModReq)

#define l_flg_tst_LI0_RLS_ClosedWind_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ClosedWind],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ClosedWind)
#define l_flg_clr_LI0_RLS_ClosedWind_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ClosedWind],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ClosedWind)



/* Frame flag APIs */

#define l_flg_tst_LI0_BCM_01_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_01],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_01)
#define l_flg_clr_LI0_BCM_01_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_01],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_01)

#define l_flg_tst_LI0_RLS_01_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_01],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_01)
#define l_flg_clr_LI0_RLS_01_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_01],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_01)



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */
