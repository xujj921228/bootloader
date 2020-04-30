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
* @author    xujun
*  
* @version   1.0 
*  
* @date      Sat Aug 04 10:53:51 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _GPIO_H_  
#define    _GPIO_H_  

#include "derivative.h" /* include peripheral declarations */


/***********************************************************
 * 
 * Ports mapped to GPIOA,GPIOB and GPIOC registers
 * 
 **********************************************************/
#define PTA     GPIOA_BASE_PTR
#define PTB     GPIOA_BASE_PTR
#define PTC     GPIOA_BASE_PTR
#define PTD     GPIOA_BASE_PTR

#define PTE     GPIOB_BASE_PTR
#define PTF		GPIOB_BASE_PTR
#define PTG		GPIOB_BASE_PTR
#define PTH		GPIOB_BASE_PTR

#define PTI		GPIOC_BASE_PTR

/***********************************************************
 * 
 * Input/Output macro
 * 
 **********************************************************/
#define OUTPUT  1
#define INPUT	0

enum GPIOA_Register {
PTA0,	
PTA1,
PTA2,
PTA3,
PTA4,
PTA5,
PTA6,
PTA7,
PTB0,	
PTB1,
PTB2,
PTB3,
PTB4,
PTB5,
PTB6,
PTB7,
PTC0,	
PTC1,
PTC2,
PTC3,
PTC4,
PTC5,
PTC6,
PTC7,
PTD0,	
PTD1,
PTD2,
PTD3,
PTD4,
PTD5,
PTD6,
PTD7,
};

enum GPIOB_Register {
PTE0,	
PTE1,
PTE2,
PTE3,
PTE4,
PTE5,
PTE6,
PTE7,
PTF0,	
PTF1,
PTF2,
PTF3,
PTF4,
PTF5,
PTF6,
PTF7,
PTG0,	
PTG1,
PTG2,
PTG3,
PTG4,
PTG5,
PTG6,
PTG7,
PTH0,	
PTH1,
PTH2,
PTH3,
PTH4,
PTH5,
PTH6,
PTH7,
};



/***********************************************************
 * 
 * GPIO configuration macro
 * 
 **********************************************************/
#define CONFIG_PIN_AS_GPIO(port,port_pin,mode)    	XCONFIG_PIN_AS_GPIO(port,port_pin,mode)
#define XCONFIG_PIN_AS_GPIO(port,port_pin,mode)   	(mode == 0) ? (port->PDDR &=~(1<< port_pin)) : (port->PDDR |= (1 << port_pin)) 

/***********************************************************
 * 
 * Enable and Disable input macro
 * 
 **********************************************************/
#define ENABLE_INPUT(port,port_pin) 				XENABLE_INPUT(port,port_pin)
#define XENABLE_INPUT(port,port_pin)				port->PIDR &=~ (1<<port_pin)

#define DISABLE_INPUT(port,port_pin) 				XDISABLE_INPUT(port,port_pin)
#define XDISABLE_INPUT(port,port_pin)				port->PIDR |= (1<<port_pin)


/***********************************************************
 * 
 * Read input macro
 * 
 **********************************************************/
#define READ_INPUT(port,port_pin)					XREAD_INPUT(port,port_pin)
#define XREAD_INPUT(port,port_pin)					(port->PDIR & GPIO_PDIR_PDI(1<<port_pin))


#define   LIN_ENABLE       GPIOA_PSOR |= 0x00008000
#define   LIN_DISABLE      GPIOA_PCOR |= 0x00008000

#define   CS_HIGH          GPIOA_PSOR |= 0x00002000 
#define   CS_LOW           GPIOA_PCOR |= 0x00002000 

#define   SCLK_HIGH        GPIOA_PSOR |= 0x00000400 
#define   SCLK_LOW         GPIOA_PCOR |= 0x00000400 

#define   MOSI_HIGH        GPIOA_PSOR |= 0x00000800 
#define   MOSI_LOW         GPIOA_PCOR |= 0x00000800 


#define   MISO            ((GPIOA_PDIR&0x00001000)>>12) //PTB4-intput  MISO  //
#define   DR              ((GPIOA_PDIR&0x00004000)>>14) //PTB6-intput  DR    //
#define   MR              ((GPIOA_PDIR&0x08000000)>>27) //PTD3-intput  MR    //

#define RLS_Enable_Light()\
{\
GPIOA_PDDR|=0x00000002;\
GPIOA_PSOR|=0x00000002;\
GPIOA_PDDR|=0x00040000;\
GPIOA_PSOR|=0x00040000;}

#define RLS_Disable_Light()\
{\
GPIOA_PDDR|=0x00000002;\
GPIOA_PCOR|=0x00000002;\ 
GPIOA_PDDR|=0x00040000;\ 
GPIOA_PCOR|=0x00040000;}   


extern void GPIO_Init(void);

#endif    /* _ADC_H_ */
