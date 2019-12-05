/**************************************************************************//**
*
* @file      bsp/UART/lin_lld_UART.c
*
* @author    FPT Software
*
* @brief     UART for LIN network
*
******************************************************************************/


#include "lin_lld_uart.h"
#include "lin_hw_cfg.h"
#include "lin_common_proto.h"
#include "lin_lld_timesrv.h"
#include "lin_diagnostic_service.h"
#include "lin_cfg.h"





/* pUART func ifc checksum_mode state  l_status cnt_byte  *ptr current_pid *response_buffer
  pid_out tbit frame_timeout_cnt res_frame_timeout_cnt idle_timeout_cnt */

static tUART          *pUART = (tUART*)UART_ADDR;

/**
* @var static l_u8          ifc
*/
static l_u8          ifc = 0xFF;

/**
* @var static l_u8          state
*/
static l_u8          state = UNINIT;

/**
* @var static lin_status    l_status
*/
static lin_status    l_status;

/**
* @var static l_u8          cnt_byte
*/
static l_u8          cnt_byte = 0;

/**
* @var static l_u8         *ptr
*/
static l_u8          *ptr = 0;

/**
* @var static l_u8          current_id
*/
static l_u8          current_id = 0x00;

/**
* @var static l_u8         *response_buffer
*/
static l_u8          *response_buffer = 0;

/**
* @var static l_u8          pid
*/
static l_u8          pid = 0x80;

/**
* @var static l_u16          tbit
*/
static l_u16         tbit = 0;

/**
* @var static l_u16          frame_timeout_cnt
*/
static l_u16         frame_timeout_cnt = 0;

/**
* @var static l_u16          res_frame_timeout_cnt
*/
static l_u16         res_frame_timeout_cnt = 0;

/**
* @var static l_u16          idle_timeout_cnt
*/
static l_u16         idle_timeout_cnt = 0;


extern const l_u16 lin_max_frame_res_timeout_val[8];

extern l_u8 lin_lld_response_buffer[10];

extern l_u8 boot_rx_ok_id;

/***** LOW-LEVEL API *****/

void lin_lld_uart_init
(
    /* [IN] LIN interface name */
    l_ifc_handle iii
)
{

/*--------------------------------------------------------------------*/

    l_u16 tmp;
    /* Resyn initialization */
    /* Config */
    ifc = (l_u8)iii;
    response_buffer = lin_lld_response_buffer;
    /* Set UART is Master or Slave */
    tbit = (1000000/LIN_BAUD_RATE);
    /* Initialize UART */
    /* Set baud rate */
    tmp = MCU_BUS_FREQ/LIN_BAUD_RATE/16;
    //tmp = (MCU_BUS_FREQ/LIN_BAUD_RATE) >> 4;
    /* Select clock source for UART */
    SIM_SCGC |= SIM_SCGC_UART0_MASK;  //uart0 timer enable


    pUART->uartbdh.byte = (tmp >> 8)&0x1F;
    pUART->uartbdl.byte = tmp&0xFF;

    /* Enable use of 13bit breaks and UART frame for LIN */
    pUART->uartcr1.byte = 0x00;    /* one start bit, eight data bits, one stop bit */
    pUART->uartcr2.byte = (UARTCR2_TE_MASK | UARTCR2_RE_MASK | UARTCR2_RIE_MASK);
    pUART->uartsr2.byte |= (UARTSR2_LBKDIF_MASK | UARTSR2_BRK13_MASK | UARTSR2_LBKDE_MASK);   /* clear LIN Break Detection flag */
    pUART->uartcr3.byte |= UARTCR3_FEIE_MASK;     /* Enable Frame Error interrupt */
    pUART->uartbdh.byte |= UARTBDH_LBKDIE_MASK;        /* enable LIN Break Detection interrupt */
    /* Receive data not inverted */
    pUART->uartsr2.bit.rxinv = 0;
    /* Enter IDLE state */
    lin_goto_idle_state();
} /* End of function lin_lld_uart_init( l_ifc_handle iii ) */
/*--------------------------------------------------------------------*/

void lin_lld_uart_deinit
(
)
{
    state = UNINIT;
    lin_lld_uart_int_disable();
}


void lin_lld_uart_tx_wake_up
(
)
{
    l_u8 uart_flag_sr1;
    if ((state == IDLE) || (state == SLEEP_MODE))
    {
        uart_flag_sr1 = pUART->uartsr1.byte;
        /* Send wake signal byte = 0x80 */
        pUART->uartd.byte = UARTD_R7_T7_MASK;
        /* Set Lin state to idle */
        lin_goto_idle_state();
    }
} /* End function lin_lld_UART_tx_wake_up() */
/*--------------------------------------------------------------------*/

void lin_lld_uart_int_enable
(
)
{
    /* Can't enable in interrupt context */
    if ((state == PROC_CALLBACK) || (state == UNINIT) || (state == SLEEP_MODE))
    {
        return;
    }

    /* Enable UART Channel */
    pUART->uartcr2.byte |= (UARTCR2_RE_MASK | UARTCR2_RIE_MASK);
    /* Enable timeout interrupt 0 channel */


} /* End function lin_lld_UART_int_enable() */
/*--------------------------------------------------------------------*/

void lin_lld_uart_int_disable
(
)
{
    /*--------------------------------------------------------------------*/
    /* Can't disable in interrupt context */
    if ((state == PROC_CALLBACK) || (state == UNINIT) || (state == SLEEP_MODE))
    {
        return;
    }

    while(state != IDLE)
    {}
    /* Disable UART Channel */
    pUART->uartcr2.byte &= ~(UARTCR2_RE_MASK | UARTCR2_RIE_MASK);
    /* Disable timeout interrupt 0 channel */
} /* End function lin_lld_UART_int_disable() */


void lin_lld_uart_ignore_response
(
)
{
    lin_goto_idle_state();
}


void lin_lld_uart_set_low_power_mode
(
)
{
    /* Configure Hw code */

    /* Set Lin status = sleep mode */
    state = SLEEP_MODE;
}
void lin_lld_uart_rx_response
(
    /* [IN] Length of response data expect to wait */
    l_u8  msg_length
)
{
    /* Put response length and pointer of response buffer into descriptor */
    *(response_buffer) = msg_length;
    cnt_byte = 0;
    ptr = response_buffer;
    /* Set Lin status = receiving data */
    state = RECV_DATA;
}

void lin_lld_uart_tx_response
(
)
{
    /* calculate checksum */
    response_buffer[*(response_buffer)+1] = lin_checksum(response_buffer, pid);
    cnt_byte = 1;
    /* Send First byte */
    pUART->uartd.byte = response_buffer[1];
    /* Set LIN Status */
    state = SEND_DATA;
} /* End function lin_lld_UART_tx_response() */
/*--------------------------------------------------------------------*/

l_u8 lin_lld_uart_get_status
(
)
{
    return l_status.byte;
}


l_u8 lin_lld_uart_get_state()
{
    return state;
}


void lin_lld_uart_timeout
(
)
{
    if (LD_CHECK_N_CR_TIMEOUT == tl_check_timeout_type)
    {
        if (0 == --tl_check_timeout)
        {
            /* update status of transport layer */
            tl_service_status = LD_SERVICE_ERROR;
            tl_receive_msg_status = LD_N_CR_TIMEOUT;
            tl_rx_msg_status = LD_N_CR_TIMEOUT;
            tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
            tl_diag_state = LD_DIAG_IDLE;
        }
    }

    if (LD_CHECK_N_AS_TIMEOUT == tl_check_timeout_type)
    {
        if (0 == --tl_check_timeout)
        {
            /* update status of transport layer */
            tl_service_status = LD_SERVICE_ERROR;
            tl_tx_msg_status = LD_N_AS_TIMEOUT;
            tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
            tl_diag_state = LD_DIAG_IDLE;
        }
    }
    switch(state)
    {
        case IDLE:
            if (idle_timeout_cnt == 0)
            {
                /* Set LIN mode to sleep mode */
                lin_goto_sleep_flg = 1;
                /* trigger callback */
                lin_bus_activity_timeout(0xFF);
                /* goback to IDLE, reset max idle timeout */
                idle_timeout_cnt = _MAX_IDLE_TIMEOUT_;
                /* disable LIN break detect interrupt */
                pUART->uartsr2.bit.lbkde = 0;
                /* Set state to sleep mode */
                state = SLEEP_MODE;
            }
            else
            {
                idle_timeout_cnt--;
            }
            break;
        case SEND_PID:    /* Master */
        case RECV_SYN:
        case RECV_PID:
        case SEND_DATA:
        case SEND_DATA_COMPLETED:
            /* timeout send has occurred - change state of the node and inform core */
            if (0 == frame_timeout_cnt)
            {
                lin_goto_idle_state();
            }
            else
            {
                frame_timeout_cnt--;
            }
            break;
        case RECV_DATA:
            /* timeout receive has occurred - change state of the node and inform core */
            if (0 == res_frame_timeout_cnt)
            {
                if (cnt_byte)
                {
                    /* set lin status: error_in_response */
                    l_status.byte |= LIN_STA_ERROR_RESP;
                    /* trigger callback */
                    lin_handle_error(LIN_LLD_NODATA_TIMEOUT, current_id);
                }
                lin_goto_idle_state();
            }
            else
            {
                res_frame_timeout_cnt--;
            }
            break;
        case PROC_CALLBACK:
            break;
        default:
            ;
    }
} /* End function lin_lld_UART_timeout() */


/*** INTERNAL FUNTIONS ***/


void lin_goto_idle_state
(
)
{
    /* set lin status: ~bus_activity */
    l_status.byte &= ~LIN_STA_BUS_ACTIVITY;
    /* Set max idle timeout */
    idle_timeout_cnt = _MAX_IDLE_TIMEOUT_;
    state = IDLE;
    /* Enable LBK detect */
    pUART->uartsr2.bit.lbkde = 1;
} /* End function lin_goto_idle_state() */

extern l_u8 boot_status_flag;
void lin_lld_uart_rx_isr
(
)
{
    /*--------------------------------------------------------------------*/
    l_u8 uart_flag_sr1;
    l_u8 uart_flag_sr2;
    l_u8 tmp_byte;

    /******************************
    *** 1. BREAK DETECTED
    *******************************/
    /* if the lbkdif is set */
    uart_flag_sr1 = pUART->uartsr1.byte ;
    uart_flag_sr2 = pUART->uartsr2.byte ;
    if ((uart_flag_sr2 & UARTSR2_RXEDGIF_MASK) && (!(uart_flag_sr2 & UARTSR2_LBKDIF_MASK)))
    {
        /* Clear flag */
        pUART->uartsr2.bit.rxedgif = 1;

        pUART->uartbdh.byte &= ~UARTBDH_RXEDGIE_MASK; /* Disable rx edged detection */
        /* End Resynchronization */

        if (SLEEP_MODE == state)
        {
            lin_goto_idle_state();
            lin_goto_sleep_flg = 0;
        }

        /* Enable Break interrupt */
        pUART->uartbdh.byte |= UARTBDH_LBKDIE_MASK ;

        /* Receive data not inverted */
        pUART->uartsr2.bit.rxinv = 0;
        /* check state of node is SLEEP_MODE */
        //return;
    }
    /******************************
    *** 3. FRAME ERROR DETECTED
    *******************************/
    if (0 != (uart_flag_sr1&UARTSR1_FE_MASK))
    {
        /* Clear FE flags */
        pUART->uartsr1.byte |= UARTSR1_FE_MASK;
        tmp_byte = pUART->uartd.byte;
        /* set lin status: error_in_response, framing_error */
        l_status.byte |= (LIN_STA_ERROR_RESP|LIN_STA_FRAME_ERR);
        /* trigger callback */
        if ((state == RECV_DATA) || (state == SEND_DATA) || (state == SEND_DATA_COMPLETED))
        {
            lin_handle_error(LIN_LLD_FRAME_ERR, current_id);
        }
        lin_goto_idle_state();

    }

    if (uart_flag_sr2 & UARTSR2_LBKDIF_MASK)
    {
        /* Clear flag */
        pUART->uartsr2.bit.lbkdif = 1;
        /* Enable Active Edge interrupt */
        pUART->uartbdh.byte |= UARTBDH_RXEDGIE_MASK;
        /* Disable Break interrupt */
        pUART->uartbdh.byte &= ~UARTBDH_LBKDIE_MASK ;
        /* check state of node is SLEEP_MODE */
        if (SLEEP_MODE == state)
        {
            lin_goto_idle_state();
            return;
        }
        /* reset lin status */
        l_status.byte = LIN_STA_BUS_ACTIVITY;
        /* Set max frame timeout */
        frame_timeout_cnt = lin_max_frame_res_timeout_val[7];
        /******************************
        *** 1.2 SLAVE NODE: Wait for SYN
        *******************************/
        /* Start resyn */
        /* Enable Active Edge interrupt */
        pUART->uartbdh.byte |= 0x40 ; /* UARTBDH_RXEDGIE_MASK; */

        state = RECV_SYN;              
        
        /* Disable LBK detect */
        pUART->uartsr2.bit.lbkde = 0;
        return;
    }
    else
    {    	
        uart_flag_sr1 = pUART->uartsr1.byte;
        tmp_byte = pUART->uartd.byte;
        /******************************
        *** 4. BYTE RECIEVED
        *******************************/
        if (0 != (uart_flag_sr1&UARTSR1_RDRF_MASK))
        {
            switch(state)
            {
                /******************************
                *** 4.2 SLAVE: Receiving SYN byte
                *******************************/
                case RECV_SYN:
                    if (0x55 == tmp_byte)
                    {
                        state = RECV_PID;
                    }
                    else
                    {
                        lin_handle_error(LIN_LLD_READBACK_ERR, current_id);
                        lin_goto_idle_state();
                    }
                    break;
                /******************************
                *** 4.3 SLAVE: Receiving PID
                *******************************/
                case RECV_PID:
                    /* checkparity and extrait PID */
                    current_id = lin_process_parity(tmp_byte, CHECK_PARITY);
                    /* Keep the PID */
                    pid = tmp_byte;
                    
                    if((current_id == 0x3C)||(current_id == 0x3D))
                    {
                    	diagnostic_Session_timer = 0;
                    	diagnostic_Session_flg = 1;
                    }
                    
                    if (current_id != 0xFF)
                    {
                        /*****************************************/
                        /*** ID received correctly - parity OK ***/
                        /*****************************************/
                        /* trigger callback */
                        lin_process_pid(current_id);
                        /* Set Maximum response frame timeout */
                        res_frame_timeout_cnt = lin_max_frame_res_timeout_val[*(response_buffer) - 1];
                    }
                    else
                    {
                        /*****************************************/
                        /*** ID Parity Error                   ***/
                        /*****************************************/
                        /* set lin status: parity_error */
                        l_status.byte |= LIN_STA_PARITY_ERR;
                        /* trigger callback */
                        lin_handle_error(LIN_LLD_PID_ERR, 0xFF);
                        lin_goto_idle_state();
                    }
                    break;
                /******************************
                *** 4.4 SLAVE: Receiving data
                *******************************/
                case RECV_DATA:
                    ptr++;
                    *(ptr) = tmp_byte;
                    /* Check bytes received fully */
                    if (cnt_byte == (response_buffer[0]))
                    {
                        /* checksum checking */
                        if (lin_checksum(response_buffer, pid) == tmp_byte)
                        {                       	
                            /*******************************************/
                            /***  RX Buffer Full - Checksum OK       ***/
                            /*******************************************/
                            /* set lin status: successful_transfer */
                            l_status.byte |= LIN_STA_SUCC_TRANSFER;
                            /* disable RX interrupt */
                            pUART->uartcr2.byte &= ~(UARTCR2_RE_MASK | UARTCR2_RIE_MASK);
                            state = PROC_CALLBACK;
                            boot_rx_ok_id = current_id;
                        }
                        else
                        {
                            /*******************************************/
                            /***  RX Buffer Full - Checksum ERROR    ***/
                            /*******************************************/
                            /* set lin status: error_in_response, checksum_error */
                            l_status.byte |= (LIN_STA_ERROR_RESP|LIN_STA_CHECKSUM_ERR);
                            /* trigger callback */
                            lin_handle_error(LIN_LLD_CHECKSUM_ERR, current_id);
                            lin_goto_idle_state();
                        }
                    }
                    cnt_byte++;
                    break;

                /******************************
                *** 4.5 SLAVE: Sending data
                *******************************/
                case SEND_DATA:
                    /* Check for READBACK error */
                    if (0 == (uart_flag_sr1&UARTSR1_TC_MASK))
                    {
                        lin_handle_error(LIN_LLD_READBACK_ERR, current_id);
                        lin_goto_idle_state();
                        break;
                    }
                    else
                    {
                        if (tmp_byte != response_buffer[cnt_byte])
                        {
                            /* Check if event trigger frame then allow to continue sending data */
                        	lin_handle_error(LIN_LLD_READBACK_ERR, current_id);
                            lin_goto_idle_state();
                            break;
                        }//End if (tmp_byte != response_buffer[cnt_byte])
                    }
                    if (cnt_byte <= (response_buffer[0]))
                    {
                        /* Send data bytes and checksum */
                        cnt_byte++;
                        pUART->uartd.byte = response_buffer[cnt_byte];
                    }
                    else
                    {
                    	if(boot_status_flag == 2 )
                    	{
                    		boot_status_flag = 3;
                    	}
                        /* TX transfer complete */
                        l_status.byte |= LIN_STA_SUCC_TRANSFER;
                        /* Disable RX interrupt */
                        pUART->uartcr2.byte &= ~(UARTCR2_RE_MASK|UARTCR2_RIE_MASK);
                        state = PROC_CALLBACK;
                        /* trigger CALLBACK */
                        lin_update_tx(current_id);
                        /* Enable RX interrupt */
                        pUART->uartcr2.byte |= (UARTCR2_RE_MASK|UARTCR2_RIE_MASK);
                        lin_goto_idle_state();
                    }
                    break;
                /******************************
                *** 4.8 SLAVE: Low power mode
                *******************************/
                case SLEEP_MODE:
                    if ((tmp_byte == 0xF0) || (tmp_byte == 0xE0) || (tmp_byte == 0xC0) || (tmp_byte == 0x80) || (tmp_byte == 0x00))
                    {
                        /* Set idle timeout again */
                        lin_goto_idle_state();
                        /* Enable LIN break detect interrupt */
                        pUART->uartsr2.bit.lbkde = 1;
                    }
                    break;
                default:
                    break;
            }
        }
    }
} /* End function lin_lld_UART_rx_isr() */

void Strart_next_rx(void)
{
	 /* enable RX interrupt */
	pUART->uartcr2.byte |= (UARTCR2_RE_MASK | UARTCR2_RIE_MASK);
	if (SLEEP_MODE != state)
	{
		lin_goto_idle_state();
	}      
}

