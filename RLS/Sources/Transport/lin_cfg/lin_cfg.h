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
#define LIN_FRAME_BUF_SIZE			16
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
#define LIN_NUM_OF_SIGS  25
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_BCM_Status_IGN

   , LI0_BCM_CMD_AutoWiper
  
   , LI0_BCM_RQ_FrontWash
  
   , LI0_BCM_ParkPosition
  
   , LI0_BCM_RainSensitivity
  
   , LI0_BCM_CMD_AutoLight
  
   , LI0_BCM_BladesTurningPoint
  
   , LI0_BCM_RoofStatus
  
   , LI0_BCM_SPD_Vehicle
  
   , LI0_BCM_OutsideTemp
  
   , LI0_RLS_MsgCounter
  
   , LI0_RLS_RQ_WiperSPD
  
   , LI0_RLS_RQ_LowBeam
  
   , LI0_RLS_RQ_PositionLamp
  
   , LI0_RLS_Fault_Rain
  
   , LI0_RLS_Fault_Light
  
   , LI0_RLS_REP_Error
  
   , LI0_RLS_VOLT_Error
  
   , LI0_RLS_Humid_Temp_Error
  
   , LI0_RLS_Brightness_IR_L
  
   , LI0_RLS_Brightness_FW
  
   , LI0_RLS_Rain_Intensity
  
   , LI0_RLS_Brightness_IR_R
  
   , LI0_RLS_Temperature
  
   , LI0_RLS_Humid
  
  
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

   LI0_RLS_01

   , LI0_BCM_01
  
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


#define LIN_BYTE_OFFSET_LI0_BCM_Status_IGN    8
#define LIN_BIT_OFFSET_LI0_BCM_Status_IGN    0
#define LIN_SIGNAL_SIZE_LI0_BCM_Status_IGN    2
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_Status_IGN    2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_Status_IGN    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Status_IGN    1

#define LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper    8
#define LIN_BIT_OFFSET_LI0_BCM_CMD_AutoWiper    2
#define LIN_SIGNAL_SIZE_LI0_BCM_CMD_AutoWiper    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper    2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_CMD_AutoWiper    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper    1

#define LIN_BYTE_OFFSET_LI0_BCM_RQ_FrontWash    8
#define LIN_BIT_OFFSET_LI0_BCM_RQ_FrontWash    3
#define LIN_SIGNAL_SIZE_LI0_BCM_RQ_FrontWash    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_RQ_FrontWash    2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_RQ_FrontWash    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RQ_FrontWash    1

#define LIN_BYTE_OFFSET_LI0_BCM_ParkPosition    8
#define LIN_BIT_OFFSET_LI0_BCM_ParkPosition    4
#define LIN_SIGNAL_SIZE_LI0_BCM_ParkPosition    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_ParkPosition    2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_ParkPosition    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_ParkPosition    1

#define LIN_BYTE_OFFSET_LI0_BCM_RainSensitivity    8
#define LIN_BIT_OFFSET_LI0_BCM_RainSensitivity    5
#define LIN_SIGNAL_SIZE_LI0_BCM_RainSensitivity    3
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_RainSensitivity    2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_RainSensitivity    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RainSensitivity    1

#define LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoLight    9
#define LIN_BIT_OFFSET_LI0_BCM_CMD_AutoLight    0
#define LIN_SIGNAL_SIZE_LI0_BCM_CMD_AutoLight    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_CMD_AutoLight    2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_CMD_AutoLight    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_CMD_AutoLight    1

#define LIN_BYTE_OFFSET_LI0_BCM_BladesTurningPoint    9
#define LIN_BIT_OFFSET_LI0_BCM_BladesTurningPoint    1
#define LIN_SIGNAL_SIZE_LI0_BCM_BladesTurningPoint    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_BladesTurningPoint    2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_BladesTurningPoint    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_BladesTurningPoint    1

#define LIN_BYTE_OFFSET_LI0_BCM_RoofStatus    9
#define LIN_BIT_OFFSET_LI0_BCM_RoofStatus    2
#define LIN_SIGNAL_SIZE_LI0_BCM_RoofStatus    1
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_RoofStatus    3
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_RoofStatus    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RoofStatus    1

#define LIN_BYTE_OFFSET_LI0_BCM_SPD_Vehicle    10
#define LIN_BIT_OFFSET_LI0_BCM_SPD_Vehicle    0
#define LIN_SIGNAL_SIZE_LI0_BCM_SPD_Vehicle    13
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_SPD_Vehicle    3
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_SPD_Vehicle    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_SPD_Vehicle    1

#define LIN_BYTE_OFFSET_LI0_BCM_OutsideTemp    12
#define LIN_BIT_OFFSET_LI0_BCM_OutsideTemp    0
#define LIN_SIGNAL_SIZE_LI0_BCM_OutsideTemp    8
#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_OutsideTemp    3
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_OutsideTemp    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_OutsideTemp    1

#define LIN_BYTE_OFFSET_LI0_RLS_MsgCounter    0
#define LIN_BIT_OFFSET_LI0_RLS_MsgCounter    0
#define LIN_SIGNAL_SIZE_LI0_RLS_MsgCounter    4
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_MsgCounter    0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_MsgCounter    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_MsgCounter    0

#define LIN_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD    0
#define LIN_BIT_OFFSET_LI0_RLS_RQ_WiperSPD    4
#define LIN_SIGNAL_SIZE_LI0_RLS_RQ_WiperSPD    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD    0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_WiperSPD    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD    0

#define LIN_BYTE_OFFSET_LI0_RLS_RQ_LowBeam    0
#define LIN_BIT_OFFSET_LI0_RLS_RQ_LowBeam    7
#define LIN_SIGNAL_SIZE_LI0_RLS_RQ_LowBeam    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_LowBeam    0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_LowBeam    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RQ_LowBeam    0

#define LIN_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp    1
#define LIN_BIT_OFFSET_LI0_RLS_RQ_PositionLamp    0
#define LIN_SIGNAL_SIZE_LI0_RLS_RQ_PositionLamp    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp    0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_PositionLamp    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp    0

#define LIN_BYTE_OFFSET_LI0_RLS_Fault_Rain    1
#define LIN_BIT_OFFSET_LI0_RLS_Fault_Rain    1
#define LIN_SIGNAL_SIZE_LI0_RLS_Fault_Rain    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Fault_Rain    0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Fault_Rain    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Fault_Rain    0

#define LIN_BYTE_OFFSET_LI0_RLS_Fault_Light    1
#define LIN_BIT_OFFSET_LI0_RLS_Fault_Light    2
#define LIN_SIGNAL_SIZE_LI0_RLS_Fault_Light    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Fault_Light    0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Fault_Light    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Fault_Light    0

#define LIN_BYTE_OFFSET_LI0_RLS_REP_Error    1
#define LIN_BIT_OFFSET_LI0_RLS_REP_Error    3
#define LIN_SIGNAL_SIZE_LI0_RLS_REP_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_REP_Error    0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_REP_Error    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_REP_Error    0

#define LIN_BYTE_OFFSET_LI0_RLS_VOLT_Error    1
#define LIN_BIT_OFFSET_LI0_RLS_VOLT_Error    4
#define LIN_SIGNAL_SIZE_LI0_RLS_VOLT_Error    2
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_VOLT_Error    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_VOLT_Error    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_VOLT_Error    0

#define LIN_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error    1
#define LIN_BIT_OFFSET_LI0_RLS_Humid_Temp_Error    6
#define LIN_SIGNAL_SIZE_LI0_RLS_Humid_Temp_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid_Temp_Error    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error    0

#define LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_L    2
#define LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_L    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_L    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_IR_L    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_IR_L    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Brightness_IR_L    0

#define LIN_BYTE_OFFSET_LI0_RLS_Brightness_FW    3
#define LIN_BIT_OFFSET_LI0_RLS_Brightness_FW    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Brightness_FW    10
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_FW    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_FW    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Brightness_FW    0

#define LIN_BYTE_OFFSET_LI0_RLS_Rain_Intensity    4
#define LIN_BIT_OFFSET_LI0_RLS_Rain_Intensity    2
#define LIN_SIGNAL_SIZE_LI0_RLS_Rain_Intensity    4
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Rain_Intensity    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Rain_Intensity    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Rain_Intensity    0

#define LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_R    5
#define LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_R    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_R    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_IR_R    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_IR_R    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Brightness_IR_R    0

#define LIN_BYTE_OFFSET_LI0_RLS_Temperature    6
#define LIN_BIT_OFFSET_LI0_RLS_Temperature    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Temperature    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Temperature    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Temperature    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Temperature    0

#define LIN_BYTE_OFFSET_LI0_RLS_Humid    7
#define LIN_BIT_OFFSET_LI0_RLS_Humid    0
#define LIN_SIGNAL_SIZE_LI0_RLS_Humid    8
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Humid    0




#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_01             0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_01              0

#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_01             2
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_01              0


/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */


/* static access macros for signal LI0_BCM_Status_IGN */
#define l_u8_rd_LI0_BCM_Status_IGN() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Status_IGN] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_Status_IGN) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_Status_IGN )) >> LIN_BIT_OFFSET_LI0_BCM_Status_IGN))
#define l_u8_wr_LI0_BCM_Status_IGN(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Status_IGN] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_Status_IGN] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_Status_IGN) - 1) << LIN_BIT_OFFSET_LI0_BCM_Status_IGN)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_Status_IGN) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_Status_IGN))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_Status_IGN] = 1;}

/* static access macros for signal LI0_BCM_CMD_AutoWiper */
#define l_bool_rd_LI0_BCM_CMD_AutoWiper() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper], \
   	LIN_BIT_OFFSET_LI0_BCM_CMD_AutoWiper))
#define l_bool_wr_LI0_BCM_CMD_AutoWiper(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper], \
  	LIN_BIT_OFFSET_LI0_BCM_CMD_AutoWiper)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper], \
  	LIN_BIT_OFFSET_LI0_BCM_CMD_AutoWiper));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper] = 1;}

/* static access macros for signal LI0_BCM_RQ_FrontWash */
#define l_bool_rd_LI0_BCM_RQ_FrontWash() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RQ_FrontWash], \
   	LIN_BIT_OFFSET_LI0_BCM_RQ_FrontWash))
#define l_bool_wr_LI0_BCM_RQ_FrontWash(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RQ_FrontWash], \
  	LIN_BIT_OFFSET_LI0_BCM_RQ_FrontWash)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RQ_FrontWash], \
  	LIN_BIT_OFFSET_LI0_BCM_RQ_FrontWash));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RQ_FrontWash] = 1;}

/* static access macros for signal LI0_BCM_ParkPosition */
#define l_bool_rd_LI0_BCM_ParkPosition() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_ParkPosition], \
   	LIN_BIT_OFFSET_LI0_BCM_ParkPosition))
#define l_bool_wr_LI0_BCM_ParkPosition(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_ParkPosition], \
  	LIN_BIT_OFFSET_LI0_BCM_ParkPosition)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_ParkPosition], \
  	LIN_BIT_OFFSET_LI0_BCM_ParkPosition));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_ParkPosition] = 1;}

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

/* static access macros for signal LI0_BCM_CMD_AutoLight */
#define l_bool_rd_LI0_BCM_CMD_AutoLight() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoLight], \
   	LIN_BIT_OFFSET_LI0_BCM_CMD_AutoLight))
#define l_bool_wr_LI0_BCM_CMD_AutoLight(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoLight], \
  	LIN_BIT_OFFSET_LI0_BCM_CMD_AutoLight)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_CMD_AutoLight], \
  	LIN_BIT_OFFSET_LI0_BCM_CMD_AutoLight));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_CMD_AutoLight] = 1;}

/* static access macros for signal LI0_BCM_BladesTurningPoint */
#define l_bool_rd_LI0_BCM_BladesTurningPoint() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_BladesTurningPoint], \
   	LIN_BIT_OFFSET_LI0_BCM_BladesTurningPoint))
#define l_bool_wr_LI0_BCM_BladesTurningPoint(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_BladesTurningPoint], \
  	LIN_BIT_OFFSET_LI0_BCM_BladesTurningPoint)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_BladesTurningPoint], \
  	LIN_BIT_OFFSET_LI0_BCM_BladesTurningPoint));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_BladesTurningPoint] = 1;}

/* static access macros for signal LI0_BCM_RoofStatus */
#define l_bool_rd_LI0_BCM_RoofStatus() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RoofStatus], \
   	LIN_BIT_OFFSET_LI0_BCM_RoofStatus))
#define l_bool_wr_LI0_BCM_RoofStatus(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RoofStatus], \
  	LIN_BIT_OFFSET_LI0_BCM_RoofStatus)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_RoofStatus], \
  	LIN_BIT_OFFSET_LI0_BCM_RoofStatus));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_RoofStatus] = 1;}

/* static access macros for signal LI0_BCM_SPD_Vehicle */
#define l_u16_rd_LI0_BCM_SPD_Vehicle() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_SPD_Vehicle + 1] & 0x1f) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_SPD_Vehicle]) >> 0x00))
#define l_u16_wr_LI0_BCM_SPD_Vehicle(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_SPD_Vehicle + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_SPD_Vehicle + 1] &  (0xe0))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0x1f))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_SPD_Vehicle] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_SPD_Vehicle] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_BCM_SPD_Vehicle))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_SPD_Vehicle] = 1;}

/* static access macros for signal LI0_BCM_OutsideTemp */
#define l_u8_rd_LI0_BCM_OutsideTemp() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_OutsideTemp] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCM_OutsideTemp) - 1) \
    << LIN_BIT_OFFSET_LI0_BCM_OutsideTemp )) >> LIN_BIT_OFFSET_LI0_BCM_OutsideTemp))
#define l_u8_wr_LI0_BCM_OutsideTemp(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_OutsideTemp] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCM_OutsideTemp] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCM_OutsideTemp) - 1) << LIN_BIT_OFFSET_LI0_BCM_OutsideTemp)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCM_OutsideTemp) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCM_OutsideTemp))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCM_OutsideTemp] = 1;}

/* static access macros for signal LI0_RLS_MsgCounter */
#define l_u8_rd_LI0_RLS_MsgCounter() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_MsgCounter] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_MsgCounter) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_MsgCounter )) >> LIN_BIT_OFFSET_LI0_RLS_MsgCounter))
#define l_u8_wr_LI0_RLS_MsgCounter(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_MsgCounter] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_MsgCounter] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_MsgCounter) - 1) << LIN_BIT_OFFSET_LI0_RLS_MsgCounter)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_MsgCounter) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_MsgCounter))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_MsgCounter] = 1;}

/* static access macros for signal LI0_RLS_RQ_WiperSPD */
#define l_u8_rd_LI0_RLS_RQ_WiperSPD() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_RQ_WiperSPD) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_RQ_WiperSPD )) >> LIN_BIT_OFFSET_LI0_RLS_RQ_WiperSPD))
#define l_u8_wr_LI0_RLS_RQ_WiperSPD(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_RQ_WiperSPD) - 1) << LIN_BIT_OFFSET_LI0_RLS_RQ_WiperSPD)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_RQ_WiperSPD) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_RQ_WiperSPD))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD] = 1;}

/* static access macros for signal LI0_RLS_RQ_LowBeam */
#define l_bool_rd_LI0_RLS_RQ_LowBeam() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_LowBeam], \
   	LIN_BIT_OFFSET_LI0_RLS_RQ_LowBeam))
#define l_bool_wr_LI0_RLS_RQ_LowBeam(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_LowBeam], \
  	LIN_BIT_OFFSET_LI0_RLS_RQ_LowBeam)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_LowBeam], \
  	LIN_BIT_OFFSET_LI0_RLS_RQ_LowBeam));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RQ_LowBeam] = 1;}

/* static access macros for signal LI0_RLS_RQ_PositionLamp */
#define l_bool_rd_LI0_RLS_RQ_PositionLamp() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp], \
   	LIN_BIT_OFFSET_LI0_RLS_RQ_PositionLamp))
#define l_bool_wr_LI0_RLS_RQ_PositionLamp(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp], \
  	LIN_BIT_OFFSET_LI0_RLS_RQ_PositionLamp)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp], \
  	LIN_BIT_OFFSET_LI0_RLS_RQ_PositionLamp));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp] = 1;}

/* static access macros for signal LI0_RLS_Fault_Rain */
#define l_bool_rd_LI0_RLS_Fault_Rain() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Fault_Rain], \
   	LIN_BIT_OFFSET_LI0_RLS_Fault_Rain))
#define l_bool_wr_LI0_RLS_Fault_Rain(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Fault_Rain], \
  	LIN_BIT_OFFSET_LI0_RLS_Fault_Rain)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Fault_Rain], \
  	LIN_BIT_OFFSET_LI0_RLS_Fault_Rain));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Fault_Rain] = 1;}

/* static access macros for signal LI0_RLS_Fault_Light */
#define l_bool_rd_LI0_RLS_Fault_Light() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Fault_Light], \
   	LIN_BIT_OFFSET_LI0_RLS_Fault_Light))
#define l_bool_wr_LI0_RLS_Fault_Light(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Fault_Light], \
  	LIN_BIT_OFFSET_LI0_RLS_Fault_Light)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Fault_Light], \
  	LIN_BIT_OFFSET_LI0_RLS_Fault_Light));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Fault_Light] = 1;}

/* static access macros for signal LI0_RLS_REP_Error */
#define l_bool_rd_LI0_RLS_REP_Error() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_REP_Error], \
   	LIN_BIT_OFFSET_LI0_RLS_REP_Error))
#define l_bool_wr_LI0_RLS_REP_Error(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_REP_Error], \
  	LIN_BIT_OFFSET_LI0_RLS_REP_Error)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_REP_Error], \
  	LIN_BIT_OFFSET_LI0_RLS_REP_Error));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_REP_Error] = 1;}

/* static access macros for signal LI0_RLS_VOLT_Error */
#define l_u8_rd_LI0_RLS_VOLT_Error() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_VOLT_Error] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_VOLT_Error) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_VOLT_Error )) >> LIN_BIT_OFFSET_LI0_RLS_VOLT_Error))
#define l_u8_wr_LI0_RLS_VOLT_Error(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_VOLT_Error] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_VOLT_Error] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_VOLT_Error) - 1) << LIN_BIT_OFFSET_LI0_RLS_VOLT_Error)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_VOLT_Error) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_VOLT_Error))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_VOLT_Error] = 1;}

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

/* static access macros for signal LI0_RLS_Brightness_IR_L */
#define l_u8_rd_LI0_RLS_Brightness_IR_L() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_L] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_L) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_L )) >> LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_L))
#define l_u8_wr_LI0_RLS_Brightness_IR_L(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_L] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_L] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_L) - 1) << LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_L)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_L) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_L))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Brightness_IR_L] = 1;}

/* static access macros for signal LI0_RLS_Brightness_FW */
#define l_u16_rd_LI0_RLS_Brightness_FW() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_FW + 1] & 0x03) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_FW]) >> 0x00))
#define l_u16_wr_LI0_RLS_Brightness_FW(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_FW + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_FW + 1] &  (0xfc))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0x03))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_FW] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_FW] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_RLS_Brightness_FW))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Brightness_FW] = 1;}

/* static access macros for signal LI0_RLS_Rain_Intensity */
#define l_u8_rd_LI0_RLS_Rain_Intensity() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Rain_Intensity] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Rain_Intensity) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Rain_Intensity )) >> LIN_BIT_OFFSET_LI0_RLS_Rain_Intensity))
#define l_u8_wr_LI0_RLS_Rain_Intensity(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Rain_Intensity] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Rain_Intensity] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Rain_Intensity) - 1) << LIN_BIT_OFFSET_LI0_RLS_Rain_Intensity)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Rain_Intensity) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Rain_Intensity))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Rain_Intensity] = 1;}

/* static access macros for signal LI0_RLS_Brightness_IR_R */
#define l_u8_rd_LI0_RLS_Brightness_IR_R() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_R] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_R) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_R )) >> LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_R))
#define l_u8_wr_LI0_RLS_Brightness_IR_R(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_R] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Brightness_IR_R] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_R) - 1) << LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_R)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Brightness_IR_R) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Brightness_IR_R))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Brightness_IR_R] = 1;}

/* static access macros for signal LI0_RLS_Temperature */
#define l_u8_rd_LI0_RLS_Temperature() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Temperature] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Temperature) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Temperature )) >> LIN_BIT_OFFSET_LI0_RLS_Temperature))
#define l_u8_wr_LI0_RLS_Temperature(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Temperature] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Temperature] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Temperature) - 1) << LIN_BIT_OFFSET_LI0_RLS_Temperature)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Temperature) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Temperature))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Temperature] = 1;}

/* static access macros for signal LI0_RLS_Humid */
#define l_u8_rd_LI0_RLS_Humid() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Humid] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_RLS_Humid) - 1) \
    << LIN_BIT_OFFSET_LI0_RLS_Humid )) >> LIN_BIT_OFFSET_LI0_RLS_Humid))
#define l_u8_wr_LI0_RLS_Humid(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Humid] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLS_Humid] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_RLS_Humid) - 1) << LIN_BIT_OFFSET_LI0_RLS_Humid)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_RLS_Humid) - 1) & (A)) << LIN_BIT_OFFSET_LI0_RLS_Humid))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_Humid] = 1;}



/* Signal flag APIs */


#define l_flg_tst_LI0_BCM_Status_IGN_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Status_IGN],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Status_IGN)
#define l_flg_clr_LI0_BCM_Status_IGN_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_Status_IGN],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_Status_IGN)

#define l_flg_tst_LI0_BCM_CMD_AutoWiper_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_CMD_AutoWiper)
#define l_flg_clr_LI0_BCM_CMD_AutoWiper_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_CMD_AutoWiper],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_CMD_AutoWiper)

#define l_flg_tst_LI0_BCM_RQ_FrontWash_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RQ_FrontWash],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RQ_FrontWash)
#define l_flg_clr_LI0_BCM_RQ_FrontWash_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RQ_FrontWash],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RQ_FrontWash)

#define l_flg_tst_LI0_BCM_ParkPosition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_ParkPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_ParkPosition)
#define l_flg_clr_LI0_BCM_ParkPosition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_ParkPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_ParkPosition)

#define l_flg_tst_LI0_BCM_RainSensitivity_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RainSensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RainSensitivity)
#define l_flg_clr_LI0_BCM_RainSensitivity_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RainSensitivity],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RainSensitivity)

#define l_flg_tst_LI0_BCM_CMD_AutoLight_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_CMD_AutoLight],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_CMD_AutoLight)
#define l_flg_clr_LI0_BCM_CMD_AutoLight_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_CMD_AutoLight],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_CMD_AutoLight)

#define l_flg_tst_LI0_BCM_BladesTurningPoint_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_BladesTurningPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_BladesTurningPoint)
#define l_flg_clr_LI0_BCM_BladesTurningPoint_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_BladesTurningPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_BladesTurningPoint)

#define l_flg_tst_LI0_BCM_RoofStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RoofStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RoofStatus)
#define l_flg_clr_LI0_BCM_RoofStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_RoofStatus],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_RoofStatus)

#define l_flg_tst_LI0_BCM_SPD_Vehicle_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_SPD_Vehicle],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_SPD_Vehicle)
#define l_flg_clr_LI0_BCM_SPD_Vehicle_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_SPD_Vehicle],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_SPD_Vehicle)

#define l_flg_tst_LI0_BCM_OutsideTemp_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_OutsideTemp],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_OutsideTemp)
#define l_flg_clr_LI0_BCM_OutsideTemp_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_OutsideTemp],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_OutsideTemp)

#define l_flg_tst_LI0_RLS_MsgCounter_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_MsgCounter],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_MsgCounter)
#define l_flg_clr_LI0_RLS_MsgCounter_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_MsgCounter],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_MsgCounter)

#define l_flg_tst_LI0_RLS_RQ_WiperSPD_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_WiperSPD)
#define l_flg_clr_LI0_RLS_RQ_WiperSPD_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_WiperSPD],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_WiperSPD)

#define l_flg_tst_LI0_RLS_RQ_LowBeam_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_LowBeam],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_LowBeam)
#define l_flg_clr_LI0_RLS_RQ_LowBeam_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_LowBeam],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_LowBeam)

#define l_flg_tst_LI0_RLS_RQ_PositionLamp_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_PositionLamp)
#define l_flg_clr_LI0_RLS_RQ_PositionLamp_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_RQ_PositionLamp],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_RQ_PositionLamp)

#define l_flg_tst_LI0_RLS_Fault_Rain_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Fault_Rain],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Fault_Rain)
#define l_flg_clr_LI0_RLS_Fault_Rain_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Fault_Rain],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Fault_Rain)

#define l_flg_tst_LI0_RLS_Fault_Light_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Fault_Light],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Fault_Light)
#define l_flg_clr_LI0_RLS_Fault_Light_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Fault_Light],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Fault_Light)

#define l_flg_tst_LI0_RLS_REP_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_REP_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_REP_Error)
#define l_flg_clr_LI0_RLS_REP_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_REP_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_REP_Error)

#define l_flg_tst_LI0_RLS_VOLT_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_VOLT_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_VOLT_Error)
#define l_flg_clr_LI0_RLS_VOLT_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_VOLT_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_VOLT_Error)

#define l_flg_tst_LI0_RLS_Humid_Temp_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid_Temp_Error)
#define l_flg_clr_LI0_RLS_Humid_Temp_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid_Temp_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid_Temp_Error)

#define l_flg_tst_LI0_RLS_Brightness_IR_L_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_IR_L],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_IR_L)
#define l_flg_clr_LI0_RLS_Brightness_IR_L_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_IR_L],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_IR_L)

#define l_flg_tst_LI0_RLS_Brightness_FW_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_FW],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_FW)
#define l_flg_clr_LI0_RLS_Brightness_FW_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_FW],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_FW)

#define l_flg_tst_LI0_RLS_Rain_Intensity_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Rain_Intensity],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Rain_Intensity)
#define l_flg_clr_LI0_RLS_Rain_Intensity_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Rain_Intensity],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Rain_Intensity)

#define l_flg_tst_LI0_RLS_Brightness_IR_R_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_IR_R],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_IR_R)
#define l_flg_clr_LI0_RLS_Brightness_IR_R_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Brightness_IR_R],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Brightness_IR_R)

#define l_flg_tst_LI0_RLS_Temperature_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Temperature],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Temperature)
#define l_flg_clr_LI0_RLS_Temperature_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Temperature],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Temperature)

#define l_flg_tst_LI0_RLS_Humid_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid)
#define l_flg_clr_LI0_RLS_Humid_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_Humid],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_Humid)



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



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */