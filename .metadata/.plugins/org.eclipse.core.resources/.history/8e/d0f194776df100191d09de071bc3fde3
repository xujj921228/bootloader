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
#include "adc.h"

void ADC_Init(void)
{
	SIM_SCGC |= SIM_SCGC_ADC_MASK ;
	ADC_APCTL1 |= 0x0800 ;  //ad 11
	ADC_SC3 = 0x0038; //12BIT,bus clock 
	ADC_SC4 = 0x0000; 
}


uint16 get_adc(uint8 num)
{

   ADC_SC1 = num;       // 转换AD1
                        // 
                        // Bit 7   (0)    : COCO, Conversion Complete Flag
                        // Bit 6   (0)    : AIEN, Interrupt Enable
                        // Bit 5   (0)    : ADCO, Continuous Conversion Enable       
                        // Bit 4-0 (00000): ADCH, Input Channel Select
   
   
   while((ADC_SC1 & 0x80) == 0x00)   //等待转换完成
   {
	   WDOG_Feed();
   } 
   
   return ADC_R;
   
}

uint16 get_adc_times(uint8 chnl,uint8 convert_times)
{
   uint32 tmp;
   uint16 result;
   uint8 i;
   
   tmp = 0;

   for(i = 0; i < convert_times; i++)
      tmp += get_adc(chnl); 
      
   tmp = tmp / convert_times;
   
   result = (uint16)(tmp);  
      
   return result;
   
}
