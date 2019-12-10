/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      adc.c
*
* @author    FPT Software
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include <SKEAZN642.h>
#include "gpio.h"


/***********************************************************************************************
*
* @brief    gpio_Init 
* @param    none
* @return   none
*
************************************************************************************************/  
void GPIO_Init(void)
{
	GPIOA_PDDR |= 0x00008000 ; //PTB7-output  LIN_EN
	LIN_ENABLE;
    
    SIM_SOPT &= 0xFFFFFFFD;   //DIS_NMI

 
}
