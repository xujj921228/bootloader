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
#include "ftm.h"
#include "lin_hw_cfg.h"
#include "config_parameter.h"


uint8  G_10ms_counter = FALSE;
uint8  G_20ms_counter = FALSE;
uint8  G_50ms_counter = FALSE;
uint8  G_100ms_counter = FALSE;
uint8  G_500ms_counter = FALSE;
uint16  G_4s_counter = FALSE;

uint8  G_10msFlag = FALSE;
uint8  G_20msFlag = FALSE;
uint8  G_50msFlag = FALSE;
uint8  G_100msFlag = FALSE;
uint8  G_500msFlag = FALSE;
uint8  G_4sFlag = FALSE;

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
    
		G_10ms_counter++;
		G_50ms_counter++;
		G_100ms_counter++;
		G_500ms_counter++;
		G_4s_counter++;
		
		if(G_4s_counter >= 400)
		{
			G_4s_counter = 400;
			G_4sFlag =  TRUE ;
		}
		else
		{
			G_4sFlag =  FALSE ;
		}
		
		if(G_10ms_counter >= 1)
		{
			G_10ms_counter = 0;
			G_10msFlag = 1;
		}

		if(G_50ms_counter >= 5)
		{
			G_50ms_counter = 0;
			G_50msFlag = 1;
		}
		 if(G_100ms_counter >= 10)
		{
			G_100ms_counter = 0;
			G_100msFlag = 1;     
		}
		if(G_500ms_counter>= 50)
		{
			G_500ms_counter=0;
			G_500msFlag=1;    
		}    
            
    }
}
