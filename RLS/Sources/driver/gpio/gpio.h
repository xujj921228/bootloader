/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      gpio.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Sat Aug 04 10:53:51 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#include <SKEAZN642.h>

#define   LIN_ENABLE       GPIOA_PSOR |= 0x00008000
#define   LIN_DISABLE      GPIOA_PCOR |= 0x00008000

extern void GPIO_Init(void);

