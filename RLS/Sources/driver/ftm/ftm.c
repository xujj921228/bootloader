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
* @author    xujun
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "ftm.h"
#include "lin_hw_cfg.h"
#include "config_parameter.h"


extern uint8  Timer_50ms;
extern uint8  Timer_100ms;
extern uint8  Timer_500ms;

extern uint8  Timer_10ms_flag;
extern uint8  Timer_50ms_flag;
extern uint8  Timer_100ms_flag;
extern uint8  Timer_500ms_flag;
extern uint8  Timer_4s;
extern uint8  Timer_600ms;

void FTM0_Init(void)
{
    /* Enable Clock for FTM0 */
    SIM_SCGC |= SIM_SCGC_FTM0_MASK;
    /* Select Timer Prescale equal to 128 */
    FTM0_SC |= FTM_SC_PS(7);
    /* Enable Channle 0 */
    /* Enable channel 0 interrupt */
    FTM0_C0SC |= FTM_CnSC_CHIE_MASK;
    /* Channel as Output compare mode */
    FTM0_C0SC |= FTM_CnSC_MSA_MASK;
    /* Interrupt every TIME_BASE_PERIOD (us) */
    FTM0_C0V = FTM_CnV_VAL((MCU_BUS_FREQ /1000000.0) * (TIME_BASE_PERIOD_10ms / 128.0));
    /* FTM1 use system clock */
    FTM0_SC |= FTM_SC_CLKS(1);

    /* Set the ICPR and ISER registers accordingly */
    NVIC_ICPR |= 1 << ((INT_FTM0-16)%32);
    NVIC_ISER |= 1 << ((INT_FTM0-16)%32);
}



void FTM0_IRQHandler()   //10ms
{
    if (1 == ((FTM0_C0SC & FTM_CnSC_CHF_MASK) >> FTM_CnSC_CHF_SHIFT))  /* If the CHF of the channel is equal to 0 */
    {
        (void)FTM0_C0SC;                            /* Read to clear flag */
        /* Clear flag */
        FTM0_C0SC ^= FTM_CnSC_CHF_MASK;
        /* Update Value of Channel Value register to generate next interrupt after TIME_BASE_PERIOD (us) */
        FTM0_C0V += ((MCU_BUS_FREQ  / 1000000.0) * (TIME_BASE_PERIOD_10ms / 128.0));
        /* Call Timer interrupt handler function */
    

        Timer_10ms_flag = 1;
        Timer_50ms++;
        Timer_100ms++;
        Timer_500ms++;

        if(Timer_50ms >= 5) //   50ms Task
        {
              Timer_50ms = 0;
              Timer_50ms_flag = 1;
        } 
        if(Timer_100ms >= 10)  //   100ms Task
        {
                Timer_100ms = 0;  
                Timer_100ms_flag = 1;
        }
        if(Timer_500ms >= 50) //   500ms  Task
        {
               Timer_500ms = 0;
               Timer_500ms_flag = 1;
        }

    }
}
