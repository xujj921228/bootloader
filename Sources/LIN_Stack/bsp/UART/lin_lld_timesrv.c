/**************************************************************************//**
*
* @file      bsp/UART/lin_lld_timesrv.c
*
* @author    FPT Software
*
* @brief     Timer for KEA
*
******************************************************************************/

#include "lin_lld_timesrv.h"
#include "lin_lld_uart.h"
#include "lin_common_proto.h"
#include "lin_hw_cfg.h"


void lin_lld_timer_K_init
(
    void
)
{
    /* Enable Clock for FTM1 */
    SIM_SCGC |= SIM_SCGC_FTM1_MASK;
    /* Select Timer Prescale equal to 128 */
    FTM1_SC |= FTM_SC_PS(7);
    /* Enable Channle 0 */
    /* Enable channel 0 interrupt */
    FTM1_C0SC |= FTM_CnSC_CHIE_MASK;
    /* Channel as Output compare mode */
    FTM1_C0SC |= FTM_CnSC_MSA_MASK;
    /* Interrupt every TIME_BASE_PERIOD (us) */
    FTM1_C0V = FTM_CnV_VAL((MCU_BUS_FREQ /1000000.0) * (TIME_BASE_PERIOD / 128.0));
    /* FTM1 use system clock */
    FTM1_SC |= FTM_SC_CLKS(1);

    /* Set the ICPR and ISER registers accordingly */
    NVIC_ICPR |= 1 << ((INT_FTM1-16)%32);
    NVIC_ISER |= 1 << ((INT_FTM1-16)%32);
}

void lin_lld_timer_isr(void)
{
   lin_lld_uart_timeout();
}
