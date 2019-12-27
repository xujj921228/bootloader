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
* @author    xujun
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
#define LIN_FRAME_BUF_SIZE			26
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
#define LIN_NUM_OF_SIGS  32
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_STAT_Terminal

   , LI0_vehicleSpeed
  
   , LI0_WiperSpeed
  
   , LI0_STAT_RS
  
   , LI0_STAT_RSError
  
   , LI0_LightOnReq
  
   , LI0_STAT_DayNightMode
  
   , LI0_STAT_LS
  
   , LI0_STAT_LSError
  
   , LI0_FrontWiperSwitch
  
   , LI0_FrontWasherSwitch
  
   , LI0_FrontWiperPosition
  
   , LI0_MasterLightSwitch
  
   , LI0_LightOnReason
  
   , LI0_VehicleSpeedValid
  
   , LI0_Day
  
   , LI0_Month
  
   , LI0_Year
  
   , LI0_RLS_REP_Error
  
   , LI0_FrontWiperInterval
  
   , LI0_HUDBrightnessUnit
  
   , LI0_HUDBrightnessRawValue
  
   , LI0_RainDayGlobalClose
  
   , LI0_RLSHumidTempError
  
   , LI0_InterTempDewPoint
  
   , LI0_InterTempSensorValue
  
   , LI0_InterHumidSensorValue
  
   , LI0_SolarIrradianceLeft
  
   , LI0_SolarIrradianceRight
  
   , LI0_AmbientTemp
  
   , LI0_WindowSunroofPosition
  
   , LI0_STAT_RemoteControl
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

   LI0_RLS_2

   , LI0_BCM_LIN_3
  
   , LI0_BCM_LIN_1
  
   , LI0_BCM_LIN_2
  
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


#define LIN_BYTE_OFFSET_LI0_STAT_Terminal    13
#define LIN_BIT_OFFSET_LI0_STAT_Terminal    0
#define LIN_SIGNAL_SIZE_LI0_STAT_Terminal    3
#define LIN_FLAG_BYTE_OFFSET_LI0_STAT_Terminal    4
#define LIN_FLAG_BIT_OFFSET_LI0_STAT_Terminal    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_Terminal    2

#define LIN_BYTE_OFFSET_LI0_vehicleSpeed    14
#define LIN_BIT_OFFSET_LI0_vehicleSpeed    4
#define LIN_SIGNAL_SIZE_LI0_vehicleSpeed    12
#define LIN_FLAG_BYTE_OFFSET_LI0_vehicleSpeed    4
#define LIN_FLAG_BIT_OFFSET_LI0_vehicleSpeed    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_vehicleSpeed    2

#define LIN_BYTE_OFFSET_LI0_WiperSpeed    0
#define LIN_BIT_OFFSET_LI0_WiperSpeed    0
#define LIN_SIGNAL_SIZE_LI0_WiperSpeed    2
#define LIN_FLAG_BYTE_OFFSET_LI0_WiperSpeed    0
#define LIN_FLAG_BIT_OFFSET_LI0_WiperSpeed    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_WiperSpeed    0

#define LIN_BYTE_OFFSET_LI0_STAT_RS    0
#define LIN_BIT_OFFSET_LI0_STAT_RS    2
#define LIN_SIGNAL_SIZE_LI0_STAT_RS    1
#define LIN_FLAG_BYTE_OFFSET_LI0_STAT_RS    0
#define LIN_FLAG_BIT_OFFSET_LI0_STAT_RS    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_RS    0

#define LIN_BYTE_OFFSET_LI0_STAT_RSError    0
#define LIN_BIT_OFFSET_LI0_STAT_RSError    3
#define LIN_SIGNAL_SIZE_LI0_STAT_RSError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_STAT_RSError    0
#define LIN_FLAG_BIT_OFFSET_LI0_STAT_RSError    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_RSError    0

#define LIN_BYTE_OFFSET_LI0_LightOnReq    0
#define LIN_BIT_OFFSET_LI0_LightOnReq    4
#define LIN_SIGNAL_SIZE_LI0_LightOnReq    1
#define LIN_FLAG_BYTE_OFFSET_LI0_LightOnReq    0
#define LIN_FLAG_BIT_OFFSET_LI0_LightOnReq    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LightOnReq    0

#define LIN_BYTE_OFFSET_LI0_STAT_DayNightMode    0
#define LIN_BIT_OFFSET_LI0_STAT_DayNightMode    5
#define LIN_SIGNAL_SIZE_LI0_STAT_DayNightMode    2
#define LIN_FLAG_BYTE_OFFSET_LI0_STAT_DayNightMode    0
#define LIN_FLAG_BIT_OFFSET_LI0_STAT_DayNightMode    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_DayNightMode    0

#define LIN_BYTE_OFFSET_LI0_STAT_LS    0
#define LIN_BIT_OFFSET_LI0_STAT_LS    7
#define LIN_SIGNAL_SIZE_LI0_STAT_LS    1
#define LIN_FLAG_BYTE_OFFSET_LI0_STAT_LS    0
#define LIN_FLAG_BIT_OFFSET_LI0_STAT_LS    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_LS    0

#define LIN_BYTE_OFFSET_LI0_STAT_LSError    1
#define LIN_BIT_OFFSET_LI0_STAT_LSError    0
#define LIN_SIGNAL_SIZE_LI0_STAT_LSError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_STAT_LSError    0
#define LIN_FLAG_BIT_OFFSET_LI0_STAT_LSError    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_LSError    0

#define LIN_BYTE_OFFSET_LI0_FrontWiperSwitch    8
#define LIN_BIT_OFFSET_LI0_FrontWiperSwitch    0
#define LIN_SIGNAL_SIZE_LI0_FrontWiperSwitch    3
#define LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperSwitch    3
#define LIN_FLAG_BIT_OFFSET_LI0_FrontWiperSwitch    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWiperSwitch    1

#define LIN_BYTE_OFFSET_LI0_FrontWasherSwitch    8
#define LIN_BIT_OFFSET_LI0_FrontWasherSwitch    3
#define LIN_SIGNAL_SIZE_LI0_FrontWasherSwitch    2
#define LIN_FLAG_BYTE_OFFSET_LI0_FrontWasherSwitch    3
#define LIN_FLAG_BIT_OFFSET_LI0_FrontWasherSwitch    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWasherSwitch    1

#define LIN_BYTE_OFFSET_LI0_FrontWiperPosition    9
#define LIN_BIT_OFFSET_LI0_FrontWiperPosition    3
#define LIN_SIGNAL_SIZE_LI0_FrontWiperPosition    1
#define LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperPosition    3
#define LIN_FLAG_BIT_OFFSET_LI0_FrontWiperPosition    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWiperPosition    1

#define LIN_BYTE_OFFSET_LI0_MasterLightSwitch    9
#define LIN_BIT_OFFSET_LI0_MasterLightSwitch    0
#define LIN_SIGNAL_SIZE_LI0_MasterLightSwitch    3
#define LIN_FLAG_BYTE_OFFSET_LI0_MasterLightSwitch    3
#define LIN_FLAG_BIT_OFFSET_LI0_MasterLightSwitch    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_MasterLightSwitch    1

#define LIN_BYTE_OFFSET_LI0_LightOnReason    1
#define LIN_BIT_OFFSET_LI0_LightOnReason    1
#define LIN_SIGNAL_SIZE_LI0_LightOnReason    2
#define LIN_FLAG_BYTE_OFFSET_LI0_LightOnReason    0
#define LIN_FLAG_BIT_OFFSET_LI0_LightOnReason    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LightOnReason    0

#define LIN_BYTE_OFFSET_LI0_VehicleSpeedValid    10
#define LIN_BIT_OFFSET_LI0_VehicleSpeedValid    6
#define LIN_SIGNAL_SIZE_LI0_VehicleSpeedValid    2
#define LIN_FLAG_BYTE_OFFSET_LI0_VehicleSpeedValid    4
#define LIN_FLAG_BIT_OFFSET_LI0_VehicleSpeedValid    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_VehicleSpeedValid    2

#define LIN_BYTE_OFFSET_LI0_Day    13
#define LIN_BIT_OFFSET_LI0_Day    3
#define LIN_SIGNAL_SIZE_LI0_Day    5
#define LIN_FLAG_BYTE_OFFSET_LI0_Day    4
#define LIN_FLAG_BIT_OFFSET_LI0_Day    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Day    2

#define LIN_BYTE_OFFSET_LI0_Month    14
#define LIN_BIT_OFFSET_LI0_Month    0
#define LIN_SIGNAL_SIZE_LI0_Month    4
#define LIN_FLAG_BYTE_OFFSET_LI0_Month    4
#define LIN_FLAG_BIT_OFFSET_LI0_Month    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Month    2

#define LIN_BYTE_OFFSET_LI0_Year    16
#define LIN_BIT_OFFSET_LI0_Year    0
#define LIN_SIGNAL_SIZE_LI0_Year    7
#define LIN_FLAG_BYTE_OFFSET_LI0_Year    4
#define LIN_FLAG_BIT_OFFSET_LI0_Year    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Year    2

#define LIN_BYTE_OFFSET_LI0_RLS_REP_Error    1
#define LIN_BIT_OFFSET_LI0_RLS_REP_Error    3
#define LIN_SIGNAL_SIZE_LI0_RLS_REP_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_REP_Error    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_REP_Error    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLS_REP_Error    0

#define LIN_BYTE_OFFSET_LI0_FrontWiperInterval    8
#define LIN_BIT_OFFSET_LI0_FrontWiperInterval    5
#define LIN_SIGNAL_SIZE_LI0_FrontWiperInterval    3
#define LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperInterval    3
#define LIN_FLAG_BIT_OFFSET_LI0_FrontWiperInterval    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWiperInterval    1

#define LIN_BYTE_OFFSET_LI0_HUDBrightnessUnit    1
#define LIN_BIT_OFFSET_LI0_HUDBrightnessUnit    4
#define LIN_SIGNAL_SIZE_LI0_HUDBrightnessUnit    2
#define LIN_FLAG_BYTE_OFFSET_LI0_HUDBrightnessUnit    1
#define LIN_FLAG_BIT_OFFSET_LI0_HUDBrightnessUnit    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_HUDBrightnessUnit    0

#define LIN_BYTE_OFFSET_LI0_HUDBrightnessRawValue    2
#define LIN_BIT_OFFSET_LI0_HUDBrightnessRawValue    0
#define LIN_SIGNAL_SIZE_LI0_HUDBrightnessRawValue    7
#define LIN_FLAG_BYTE_OFFSET_LI0_HUDBrightnessRawValue    1
#define LIN_FLAG_BIT_OFFSET_LI0_HUDBrightnessRawValue    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_HUDBrightnessRawValue    0

#define LIN_BYTE_OFFSET_LI0_RainDayGlobalClose    1
#define LIN_BIT_OFFSET_LI0_RainDayGlobalClose    6
#define LIN_SIGNAL_SIZE_LI0_RainDayGlobalClose    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RainDayGlobalClose    1
#define LIN_FLAG_BIT_OFFSET_LI0_RainDayGlobalClose    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RainDayGlobalClose    0

#define LIN_BYTE_OFFSET_LI0_RLSHumidTempError    1
#define LIN_BIT_OFFSET_LI0_RLSHumidTempError    7
#define LIN_SIGNAL_SIZE_LI0_RLSHumidTempError    1
#define LIN_FLAG_BYTE_OFFSET_LI0_RLSHumidTempError    1
#define LIN_FLAG_BIT_OFFSET_LI0_RLSHumidTempError    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLSHumidTempError    0

#define LIN_BYTE_OFFSET_LI0_InterTempDewPoint    2
#define LIN_BIT_OFFSET_LI0_InterTempDewPoint    7
#define LIN_SIGNAL_SIZE_LI0_InterTempDewPoint    9
#define LIN_FLAG_BYTE_OFFSET_LI0_InterTempDewPoint    1
#define LIN_FLAG_BIT_OFFSET_LI0_InterTempDewPoint    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_InterTempDewPoint    0

#define LIN_BYTE_OFFSET_LI0_InterTempSensorValue    4
#define LIN_BIT_OFFSET_LI0_InterTempSensorValue    0
#define LIN_SIGNAL_SIZE_LI0_InterTempSensorValue    8
#define LIN_FLAG_BYTE_OFFSET_LI0_InterTempSensorValue    1
#define LIN_FLAG_BIT_OFFSET_LI0_InterTempSensorValue    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_InterTempSensorValue    0

#define LIN_BYTE_OFFSET_LI0_InterHumidSensorValue    5
#define LIN_BIT_OFFSET_LI0_InterHumidSensorValue    0
#define LIN_SIGNAL_SIZE_LI0_InterHumidSensorValue    8
#define LIN_FLAG_BYTE_OFFSET_LI0_InterHumidSensorValue    1
#define LIN_FLAG_BIT_OFFSET_LI0_InterHumidSensorValue    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_InterHumidSensorValue    0

#define LIN_BYTE_OFFSET_LI0_SolarIrradianceLeft    6
#define LIN_BIT_OFFSET_LI0_SolarIrradianceLeft    0
#define LIN_SIGNAL_SIZE_LI0_SolarIrradianceLeft    8
#define LIN_FLAG_BYTE_OFFSET_LI0_SolarIrradianceLeft    2
#define LIN_FLAG_BIT_OFFSET_LI0_SolarIrradianceLeft    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SolarIrradianceLeft    0

#define LIN_BYTE_OFFSET_LI0_SolarIrradianceRight    7
#define LIN_BIT_OFFSET_LI0_SolarIrradianceRight    0
#define LIN_SIGNAL_SIZE_LI0_SolarIrradianceRight    8
#define LIN_FLAG_BYTE_OFFSET_LI0_SolarIrradianceRight    2
#define LIN_FLAG_BIT_OFFSET_LI0_SolarIrradianceRight    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SolarIrradianceRight    0

#define LIN_BYTE_OFFSET_LI0_AmbientTemp    20
#define LIN_BIT_OFFSET_LI0_AmbientTemp    0
#define LIN_SIGNAL_SIZE_LI0_AmbientTemp    8
#define LIN_FLAG_BYTE_OFFSET_LI0_AmbientTemp    5
#define LIN_FLAG_BIT_OFFSET_LI0_AmbientTemp    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_AmbientTemp    3

#define LIN_BYTE_OFFSET_LI0_WindowSunroofPosition    22
#define LIN_BIT_OFFSET_LI0_WindowSunroofPosition    0
#define LIN_SIGNAL_SIZE_LI0_WindowSunroofPosition    2
#define LIN_FLAG_BYTE_OFFSET_LI0_WindowSunroofPosition    5
#define LIN_FLAG_BIT_OFFSET_LI0_WindowSunroofPosition    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_WindowSunroofPosition    3

#define LIN_BYTE_OFFSET_LI0_STAT_RemoteControl    22
#define LIN_BIT_OFFSET_LI0_STAT_RemoteControl    2
#define LIN_SIGNAL_SIZE_LI0_STAT_RemoteControl    1
#define LIN_FLAG_BYTE_OFFSET_LI0_STAT_RemoteControl    5
#define LIN_FLAG_BIT_OFFSET_LI0_STAT_RemoteControl    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_RemoteControl    3




#define LIN_FLAG_BYTE_OFFSET_LI0_RLS_2             0
#define LIN_FLAG_BIT_OFFSET_LI0_RLS_2              0

#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_3             3
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_3              0

#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_1             4
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_1              0

#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_2             5
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_2              0


/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */


/* static access macros for signal LI0_STAT_Terminal */
   
#define l_u8_rd_LI0_STAT_Terminal() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_Terminal] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_STAT_Terminal) - 1) \
    << LIN_BIT_OFFSET_LI0_STAT_Terminal )) >> LIN_BIT_OFFSET_LI0_STAT_Terminal))
#define l_u8_wr_LI0_STAT_Terminal(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_Terminal] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_Terminal] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_STAT_Terminal) - 1) << LIN_BIT_OFFSET_LI0_STAT_Terminal)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_STAT_Terminal) - 1) & (A)) << LIN_BIT_OFFSET_LI0_STAT_Terminal))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_Terminal] = 1;}


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

/* static access macros for signal LI0_STAT_RS */
   
#define l_bool_rd_LI0_STAT_RS() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RS], \
   	LIN_BIT_OFFSET_LI0_STAT_RS))
#define l_bool_wr_LI0_STAT_RS(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RS], \
  	LIN_BIT_OFFSET_LI0_STAT_RS)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RS], \
  	LIN_BIT_OFFSET_LI0_STAT_RS));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_RS] = 1;}

/* static access macros for signal LI0_STAT_RSError */
   
#define l_bool_rd_LI0_STAT_RSError() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RSError], \
   	LIN_BIT_OFFSET_LI0_STAT_RSError))
#define l_bool_wr_LI0_STAT_RSError(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RSError], \
  	LIN_BIT_OFFSET_LI0_STAT_RSError)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RSError], \
  	LIN_BIT_OFFSET_LI0_STAT_RSError));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_RSError] = 1;}

/* static access macros for signal LI0_LightOnReq */
   
#define l_bool_rd_LI0_LightOnReq() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightOnReq], \
   	LIN_BIT_OFFSET_LI0_LightOnReq))
#define l_bool_wr_LI0_LightOnReq(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightOnReq], \
  	LIN_BIT_OFFSET_LI0_LightOnReq)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightOnReq], \
  	LIN_BIT_OFFSET_LI0_LightOnReq));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LightOnReq] = 1;}

/* static access macros for signal LI0_STAT_DayNightMode */
   
#define l_u8_rd_LI0_STAT_DayNightMode() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_DayNightMode] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_STAT_DayNightMode) - 1) \
    << LIN_BIT_OFFSET_LI0_STAT_DayNightMode )) >> LIN_BIT_OFFSET_LI0_STAT_DayNightMode))
#define l_u8_wr_LI0_STAT_DayNightMode(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_DayNightMode] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_DayNightMode] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_STAT_DayNightMode) - 1) << LIN_BIT_OFFSET_LI0_STAT_DayNightMode)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_STAT_DayNightMode) - 1) & (A)) << LIN_BIT_OFFSET_LI0_STAT_DayNightMode))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_DayNightMode] = 1;}

/* static access macros for signal LI0_STAT_LS */
   
#define l_bool_rd_LI0_STAT_LS() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_LS], \
   	LIN_BIT_OFFSET_LI0_STAT_LS))
#define l_bool_wr_LI0_STAT_LS(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_LS], \
  	LIN_BIT_OFFSET_LI0_STAT_LS)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_LS], \
  	LIN_BIT_OFFSET_LI0_STAT_LS));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_LS] = 1;}

/* static access macros for signal LI0_STAT_LSError */
   
#define l_bool_rd_LI0_STAT_LSError() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_LSError], \
   	LIN_BIT_OFFSET_LI0_STAT_LSError))
#define l_bool_wr_LI0_STAT_LSError(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_LSError], \
  	LIN_BIT_OFFSET_LI0_STAT_LSError)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_LSError], \
  	LIN_BIT_OFFSET_LI0_STAT_LSError));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_LSError] = 1;}

/* static access macros for signal LI0_FrontWiperSwitch */
   
#define l_u8_rd_LI0_FrontWiperSwitch() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperSwitch] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_FrontWiperSwitch) - 1) \
    << LIN_BIT_OFFSET_LI0_FrontWiperSwitch )) >> LIN_BIT_OFFSET_LI0_FrontWiperSwitch))
#define l_u8_wr_LI0_FrontWiperSwitch(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperSwitch] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperSwitch] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_FrontWiperSwitch) - 1) << LIN_BIT_OFFSET_LI0_FrontWiperSwitch)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_FrontWiperSwitch) - 1) & (A)) << LIN_BIT_OFFSET_LI0_FrontWiperSwitch))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWiperSwitch] = 1;}

/* static access macros for signal LI0_FrontWasherSwitch */
   
#define l_u8_rd_LI0_FrontWasherSwitch() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWasherSwitch] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_FrontWasherSwitch) - 1) \
    << LIN_BIT_OFFSET_LI0_FrontWasherSwitch )) >> LIN_BIT_OFFSET_LI0_FrontWasherSwitch))
#define l_u8_wr_LI0_FrontWasherSwitch(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWasherSwitch] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWasherSwitch] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_FrontWasherSwitch) - 1) << LIN_BIT_OFFSET_LI0_FrontWasherSwitch)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_FrontWasherSwitch) - 1) & (A)) << LIN_BIT_OFFSET_LI0_FrontWasherSwitch))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWasherSwitch] = 1;}

/* static access macros for signal LI0_FrontWiperPosition */
   
#define l_bool_rd_LI0_FrontWiperPosition() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperPosition], \
   	LIN_BIT_OFFSET_LI0_FrontWiperPosition))
#define l_bool_wr_LI0_FrontWiperPosition(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperPosition], \
  	LIN_BIT_OFFSET_LI0_FrontWiperPosition)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperPosition], \
  	LIN_BIT_OFFSET_LI0_FrontWiperPosition));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWiperPosition] = 1;}

/* static access macros for signal LI0_MasterLightSwitch */
   
#define l_u8_rd_LI0_MasterLightSwitch() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_MasterLightSwitch] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_MasterLightSwitch) - 1) \
    << LIN_BIT_OFFSET_LI0_MasterLightSwitch )) >> LIN_BIT_OFFSET_LI0_MasterLightSwitch))
#define l_u8_wr_LI0_MasterLightSwitch(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_MasterLightSwitch] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_MasterLightSwitch] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_MasterLightSwitch) - 1) << LIN_BIT_OFFSET_LI0_MasterLightSwitch)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_MasterLightSwitch) - 1) & (A)) << LIN_BIT_OFFSET_LI0_MasterLightSwitch))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_MasterLightSwitch] = 1;}

/* static access macros for signal LI0_LightOnReason */
   
#define l_u8_rd_LI0_LightOnReason() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightOnReason] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_LightOnReason) - 1) \
    << LIN_BIT_OFFSET_LI0_LightOnReason )) >> LIN_BIT_OFFSET_LI0_LightOnReason))
#define l_u8_wr_LI0_LightOnReason(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightOnReason] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_LightOnReason] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_LightOnReason) - 1) << LIN_BIT_OFFSET_LI0_LightOnReason)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_LightOnReason) - 1) & (A)) << LIN_BIT_OFFSET_LI0_LightOnReason))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_LightOnReason] = 1;}

/* static access macros for signal LI0_VehicleSpeedValid */
   
#define l_u8_rd_LI0_VehicleSpeedValid() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeedValid] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_VehicleSpeedValid) - 1) \
    << LIN_BIT_OFFSET_LI0_VehicleSpeedValid )) >> LIN_BIT_OFFSET_LI0_VehicleSpeedValid))
#define l_u8_wr_LI0_VehicleSpeedValid(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeedValid] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_VehicleSpeedValid] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_VehicleSpeedValid) - 1) << LIN_BIT_OFFSET_LI0_VehicleSpeedValid)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_VehicleSpeedValid) - 1) & (A)) << LIN_BIT_OFFSET_LI0_VehicleSpeedValid))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_VehicleSpeedValid] = 1;}

/* static access macros for signal LI0_Day */
   
#define l_u8_rd_LI0_Day() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Day] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_Day) - 1) \
    << LIN_BIT_OFFSET_LI0_Day )) >> LIN_BIT_OFFSET_LI0_Day))
#define l_u8_wr_LI0_Day(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Day] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Day] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_Day) - 1) << LIN_BIT_OFFSET_LI0_Day)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_Day) - 1) & (A)) << LIN_BIT_OFFSET_LI0_Day))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Day] = 1;}

/* static access macros for signal LI0_Month */
   
#define l_u8_rd_LI0_Month() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Month] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_Month) - 1) \
    << LIN_BIT_OFFSET_LI0_Month )) >> LIN_BIT_OFFSET_LI0_Month))
#define l_u8_wr_LI0_Month(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Month] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Month] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_Month) - 1) << LIN_BIT_OFFSET_LI0_Month)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_Month) - 1) & (A)) << LIN_BIT_OFFSET_LI0_Month))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Month] = 1;}

/* static access macros for signal LI0_Year */
   
#define l_u8_rd_LI0_Year() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Year] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_Year) - 1) \
    << LIN_BIT_OFFSET_LI0_Year )) >> LIN_BIT_OFFSET_LI0_Year))
#define l_u8_wr_LI0_Year(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Year] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_Year] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_Year) - 1) << LIN_BIT_OFFSET_LI0_Year)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_Year) - 1) & (A)) << LIN_BIT_OFFSET_LI0_Year))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_Year] = 1;}

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

/* static access macros for signal LI0_FrontWiperInterval */
   
#define l_u8_rd_LI0_FrontWiperInterval() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperInterval] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_FrontWiperInterval) - 1) \
    << LIN_BIT_OFFSET_LI0_FrontWiperInterval )) >> LIN_BIT_OFFSET_LI0_FrontWiperInterval))
#define l_u8_wr_LI0_FrontWiperInterval(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperInterval] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrontWiperInterval] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_FrontWiperInterval) - 1) << LIN_BIT_OFFSET_LI0_FrontWiperInterval)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_FrontWiperInterval) - 1) & (A)) << LIN_BIT_OFFSET_LI0_FrontWiperInterval))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrontWiperInterval] = 1;}

/* static access macros for signal LI0_HUDBrightnessUnit */
   
#define l_u8_rd_LI0_HUDBrightnessUnit() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_HUDBrightnessUnit] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_HUDBrightnessUnit) - 1) \
    << LIN_BIT_OFFSET_LI0_HUDBrightnessUnit )) >> LIN_BIT_OFFSET_LI0_HUDBrightnessUnit))
#define l_u8_wr_LI0_HUDBrightnessUnit(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_HUDBrightnessUnit] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_HUDBrightnessUnit] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_HUDBrightnessUnit) - 1) << LIN_BIT_OFFSET_LI0_HUDBrightnessUnit)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_HUDBrightnessUnit) - 1) & (A)) << LIN_BIT_OFFSET_LI0_HUDBrightnessUnit))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_HUDBrightnessUnit] = 1;}

/* static access macros for signal LI0_HUDBrightnessRawValue */
   
#define l_u8_rd_LI0_HUDBrightnessRawValue() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_HUDBrightnessRawValue] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_HUDBrightnessRawValue) - 1) \
    << LIN_BIT_OFFSET_LI0_HUDBrightnessRawValue )) >> LIN_BIT_OFFSET_LI0_HUDBrightnessRawValue))
#define l_u8_wr_LI0_HUDBrightnessRawValue(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_HUDBrightnessRawValue] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_HUDBrightnessRawValue] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_HUDBrightnessRawValue) - 1) << LIN_BIT_OFFSET_LI0_HUDBrightnessRawValue)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_HUDBrightnessRawValue) - 1) & (A)) << LIN_BIT_OFFSET_LI0_HUDBrightnessRawValue))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_HUDBrightnessRawValue] = 1;}

/* static access macros for signal LI0_RainDayGlobalClose */
   
#define l_bool_rd_LI0_RainDayGlobalClose() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RainDayGlobalClose], \
   	LIN_BIT_OFFSET_LI0_RainDayGlobalClose))
#define l_bool_wr_LI0_RainDayGlobalClose(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RainDayGlobalClose], \
  	LIN_BIT_OFFSET_LI0_RainDayGlobalClose)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RainDayGlobalClose], \
  	LIN_BIT_OFFSET_LI0_RainDayGlobalClose));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RainDayGlobalClose] = 1;}

/* static access macros for signal LI0_RLSHumidTempError */
   
#define l_bool_rd_LI0_RLSHumidTempError() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLSHumidTempError], \
   	LIN_BIT_OFFSET_LI0_RLSHumidTempError))
#define l_bool_wr_LI0_RLSHumidTempError(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLSHumidTempError], \
  	LIN_BIT_OFFSET_LI0_RLSHumidTempError)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_RLSHumidTempError], \
  	LIN_BIT_OFFSET_LI0_RLSHumidTempError));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_RLSHumidTempError] = 1;}


/* static access macros for signal LI0_InterTempSensorValue */
   
#define l_u8_rd_LI0_InterTempSensorValue() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempSensorValue] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_InterTempSensorValue) - 1) \
    << LIN_BIT_OFFSET_LI0_InterTempSensorValue )) >> LIN_BIT_OFFSET_LI0_InterTempSensorValue))
#define l_u8_wr_LI0_InterTempSensorValue(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempSensorValue] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempSensorValue] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_InterTempSensorValue) - 1) << LIN_BIT_OFFSET_LI0_InterTempSensorValue)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_InterTempSensorValue) - 1) & (A)) << LIN_BIT_OFFSET_LI0_InterTempSensorValue))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_InterTempSensorValue] = 1;}

/* static access macros for signal LI0_InterHumidSensorValue */
   
#define l_u8_rd_LI0_InterHumidSensorValue() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterHumidSensorValue] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_InterHumidSensorValue) - 1) \
    << LIN_BIT_OFFSET_LI0_InterHumidSensorValue )) >> LIN_BIT_OFFSET_LI0_InterHumidSensorValue))
#define l_u8_wr_LI0_InterHumidSensorValue(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterHumidSensorValue] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterHumidSensorValue] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_InterHumidSensorValue) - 1) << LIN_BIT_OFFSET_LI0_InterHumidSensorValue)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_InterHumidSensorValue) - 1) & (A)) << LIN_BIT_OFFSET_LI0_InterHumidSensorValue))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_InterHumidSensorValue] = 1;}

/* static access macros for signal LI0_SolarIrradianceLeft */
   
#define l_u8_rd_LI0_SolarIrradianceLeft() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SolarIrradianceLeft] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_SolarIrradianceLeft) - 1) \
    << LIN_BIT_OFFSET_LI0_SolarIrradianceLeft )) >> LIN_BIT_OFFSET_LI0_SolarIrradianceLeft))
#define l_u8_wr_LI0_SolarIrradianceLeft(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SolarIrradianceLeft] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SolarIrradianceLeft] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_SolarIrradianceLeft) - 1) << LIN_BIT_OFFSET_LI0_SolarIrradianceLeft)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_SolarIrradianceLeft) - 1) & (A)) << LIN_BIT_OFFSET_LI0_SolarIrradianceLeft))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SolarIrradianceLeft] = 1;}

/* static access macros for signal LI0_SolarIrradianceRight */
   
#define l_u8_rd_LI0_SolarIrradianceRight() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SolarIrradianceRight] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_SolarIrradianceRight) - 1) \
    << LIN_BIT_OFFSET_LI0_SolarIrradianceRight )) >> LIN_BIT_OFFSET_LI0_SolarIrradianceRight))
#define l_u8_wr_LI0_SolarIrradianceRight(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SolarIrradianceRight] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_SolarIrradianceRight] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_SolarIrradianceRight) - 1) << LIN_BIT_OFFSET_LI0_SolarIrradianceRight)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_SolarIrradianceRight) - 1) & (A)) << LIN_BIT_OFFSET_LI0_SolarIrradianceRight))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_SolarIrradianceRight] = 1;}

/* static access macros for signal LI0_AmbientTemp */
   
#define l_u8_rd_LI0_AmbientTemp() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_AmbientTemp] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_AmbientTemp) - 1) \
    << LIN_BIT_OFFSET_LI0_AmbientTemp )) >> LIN_BIT_OFFSET_LI0_AmbientTemp))
#define l_u8_wr_LI0_AmbientTemp(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_AmbientTemp] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_AmbientTemp] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_AmbientTemp) - 1) << LIN_BIT_OFFSET_LI0_AmbientTemp)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_AmbientTemp) - 1) & (A)) << LIN_BIT_OFFSET_LI0_AmbientTemp))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_AmbientTemp] = 1;}

/* static access macros for signal LI0_WindowSunroofPosition */
   
#define l_u8_rd_LI0_WindowSunroofPosition() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_WindowSunroofPosition] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_WindowSunroofPosition) - 1) \
    << LIN_BIT_OFFSET_LI0_WindowSunroofPosition )) >> LIN_BIT_OFFSET_LI0_WindowSunroofPosition))
#define l_u8_wr_LI0_WindowSunroofPosition(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_WindowSunroofPosition] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_WindowSunroofPosition] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_WindowSunroofPosition) - 1) << LIN_BIT_OFFSET_LI0_WindowSunroofPosition)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_WindowSunroofPosition) - 1) & (A)) << LIN_BIT_OFFSET_LI0_WindowSunroofPosition))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_WindowSunroofPosition] = 1;}

/* static access macros for signal LI0_STAT_RemoteControl */
   
#define l_bool_rd_LI0_STAT_RemoteControl() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RemoteControl], \
   	LIN_BIT_OFFSET_LI0_STAT_RemoteControl))
#define l_bool_wr_LI0_STAT_RemoteControl(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RemoteControl], \
  	LIN_BIT_OFFSET_LI0_STAT_RemoteControl)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_STAT_RemoteControl], \
  	LIN_BIT_OFFSET_LI0_STAT_RemoteControl));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_STAT_RemoteControl] = 1;}



/* static access macros for signal LI0_vehicleSpeed */
#define l_u16_rd_LI0_vehicleSpeed() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_vehicleSpeed + 1] & 0xff) << 4) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_vehicleSpeed]) >> 0x04))
#define l_u16_wr_LI0_vehicleSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_vehicleSpeed + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_vehicleSpeed + 1] &  (0x00))) | \
	((l_u8) ((l_u8) ((A) >> 4)) & 0xff))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_vehicleSpeed] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_vehicleSpeed] & (0x0f))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_vehicleSpeed))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_vehicleSpeed] = 1;}

/* static access macros for signal LI0_InterTempDewPoint */
#define l_u16_rd_LI0_InterTempDewPoint() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempDewPoint + 1] & 0xff) << 1) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempDewPoint]) >> 0x07))
#define l_u16_wr_LI0_InterTempDewPoint(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempDewPoint + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempDewPoint + 1] &  (0x00))) | \
	((l_u8) ((l_u8) ((A) >> 1)) & 0xff))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempDewPoint] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_InterTempDewPoint] & (0x7f))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LI0_InterTempDewPoint))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_InterTempDewPoint] = 1;}





/* Signal flag APIs */

#define l_flg_tst_LI0_STAT_Terminal_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_Terminal],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_Terminal)
#define l_flg_clr_LI0_STAT_Terminal_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_Terminal],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_Terminal)

#define l_flg_tst_LI0_vehicleSpeed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_vehicleSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_vehicleSpeed)
#define l_flg_clr_LI0_vehicleSpeed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_vehicleSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_vehicleSpeed)

#define l_flg_tst_LI0_WiperSpeed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_WiperSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_WiperSpeed)
#define l_flg_clr_LI0_WiperSpeed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_WiperSpeed],\
         LIN_FLAG_BIT_OFFSET_LI0_WiperSpeed)

#define l_flg_tst_LI0_STAT_RS_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_RS],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_RS)
#define l_flg_clr_LI0_STAT_RS_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_RS],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_RS)

#define l_flg_tst_LI0_STAT_RSError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_RSError],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_RSError)
#define l_flg_clr_LI0_STAT_RSError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_RSError],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_RSError)

#define l_flg_tst_LI0_LightOnReq_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LightOnReq],\
         LIN_FLAG_BIT_OFFSET_LI0_LightOnReq)
#define l_flg_clr_LI0_LightOnReq_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LightOnReq],\
         LIN_FLAG_BIT_OFFSET_LI0_LightOnReq)

#define l_flg_tst_LI0_STAT_DayNightMode_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_DayNightMode],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_DayNightMode)
#define l_flg_clr_LI0_STAT_DayNightMode_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_DayNightMode],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_DayNightMode)

#define l_flg_tst_LI0_STAT_LS_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_LS],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_LS)
#define l_flg_clr_LI0_STAT_LS_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_LS],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_LS)

#define l_flg_tst_LI0_STAT_LSError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_LSError],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_LSError)
#define l_flg_clr_LI0_STAT_LSError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_LSError],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_LSError)

#define l_flg_tst_LI0_FrontWiperSwitch_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWiperSwitch)
#define l_flg_clr_LI0_FrontWiperSwitch_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWiperSwitch)

#define l_flg_tst_LI0_FrontWasherSwitch_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWasherSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWasherSwitch)
#define l_flg_clr_LI0_FrontWasherSwitch_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWasherSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWasherSwitch)

#define l_flg_tst_LI0_FrontWiperPosition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWiperPosition)
#define l_flg_clr_LI0_FrontWiperPosition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWiperPosition)

#define l_flg_tst_LI0_MasterLightSwitch_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_MasterLightSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_MasterLightSwitch)
#define l_flg_clr_LI0_MasterLightSwitch_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_MasterLightSwitch],\
         LIN_FLAG_BIT_OFFSET_LI0_MasterLightSwitch)

#define l_flg_tst_LI0_LightOnReason_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LightOnReason],\
         LIN_FLAG_BIT_OFFSET_LI0_LightOnReason)
#define l_flg_clr_LI0_LightOnReason_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_LightOnReason],\
         LIN_FLAG_BIT_OFFSET_LI0_LightOnReason)

#define l_flg_tst_LI0_VehicleSpeedValid_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_VehicleSpeedValid],\
         LIN_FLAG_BIT_OFFSET_LI0_VehicleSpeedValid)
#define l_flg_clr_LI0_VehicleSpeedValid_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_VehicleSpeedValid],\
         LIN_FLAG_BIT_OFFSET_LI0_VehicleSpeedValid)

#define l_flg_tst_LI0_Day_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Day],\
         LIN_FLAG_BIT_OFFSET_LI0_Day)
#define l_flg_clr_LI0_Day_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Day],\
         LIN_FLAG_BIT_OFFSET_LI0_Day)

#define l_flg_tst_LI0_Month_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Month],\
         LIN_FLAG_BIT_OFFSET_LI0_Month)
#define l_flg_clr_LI0_Month_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Month],\
         LIN_FLAG_BIT_OFFSET_LI0_Month)

#define l_flg_tst_LI0_Year_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Year],\
         LIN_FLAG_BIT_OFFSET_LI0_Year)
#define l_flg_clr_LI0_Year_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_Year],\
         LIN_FLAG_BIT_OFFSET_LI0_Year)

#define l_flg_tst_LI0_RLS_REP_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_REP_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_REP_Error)
#define l_flg_clr_LI0_RLS_REP_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_REP_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_REP_Error)

#define l_flg_tst_LI0_FrontWiperInterval_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperInterval],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWiperInterval)
#define l_flg_clr_LI0_FrontWiperInterval_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrontWiperInterval],\
         LIN_FLAG_BIT_OFFSET_LI0_FrontWiperInterval)

#define l_flg_tst_LI0_HUDBrightnessUnit_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_HUDBrightnessUnit],\
         LIN_FLAG_BIT_OFFSET_LI0_HUDBrightnessUnit)
#define l_flg_clr_LI0_HUDBrightnessUnit_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_HUDBrightnessUnit],\
         LIN_FLAG_BIT_OFFSET_LI0_HUDBrightnessUnit)

#define l_flg_tst_LI0_HUDBrightnessRawValue_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_HUDBrightnessRawValue],\
         LIN_FLAG_BIT_OFFSET_LI0_HUDBrightnessRawValue)
#define l_flg_clr_LI0_HUDBrightnessRawValue_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_HUDBrightnessRawValue],\
         LIN_FLAG_BIT_OFFSET_LI0_HUDBrightnessRawValue)

#define l_flg_tst_LI0_RainDayGlobalClose_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RainDayGlobalClose],\
         LIN_FLAG_BIT_OFFSET_LI0_RainDayGlobalClose)
#define l_flg_clr_LI0_RainDayGlobalClose_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RainDayGlobalClose],\
         LIN_FLAG_BIT_OFFSET_LI0_RainDayGlobalClose)

#define l_flg_tst_LI0_RLSHumidTempError_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLSHumidTempError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLSHumidTempError)
#define l_flg_clr_LI0_RLSHumidTempError_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLSHumidTempError],\
         LIN_FLAG_BIT_OFFSET_LI0_RLSHumidTempError)

#define l_flg_tst_LI0_InterTempDewPoint_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_InterTempDewPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_InterTempDewPoint)
#define l_flg_clr_LI0_InterTempDewPoint_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_InterTempDewPoint],\
         LIN_FLAG_BIT_OFFSET_LI0_InterTempDewPoint)

#define l_flg_tst_LI0_InterTempSensorValue_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_InterTempSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_InterTempSensorValue)
#define l_flg_clr_LI0_InterTempSensorValue_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_InterTempSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_InterTempSensorValue)

#define l_flg_tst_LI0_InterHumidSensorValue_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_InterHumidSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_InterHumidSensorValue)
#define l_flg_clr_LI0_InterHumidSensorValue_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_InterHumidSensorValue],\
         LIN_FLAG_BIT_OFFSET_LI0_InterHumidSensorValue)

#define l_flg_tst_LI0_SolarIrradianceLeft_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SolarIrradianceLeft],\
         LIN_FLAG_BIT_OFFSET_LI0_SolarIrradianceLeft)
#define l_flg_clr_LI0_SolarIrradianceLeft_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SolarIrradianceLeft],\
         LIN_FLAG_BIT_OFFSET_LI0_SolarIrradianceLeft)

#define l_flg_tst_LI0_SolarIrradianceRight_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SolarIrradianceRight],\
         LIN_FLAG_BIT_OFFSET_LI0_SolarIrradianceRight)
#define l_flg_clr_LI0_SolarIrradianceRight_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_SolarIrradianceRight],\
         LIN_FLAG_BIT_OFFSET_LI0_SolarIrradianceRight)

#define l_flg_tst_LI0_AmbientTemp_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_AmbientTemp],\
         LIN_FLAG_BIT_OFFSET_LI0_AmbientTemp)
#define l_flg_clr_LI0_AmbientTemp_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_AmbientTemp],\
         LIN_FLAG_BIT_OFFSET_LI0_AmbientTemp)

#define l_flg_tst_LI0_WindowSunroofPosition_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_WindowSunroofPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_WindowSunroofPosition)
#define l_flg_clr_LI0_WindowSunroofPosition_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_WindowSunroofPosition],\
         LIN_FLAG_BIT_OFFSET_LI0_WindowSunroofPosition)

#define l_flg_tst_LI0_STAT_RemoteControl_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_RemoteControl],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_RemoteControl)
#define l_flg_clr_LI0_STAT_RemoteControl_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_STAT_RemoteControl],\
         LIN_FLAG_BIT_OFFSET_LI0_STAT_RemoteControl)



/* Frame flag APIs */

#define l_flg_tst_LI0_RLS_2_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_2],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_2)
#define l_flg_clr_LI0_RLS_2_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RLS_2],\
         LIN_FLAG_BIT_OFFSET_LI0_RLS_2)

#define l_flg_tst_LI0_BCM_LIN_3_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_3],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_3)
#define l_flg_clr_LI0_BCM_LIN_3_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_3],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_3)

#define l_flg_tst_LI0_BCM_LIN_1_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_1],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_1)
#define l_flg_clr_LI0_BCM_LIN_1_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_1],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_1)

#define l_flg_tst_LI0_BCM_LIN_2_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_2],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_2)
#define l_flg_clr_LI0_BCM_LIN_2_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN_2],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN_2)



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */
