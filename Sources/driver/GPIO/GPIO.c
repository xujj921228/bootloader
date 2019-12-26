/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           gpio.c
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

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "gpio.h" /* include peripheral declarations */
#include "global_parameter.h"

/*******************************************************
 * FUNCTION NAME : GPIO_Init()
 *   DESCRIPTION : init gpio reg
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
 
void GPIO_Init(void)
{
    PT0AD_PT0AD1 = 1;
    DDR0AD_DDR0AD1 = 1;//WT OUTPUT  WT-PAD1(output)
    PER0AD_PER0AD1 = 1;

    DDR0AD_DDR0AD0 = 0;//MR INPUT   MR-PAD0(input)
    PER0AD_PER0AD0 = 1;

    PTT_PTT2 = 1;
    DDRT_DDRT2 = 1; //WAKE_UP output WAKE_UP-PT2(output)
    PERT_PERT2 = 1; //PULL UP

    CS = 1;         
    DDRS_DDRS7 = 1; //CS OUTPUT  CS-PP0
    PERS_PERS7 = 1; //PULL UP

    MOSI = 1;
    DDRS_DDRS5 = 1; //MOSI OUTPUT   MOSI-PT1
    PERS_PERS5 = 1; //PULL UP

    SCLK = 1;
    DDRS_DDRS6 = 1; //SCLK OUTPUT   SCLK-PT0
    PERS_PERS6 = 1; //PULL UP

    DDRS_DDRS4 = 0; //MISO INPUT    MISO-PAD2
    PERS_PERS4 = 1; //PULL UP

    DDRT_DDRT3 = 0; //DR INPUT  DR-PT3
    PERT_PERT3 = 1; //PULL UP

    
    #ifdef FOUR_TO_ONE
        DDRP_DDRP0 = 1; //LIN_EN OUTPUT 
        PERP_PERP0 = 1; //PULL UP
    #else

        DDRT_DDRT1 = 1; //LIN_EN OUTPUT 
        PERT_PERT1 = 1; //PULL UP
    #endif 
       
    LIN_EN = 1;

    DDRM_DDRM0 = 0;
    DDRM_DDRM1 = 0;
}