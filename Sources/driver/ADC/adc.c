/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           adc.c
** Last modified Date:  2017-12-19
** Last Version:        V1.00
** Descriptions:        ȫ�ֲ���������
**
**--------------------------------------------------------------------------------------------------------
** Created by:          xujun
** Created date:        2017-12-19
** Version:             V1.00
** Descriptions:        �����ļ�
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/


#include "derivative.h" /* include peripheral declarations */
#include <hidef.h> /* for EnableInterrupts macro */
#include "system.h"
#include "adc.h"


/*******************************************************
 * FUNCTION NAME : ADC_Init()
 *   DESCRIPTION : init adc reg
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
 
void ADC_Init(void)
{
   ATDCTL2 = 0x40;  //����A/Dת��,��������,��ֹ�ж�
   ATDCTL1_SRES=1;  //ѡ��10λģ��ת��
   ATDCTL3 = 0x88;   //ÿ��ת��1��ͨ��
   ATDCTL4 = 0x07;   //ADģ��ʱ��Ƶ�� 
 
}


/*******************************************************
 * FUNCTION NAME : get_adc(num)
 *   DESCRIPTION : init adc reg
 *         INPUT : adc channal  
 *        OUTPUT : measure adc value  
 *        RETURN : measure adc value              
 *        OTHERS : NONE
 *******************************************************/

uint16 get_adc(uint8 num)
{
   uint16 AD_data;
   ATDCTL5 = num;       // ת��AD
                       
   while(!ATDSTAT0_SCF)
   {
        _FEED_COP(); /* feeds the dog */
   }
   
   AD_data = ATDDR0;
   
   return(AD_data);
}


/*******************************************************
 * FUNCTION NAME : get_adc_times(ch,num)
 *   DESCRIPTION : get avg value
 *         INPUT : adc channal ; number
 *        OUTPUT : avg value 
 *        RETURN : avg value              
 *        OTHERS : NONE
 *******************************************************/
 
uint16 get_adc_times(uint8 ch,uint8 convert_times)
{
   uint32 tmp;
   uint16 result;
   uint8 i;
   
   tmp = 0;

   for(i = 0; i < convert_times; i++)
   {
      tmp += get_adc(ch);
   }
      
      
   tmp = tmp / convert_times;
   
   result = (uint16)(tmp);  
      
   return result;
   
}



/* END */

/*
** ###################################################################
**
**     This file was created by Processor Expert
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/