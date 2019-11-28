/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      lin_cfg.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Fri Sep 07 16:59:11 CST 2018
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

#define MAX_QUEUE_SIZE 6

#define DIAGSRV_SESSION_DEFAULT 1
#define DIAGSRV_SESSION_PROGRAM 2
#define DIAGSRV_SESSION_EXTERN  3
#define DIAGSRV_SESSION_RESTART  7 

#define _DIAG_NUMBER_OF_SERVICES_    7

#define DIAGSRV_READ_BY_IDENTIFIER_ORDER    0

#define DIAGSRV_SAVE_CONFIGURATION_ORDER    1

#define DIAGSRV_ASSIGN_FRAME_ID_RANGE_ORDER    2

#define DIAGSRV_READ_DATA_BY_IDENTIFIER_ORDER    3

#define DIAGSRV_SESSION_CONTROL_ORDER    4

#define DIAGSRV_CONDITIONAL_CHANGE_NAD_ORDER    5

#define DIAGSRV_ASSIGN_NAD_ORDER    6

#define DIAGSRV_WRITE_DATA_BY_IDENTIFIER_ORDER    7


/**************** FRAME SUPPORT DEFINITION ******************/
#define _TL_SINGLE_FRAME_       0
#define _TL_MULTI_FRAME_        1

#define _TL_FRAME_SUPPORT_      _TL_MULTI_FRAME_

/* frame buffer size */
#define LIN_FRAME_BUF_SIZE			18
#define LIN_FLAG_BUF_SIZE			6

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
#define LIN_NUM_OF_SIGS  29
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_Ignition

   , LI0_SCS_Automatic
  
   , LI0_VehicleSpeed
  
   , LI0_Status_SMA
  
   , LI0_ParkPosition
  
   , LI0_RLS_HumidSensorValue
  
   , LI0_RLS_TempSensorValue
  
   , LI0_RLS_TempDewPoint
  
   , LI0_RLS_Humid_Temp_Error
  
   , LI0_RLS_LIN_Error
  
   , LI0_RLS_VotalgeError
  
   , LI0_S_COMMFAULT
  
   , LI0_S_Window_CMD
  
   , LI0_S_AUTO_Panel
  
   , LI0_S_Auto_Lamp
  
   , LI0_S_RS_FAULT
  
   , LI0_S_RAIN
  
   , LI0_S_AUTO_H
  
   , LI0_S_AUTO_L
  
   , LI0_RSP_Err
  
   , LI0_S_TRANS_550nm_RSP
  
   , LI0_S_TRANS_880nm_RSP
  
   , LI0_S_WASH
  
   , LI0_S_HIGH
  
   , LI0_S_LOW
  
   , LI0_S_SENS
  
   , LI0_S_Trans_550nm
  
   , LI0_S_Trans_880nm
  
   , LI0_S_WASH_MODE
  
  
} l_signal_handle; 
/**********************************************************************/
/*****************               Frame             ********************/
/**********************************************************************/
/* Number of frames */
#define LIN_NUM_OF_FRMS  6 
/* List of frames */
typedef enum {
/* All frames for master node */

   /* Interface_name = LI0 */

   LI0_BCM_01

   , LI0_BCM_02
  
   , LI0_RLS_01
  
   , LI0_RLS_02
  
   , LI0_MasterReq
  
   , LI0_SlaveResp
  
  
} l_frame_handle; 
 
/**********************************************************************/
/***************             Configuration          *******************/
/**********************************************************************/
/* Size of configuration in ROM and RAM used for interface: LI1 */
#define LIN_SIZE_OF_CFG  8 
#define LIN_CFG_FRAME_NUM  4 
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


#define LIN_BYTE_OFFSET_LI0_Ignition    0
#define LIN_BIT_OFFSET_LI0_Ignition    0
#define LIN_SIGNAL_SIZE_LI0_Ignition    2
#define LIN_FLAG_BYTE_OFFSET_LI0_Ignition    0
#define LIN_FLAG_BIT_OFFSET_LI0_Ignition    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Ignition    0

#define LIN_BYTE_OFFSET_LI0_SCS_Automatic    0
#define LIN_BIT_OFFSET_LI0_SCS_Automatic    5
#define LIN_SIGNAL_SIZE_LI0_SCS_Automatic    1
#define LIN_FLAG_BYTE_OFFSET_LI0_SCS_Automatic    0
#define LIN_FLAG_BIT_OFFSET_LI0_SCS_Automatic    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SCS_Automatic    0

#define LIN_BYTE_OFFSET_LI0_VehicleSpeed    4
#define LIN_BIT_OFFSET_LI0_VehicleSpeed    3
#define LIN_SIGNAL_SIZE_LI0_VehicleSpeed    13
#define LIN_FLAG_BYTE_OFFSET_LI0_VehicleSpeed    2
#define LIN_FLAG_BIT_OFFSET_LI0_VehicleSpeed    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_VehicleSpeed    1

#define LIN_BYTE_OFFSET_LI0_Status_SMA    0
#define LIN_BIT_OFFSET_LI0_Status_SMA    2
#define LIN_SIGNAL_SIZE_LI0_Status_SMA    2
#define LIN_FLAG_BYTE_OFFSET_LI0_Status_SMA    0
#define LIN_FLAG_BIT_OFFSET_LI0_Status_SMA    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Status_SMA    0

#define LIN_BYTE_OFFSET_LI0_ParkPosition    4
#define LIN_BIT_OFFSET_LI0_ParkPosition    0
#define LIN_SIGNAL_SIZE_LI0_ParkPosition    1
#define LIN_FLAG_BYTE_OFFSET_LI0_ParkPosition    2
#define LIN_FLAG_BIT_OFFSET_LI0_ParkPosition    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_ParkPosition    1

#define LIN_BYTE_OFFSET_LI0_RLS_HumidSensorValue    10
#define LIN_BIT_OFFSET_LI0_RLS_HumidSensorValue    0
#define LIN_SIGNAL_SIZE_LI0_RLS_HumidSensorValue    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_HumidSensorValue    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_HumidSensorValue    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_HumidSensorValue    2

#define LIN_BYTE_OFFSET_LI0_RLS_TempSensorValue    11
#define LIN_BIT_OFFSET_LI0_RLS_TempSensorValue    0
#define LIN_SIGNAL_SIZE_LI0_RLS_TempSensorValue    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_TempSensorValue    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_TempSensorValue    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_TempSensorValue    2

#define LIN_BYTE_OFFSET_LI0_RLS_TempDewPoint    12
#define LIN_BIT_OFFSET_LI0_RLS_TempDewPoint    0
#define LIN_SIGNAL_SIZE_LI0_RLS_TempDewPoint    11
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_TempDewPoint    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_TempDewPoint    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_TempDewPoint    2

#define LIN_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error    13
#define LIN_BIT_OFFSET_LI0_RLS_Humid_Temp_Error    5
#define LIN_SIGNAL_SIZE_LI0_RLS_Humid_Temp_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid_Temp_Error    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error    2

#define LIN_BYTE_OFFSET_LI0_RLS_LIN_Error    13
#define LIN_BIT_OFFSET_LI0_RLS_LIN_Error    4
#define LIN_SIGNAL_SIZE_LI0_RLS_LIN_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_LIN_Error    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_LIN_Error    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LIN_Error    2

#define LIN_BYTE_OFFSET_LI0_RLS_VotalgeError    13
#define LIN_BIT_OFFSET_LI0_RLS_VotalgeError    6
#define LIN_SIGNAL_SIZE_LI0_RLS_VotalgeError    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_VotalgeError    3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_VotalgeError    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_VotalgeError    2

#define LIN_BYTE_OFFSET_LI0_S_COMMFAULT    14
#define LIN_BIT_OFFSET_LI0_S_COMMFAULT    0
#define LIN_SIGNAL_SIZE_LI0_S_COMMFAULT    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_COMMFAULT    4
#define LIN_FLAG_BIT_OFFSET_LI0_S_COMMFAULT    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_COMMFAULT    3

#define LIN_BYTE_OFFSET_LI0_S_Window_CMD    14
#define LIN_BIT_OFFSET_LI0_S_Window_CMD    1
#define LIN_SIGNAL_SIZE_LI0_S_Window_CMD    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_Window_CMD    4
#define LIN_FLAG_BIT_OFFSET_LI0_S_Window_CMD    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Window_CMD    3

#define LIN_BYTE_OFFSET_LI0_S_AUTO_Panel    14
#define LIN_BIT_OFFSET_LI0_S_AUTO_Panel    2
#define LIN_SIGNAL_SIZE_LI0_S_AUTO_Panel    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_Panel    4
#define LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_Panel    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_AUTO_Panel    3

#define LIN_BYTE_OFFSET_LI0_S_Auto_Lamp    14
#define LIN_BIT_OFFSET_LI0_S_Auto_Lamp    3
#define LIN_SIGNAL_SIZE_LI0_S_Auto_Lamp    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_Auto_Lamp    4
#define LIN_FLAG_BIT_OFFSET_LI0_S_Auto_Lamp    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Auto_Lamp    3

#define LIN_BYTE_OFFSET_LI0_S_RS_FAULT    14
#define LIN_BIT_OFFSET_LI0_S_RS_FAULT    4
#define LIN_SIGNAL_SIZE_LI0_S_RS_FAULT    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_RS_FAULT    4
#define LIN_FLAG_BIT_OFFSET_LI0_S_RS_FAULT    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_RS_FAULT    3

#define LIN_BYTE_OFFSET_LI0_S_RAIN    14
#define LIN_BIT_OFFSET_LI0_S_RAIN    5
#define LIN_SIGNAL_SIZE_LI0_S_RAIN    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_RAIN    4
#define LIN_FLAG_BIT_OFFSET_LI0_S_RAIN    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_RAIN    3

#define LIN_BYTE_OFFSET_LI0_S_AUTO_H    14
#define LIN_BIT_OFFSET_LI0_S_AUTO_H    6
#define LIN_SIGNAL_SIZE_LI0_S_AUTO_H    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_H    4
#define LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_H    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_AUTO_H    3

#define LIN_BYTE_OFFSET_LI0_S_AUTO_L    14
#define LIN_BIT_OFFSET_LI0_S_AUTO_L    7
#define LIN_SIGNAL_SIZE_LI0_S_AUTO_L    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_L    5
#define LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_L    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_AUTO_L    3

#define LIN_BYTE_OFFSET_LI0_RSP_Err    15
#define LIN_BIT_OFFSET_LI0_RSP_Err    7
#define LIN_SIGNAL_SIZE_LI0_RSP_Err    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RSP_Err    5
#define LIN_FLAG_BIT_OFFSET_LI0_RSP_Err    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RSP_Err    3

#define LIN_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP    16
#define LIN_BIT_OFFSET_LI0_S_TRANS_550nm_RSP    0
#define LIN_SIGNAL_SIZE_LI0_S_TRANS_550nm_RSP    8
#define LIN_FLAG_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP    5
#define LIN_FLAG_BIT_OFFSET_LI0_S_TRANS_550nm_RSP    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP    3

#define LIN_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP    17
#define LIN_BIT_OFFSET_LI0_S_TRANS_880nm_RSP    0
#define LIN_SIGNAL_SIZE_LI0_S_TRANS_880nm_RSP    8
#define LIN_FLAG_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP    5
#define LIN_FLAG_BIT_OFFSET_LI0_S_TRANS_880nm_RSP    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP    3

#define LIN_BYTE_OFFSET_LI0_S_WASH    0
#define LIN_BIT_OFFSET_LI0_S_WASH    4
#define LIN_SIGNAL_SIZE_LI0_S_WASH    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_WASH    0
#define LIN_FLAG_BIT_OFFSET_LI0_S_WASH    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_WASH    0

#define LIN_BYTE_OFFSET_LI0_S_HIGH    0
#define LIN_BIT_OFFSET_LI0_S_HIGH    6
#define LIN_SIGNAL_SIZE_LI0_S_HIGH    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_HIGH    0
#define LIN_FLAG_BIT_OFFSET_LI0_S_HIGH    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_HIGH    0

#define LIN_BYTE_OFFSET_LI0_S_LOW    0
#define LIN_BIT_OFFSET_LI0_S_LOW    7
#define LIN_SIGNAL_SIZE_LI0_S_LOW    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_LOW    0
#define LIN_FLAG_BIT_OFFSET_LI0_S_LOW    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_LOW    0

#define LIN_BYTE_OFFSET_LI0_S_SENS    1
#define LIN_BIT_OFFSET_LI0_S_SENS    5
#define LIN_SIGNAL_SIZE_LI0_S_SENS    3
#define LIN_FLAG_BYTE_OFFSET_LI0_S_SENS    0
#define LIN_FLAG_BIT_OFFSET_LI0_S_SENS    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_SENS    0

#define LIN_BYTE_OFFSET_LI0_S_Trans_550nm    2
#define LIN_BIT_OFFSET_LI0_S_Trans_550nm    0
#define LIN_SIGNAL_SIZE_LI0_S_Trans_550nm    8
#define LIN_FLAG_BYTE_OFFSET_LI0_S_Trans_550nm    1
#define LIN_FLAG_BIT_OFFSET_LI0_S_Trans_550nm    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Trans_550nm    0

#define LIN_BYTE_OFFSET_LI0_S_Trans_880nm    3
#define LIN_BIT_OFFSET_LI0_S_Trans_880nm    0
#define LIN_SIGNAL_SIZE_LI0_S_Trans_880nm    8
#define LIN_FLAG_BYTE_OFFSET_LI0_S_Trans_880nm    1
#define LIN_FLAG_BIT_OFFSET_LI0_S_Trans_880nm    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Trans_880nm    0

#define LIN_BYTE_OFFSET_LI0_S_WASH_MODE    4
#define LIN_BIT_OFFSET_LI0_S_WASH_MODE    1
#define LIN_SIGNAL_SIZE_LI0_S_WASH_MODE    1
#define LIN_FLAG_BYTE_OFFSET_LI0_S_WASH_MODE    2
#define LIN_FLAG_BIT_OFFSET_LI0_S_WASH_MODE    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_WASH_MODE    1




#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_01             0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_02             2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_02              0

#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_01             3
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_02             4
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_02              0

/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */


/* static access macros for signal LI0_Ignition */
   
#define l_u8_rd_LI0_Ignition() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Ignition] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_Ignition) - 1) \
    << LIN_BIT_OFFSET_LI0_Ignition )) >> LIN_BIT_OFFSET_LI0_Ignition))
#define l_u8_wr_LI0_Ignition(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Ignition] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Ignition] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_Ignition) - 1) << LIN_BIT_OFFSET_LI0_Ignition)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_Ignition) - 1) & (A)) << LIN_BIT_OFFSET_LI0_Ignition))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Ignition] = 1;}

/* static access macros for signal LI0_SCS_Automatic */
   
#define l_bool_rd_LI0_SCS_Automatic() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_Automatic], \
   	LIN_BIT_OFFSET_LI0_SCS_Automatic))
#define l_bool_wr_LI0_SCS_Automatic(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_Automatic], \
  	LIN_BIT_OFFSET_LI0_SCS_Automatic)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_Automatic], \
  	LIN_BIT_OFFSET_LI0_SCS_Automatic));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SCS_Automatic] = 1;}

/* static access macros for signal LI0_VehicleSpeed */
#define l_u16_rd_LI0_VehicleSpeed() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed + 1] & 0xff) << 5) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed]) >> 0x03))
#define l_u16_wr_LI0_VehicleSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed + 1] &  (0x00))) | \
	((l_u8) ((l_u8) ((A) >> 5)) & 0xff))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed] & (0x07))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_VehicleSpeed))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_VehicleSpeed] = 1;}

/* static access macros for signal LI0_Status_SMA */
#define l_u8_rd_LI0_Status_SMA() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Status_SMA] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_Status_SMA) - 1) \
    << LIN_BIT_OFFSET_LI0_Status_SMA )) >> LIN_BIT_OFFSET_LI0_Status_SMA))
#define l_u8_wr_LI0_Status_SMA(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Status_SMA] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Status_SMA] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_Status_SMA) - 1) << LIN_BIT_OFFSET_LI0_Status_SMA)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_Status_SMA) - 1) & (A)) << LIN_BIT_OFFSET_LI0_Status_SMA))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Status_SMA] = 1;}

/* static access macros for signal LI0_ParkPosition */
   
#define l_bool_rd_LI0_ParkPosition() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_ParkPosition], \
   	LIN_BIT_OFFSET_LI0_ParkPosition))
#define l_bool_wr_LI0_ParkPosition(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_ParkPosition], \
  	LIN_BIT_OFFSET_LI0_ParkPosition)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_ParkPosition], \
  	LIN_BIT_OFFSET_LI0_ParkPosition));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_ParkPosition] = 1;}

/* static access macros for signal LI0_RLS_HumidSensorValue */
   
#define l_u8_rd_LI0_RLS_HumidSensorValue() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_HumidSensorValue] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_HumidSensorValue) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_HumidSensorValue )) >> LIN_BIT_OFFSET_LI0_RLS_HumidSensorValue))
#define l_u8_wr_LI0_RLS_HumidSensorValue(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_HumidSensorValue] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_HumidSensorValue] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_HumidSensorValue) - 1) << LIN_BIT_OFFSET_LI0_RLS_HumidSensorValue)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_HumidSensorValue) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_HumidSensorValue))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_HumidSensorValue] = 1;}

/* static access macros for signal LI0_RLS_TempSensorValue */
   
#define l_u8_rd_LI0_RLS_TempSensorValue() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempSensorValue] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_TempSensorValue) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_TempSensorValue )) >> LIN_BIT_OFFSET_LI0_RLS_TempSensorValue))
#define l_u8_wr_LI0_RLS_TempSensorValue(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempSensorValue] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempSensorValue] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_TempSensorValue) - 1) << LIN_BIT_OFFSET_LI0_RLS_TempSensorValue)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_TempSensorValue) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_TempSensorValue))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_TempSensorValue] = 1;}

/* static access macros for signal LI0_RLS_TempDewPoint */
#define l_u16_rd_LI0_RLS_TempDewPoint() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempDewPoint + 1] & 0x07) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempDewPoint]) >> 0x00))
#define l_u16_wr_LI0_RLS_TempDewPoint(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempDewPoint + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempDewPoint + 1] &  (0xf8))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0x07))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempDewPoint] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_TempDewPoint] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_RLS_TempDewPoint))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_TempDewPoint] = 1;}

/* static access macros for signal LI0_RLS_Humid_Temp_Error */
#define l_bool_rd_LI0_RLS_Humid_Temp_Error() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error], \
   	LIN_BIT_OFFSET_LI0_RLS_Humid_Temp_Error))
#define l_bool_wr_LI0_RLS_Humid_Temp_Error(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error], \
  	LIN_BIT_OFFSET_LI0_RLS_Humid_Temp_Error)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error], \
  	LIN_BIT_OFFSET_LI0_RLS_Humid_Temp_Error));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error] = 1;}

/* static access macros for signal LI0_RLS_LIN_Error */
#define l_bool_rd_LI0_RLS_LIN_Error() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LIN_Error], \
   	LIN_BIT_OFFSET_LI0_RLS_LIN_Error))
#define l_bool_wr_LI0_RLS_LIN_Error(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LIN_Error], \
  	LIN_BIT_OFFSET_LI0_RLS_LIN_Error)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_LIN_Error], \
  	LIN_BIT_OFFSET_LI0_RLS_LIN_Error));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_LIN_Error] = 1;}

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

/* static access macros for signal LI0_S_COMMFAULT */
#define l_bool_rd_LI0_S_COMMFAULT() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_COMMFAULT], \
   	LIN_BIT_OFFSET_LI0_S_COMMFAULT))
#define l_bool_wr_LI0_S_COMMFAULT(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_COMMFAULT], \
  	LIN_BIT_OFFSET_LI0_S_COMMFAULT)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_COMMFAULT], \
  	LIN_BIT_OFFSET_LI0_S_COMMFAULT));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_COMMFAULT] = 1;}

/* static access macros for signal LI0_S_Window_CMD */
#define l_bool_rd_LI0_S_Window_CMD() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Window_CMD], \
   	LIN_BIT_OFFSET_LI0_S_Window_CMD))
#define l_bool_wr_LI0_S_Window_CMD(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Window_CMD], \
  	LIN_BIT_OFFSET_LI0_S_Window_CMD)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Window_CMD], \
  	LIN_BIT_OFFSET_LI0_S_Window_CMD));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Window_CMD] = 1;}

/* static access macros for signal LI0_S_AUTO_Panel */
#define l_bool_rd_LI0_S_AUTO_Panel() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_Panel], \
   	LIN_BIT_OFFSET_LI0_S_AUTO_Panel))
#define l_bool_wr_LI0_S_AUTO_Panel(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_Panel], \
  	LIN_BIT_OFFSET_LI0_S_AUTO_Panel)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_Panel], \
  	LIN_BIT_OFFSET_LI0_S_AUTO_Panel));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_AUTO_Panel] = 1;}

/* static access macros for signal LI0_S_Auto_Lamp */
#define l_bool_rd_LI0_S_Auto_Lamp() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Auto_Lamp], \
   	LIN_BIT_OFFSET_LI0_S_Auto_Lamp))
#define l_bool_wr_LI0_S_Auto_Lamp(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Auto_Lamp], \
  	LIN_BIT_OFFSET_LI0_S_Auto_Lamp)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Auto_Lamp], \
  	LIN_BIT_OFFSET_LI0_S_Auto_Lamp));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Auto_Lamp] = 1;}

/* static access macros for signal LI0_S_RS_FAULT */
#define l_bool_rd_LI0_S_RS_FAULT() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_RS_FAULT], \
   	LIN_BIT_OFFSET_LI0_S_RS_FAULT))
#define l_bool_wr_LI0_S_RS_FAULT(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_RS_FAULT], \
  	LIN_BIT_OFFSET_LI0_S_RS_FAULT)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_RS_FAULT], \
  	LIN_BIT_OFFSET_LI0_S_RS_FAULT));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_RS_FAULT] = 1;}

/* static access macros for signal LI0_S_RAIN */
#define l_bool_rd_LI0_S_RAIN() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_RAIN], \
   	LIN_BIT_OFFSET_LI0_S_RAIN))
#define l_bool_wr_LI0_S_RAIN(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_RAIN], \
  	LIN_BIT_OFFSET_LI0_S_RAIN)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_RAIN], \
  	LIN_BIT_OFFSET_LI0_S_RAIN));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_RAIN] = 1;}

/* static access macros for signal LI0_S_AUTO_H */
#define l_bool_rd_LI0_S_AUTO_H() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_H], \
   	LIN_BIT_OFFSET_LI0_S_AUTO_H))
#define l_bool_wr_LI0_S_AUTO_H(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_H], \
  	LIN_BIT_OFFSET_LI0_S_AUTO_H)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_H], \
  	LIN_BIT_OFFSET_LI0_S_AUTO_H));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_AUTO_H] = 1;}

/* static access macros for signal LI0_S_AUTO_L */
#define l_bool_rd_LI0_S_AUTO_L() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_L], \
   	LIN_BIT_OFFSET_LI0_S_AUTO_L))
#define l_bool_wr_LI0_S_AUTO_L(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_L], \
  	LIN_BIT_OFFSET_LI0_S_AUTO_L)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_AUTO_L], \
  	LIN_BIT_OFFSET_LI0_S_AUTO_L));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_AUTO_L] = 1;}

/* static access macros for signal LI0_RSP_Err */
#define l_bool_rd_LI0_RSP_Err() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RSP_Err], \
   	LIN_BIT_OFFSET_LI0_RSP_Err))
#define l_bool_wr_LI0_RSP_Err(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RSP_Err], \
  	LIN_BIT_OFFSET_LI0_RSP_Err)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RSP_Err], \
  	LIN_BIT_OFFSET_LI0_RSP_Err));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RSP_Err] = 1;}

/* static access macros for signal LI0_S_TRANS_550nm_RSP */
#define l_u8_rd_LI0_S_TRANS_550nm_RSP() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_S_TRANS_550nm_RSP) - 1) \
    << LIN_BIT_OFFSET_LI0_S_TRANS_550nm_RSP )) >> LIN_BIT_OFFSET_LI0_S_TRANS_550nm_RSP))
#define l_u8_wr_LI0_S_TRANS_550nm_RSP(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_S_TRANS_550nm_RSP) - 1) << LIN_BIT_OFFSET_LI0_S_TRANS_550nm_RSP)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_S_TRANS_550nm_RSP) - 1) & (A)) << LIN_BIT_OFFSET_LI0_S_TRANS_550nm_RSP))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP] = 1;}

/* static access macros for signal LI0_S_TRANS_880nm_RSP */
#define l_u8_rd_LI0_S_TRANS_880nm_RSP() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_S_TRANS_880nm_RSP) - 1) \
    << LIN_BIT_OFFSET_LI0_S_TRANS_880nm_RSP )) >> LIN_BIT_OFFSET_LI0_S_TRANS_880nm_RSP))
#define l_u8_wr_LI0_S_TRANS_880nm_RSP(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_S_TRANS_880nm_RSP) - 1) << LIN_BIT_OFFSET_LI0_S_TRANS_880nm_RSP)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_S_TRANS_880nm_RSP) - 1) & (A)) << LIN_BIT_OFFSET_LI0_S_TRANS_880nm_RSP))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP] = 1;}

/* static access macros for signal LI0_S_WASH */
#define l_bool_rd_LI0_S_WASH() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_WASH], \
   	LIN_BIT_OFFSET_LI0_S_WASH))
#define l_bool_wr_LI0_S_WASH(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_WASH], \
  	LIN_BIT_OFFSET_LI0_S_WASH)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_WASH], \
  	LIN_BIT_OFFSET_LI0_S_WASH));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_WASH] = 1;}

/* static access macros for signal LI0_S_HIGH */
#define l_bool_rd_LI0_S_HIGH() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_HIGH], \
   	LIN_BIT_OFFSET_LI0_S_HIGH))
#define l_bool_wr_LI0_S_HIGH(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_HIGH], \
  	LIN_BIT_OFFSET_LI0_S_HIGH)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_HIGH], \
  	LIN_BIT_OFFSET_LI0_S_HIGH));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_HIGH] = 1;}

/* static access macros for signal LI0_S_LOW */
#define l_bool_rd_LI0_S_LOW() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_LOW], \
   	LIN_BIT_OFFSET_LI0_S_LOW))
#define l_bool_wr_LI0_S_LOW(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_LOW], \
  	LIN_BIT_OFFSET_LI0_S_LOW)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_LOW], \
  	LIN_BIT_OFFSET_LI0_S_LOW));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_LOW] = 1;}

/* static access macros for signal LI0_S_SENS */
#define l_u8_rd_LI0_S_SENS() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_SENS] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_S_SENS) - 1) \
    << LIN_BIT_OFFSET_LI0_S_SENS )) >> LIN_BIT_OFFSET_LI0_S_SENS))
#define l_u8_wr_LI0_S_SENS(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_SENS] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_SENS] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_S_SENS) - 1) << LIN_BIT_OFFSET_LI0_S_SENS)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_S_SENS) - 1) & (A)) << LIN_BIT_OFFSET_LI0_S_SENS))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_SENS] = 1;}

/* static access macros for signal LI0_S_Trans_550nm */
#define l_u8_rd_LI0_S_Trans_550nm() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Trans_550nm] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_S_Trans_550nm) - 1) \
    << LIN_BIT_OFFSET_LI0_S_Trans_550nm )) >> LIN_BIT_OFFSET_LI0_S_Trans_550nm))
#define l_u8_wr_LI0_S_Trans_550nm(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Trans_550nm] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Trans_550nm] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_S_Trans_550nm) - 1) << LIN_BIT_OFFSET_LI0_S_Trans_550nm)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_S_Trans_550nm) - 1) & (A)) << LIN_BIT_OFFSET_LI0_S_Trans_550nm))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Trans_550nm] = 1;}

/* static access macros for signal LI0_S_Trans_880nm */
#define l_u8_rd_LI0_S_Trans_880nm() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Trans_880nm] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_S_Trans_880nm) - 1) \
    << LIN_BIT_OFFSET_LI0_S_Trans_880nm )) >> LIN_BIT_OFFSET_LI0_S_Trans_880nm))
#define l_u8_wr_LI0_S_Trans_880nm(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Trans_880nm] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_Trans_880nm] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_S_Trans_880nm) - 1) << LIN_BIT_OFFSET_LI0_S_Trans_880nm)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_S_Trans_880nm) - 1) & (A)) << LIN_BIT_OFFSET_LI0_S_Trans_880nm))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_Trans_880nm] = 1;}

/* static access macros for signal LI0_S_WASH_MODE */
#define l_bool_rd_LI0_S_WASH_MODE() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_WASH_MODE], \
   	LIN_BIT_OFFSET_LI0_S_WASH_MODE))
#define l_bool_wr_LI0_S_WASH_MODE(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_WASH_MODE], \
  	LIN_BIT_OFFSET_LI0_S_WASH_MODE)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_S_WASH_MODE], \
  	LIN_BIT_OFFSET_LI0_S_WASH_MODE));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_S_WASH_MODE] = 1;}
/* Signal flag APIs */

#define l_flg_tst_LI0_Ignition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Ignition],\
         LIN_FLAG_BIT_OFFSET_LI0_Ignition)
#define l_flg_clr_LI0_Ignition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Ignition],\
         LIN_FLAG_BIT_OFFSET_LI0_Ignition)

#define l_flg_tst_LI0_SCS_Automatic_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SCS_Automatic],\
         LIN_FLAG_BIT_OFFSET_LI0_SCS_Automatic)
#define l_flg_clr_LI0_SCS_Automatic_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SCS_Automatic],\
         LIN_FLAG_BIT_OFFSET_LI0_SCS_Automatic)

#define l_flg_tst_LI0_VehicleSpeed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_VehicleSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_VehicleSpeed)
#define l_flg_clr_LI0_VehicleSpeed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_VehicleSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_VehicleSpeed)

#define l_flg_tst_LI0_Status_SMA_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Status_SMA],\
         LIN_FLAG_BIT_OFFSET_LI0_Status_SMA)
#define l_flg_clr_LI0_Status_SMA_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Status_SMA],\
         LIN_FLAG_BIT_OFFSET_LI0_Status_SMA)

#define l_flg_tst_LI0_ParkPosition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_ParkPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_ParkPosition)
#define l_flg_clr_LI0_ParkPosition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_ParkPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_ParkPosition)

#define l_flg_tst_LI0_RLS_HumidSensorValue_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_HumidSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_HumidSensorValue)
#define l_flg_clr_LI0_RLS_HumidSensorValue_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_HumidSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_HumidSensorValue)

#define l_flg_tst_LI0_RLS_TempSensorValue_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_TempSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_TempSensorValue)
#define l_flg_clr_LI0_RLS_TempSensorValue_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_TempSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_TempSensorValue)

#define l_flg_tst_LI0_RLS_TempDewPoint_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_TempDewPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_TempDewPoint)
#define l_flg_clr_LI0_RLS_TempDewPoint_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_TempDewPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_TempDewPoint)

#define l_flg_tst_LI0_RLS_Humid_Temp_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid_Temp_Error)
#define l_flg_clr_LI0_RLS_Humid_Temp_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid_Temp_Error)

#define l_flg_tst_LI0_RLS_LIN_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LIN_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LIN_Error)
#define l_flg_clr_LI0_RLS_LIN_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_LIN_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_LIN_Error)

#define l_flg_tst_LI0_RLS_VotalgeError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_VotalgeError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_VotalgeError)
#define l_flg_clr_LI0_RLS_VotalgeError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_VotalgeError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_VotalgeError)

#define l_flg_tst_LI0_S_COMMFAULT_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_COMMFAULT],\
         LIN_FLAG_BIT_OFFSET_LI0_S_COMMFAULT)
#define l_flg_clr_LI0_S_COMMFAULT_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_COMMFAULT],\
         LIN_FLAG_BIT_OFFSET_LI0_S_COMMFAULT)

#define l_flg_tst_LI0_S_Window_CMD_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Window_CMD],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Window_CMD)
#define l_flg_clr_LI0_S_Window_CMD_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Window_CMD],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Window_CMD)

#define l_flg_tst_LI0_S_AUTO_Panel_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_Panel],\
         LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_Panel)
#define l_flg_clr_LI0_S_AUTO_Panel_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_Panel],\
         LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_Panel)

#define l_flg_tst_LI0_S_Auto_Lamp_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Auto_Lamp],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Auto_Lamp)
#define l_flg_clr_LI0_S_Auto_Lamp_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Auto_Lamp],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Auto_Lamp)

#define l_flg_tst_LI0_S_RS_FAULT_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_RS_FAULT],\
         LIN_FLAG_BIT_OFFSET_LI0_S_RS_FAULT)
#define l_flg_clr_LI0_S_RS_FAULT_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_RS_FAULT],\
         LIN_FLAG_BIT_OFFSET_LI0_S_RS_FAULT)

#define l_flg_tst_LI0_S_RAIN_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_RAIN],\
         LIN_FLAG_BIT_OFFSET_LI0_S_RAIN)
#define l_flg_clr_LI0_S_RAIN_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_RAIN],\
         LIN_FLAG_BIT_OFFSET_LI0_S_RAIN)

#define l_flg_tst_LI0_S_AUTO_H_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_H],\
         LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_H)
#define l_flg_clr_LI0_S_AUTO_H_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_H],\
         LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_H)

#define l_flg_tst_LI0_S_AUTO_L_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_L],\
         LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_L)
#define l_flg_clr_LI0_S_AUTO_L_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_AUTO_L],\
         LIN_FLAG_BIT_OFFSET_LI0_S_AUTO_L)

#define l_flg_tst_LI0_RSP_Err_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RSP_Err],\
         LIN_FLAG_BIT_OFFSET_LI0_RSP_Err)
#define l_flg_clr_LI0_RSP_Err_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RSP_Err],\
         LIN_FLAG_BIT_OFFSET_LI0_RSP_Err)

#define l_flg_tst_LI0_S_TRANS_550nm_RSP_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP],\
         LIN_FLAG_BIT_OFFSET_LI0_S_TRANS_550nm_RSP)
#define l_flg_clr_LI0_S_TRANS_550nm_RSP_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_TRANS_550nm_RSP],\
         LIN_FLAG_BIT_OFFSET_LI0_S_TRANS_550nm_RSP)

#define l_flg_tst_LI0_S_TRANS_880nm_RSP_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP],\
         LIN_FLAG_BIT_OFFSET_LI0_S_TRANS_880nm_RSP)
#define l_flg_clr_LI0_S_TRANS_880nm_RSP_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_TRANS_880nm_RSP],\
         LIN_FLAG_BIT_OFFSET_LI0_S_TRANS_880nm_RSP)

#define l_flg_tst_LI0_S_WASH_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_WASH],\
         LIN_FLAG_BIT_OFFSET_LI0_S_WASH)
#define l_flg_clr_LI0_S_WASH_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_WASH],\
         LIN_FLAG_BIT_OFFSET_LI0_S_WASH)

#define l_flg_tst_LI0_S_HIGH_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_HIGH],\
         LIN_FLAG_BIT_OFFSET_LI0_S_HIGH)
#define l_flg_clr_LI0_S_HIGH_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_HIGH],\
         LIN_FLAG_BIT_OFFSET_LI0_S_HIGH)

#define l_flg_tst_LI0_S_LOW_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_LOW],\
         LIN_FLAG_BIT_OFFSET_LI0_S_LOW)
#define l_flg_clr_LI0_S_LOW_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_LOW],\
         LIN_FLAG_BIT_OFFSET_LI0_S_LOW)

#define l_flg_tst_LI0_S_SENS_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_SENS],\
         LIN_FLAG_BIT_OFFSET_LI0_S_SENS)
#define l_flg_clr_LI0_S_SENS_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_SENS],\
         LIN_FLAG_BIT_OFFSET_LI0_S_SENS)

#define l_flg_tst_LI0_S_Trans_550nm_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Trans_550nm],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Trans_550nm)
#define l_flg_clr_LI0_S_Trans_550nm_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Trans_550nm],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Trans_550nm)

#define l_flg_tst_LI0_S_Trans_880nm_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Trans_880nm],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Trans_880nm)
#define l_flg_clr_LI0_S_Trans_880nm_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_Trans_880nm],\
         LIN_FLAG_BIT_OFFSET_LI0_S_Trans_880nm)

#define l_flg_tst_LI0_S_WASH_MODE_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_WASH_MODE],\
         LIN_FLAG_BIT_OFFSET_LI0_S_WASH_MODE)
#define l_flg_clr_LI0_S_WASH_MODE_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_S_WASH_MODE],\
         LIN_FLAG_BIT_OFFSET_LI0_S_WASH_MODE)



/* Frame flag APIs */

#define l_flg_tst_LI0_BCM_01_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_01],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_01)
#define l_flg_clr_LI0_BCM_01_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_01],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_01)

#define l_flg_tst_LI0_BCM_02_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_02],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_02)
#define l_flg_clr_LI0_BCM_02_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_02],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_02)

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
