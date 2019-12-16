/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      clock.h 
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
#ifndef    _CLOCK_H_  
#define    _CLOCK_H_  

#include "derivative.h" /* include peripheral declarations */


#define   BUS_CLCOK 20000000


extern void Clk_Init(void);
extern void Delay_Nus(uint8 n);
extern void Delay_Ms(uint16 Ms);
#endif    /* _ADC_H_ */
