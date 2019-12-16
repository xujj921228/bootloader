/**************************************************************************//**
*
* @file      bsp/UART/lin_isr.c
*
* @author    FPT Software
*
* @brief     Interrupt service routine used in LIN driver
*
******************************************************************************/
#include "lin_hw_cfg.h"
#include "lin_lld_timesrv.h"
#include "lin_lld_uart.h"

void UART0_SCI0_IRQHandler ()
{
    lin_lld_uart_rx_isr();
}


void FTM1_IRQHandler()
{
    if (1 == ((FTM1_C0SC & FTM_CnSC_CHF_MASK) >> FTM_CnSC_CHF_SHIFT))  /* If the CHF of the channel is equal to 0 */
    {
        (void)FTM1_C0SC;                            /* Read to clear flag */
        /* Clear flag */
        FTM1_C0SC ^= FTM_CnSC_CHF_MASK;
        /* Update Value of Channel Value register to generate next interrupt after TIME_BASE_PERIOD (us) */
        FTM1_C0V += ((MCU_BUS_FREQ  / 1000000.0) * (TIME_BASE_PERIOD / 128.0));
        /* Call Timer interrupt handler function */
        lin_lld_timer_isr();
    }
}
