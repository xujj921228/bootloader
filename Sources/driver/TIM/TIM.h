/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           tim.h
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

#ifndef __TIM_H__
#define __TIM_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"


extern void TIM_Init(void);
extern void interrupt VectorNumber_Vtimch4 TIM4_ISR(void);
extern void interrupt VectorNumber_Vtimch0 TIM0_ISR(void);

#endif