/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           clock.h
** Last modified Date:  2017-12-19
** Last Version:        V1.00
** Descriptions:        全局参数声明。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          xujun
** Created date:        2017-12-19
** Version:             V1.00
** Descriptions:        创建文件
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */



extern void MCU_CLOCK_Init(void) ;
extern void Delay_Nus(uint8 n);
extern void Delay_Ms(uint16 Ms);
extern void COP_Init(void);
#endif