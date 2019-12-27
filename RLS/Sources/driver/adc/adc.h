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
* @author    xujun
*  
* @version   1.0 
*  
* @date      Sat Aug 04 10:53:51 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _ADC_H_  
#define    _ADC_H_  

#include "config_parameter.h"



extern uint16 get_adc_times(uint8 chnl,uint8 convert_times);
extern void ADC_Init(void);
#endif    /* _ADC_H_ */
