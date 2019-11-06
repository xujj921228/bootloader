/**************************************************************************//**
 *
 * @file      lin_commontl_api.c
 *
 * @author    FPT Software
 *
 * @brief     Common LIN transport layer and configuration functions
 *
 ******************************************************************************/
#include "lin_commontl_api.h"
#include "lin_commontl_proto.h"

void ld_init(void)
{
    /* init transmit queue */
    lin_tl_tx_queue.queue_header = 0;
    lin_tl_tx_queue.queue_tail = 0;
    lin_tl_tx_queue.queue_status = LD_QUEUE_EMPTY;
    lin_tl_tx_queue.queue_current_size = 0;
    /* init receive queue */
    lin_tl_rx_queue.queue_header = 0;
    lin_tl_rx_queue.queue_tail = 0;
    lin_tl_rx_queue.queue_status = LD_NO_DATA;
    lin_tl_rx_queue.queue_current_size = 0;

    /* Init transmit message */
    tl_rx_msg_status = LD_COMPLETED;
    tl_rx_msg_index = 0;
    tl_rx_msg_size = 0;
    tl_receive_msg_status = LD_NO_MSG;

    /* Init receive message */
    tl_tx_msg_status = LD_COMPLETED;
    tl_tx_msg_index = 0;
    tl_tx_msg_size = 0;

    tl_last_cfg_result = LD_SUCCESS;
    tl_last_RSID = 0;
    tl_ld_error_code = 0;

    tl_frame_counter = 0;
    tl_no_of_pdu = 0;
    tl_slaveresp_cnt = 0;

    tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
    tl_check_timeout = N_MAX_TIMEOUT_CNT;

    tl_diag_state = LD_DIAG_IDLE;
    tl_service_status = LD_SERVICE_IDLE;
}

void ld_put_raw(const l_u8* const data)
{
    tl_put_raw(data, &lin_tl_tx_queue, TRANSMISSION);
}

void ld_get_raw(l_u8* const data)
{
    tl_get_raw(data, &lin_tl_rx_queue, RECEIVING);
}

l_u8 ld_raw_tx_status(void)
{
    return (l_u8)lin_tl_tx_queue.queue_status;
}

l_u8 ld_raw_rx_status(void)
{
    return (l_u8)lin_tl_rx_queue.queue_status;
}

void ld_send_message(l_u16 length, const l_u8* const data)
{
    lin_tl_pdu_data pdu;
    l_u8 i;
    l_u8 message_size;
    l_u16 data_index = 0;
    l_u16 tmp_length = length;
    l_u16 frame_counter = 1;

    /* check message status in queue */
    if (LD_COMPLETED == tl_tx_msg_status)
    {
        /* calculate number of PDU for this message */
        if (length <= 6)
        {
            message_size = 1;
        }
        else
        {
            if ((length-5)%6 == 0)
            {
                message_size = ((length - 5) / 6) + 1;
            }
            else
            {
                message_size = ((length - 5) / 6) + 2;
            }
        }
        tl_slaveresp_cnt = message_size;

        if (message_size <= (lin_tl_tx_queue.queue_max_size - lin_tl_tx_queue.queue_current_size))
        {
            /* update information of message in queue */
            tl_tx_msg_index = lin_tl_tx_queue.queue_tail;
            tl_tx_msg_size = message_size;
            tl_tx_msg_status = LD_IN_PROGRESS;
            tl_service_status = LD_SERVICE_BUSY;

            /* package data */
            if (length <= 6)
            {
                /* package single frame */
                /* ____________________________________________ */
                /* | NAD | PCI | SID | D1 | D2 | D3 | D4 | D5 | */
                /* |_____|_____|_____|____|____|____|____|____| */

                pdu[0] = lin_configured_NAD;

                pdu[1] = (l_u8) length;
                pdu[2] = data[0]; /* SID / RSID */
                for (i = 1; i < length; i++)
                {
                    pdu[i + 2] = data[i]; /* used data */
                }
                for (i = (l_u8) length; i < 6; i++)
                {
                    pdu[i + 2] = 0xFF; /* unused data */
                }
                ld_put_raw(pdu);
            }
            else
            {
                /* package first frame */
                /* ____________________________________________ */
                /* | NAD | PCI | LEN |SID | D2 | D3 | D4 | D5 | */
                /* |_____|_____|_____|____|____|____|____|____| */

                pdu[0] = lin_configured_NAD;
                pdu[1] = ((length / 256) & 0x0F) | 0x10; /* PCI */
                pdu[2] = length % 256; /* length */
                pdu[3] = data[0]; /* SID / RSID */
                for (i = 1; i < 5; i++)
                {
                    /* data */
                    pdu[i + 3] = data[i];
                }
                data_index += 5;
                tmp_length -= 5;
                ld_put_raw(pdu);

                /* package consecutive frame */
                /* ___________________________________________ */
                /* | NAD | PCI | D1 | D2 | D3 | D4 | D5 | D6 | */
                /* |_____|_____|____|____|____|____|____|____| */
                message_size--;

                pdu[0] = lin_configured_NAD;
                while (message_size > 0)
                {
                    pdu[1] = 0x20 | (frame_counter & 0x0F);
                    frame_counter++;
                    if (frame_counter > 15)
                    {
                        frame_counter = 0;
                    }
                    if (tmp_length < 6)
                    {
                        /* last PDU */
                        /* used data */
                        for (i = 0; i < tmp_length; i++)
                        {
                            pdu[i + 2] = data[data_index++];
                        }
                        /* unused data */
                        for (i = (l_u8) tmp_length; i < 6; i++)
                        {
                            pdu[i + 2] = 0xFF;
                        }
                    }
                    else
                    {
                        for (i = 2; i < 8; i++)
                        {
                            pdu[i] = data[data_index++];
                        }
                        tmp_length -= 6;
                    } /* end of (tmp < 6 ) */
                    message_size--;
                    ld_put_raw(pdu);
                } /* end of (message > 0) */
            } /* end of (length < 6) */

        } /* end of check message size */
    } /* end of (LD_COMPLETED == tl_conf->tl_message_status) */
}

void ld_receive_message(l_u16* const length, l_u8* const data)
{

    lin_tl_pdu_data pdu;
    l_u8 i;
    l_u16 data_index = 0;
    l_u16 tmp_length;
    l_u16 frame_counter;
    l_u8 PCI_type;

    /* set status of receive message */
    tl_rx_msg_status = LD_IN_PROGRESS;

    /* wait message is received completely */
    while (LD_COMPLETED != tl_receive_msg_status)
    {
        /* check message error */
        if ((LD_FAILED == tl_receive_msg_status) || (LD_WRONG_SN == tl_receive_msg_status) ||
            (LD_N_CR_TIMEOUT == tl_receive_msg_status))
        {
            tl_rx_msg_status = tl_receive_msg_status;
            return;
        }
    }
    /* Message is received completely */
    /* get data from receive queue */
    ld_get_raw(pdu);
    /* Check type of pdu */
    PCI_type = (pdu[1] & 0xF0) >> 4;
    switch (PCI_type)
    {
        /* Single frame */
        case SF:
            tmp_length = pdu[1] & 0x0f;
            *length = tmp_length;
            data[0] = pdu[2];
            for (i = 1; i < tmp_length; i++)
            {
                data[i] = pdu[i + 2];
            }
            break;
        /* First frame */
        case FF:
            tmp_length = (pdu[1] & 0x0F) * 256 + pdu[2];
            *length = tmp_length;
            data[0] = pdu[3];
            for (i = 1; i < 5; i++)
            {
                data[i] = pdu[i + 3];
            }
            tmp_length -= 5;
            data_index += 5;
        /* Consecutive frame */
        case CF:
            while (tmp_length > 6)
            {
                /* get PDU */
                ld_get_raw(pdu);
                frame_counter = pdu[1] & 0x0F;

                for (i = 2; i < 8; i++)
                {
                    data[data_index++] = pdu[i];
                }
                tmp_length -= 6;
            }

            /* Last frame */
            if (tmp_length > 0)
            {
                /* get PDU */
                ld_get_raw(pdu);
                frame_counter = pdu[1] & 0x0F;

                for (i = 0; i < tmp_length; i++)
                {
                    data[data_index++] = pdu[i + 2];
                }
            }

            break;
        default:
            break;
    } /* end of switch */
    tl_receive_msg_status = LD_NO_MSG;
    tl_rx_msg_status = LD_COMPLETED;
}

l_u8 ld_tx_status(void)
{
    return (l_u8)tl_tx_msg_status;
}

l_u8 ld_rx_status(void)
{
    return (l_u8)tl_rx_msg_status;
}
/** @} */


l_u8 ld_read_configuration
(
    /* [IN] data area to save configuration */
    l_u8* const data,
    /* [IN] length of data area */
    l_u8* const length
)
{
    l_u8 i, temp;
    /* Set the default returned value to LD_READ_OK */
    l_u8 retval = (l_u8)LD_READ_OK;
    /** Set the expected length value to
     * EXP = NN + NF, where :
     * NN = the number of NAD.
     * NF = the number of configurable frames;
     * Moreover:
     * Not taken PID's diagnostics frame: 3C, 3D
    */
    l_u8 expected_length = (l_u8)(LIN_NUM_OF_FRMS - 1U);
    temp = *length;
    if (temp < expected_length)
    {
        /* The 'data' size is not enough to store NAD+PIDs */
        retval = (l_u8)LD_LENGTH_TOO_SHORT;
    }
    else
    {
        /* The 'data' size is enough to store NAD+PIDs, so proceed to store them */
        /* Copy actual NAD to 'data' */
        data[0] = lin_configured_NAD;
        /* Copy protected IDs to 'data' */
        for (i = 1U; i < expected_length; ++i)
        {
            data[i] = lin_configuration_RAM[i];
        }
        /* Set the length parameter to the actual size of the configuration */
        *length = expected_length;
    }
    return retval;
} /* End ld_read_configuration() */


l_u8 ld_set_configuration
(
    /* [IN] data area to set configuration */
    const l_u8* const data,
    /* [IN] length of data area */
    l_u16 length
)
{
    l_u8 i;
    /* Set the default returned value to LD_DATA_ERROR */
    l_u8 retval = LD_DATA_ERROR;
    /** Set the expected length value to
     * EXP = NN + NF, where :
     * NN = the number of NAD.
     * NF = the number of configurable frames;
     * Moreover:
     * Not taken PID's diagnostics frame: 3C, 3D
     */
    l_u16 expected_length = (l_u8)(LIN_NUM_OF_FRMS - 1U);
    if (length < expected_length)
    {
        /* The 'data' size is not enough to contain NAD+PIDs */
        retval = LD_LENGTH_NOT_CORRECT;
    }
    else
    {
        /* The 'data' size is enough to contain NAD+PIDs, so proceed to read from 'data' */
        /* Read actual NAD from 'data' */
        lin_configured_NAD = data[0];
        /* Copy protected IDs in 'data' to RAM configuration */
        for (i = 1U; i < expected_length; ++i)
        {
            lin_configuration_RAM[i] = data[i];
        }
        /* No error, return OK */
        retval = LD_SET_OK;
    }
    return retval;
} /* End ld_set_configuration() */

