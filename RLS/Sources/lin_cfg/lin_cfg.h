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


#define LIN_BAUD_RATE    19200    	 /*For slave*/ 
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
#define LIN_FRAME_BUF_SIZE			24
#define LIN_FLAG_BUF_SIZE			5

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
#define LIN_NUM_OF_SIGS  20
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_BCM_WiperPosition

   , LI0_BCM_WiperSwitch
  
   , LI0_BCM_Washer
  
   , LI0_BCM_WindowStatus
  
   , LI0_BCM_Ignition
  
   , LI0_BCM_RainSensitivity
  
   , LI0_BCM_VehicleSpeed
  
   , LI0_BCM_Transmision550nm
  
   , LI0_BCM_Transmision880nm
  
   , LI0_RLS_WiperRequest
  
   , LI0_RLS_RainSensorError
  
   , LI0_RLS_WindowCloseReq
  
   , LI0_RLS_LightSensorError
  
   , LI0_RLS_LightRequest
  
   , LI0_RLS_VotalgeError
  
   , LI0_RLS_ResponseError
  
   , LI0_RLS_FW_value
  
   , LI0_RLS_Amb_value
  
   , LI0_RLS_Solar_Right
  
   , LI0_RLS_Solar_Left
  
  
} l_signal_handle; 
/**********************************************************************/
/*****************               Frame             ********************/
/**********************************************************************/
/* Number of frames */
#define LIN_NUM_OF_FRMS  5 
/* List of frames */
typedef enum {
/* All frames for master node */

   /* Interface_name = LI0 */

   LI0_BCM_01

   , LI0_RLS_01
  
   , LI0_RLS_02
  
   , LI0_MasterReq
  
   , LI0_SlaveResp
  
  
} l_frame_handle; 
 
/**********************************************************************/
/***************             Configuration          *******************/
/**********************************************************************/
/* Size of configuration in ROM and RAM used for interface: LI1 */
#define LIN_SIZE_OF_CFG  7 
#define LIN_CFG_FRAME_NUM  3 
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

#define LIN_BYTE_OFFSET_LI0_BCM_WiperSwitch    0
#define LIN_BIT_OFFSET_LI0_BCM_WiperSwitch    1
#define LIN_SIGNAL_SIZE_LI0_BCM_WiperSwitch    3
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperSwitch    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperSwitch    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_WiperSwitch    0

#define LIN_BYTE_OFFSET_LI0_BCM_Washer    0
#define LIN_BIT_OFFSET_LI0_BCM_Washer    4
#define LIN_SIGNAL_SIZE_LI0_BCM_Washer    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_Washer    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_Washer    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Washer    0

#define LIN_BYTE_OFFSET_LI0_BCM_WindowStatus    0
#define LIN_BIT_OFFSET_LI0_BCM_WindowStatus    5
#define LIN_SIGNAL_SIZE_LI0_BCM_WindowStatus    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_WindowStatus    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_WindowStatus    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_WindowStatus    0

#define LIN_BYTE_OFFSET_LI0_BCM_Ignition    0
#define LIN_BIT_OFFSET_LI0_BCM_Ignition    6
#define LIN_SIGNAL_SIZE_LI0_BCM_Ignition    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_Ignition    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_Ignition    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Ignition    0

#define LIN_BYTE_OFFSET_LI0_BCM_RainSensitivity    1
#define LIN_BIT_OFFSET_LI0_BCM_RainSensitivity    0
#define LIN_SIGNAL_SIZE_LI0_BCM_RainSensitivity    3
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_RainSensitivity    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_RainSensitivity    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RainSensitivity    0

#define LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed    2
#define LIN_BIT_OFFSET_LI0_BCM_VehicleSpeed    0
#define LIN_SIGNAL_SIZE_LI0_BCM_VehicleSpeed    16
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_VehicleSpeed    0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_VehicleSpeed    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_VehicleSpeed    0

#define LIN_BYTE_OFFSET_LI0_BCM_Transmision550nm    4
#define LIN_BIT_OFFSET_LI0_BCM_Transmision550nm    0
#define LIN_SIGNAL_SIZE_LI0_BCM_Transmision550nm    8
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_Transmision550nm    1
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_Transmision550nm    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Transmision550nm    0

#define LIN_BYTE_OFFSET_LI0_BCM_Transmision880nm    5
#define LIN_BIT_OFFSET_LI0_BCM_Transmision880nm    0
#define LIN_SIGNAL_SIZE_LI0_BCM_Transmision880nm    8
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_Transmision880nm    1
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_Transmision880nm    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Transmision880nm    0

#define LIN_BYTE_OFFSET_LI0_RLS_WiperRequest    8
#define LIN_BIT_OFFSET_LI0_RLS_WiperRequest    0
#define LIN_SIGNAL_SIZE_LI0_RLS_WiperRequest    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_WiperRequest    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_WiperRequest    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_WiperRequest    1

#define LIN_BYTE_OFFSET_LI0_RLS_RainSensorError    8
#define LIN_BIT_OFFSET_LI0_RLS_RainSensorError    2
#define LIN_SIGNAL_SIZE_LI0_RLS_RainSensorError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_RainSensorError    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_RainSensorError    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RainSensorError    1

#define LIN_BYTE_OFFSET_LI0_RLS_WindowCloseReq    8
#define LIN_BIT_OFFSET_LI0_RLS_WindowCloseReq    3
#define LIN_SIGNAL_SIZE_LI0_RLS_WindowCloseReq    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_WindowCloseReq    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_WindowCloseReq    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_WindowCloseReq    1

#define LIN_BYTE_OFFSET_LI0_RLS_LightSensorError    8
#define LIN_BIT_OFFSET_LI0_RLS_LightSensorError    4
#define LIN_SIGNAL_SIZE_LI0_RLS_LightSensorError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorError    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorError    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LightSensorError    1

#define LIN_BYTE_OFFSET_LI0_RLS_LightRequest    8
#define LIN_BIT_OFFSET_LI0_RLS_LightRequest    5
#define LIN_SIGNAL_SIZE_LI0_RLS_LightRequest    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightRequest    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_LightRequest    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LightRequest    1

#define LIN_BYTE_OFFSET_LI0_RLS_VotalgeError    8
#define LIN_BIT_OFFSET_LI0_RLS_VotalgeError    6
#define LIN_SIGNAL_SIZE_LI0_RLS_VotalgeError    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_VotalgeError    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_VotalgeError    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_VotalgeError    1

#define LIN_BYTE_OFFSET_LI0_RLS_ResponseError    9
#define LIN_BIT_OFFSET_LI0_RLS_ResponseError    0
#define LIN_SIGNAL_SIZE_LI0_RLS_ResponseError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_ResponseError    2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_ResponseError    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ResponseError    1

#define LIN_BYTE_OFFSET_LI0_RLS_FW_value    10
#define LIN_BIT_OFFSET_LI0_RLS_FW_value    0
#define LIN_SIGNAL_SIZE_LI0_RLS_FW_value    12
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_FW_value    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_FW_value    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_FW_value    1

#define LIN_BYTE_OFFSET_LI0_RLS_Amb_value    12
#define LIN_BIT_OFFSET_LI0_RLS_Amb_value    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Amb_value    12
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_value    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_value    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Amb_value    1

#define LIN_BYTE_OFFSET_LI0_RLS_Solar_Right    16
#define LIN_BIT_OFFSET_LI0_RLS_Solar_Right    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Solar_Right    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Solar_Right    4
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Solar_Right    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Solar_Right    2

#define LIN_BYTE_OFFSET_LI0_RLS_Solar_Left    17
#define LIN_BIT_OFFSET_LI0_RLS_Solar_Left    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Solar_Left    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Solar_Left    4
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Solar_Left    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Solar_Left    2




#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_01             0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_01             2
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_02             4
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_02              0


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

/* static access macros for signal LI0_BCM_WiperSwitch */
#define l_u8_rd_LI0_BCM_WiperSwitch() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WiperSwitch] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_WiperSwitch) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_WiperSwitch )) >> LIN_BIT_OFFSET_LI0_BCM_WiperSwitch))
#define l_u8_wr_LI0_BCM_WiperSwitch(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WiperSwitch] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WiperSwitch] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_WiperSwitch) - 1) << LIN_BIT_OFFSET_LI0_BCM_WiperSwitch)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_WiperSwitch) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_WiperSwitch))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_WiperSwitch] = 1;}

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

/* static access macros for signal LI0_BCM_WindowStatus */
#define l_bool_rd_LI0_BCM_WindowStatus() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WindowStatus], \
   	LIN_BIT_OFFSET_LI0_BCM_WindowStatus))
#define l_bool_wr_LI0_BCM_WindowStatus(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WindowStatus], \
  	LIN_BIT_OFFSET_LI0_BCM_WindowStatus)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_WindowStatus], \
  	LIN_BIT_OFFSET_LI0_BCM_WindowStatus));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_WindowStatus] = 1;}

/* static access macros for signal LI0_BCM_Ignition */
#define l_bool_rd_LI0_BCM_Ignition() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Ignition], \
   	LIN_BIT_OFFSET_LI0_BCM_Ignition))
#define l_bool_wr_LI0_BCM_Ignition(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Ignition], \
  	LIN_BIT_OFFSET_LI0_BCM_Ignition)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Ignition], \
  	LIN_BIT_OFFSET_LI0_BCM_Ignition));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Ignition] = 1;}

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
#define l_u16_rd_LI0_BCM_VehicleSpeed() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed + 1] & 0xff) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed]) >> 0x00))
#define l_u16_wr_LI0_BCM_VehicleSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed + 1] &  (0x00))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0xff))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_VehicleSpeed] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_BCM_VehicleSpeed))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_VehicleSpeed] = 1;}

/* static access macros for signal LI0_BCM_Transmision550nm */
#define l_u8_rd_LI0_BCM_Transmision550nm() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Transmision550nm] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_Transmision550nm) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_Transmision550nm )) >> LIN_BIT_OFFSET_LI0_BCM_Transmision550nm))
#define l_u8_wr_LI0_BCM_Transmision550nm(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Transmision550nm] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Transmision550nm] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_Transmision550nm) - 1) << LIN_BIT_OFFSET_LI0_BCM_Transmision550nm)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_Transmision550nm) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_Transmision550nm))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Transmision550nm] = 1;}

/* static access macros for signal LI0_BCM_Transmision880nm */
#define l_u8_rd_LI0_BCM_Transmision880nm() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Transmision880nm] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_Transmision880nm) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_Transmision880nm )) >> LIN_BIT_OFFSET_LI0_BCM_Transmision880nm))
#define l_u8_wr_LI0_BCM_Transmision880nm(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Transmision880nm] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Transmision880nm] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_Transmision880nm) - 1) << LIN_BIT_OFFSET_LI0_BCM_Transmision880nm)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_Transmision880nm) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_Transmision880nm))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Transmision880nm] = 1;}

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

/* static access macros for signal LI0_RLS_WindowCloseReq */
#define l_bool_rd_LI0_RLS_WindowCloseReq() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_WindowCloseReq], \
   	LIN_BIT_OFFSET_LI0_RLS_WindowCloseReq))
#define l_bool_wr_LI0_RLS_WindowCloseReq(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_WindowCloseReq], \
  	LIN_BIT_OFFSET_LI0_RLS_WindowCloseReq)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_WindowCloseReq], \
  	LIN_BIT_OFFSET_LI0_RLS_WindowCloseReq));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_WindowCloseReq] = 1;}

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

/* static access macros for signal LI0_RLS_LightRequest */
#define l_bool_rd_LI0_RLS_LightRequest() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightRequest], \
   	LIN_BIT_OFFSET_LI0_RLS_LightRequest))
#define l_bool_wr_LI0_RLS_LightRequest(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightRequest], \
  	LIN_BIT_OFFSET_LI0_RLS_LightRequest)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LightRequest], \
  	LIN_BIT_OFFSET_LI0_RLS_LightRequest));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LightRequest] = 1;}

/* static access macros for signal LI0_RLS_VotalgeError */
#define l_u8_rd_LI0_RLS_VotalgeError() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_VotalgeError] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_VotalgeError) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_VotalgeError )) >> LIN_BIT_OFFSET_LI0_RLS_VotalgeError))
#define l_u8_wr_LI0_RLS_VotalgeError(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_VotalgeError] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_VotalgeError] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_VotalgeError) - 1) << LIN_BIT_OFFSET_LI0_RLS_VotalgeError)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_VotalgeError) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_VotalgeError))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_VotalgeError] = 1;}

/* static access macros for signal LI0_RLS_ResponseError */
#define l_bool_rd_LI0_RLS_ResponseError() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ResponseError], \
   	LIN_BIT_OFFSET_LI0_RLS_ResponseError))
#define l_bool_wr_LI0_RLS_ResponseError(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ResponseError], \
  	LIN_BIT_OFFSET_LI0_RLS_ResponseError)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_ResponseError], \
  	LIN_BIT_OFFSET_LI0_RLS_ResponseError));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_ResponseError] = 1;}

/* static access macros for signal LI0_RLS_FW_value */
#define l_u16_rd_LI0_RLS_FW_value() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_value + 1] & 0x0f) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_value]) >> 0x00))
#define l_u16_wr_LI0_RLS_FW_value(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_value + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_value + 1] &  (0xf0))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0x0f))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_value] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_FW_value] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_RLS_FW_value))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_FW_value] = 1;}

/* static access macros for signal LI0_RLS_Amb_value */
#define l_u16_rd_LI0_RLS_Amb_value() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_value + 1] & 0x0f) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_value]) >> 0x00))
#define l_u16_wr_LI0_RLS_Amb_value(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_value + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_value + 1] &  (0xf0))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0x0f))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_value] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Amb_value] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_RLS_Amb_value))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Amb_value] = 1;}

/* static access macros for signal LI0_RLS_Solar_Right */
#define l_u8_rd_LI0_RLS_Solar_Right() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Solar_Right] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Solar_Right) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Solar_Right )) >> LIN_BIT_OFFSET_LI0_RLS_Solar_Right))
#define l_u8_wr_LI0_RLS_Solar_Right(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Solar_Right] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Solar_Right] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Solar_Right) - 1) << LIN_BIT_OFFSET_LI0_RLS_Solar_Right)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Solar_Right) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Solar_Right))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Solar_Right] = 1;}

/* static access macros for signal LI0_RLS_Solar_Left */
#define l_u8_rd_LI0_RLS_Solar_Left() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Solar_Left] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Solar_Left) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Solar_Left )) >> LIN_BIT_OFFSET_LI0_RLS_Solar_Left))
#define l_u8_wr_LI0_RLS_Solar_Left(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Solar_Left] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Solar_Left] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Solar_Left) - 1) << LIN_BIT_OFFSET_LI0_RLS_Solar_Left)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Solar_Left) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Solar_Left))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Solar_Left] = 1;}



/* Signal flag APIs */


#define l_flg_tst_LI0_BCM_WiperPosition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperPosition)
#define l_flg_clr_LI0_BCM_WiperPosition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperPosition)

#define l_flg_tst_LI0_BCM_WiperSwitch_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperSwitch)
#define l_flg_clr_LI0_BCM_WiperSwitch_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WiperSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WiperSwitch)

#define l_flg_tst_LI0_BCM_Washer_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Washer],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Washer)
#define l_flg_clr_LI0_BCM_Washer_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Washer],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Washer)

#define l_flg_tst_LI0_BCM_WindowStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WindowStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WindowStatus)
#define l_flg_clr_LI0_BCM_WindowStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_WindowStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_WindowStatus)

#define l_flg_tst_LI0_BCM_Ignition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Ignition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Ignition)
#define l_flg_clr_LI0_BCM_Ignition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Ignition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Ignition)

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

#define l_flg_tst_LI0_BCM_Transmision550nm_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Transmision550nm],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Transmision550nm)
#define l_flg_clr_LI0_BCM_Transmision550nm_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Transmision550nm],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Transmision550nm)

#define l_flg_tst_LI0_BCM_Transmision880nm_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Transmision880nm],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Transmision880nm)
#define l_flg_clr_LI0_BCM_Transmision880nm_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Transmision880nm],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Transmision880nm)

#define l_flg_tst_LI0_RLS_WiperRequest_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_WiperRequest],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_WiperRequest)
#define l_flg_clr_LI0_RLS_WiperRequest_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_WiperRequest],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_WiperRequest)

#define l_flg_tst_LI0_RLS_RainSensorError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RainSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RainSensorError)
#define l_flg_clr_LI0_RLS_RainSensorError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RainSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RainSensorError)

#define l_flg_tst_LI0_RLS_WindowCloseReq_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_WindowCloseReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_WindowCloseReq)
#define l_flg_clr_LI0_RLS_WindowCloseReq_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_WindowCloseReq],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_WindowCloseReq)

#define l_flg_tst_LI0_RLS_LightSensorError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorError)
#define l_flg_clr_LI0_RLS_LightSensorError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightSensorError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightSensorError)

#define l_flg_tst_LI0_RLS_LightRequest_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightRequest],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightRequest)
#define l_flg_clr_LI0_RLS_LightRequest_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LightRequest],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LightRequest)

#define l_flg_tst_LI0_RLS_VotalgeError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_VotalgeError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_VotalgeError)
#define l_flg_clr_LI0_RLS_VotalgeError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_VotalgeError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_VotalgeError)

#define l_flg_tst_LI0_RLS_ResponseError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ResponseError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ResponseError)
#define l_flg_clr_LI0_RLS_ResponseError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_ResponseError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_ResponseError)

#define l_flg_tst_LI0_RLS_FW_value_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_FW_value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_FW_value)
#define l_flg_clr_LI0_RLS_FW_value_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_FW_value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_FW_value)

#define l_flg_tst_LI0_RLS_Amb_value_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_value)
#define l_flg_clr_LI0_RLS_Amb_value_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Amb_value],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Amb_value)

#define l_flg_tst_LI0_RLS_Solar_Right_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Solar_Right],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Solar_Right)
#define l_flg_clr_LI0_RLS_Solar_Right_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Solar_Right],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Solar_Right)

#define l_flg_tst_LI0_RLS_Solar_Left_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Solar_Left],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Solar_Left)
#define l_flg_clr_LI0_RLS_Solar_Left_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Solar_Left],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Solar_Left)



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

#define l_flg_tst_LI0_RLS_02_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_02],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_02)
#define l_flg_clr_LI0_RLS_02_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_02],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_02)



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */