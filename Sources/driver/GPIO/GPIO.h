/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           gpio.h
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
#ifndef __GPIO_H__
#define __GPIO_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"

#define CS      PTS_PTS7          //CS   OUTPUT
#define MOSI    PTS_PTS5          //MOSI OUTPUT
#define SCLK    PTS_PTS6          //SCLK OUTPUT
#define MISO    PTS_PTS4      //MISO INPUT
#define DR      PTT_PTT3          //DR   INPUT
#define WAKE_UP PTT_PTT2          //WAKE_UP


#ifdef FOUR_TO_ONE
      #define LIN_EN    PTP_PTP0          //EN   OUTPUT
#else
      #define LIN_EN    PTT_PTT1          //EN   OUTPUT
#endif



extern void GPIO_Init(void);

#endif