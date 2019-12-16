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

#define MAX_QUEUE_SIZE 2

#define DIAGSRV_SESSION_DEFAULT 1
#define DIAGSRV_SESSION_PROGRAM 2
#define DIAGSRV_SESSION_EXTERN  3

#define _DIAG_NUMBER_OF_SERVICES_    8

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
#define LIN_FRAME_BUF_SIZE			22
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
#define LIN_NUM_OF_SIGS  27
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_Ignition

   , LI0_SCS_Automatic
  
   , LI0_VehicleSpeed
  
   , LI0_Status_SMA
  
   , LI0_SCS_IntervalLeve
  
   , LI0_SCS_FrontWash
  
   , LI0_LS_Sensitivity
  
   , LI0_RS_Sensitivity
  
   , LI0_RS_Deactivation
  
   , LI0_Wiper_running
  
   , LI0_BladesTurningPoint
  
   , LI0_ParkPosition
  
   , LI0_SensorMsgCounter
  
   , LI0_LightSignalReady
  
   , LI0_Light_On
  
   , LI0_Light_On_Invers
  
   , LI0_Twilight_On
  
   , LI0_Twilight_On_Invers
  
   , LI0_LS_Error
  
   , LI0_LIN_Error
  
   , LI0_Brightness_FW
  
   , LI0_Brightness_IR_L
  
   , LI0_Brightness_IR_R
  
   , LI0_RS_Error
  
   , LI0_RainIntensity
  
   , LI0_WiperSpeed
  
   , LI0_Splash
  
  
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

   LI0_RLS_01

   , LI0_BCM_01
  
   , LI0_BCM_02
  
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


#define LIN_BYTE_OFFSET_LI0_Ignition    8
#define LIN_BIT_OFFSET_LI0_Ignition    4
#define LIN_SIGNAL_SIZE_LI0_Ignition    1
#define LIN_FLAG_BYTE_OFFSET_LI0_Ignition    2
#define LIN_FLAG_BIT_OFFSET_LI0_Ignition    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Ignition    1

#define LIN_BYTE_OFFSET_LI0_SCS_Automatic    9
#define LIN_BIT_OFFSET_LI0_SCS_Automatic    5
#define LIN_SIGNAL_SIZE_LI0_SCS_Automatic    1
#define LIN_FLAG_BYTE_OFFSET_LI0_SCS_Automatic    2
#define LIN_FLAG_BIT_OFFSET_LI0_SCS_Automatic    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SCS_Automatic    1

#define LIN_BYTE_OFFSET_LI0_VehicleSpeed    12
#define LIN_BIT_OFFSET_LI0_VehicleSpeed    0
#define LIN_SIGNAL_SIZE_LI0_VehicleSpeed    8
#define LIN_FLAG_BYTE_OFFSET_LI0_VehicleSpeed    2
#define LIN_FLAG_BIT_OFFSET_LI0_VehicleSpeed    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_VehicleSpeed    1

#define LIN_BYTE_OFFSET_LI0_Status_SMA    8
#define LIN_BIT_OFFSET_LI0_Status_SMA    5
#define LIN_SIGNAL_SIZE_LI0_Status_SMA    3
#define LIN_FLAG_BYTE_OFFSET_LI0_Status_SMA    2
#define LIN_FLAG_BIT_OFFSET_LI0_Status_SMA    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Status_SMA    1

#define LIN_BYTE_OFFSET_LI0_SCS_IntervalLeve    9
#define LIN_BIT_OFFSET_LI0_SCS_IntervalLeve    0
#define LIN_SIGNAL_SIZE_LI0_SCS_IntervalLeve    4
#define LIN_FLAG_BYTE_OFFSET_LI0_SCS_IntervalLeve    2
#define LIN_FLAG_BIT_OFFSET_LI0_SCS_IntervalLeve    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SCS_IntervalLeve    1

#define LIN_BYTE_OFFSET_LI0_SCS_FrontWash    10
#define LIN_BIT_OFFSET_LI0_SCS_FrontWash    0
#define LIN_SIGNAL_SIZE_LI0_SCS_FrontWash    1
#define LIN_FLAG_BYTE_OFFSET_LI0_SCS_FrontWash    2
#define LIN_FLAG_BIT_OFFSET_LI0_SCS_FrontWash    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SCS_FrontWash    1

#define LIN_BYTE_OFFSET_LI0_LS_Sensitivity    14
#define LIN_BIT_OFFSET_LI0_LS_Sensitivity    0
#define LIN_SIGNAL_SIZE_LI0_LS_Sensitivity    3
#define LIN_FLAG_BYTE_OFFSET_LI0_LS_Sensitivity    2
#define LIN_FLAG_BIT_OFFSET_LI0_LS_Sensitivity    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LS_Sensitivity    1

#define LIN_BYTE_OFFSET_LI0_RS_Sensitivity    14
#define LIN_BIT_OFFSET_LI0_RS_Sensitivity    4
#define LIN_SIGNAL_SIZE_LI0_RS_Sensitivity    3
#define LIN_FLAG_BYTE_OFFSET_LI0_RS_Sensitivity    3
#define LIN_FLAG_BIT_OFFSET_LI0_RS_Sensitivity    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RS_Sensitivity    1

#define LIN_BYTE_OFFSET_LI0_RS_Deactivation    14
#define LIN_BIT_OFFSET_LI0_RS_Deactivation    3
#define LIN_SIGNAL_SIZE_LI0_RS_Deactivation    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RS_Deactivation    3
#define LIN_FLAG_BIT_OFFSET_LI0_RS_Deactivation    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RS_Deactivation    1

#define LIN_BYTE_OFFSET_LI0_Wiper_running    16
#define LIN_BIT_OFFSET_LI0_Wiper_running    0
#define LIN_SIGNAL_SIZE_LI0_Wiper_running    1
#define LIN_FLAG_BYTE_OFFSET_LI0_Wiper_running    4
#define LIN_FLAG_BIT_OFFSET_LI0_Wiper_running    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Wiper_running    2

#define LIN_BYTE_OFFSET_LI0_BladesTurningPoint    16
#define LIN_BIT_OFFSET_LI0_BladesTurningPoint    2
#define LIN_SIGNAL_SIZE_LI0_BladesTurningPoint    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BladesTurningPoint    4
#define LIN_FLAG_BIT_OFFSET_LI0_BladesTurningPoint    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BladesTurningPoint    2

#define LIN_BYTE_OFFSET_LI0_ParkPosition    16
#define LIN_BIT_OFFSET_LI0_ParkPosition    3
#define LIN_SIGNAL_SIZE_LI0_ParkPosition    1
#define LIN_FLAG_BYTE_OFFSET_LI0_ParkPosition    4
#define LIN_FLAG_BIT_OFFSET_LI0_ParkPosition    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_ParkPosition    2

#define LIN_BYTE_OFFSET_LI0_SensorMsgCounter    0
#define LIN_BIT_OFFSET_LI0_SensorMsgCounter    0
#define LIN_SIGNAL_SIZE_LI0_SensorMsgCounter    4
#define LIN_FLAG_BYTE_OFFSET_LI0_SensorMsgCounter    0
#define LIN_FLAG_BIT_OFFSET_LI0_SensorMsgCounter    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SensorMsgCounter    0

#define LIN_BYTE_OFFSET_LI0_LightSignalReady    0
#define LIN_BIT_OFFSET_LI0_LightSignalReady    4
#define LIN_SIGNAL_SIZE_LI0_LightSignalReady    1
#define LIN_FLAG_BYTE_OFFSET_LI0_LightSignalReady    0
#define LIN_FLAG_BIT_OFFSET_LI0_LightSignalReady    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LightSignalReady    0

#define LIN_BYTE_OFFSET_LI0_Light_On    1
#define LIN_BIT_OFFSET_LI0_Light_On    3
#define LIN_SIGNAL_SIZE_LI0_Light_On    1
#define LIN_FLAG_BYTE_OFFSET_LI0_Light_On    0
#define LIN_FLAG_BIT_OFFSET_LI0_Light_On    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Light_On    0

#define LIN_BYTE_OFFSET_LI0_Light_On_Invers    1
#define LIN_BIT_OFFSET_LI0_Light_On_Invers    4
#define LIN_SIGNAL_SIZE_LI0_Light_On_Invers    1
#define LIN_FLAG_BYTE_OFFSET_LI0_Light_On_Invers    0
#define LIN_FLAG_BIT_OFFSET_LI0_Light_On_Invers    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Light_On_Invers    0

#define LIN_BYTE_OFFSET_LI0_Twilight_On    1
#define LIN_BIT_OFFSET_LI0_Twilight_On    6
#define LIN_SIGNAL_SIZE_LI0_Twilight_On    1
#define LIN_FLAG_BYTE_OFFSET_LI0_Twilight_On    0
#define LIN_FLAG_BIT_OFFSET_LI0_Twilight_On    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Twilight_On    0

#define LIN_BYTE_OFFSET_LI0_Twilight_On_Invers    1
#define LIN_BIT_OFFSET_LI0_Twilight_On_Invers    7
#define LIN_SIGNAL_SIZE_LI0_Twilight_On_Invers    1
#define LIN_FLAG_BYTE_OFFSET_LI0_Twilight_On_Invers    1
#define LIN_FLAG_BIT_OFFSET_LI0_Twilight_On_Invers    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Twilight_On_Invers    0

#define LIN_BYTE_OFFSET_LI0_LS_Error    2
#define LIN_BIT_OFFSET_LI0_LS_Error    2
#define LIN_SIGNAL_SIZE_LI0_LS_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_LS_Error    1
#define LIN_FLAG_BIT_OFFSET_LI0_LS_Error    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LS_Error    0

#define LIN_BYTE_OFFSET_LI0_LIN_Error    2
#define LIN_BIT_OFFSET_LI0_LIN_Error    3
#define LIN_SIGNAL_SIZE_LI0_LIN_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_LIN_Error    1
#define LIN_FLAG_BIT_OFFSET_LI0_LIN_Error    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LIN_Error    0

#define LIN_BYTE_OFFSET_LI0_Brightness_FW    4
#define LIN_BIT_OFFSET_LI0_Brightness_FW    0
#define LIN_SIGNAL_SIZE_LI0_Brightness_FW    10
#define LIN_FLAG_BYTE_OFFSET_LI0_Brightness_FW    1
#define LIN_FLAG_BIT_OFFSET_LI0_Brightness_FW    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Brightness_FW    0

#define LIN_BYTE_OFFSET_LI0_Brightness_IR_L    3
#define LIN_BIT_OFFSET_LI0_Brightness_IR_L    0
#define LIN_SIGNAL_SIZE_LI0_Brightness_IR_L    8
#define LIN_FLAG_BYTE_OFFSET_LI0_Brightness_IR_L    1
#define LIN_FLAG_BIT_OFFSET_LI0_Brightness_IR_L    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Brightness_IR_L    0

#define LIN_BYTE_OFFSET_LI0_Brightness_IR_R    6
#define LIN_BIT_OFFSET_LI0_Brightness_IR_R    0
#define LIN_SIGNAL_SIZE_LI0_Brightness_IR_R    8
#define LIN_FLAG_BYTE_OFFSET_LI0_Brightness_IR_R    1
#define LIN_FLAG_BIT_OFFSET_LI0_Brightness_IR_R    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Brightness_IR_R    0

#define LIN_BYTE_OFFSET_LI0_RS_Error    2
#define LIN_BIT_OFFSET_LI0_RS_Error    1
#define LIN_SIGNAL_SIZE_LI0_RS_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RS_Error    1
#define LIN_FLAG_BIT_OFFSET_LI0_RS_Error    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RS_Error    0

#define LIN_BYTE_OFFSET_LI0_RainIntensity    5
#define LIN_BIT_OFFSET_LI0_RainIntensity    4
#define LIN_SIGNAL_SIZE_LI0_RainIntensity    4
#define LIN_FLAG_BYTE_OFFSET_LI0_RainIntensity    1
#define LIN_FLAG_BIT_OFFSET_LI0_RainIntensity    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RainIntensity    0

#define LIN_BYTE_OFFSET_LI0_WiperSpeed    0
#define LIN_BIT_OFFSET_LI0_WiperSpeed    5
#define LIN_SIGNAL_SIZE_LI0_WiperSpeed    3
#define LIN_FLAG_BYTE_OFFSET_LI0_WiperSpeed    0
#define LIN_FLAG_BIT_OFFSET_LI0_WiperSpeed    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_WiperSpeed    0

#define LIN_BYTE_OFFSET_LI0_Splash    1
#define LIN_BIT_OFFSET_LI0_Splash    0
#define LIN_SIGNAL_SIZE_LI0_Splash    1
#define LIN_FLAG_BYTE_OFFSET_LI0_Splash    0
#define LIN_FLAG_BIT_OFFSET_LI0_Splash    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Splash    0




#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_01             0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_01             2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_02             4
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_02              0


/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */


/* static access macros for signal LI0_Ignition */
#define l_bool_rd_LI0_Ignition() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Ignition], \
   	LIN_BIT_OFFSET_LI0_Ignition))
#define l_bool_wr_LI0_Ignition(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Ignition], \
  	LIN_BIT_OFFSET_LI0_Ignition)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Ignition], \
  	LIN_BIT_OFFSET_LI0_Ignition));\
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
#define l_u8_rd_LI0_VehicleSpeed() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_VehicleSpeed) - 1) \
    << LIN_BIT_OFFSET_LI0_VehicleSpeed )) >> LIN_BIT_OFFSET_LI0_VehicleSpeed))
#define l_u8_wr_LI0_VehicleSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeed] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_VehicleSpeed) - 1) << LIN_BIT_OFFSET_LI0_VehicleSpeed)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_VehicleSpeed) - 1) & (A)) << LIN_BIT_OFFSET_LI0_VehicleSpeed))));\
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

/* static access macros for signal LI0_SCS_IntervalLeve */
#define l_u8_rd_LI0_SCS_IntervalLeve() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_IntervalLeve] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_SCS_IntervalLeve) - 1) \
    << LIN_BIT_OFFSET_LI0_SCS_IntervalLeve )) >> LIN_BIT_OFFSET_LI0_SCS_IntervalLeve))
#define l_u8_wr_LI0_SCS_IntervalLeve(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_IntervalLeve] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_IntervalLeve] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_SCS_IntervalLeve) - 1) << LIN_BIT_OFFSET_LI0_SCS_IntervalLeve)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_SCS_IntervalLeve) - 1) & (A)) << LIN_BIT_OFFSET_LI0_SCS_IntervalLeve))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SCS_IntervalLeve] = 1;}

/* static access macros for signal LI0_SCS_FrontWash */
#define l_bool_rd_LI0_SCS_FrontWash() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_FrontWash], \
   	LIN_BIT_OFFSET_LI0_SCS_FrontWash))
#define l_bool_wr_LI0_SCS_FrontWash(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_FrontWash], \
  	LIN_BIT_OFFSET_LI0_SCS_FrontWash)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SCS_FrontWash], \
  	LIN_BIT_OFFSET_LI0_SCS_FrontWash));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SCS_FrontWash] = 1;}

/* static access macros for signal LI0_LS_Sensitivity */
#define l_u8_rd_LI0_LS_Sensitivity() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LS_Sensitivity] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_LS_Sensitivity) - 1) \
    << LIN_BIT_OFFSET_LI0_LS_Sensitivity )) >> LIN_BIT_OFFSET_LI0_LS_Sensitivity))
#define l_u8_wr_LI0_LS_Sensitivity(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LS_Sensitivity] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LS_Sensitivity] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_LS_Sensitivity) - 1) << LIN_BIT_OFFSET_LI0_LS_Sensitivity)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_LS_Sensitivity) - 1) & (A)) << LIN_BIT_OFFSET_LI0_LS_Sensitivity))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LS_Sensitivity] = 1;}

/* static access macros for signal LI0_RS_Sensitivity */
#define l_u8_rd_LI0_RS_Sensitivity() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Sensitivity] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RS_Sensitivity) - 1) \
    << LIN_BIT_OFFSET_LI0_RS_Sensitivity )) >> LIN_BIT_OFFSET_LI0_RS_Sensitivity))
#define l_u8_wr_LI0_RS_Sensitivity(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Sensitivity] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Sensitivity] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RS_Sensitivity) - 1) << LIN_BIT_OFFSET_LI0_RS_Sensitivity)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RS_Sensitivity) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RS_Sensitivity))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RS_Sensitivity] = 1;}

/* static access macros for signal LI0_RS_Deactivation */
#define l_bool_rd_LI0_RS_Deactivation() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Deactivation], \
   	LIN_BIT_OFFSET_LI0_RS_Deactivation))
#define l_bool_wr_LI0_RS_Deactivation(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Deactivation], \
  	LIN_BIT_OFFSET_LI0_RS_Deactivation)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Deactivation], \
  	LIN_BIT_OFFSET_LI0_RS_Deactivation));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RS_Deactivation] = 1;}

/* static access macros for signal LI0_Wiper_running */
#define l_bool_rd_LI0_Wiper_running() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Wiper_running], \
   	LIN_BIT_OFFSET_LI0_Wiper_running))
#define l_bool_wr_LI0_Wiper_running(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Wiper_running], \
  	LIN_BIT_OFFSET_LI0_Wiper_running)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Wiper_running], \
  	LIN_BIT_OFFSET_LI0_Wiper_running));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Wiper_running] = 1;}

/* static access macros for signal LI0_BladesTurningPoint */
#define l_bool_rd_LI0_BladesTurningPoint() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BladesTurningPoint], \
   	LIN_BIT_OFFSET_LI0_BladesTurningPoint))
#define l_bool_wr_LI0_BladesTurningPoint(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BladesTurningPoint], \
  	LIN_BIT_OFFSET_LI0_BladesTurningPoint)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BladesTurningPoint], \
  	LIN_BIT_OFFSET_LI0_BladesTurningPoint));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BladesTurningPoint] = 1;}

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

/* static access macros for signal LI0_SensorMsgCounter */
#define l_u8_rd_LI0_SensorMsgCounter() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SensorMsgCounter] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_SensorMsgCounter) - 1) \
    << LIN_BIT_OFFSET_LI0_SensorMsgCounter )) >> LIN_BIT_OFFSET_LI0_SensorMsgCounter))
#define l_u8_wr_LI0_SensorMsgCounter(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SensorMsgCounter] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SensorMsgCounter] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_SensorMsgCounter) - 1) << LIN_BIT_OFFSET_LI0_SensorMsgCounter)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_SensorMsgCounter) - 1) & (A)) << LIN_BIT_OFFSET_LI0_SensorMsgCounter))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SensorMsgCounter] = 1;}

/* static access macros for signal LI0_LightSignalReady */
#define l_bool_rd_LI0_LightSignalReady() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightSignalReady], \
   	LIN_BIT_OFFSET_LI0_LightSignalReady))
#define l_bool_wr_LI0_LightSignalReady(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightSignalReady], \
  	LIN_BIT_OFFSET_LI0_LightSignalReady)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightSignalReady], \
  	LIN_BIT_OFFSET_LI0_LightSignalReady));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LightSignalReady] = 1;}

/* static access macros for signal LI0_Light_On */
#define l_bool_rd_LI0_Light_On() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Light_On], \
   	LIN_BIT_OFFSET_LI0_Light_On))
#define l_bool_wr_LI0_Light_On(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Light_On], \
  	LIN_BIT_OFFSET_LI0_Light_On)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Light_On], \
  	LIN_BIT_OFFSET_LI0_Light_On));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Light_On] = 1;}

/* static access macros for signal LI0_Light_On_Invers */
#define l_bool_rd_LI0_Light_On_Invers() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Light_On_Invers], \
   	LIN_BIT_OFFSET_LI0_Light_On_Invers))
#define l_bool_wr_LI0_Light_On_Invers(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Light_On_Invers], \
  	LIN_BIT_OFFSET_LI0_Light_On_Invers)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Light_On_Invers], \
  	LIN_BIT_OFFSET_LI0_Light_On_Invers));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Light_On_Invers] = 1;}

/* static access macros for signal LI0_Twilight_On */
#define l_bool_rd_LI0_Twilight_On() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Twilight_On], \
   	LIN_BIT_OFFSET_LI0_Twilight_On))
#define l_bool_wr_LI0_Twilight_On(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Twilight_On], \
  	LIN_BIT_OFFSET_LI0_Twilight_On)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Twilight_On], \
  	LIN_BIT_OFFSET_LI0_Twilight_On));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Twilight_On] = 1;}

/* static access macros for signal LI0_Twilight_On_Invers */
#define l_bool_rd_LI0_Twilight_On_Invers() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Twilight_On_Invers], \
   	LIN_BIT_OFFSET_LI0_Twilight_On_Invers))
#define l_bool_wr_LI0_Twilight_On_Invers(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Twilight_On_Invers], \
  	LIN_BIT_OFFSET_LI0_Twilight_On_Invers)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Twilight_On_Invers], \
  	LIN_BIT_OFFSET_LI0_Twilight_On_Invers));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Twilight_On_Invers] = 1;}

/* static access macros for signal LI0_LS_Error */
#define l_bool_rd_LI0_LS_Error() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LS_Error], \
   	LIN_BIT_OFFSET_LI0_LS_Error))
#define l_bool_wr_LI0_LS_Error(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LS_Error], \
  	LIN_BIT_OFFSET_LI0_LS_Error)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LS_Error], \
  	LIN_BIT_OFFSET_LI0_LS_Error));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LS_Error] = 1;}

/* static access macros for signal LI0_LIN_Error */
#define l_bool_rd_LI0_LIN_Error() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LIN_Error], \
   	LIN_BIT_OFFSET_LI0_LIN_Error))
#define l_bool_wr_LI0_LIN_Error(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LIN_Error], \
  	LIN_BIT_OFFSET_LI0_LIN_Error)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LIN_Error], \
  	LIN_BIT_OFFSET_LI0_LIN_Error));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LIN_Error] = 1;}

/* static access macros for signal LI0_Brightness_FW */
#define l_u16_rd_LI0_Brightness_FW() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_FW + 1] & 0x03) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_FW]) >> 0x00))
#define l_u16_wr_LI0_Brightness_FW(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_FW + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_FW + 1] &  (0xfc))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0x03))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_FW] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_FW] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_Brightness_FW))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Brightness_FW] = 1;}

/* static access macros for signal LI0_Brightness_IR_L */
#define l_u8_rd_LI0_Brightness_IR_L() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_IR_L] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_Brightness_IR_L) - 1) \
    << LIN_BIT_OFFSET_LI0_Brightness_IR_L )) >> LIN_BIT_OFFSET_LI0_Brightness_IR_L))
#define l_u8_wr_LI0_Brightness_IR_L(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_IR_L] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_IR_L] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_Brightness_IR_L) - 1) << LIN_BIT_OFFSET_LI0_Brightness_IR_L)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_Brightness_IR_L) - 1) & (A)) << LIN_BIT_OFFSET_LI0_Brightness_IR_L))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Brightness_IR_L] = 1;}

/* static access macros for signal LI0_Brightness_IR_R */
#define l_u8_rd_LI0_Brightness_IR_R() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_IR_R] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_Brightness_IR_R) - 1) \
    << LIN_BIT_OFFSET_LI0_Brightness_IR_R )) >> LIN_BIT_OFFSET_LI0_Brightness_IR_R))
#define l_u8_wr_LI0_Brightness_IR_R(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_IR_R] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Brightness_IR_R] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_Brightness_IR_R) - 1) << LIN_BIT_OFFSET_LI0_Brightness_IR_R)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_Brightness_IR_R) - 1) & (A)) << LIN_BIT_OFFSET_LI0_Brightness_IR_R))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Brightness_IR_R] = 1;}

/* static access macros for signal LI0_RS_Error */
#define l_bool_rd_LI0_RS_Error() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Error], \
   	LIN_BIT_OFFSET_LI0_RS_Error))
#define l_bool_wr_LI0_RS_Error(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Error], \
  	LIN_BIT_OFFSET_LI0_RS_Error)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RS_Error], \
  	LIN_BIT_OFFSET_LI0_RS_Error));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RS_Error] = 1;}

/* static access macros for signal LI0_RainIntensity */
#define l_u8_rd_LI0_RainIntensity() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RainIntensity] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RainIntensity) - 1) \
    << LIN_BIT_OFFSET_LI0_RainIntensity )) >> LIN_BIT_OFFSET_LI0_RainIntensity))
#define l_u8_wr_LI0_RainIntensity(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RainIntensity] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RainIntensity] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RainIntensity) - 1) << LIN_BIT_OFFSET_LI0_RainIntensity)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RainIntensity) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RainIntensity))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RainIntensity] = 1;}

/* static access macros for signal LI0_WiperSpeed */
#define l_u8_rd_LI0_WiperSpeed() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_WiperSpeed] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_WiperSpeed) - 1) \
    << LIN_BIT_OFFSET_LI0_WiperSpeed )) >> LIN_BIT_OFFSET_LI0_WiperSpeed))
#define l_u8_wr_LI0_WiperSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_WiperSpeed] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_WiperSpeed] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_WiperSpeed) - 1) << LIN_BIT_OFFSET_LI0_WiperSpeed)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_WiperSpeed) - 1) & (A)) << LIN_BIT_OFFSET_LI0_WiperSpeed))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_WiperSpeed] = 1;}

/* static access macros for signal LI0_Splash */
#define l_bool_rd_LI0_Splash() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Splash], \
   	LIN_BIT_OFFSET_LI0_Splash))
#define l_bool_wr_LI0_Splash(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Splash], \
  	LIN_BIT_OFFSET_LI0_Splash)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Splash], \
  	LIN_BIT_OFFSET_LI0_Splash));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Splash] = 1;}



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

#define l_flg_tst_LI0_SCS_IntervalLeve_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SCS_IntervalLeve],\
         LIN_FLAG_BIT_OFFSET_LI0_SCS_IntervalLeve)
#define l_flg_clr_LI0_SCS_IntervalLeve_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SCS_IntervalLeve],\
         LIN_FLAG_BIT_OFFSET_LI0_SCS_IntervalLeve)

#define l_flg_tst_LI0_SCS_FrontWash_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SCS_FrontWash],\
         LIN_FLAG_BIT_OFFSET_LI0_SCS_FrontWash)
#define l_flg_clr_LI0_SCS_FrontWash_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SCS_FrontWash],\
         LIN_FLAG_BIT_OFFSET_LI0_SCS_FrontWash)

#define l_flg_tst_LI0_LS_Sensitivity_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LS_Sensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_LS_Sensitivity)
#define l_flg_clr_LI0_LS_Sensitivity_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LS_Sensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_LS_Sensitivity)

#define l_flg_tst_LI0_RS_Sensitivity_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RS_Sensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_RS_Sensitivity)
#define l_flg_clr_LI0_RS_Sensitivity_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RS_Sensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_RS_Sensitivity)

#define l_flg_tst_LI0_RS_Deactivation_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RS_Deactivation],\
         LIN_FLAG_BIT_OFFSET_LI0_RS_Deactivation)
#define l_flg_clr_LI0_RS_Deactivation_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RS_Deactivation],\
         LIN_FLAG_BIT_OFFSET_LI0_RS_Deactivation)

#define l_flg_tst_LI0_Wiper_running_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Wiper_running],\
         LIN_FLAG_BIT_OFFSET_LI0_Wiper_running)
#define l_flg_clr_LI0_Wiper_running_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Wiper_running],\
         LIN_FLAG_BIT_OFFSET_LI0_Wiper_running)

#define l_flg_tst_LI0_BladesTurningPoint_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BladesTurningPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_BladesTurningPoint)
#define l_flg_clr_LI0_BladesTurningPoint_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BladesTurningPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_BladesTurningPoint)

#define l_flg_tst_LI0_ParkPosition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_ParkPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_ParkPosition)
#define l_flg_clr_LI0_ParkPosition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_ParkPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_ParkPosition)

#define l_flg_tst_LI0_SensorMsgCounter_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SensorMsgCounter],\
         LIN_FLAG_BIT_OFFSET_LI0_SensorMsgCounter)
#define l_flg_clr_LI0_SensorMsgCounter_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SensorMsgCounter],\
         LIN_FLAG_BIT_OFFSET_LI0_SensorMsgCounter)

#define l_flg_tst_LI0_LightSignalReady_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LightSignalReady],\
         LIN_FLAG_BIT_OFFSET_LI0_LightSignalReady)
#define l_flg_clr_LI0_LightSignalReady_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LightSignalReady],\
         LIN_FLAG_BIT_OFFSET_LI0_LightSignalReady)

#define l_flg_tst_LI0_Light_On_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Light_On],\
         LIN_FLAG_BIT_OFFSET_LI0_Light_On)
#define l_flg_clr_LI0_Light_On_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Light_On],\
         LIN_FLAG_BIT_OFFSET_LI0_Light_On)

#define l_flg_tst_LI0_Light_On_Invers_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Light_On_Invers],\
         LIN_FLAG_BIT_OFFSET_LI0_Light_On_Invers)
#define l_flg_clr_LI0_Light_On_Invers_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Light_On_Invers],\
         LIN_FLAG_BIT_OFFSET_LI0_Light_On_Invers)

#define l_flg_tst_LI0_Twilight_On_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Twilight_On],\
         LIN_FLAG_BIT_OFFSET_LI0_Twilight_On)
#define l_flg_clr_LI0_Twilight_On_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Twilight_On],\
         LIN_FLAG_BIT_OFFSET_LI0_Twilight_On)

#define l_flg_tst_LI0_Twilight_On_Invers_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Twilight_On_Invers],\
         LIN_FLAG_BIT_OFFSET_LI0_Twilight_On_Invers)
#define l_flg_clr_LI0_Twilight_On_Invers_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Twilight_On_Invers],\
         LIN_FLAG_BIT_OFFSET_LI0_Twilight_On_Invers)

#define l_flg_tst_LI0_LS_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LS_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_LS_Error)
#define l_flg_clr_LI0_LS_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LS_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_LS_Error)

#define l_flg_tst_LI0_LIN_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LIN_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_LIN_Error)
#define l_flg_clr_LI0_LIN_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LIN_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_LIN_Error)

#define l_flg_tst_LI0_Brightness_FW_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Brightness_FW],\
         LIN_FLAG_BIT_OFFSET_LI0_Brightness_FW)
#define l_flg_clr_LI0_Brightness_FW_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Brightness_FW],\
         LIN_FLAG_BIT_OFFSET_LI0_Brightness_FW)

#define l_flg_tst_LI0_Brightness_IR_L_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Brightness_IR_L],\
         LIN_FLAG_BIT_OFFSET_LI0_Brightness_IR_L)
#define l_flg_clr_LI0_Brightness_IR_L_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Brightness_IR_L],\
         LIN_FLAG_BIT_OFFSET_LI0_Brightness_IR_L)

#define l_flg_tst_LI0_Brightness_IR_R_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Brightness_IR_R],\
         LIN_FLAG_BIT_OFFSET_LI0_Brightness_IR_R)
#define l_flg_clr_LI0_Brightness_IR_R_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Brightness_IR_R],\
         LIN_FLAG_BIT_OFFSET_LI0_Brightness_IR_R)

#define l_flg_tst_LI0_RS_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RS_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RS_Error)
#define l_flg_clr_LI0_RS_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RS_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RS_Error)

#define l_flg_tst_LI0_RainIntensity_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RainIntensity],\
         LIN_FLAG_BIT_OFFSET_LI0_RainIntensity)
#define l_flg_clr_LI0_RainIntensity_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RainIntensity],\
         LIN_FLAG_BIT_OFFSET_LI0_RainIntensity)

#define l_flg_tst_LI0_WiperSpeed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_WiperSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_WiperSpeed)
#define l_flg_clr_LI0_WiperSpeed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_WiperSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_WiperSpeed)

#define l_flg_tst_LI0_Splash_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Splash],\
         LIN_FLAG_BIT_OFFSET_LI0_Splash)
#define l_flg_clr_LI0_Splash_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Splash],\
         LIN_FLAG_BIT_OFFSET_LI0_Splash)



/* Frame flag APIs */

#define l_flg_tst_LI0_RLS_01_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_01],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_01)
#define l_flg_clr_LI0_RLS_01_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_01],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_01)

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



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */