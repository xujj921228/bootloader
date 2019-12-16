/**************************************************************************//**
*
* @file      lin.c
*
* @author    FPT Software
*
* @brief     LIN low level functions
*
******************************************************************************/
#include "lin.h"
#include "lin_lld_uart.h"
#include "lin_lld_timesrv.h"

/* Globle variable */
l_u8        etf_collision_flag = 0;

/* Extern globle variable */

l_u8 lin_lld_init
(
)
{
   lin_lld_uart_init((l_ifc_handle)0);
    return LIN_LLD_OK;
}

l_u8 lin_lld_deinit
(
)
{
    /* Check for valid interface */
    lin_lld_uart_deinit();
    return LIN_LLD_OK;
}

l_u8 lin_lld_get_status
(
)
{
    l_u8 ret = 0;

    lin_lld_uart_get_status();
    return ret;
}

l_u8 lin_lld_get_state()
{
    l_u8 ret = 0;

    ret = lin_lld_uart_get_state();

    return ret;
}

void lin_lld_tx_wake_up ()
{
  
    lin_lld_uart_tx_wake_up();
    return;
}

void lin_lld_int_enable ()
{
   lin_lld_uart_int_enable();

    return;
}

l_u8 lin_lld_int_disable ()
{
   
    lin_lld_uart_int_disable();

    return LIN_LLD_OK;
}

void lin_lld_ignore_response
(
)
{
    lin_lld_uart_ignore_response();

    return;
}

void lin_lld_set_low_power_mode ()
{
    lin_lld_uart_set_low_power_mode();

    return;
}

l_u8 lin_lld_set_response
(
    /* [IN] response length */
    l_u8 response_length
)
{
    l_u8 ret = 0;

    /* Check for valid response length */
    if (response_length > 8)
    {
        ret = LIN_LLD_INVALID_PARA;
    }
    else
    {
        /* Put response length into buffer */
        lin_lld_response_buffer[0] = response_length;
        lin_lld_uart_tx_response();

        ret = LIN_LLD_OK;
    }

    return ret;
}

l_u8 lin_lld_rx_response
(
    /* [IN] response length */
    l_u8 response_length
)
{
    lin_lld_uart_rx_response(response_length);

    return LIN_LLD_OK;
}



/*** Common function used to all low-level driver ***/

l_u8 lin_process_parity
(
    /* [IN] PID need to be send */
    l_u8 pid,
    /* [IN] Check or Make parity */
    l_u8 type
)
{
    l_u8 parity;
    l_u8 ret;

    parity = (((BIT(pid, 0)^BIT(pid, 1)^BIT(pid, 2)^BIT(pid, 4)) << 6)|
              ((~(BIT(pid, 1)^BIT(pid, 3)^BIT(pid, 4)^BIT(pid, 5))) << 7));
    if (CHECK_PARITY == type)
    {
        if ((pid&0xC0) != parity)
        {
            ret = 0xFF;
        }
        else
        {
            ret = (l_u8)(pid&0x3F);
        }
    }
    else
    {
        ret = (l_u8)(pid|parity);
    }

    return (ret);
}

l_u8 lin_checksum
(
    /* [IN] pointer to buffer */
    l_u8 *buffer,
    /* [IN] pid */
    l_u8 raw_pid
)
{
    l_u8 length;
    l_u16 check_sum;

    /* 1. PID correspond to Master request and Slave response, their checksum cal is classic
    the non-diagnostic frame is calculated in Enhanced */
    if ((0x3C != raw_pid) && (0x7D != raw_pid))
    {
        check_sum = raw_pid;
    }
    else
    {
        check_sum = 0;
    }

    for (length = *buffer; 0 < length; length--)
    {
        buffer++;
        check_sum += *(buffer);
        /* 2. to deal with the carry */
        if (check_sum > 0xFF)
        {
            check_sum -= 0xFF;
        }
    }

    /* 3. to reverse */
    return (l_u8)(~check_sum);
}

void lin_lld_timer_init
(
    void
)
{
    lin_lld_timer_K_init();

}


void lin_lld_mcu_reset()
{
}

void lin_lld_set_etf_collision_flag()
{
    /* Set flag in case of occurring collision in event trigger frame */
    etf_collision_flag = 1;
}

void lin_lld_clear_etf_collision_flag()
{
    /* Clear flag in case of occurring collision in event trigger frame */
    etf_collision_flag = 0;
}

/**
 * @}
 */
