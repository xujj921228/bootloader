/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      adc.h 
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
#ifndef    _FTM_H_  
#define    _FTM_H_  

#include "derivative.h" /* include peripheral declarations */

#define TIME_BASE_PERIOD_10ms   10000   //10ms




extern uint8 G_10msFlag ;
extern uint8 G_20msFlag ;
extern uint8 G_50msFlag ;
extern uint8 G_100msFlag ;
extern uint8 G_500msFlag ;
extern uint8 G_4sFlag ;

extern uint16 G_4s_counter ;
extern void FTM0_Init(void);

#endif    /* _ADC_H_ */
