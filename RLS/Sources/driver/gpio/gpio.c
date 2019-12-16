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
#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"
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
	//GPIOA_PSOR |= 0x00008000 ; //PTB7
	LIN_ENABLE;
		
	CONFIG_PIN_AS_GPIO(PTB,PTB6,INPUT);  //DR
	ENABLE_INPUT(PTB,PTB6);

	CONFIG_PIN_AS_GPIO(PTD,PTD3,INPUT);	 //MR
	ENABLE_INPUT(PTD,PTD3);
	    	
	GPIOA_PDDR |= 0x00000040 ; //PTA6-output  WT
	GPIOA_PSOR |= 0x00000040 ; //PTA6-output  WT
	
	GPIOA_PDDR |= 0x00000080 ; //PTA7-output  WAKE UP
    GPIOA_PSOR |= 0x00000080 ; //PTA7-output  WAKE UP
    PORT_PUEL  |= 0x00000080 ;
    
    GPIOA_PDDR |= 0x00002000 ; //PTB5-output  CS
    GPIOA_PSOR |= 0x00002000 ; //PTB5-output  CS
    PORT_PUEL  |= 0x00002000 ;
    
    GPIOA_PDDR |= 0x00000800 ; //PTB3-output  MOSI
	GPIOA_PSOR |= 0x00000800 ; //PTB3-output  MOSI
	PORT_PUEL  |= 0x00000800 ;
    
    SIM_SOPT &= 0xFFFFFFFD;   //DIS_NMI
    CONFIG_PIN_AS_GPIO(PTB,PTB4,INPUT);	
    ENABLE_INPUT(PTB,PTB4);      
        
    GPIOA_PDDR |= 0x00000400 ; //PTB2-output  SCK
    GPIOA_PSOR |= 0x00000400 ; //PTB2-output  SCK
    PORT_PUEL  |= 0x00000400 ;
    
	CONFIG_PIN_AS_GPIO(PTA,PTA0,INPUT);	
	ENABLE_INPUT(PTA,PTA0);
	
	CONFIG_PIN_AS_GPIO(PTA,PTA1,INPUT);	
	ENABLE_INPUT(PTA,PTA1);
	
	CONFIG_PIN_AS_GPIO(PTA,PTA2,INPUT);	
	ENABLE_INPUT(PTA,PTA2);
	
	CONFIG_PIN_AS_GPIO(PTA,PTA3,INPUT);	
	ENABLE_INPUT(PTA,PTA3);
    	
	CONFIG_PIN_AS_GPIO(PTC,PTC0,INPUT);	
	ENABLE_INPUT(PTC,PTC0);
	
	CONFIG_PIN_AS_GPIO(PTC,PTC1,INPUT);	
	ENABLE_INPUT(PTC,PTC1);
	
	CONFIG_PIN_AS_GPIO(PTC,PTC2,INPUT);	
	ENABLE_INPUT(PTC,PTC2);
	
	CONFIG_PIN_AS_GPIO(PTC,PTC5,INPUT);	
	ENABLE_INPUT(PTC,PTC5);
	
	CONFIG_PIN_AS_GPIO(PTC,PTC6,INPUT);	
	ENABLE_INPUT(PTC,PTC6);
	
	CONFIG_PIN_AS_GPIO(PTC,PTC7,INPUT);	
    ENABLE_INPUT(PTC,PTC7);
	
	CONFIG_PIN_AS_GPIO(PTD,PTD0,INPUT);	
	ENABLE_INPUT(PTD,PTD0);
	
	CONFIG_PIN_AS_GPIO(PTD,PTD1,INPUT);	
	ENABLE_INPUT(PTD,PTD1);
	
	CONFIG_PIN_AS_GPIO(PTD,PTD2,INPUT);	
	ENABLE_INPUT(PTD,PTD2);
}
