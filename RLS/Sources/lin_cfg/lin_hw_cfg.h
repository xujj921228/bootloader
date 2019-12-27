/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*! 
* 
* @file      lin_hw_cfg.h 
* 
* @author    xujun
*  
* @version   1.0 
*  
* @date      Fri Dec 28 13:33:49 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef      _LIN_HW_CFG_H
#define      _LIN_HW_CFG_H
#include <SKEAZN642.h> 

typedef enum { 
   UART0, 
   UART1, 
   UART2 
} lin_hardware_name;


/* Type of MCU */
#define _MCU_  _K_

/* Resynchronization support */
#define __RESYN_EN   0

/* Autobaud support */
#define AUTOBAUD     0 
 
/* Interface type that MCU uses */
#define XGATE_SUPPORT 0
#define _LIN_XGATE_   0 
#define _LIN_SCI_     0
#define _LIN_UART_    1 
#define _LIN_SLIC_    0
#define _LIN_GPIO_    0
/***********  SCI HARDWARE SECTION  *********/
#define NUM_OF_UART_CHANNEL    3
/* UART Base Register definition */
#define UART0_ADDR  0x4006A000  
#define UART1_ADDR  0x4006B000  
#define UART2_ADDR  0x4006C000  
 
/* Use UART Channel  */ 
#define _UART0_   1 
#define _UART1_   0 
#define _UART2_   0 
/* MCU bus frequency */
#define MCU_BUS_FREQ       20000000

/* Default interrupt period of the timer for LIN is TIME_BASE_PERIOD micro seconds */
#define TIME_BASE_PERIOD   500

/* max idle timeout for all networks = idle_timeout_value*1000000/time_base_period */
#define _MAX_IDLE_TIMEOUT_    10000      /* idle_timeout_value = 5s */
#endif
