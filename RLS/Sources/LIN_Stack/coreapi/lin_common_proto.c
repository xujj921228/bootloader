/**************************************************************************//**
*
* @file      lin_common_proto.c
*
* @author    FPT Software
*
* @brief     Common LIN protocol functions
*
******************************************************************************/

#include "lin.h"
#include "lin_common_proto.h"
#include "lin_lin21_proto.h"
#include "lin_common_api.h"

#include "lin_commontl_proto.h"
#include "lin_lin21tl_api.h"

/**
 * @var l_u8 frame_signal_error
 * frame or signal error
 */
l_u8 frame_signal_error;

/* ---------------------------- For 1 interface ----------------------------------- */
/* Global variables */
/**
 * @var l_u8 frame_index
 * index of frame in frames table
 */
l_u8 frame_index;




void lin_process_pid
(
    /* [IN] PID to process */
    l_u8 pid
)
{
    l_u8 action;
    const lin_frame_struct *lin_frame_ptr;

    /* Clear goto sleep flag */
    lin_goto_sleep_flg = 0;

    /* get frame index */
    frame_index = lin_get_frame_index(pid);
    if (0xFF == frame_index)
    {
        action = 0;
    }
    else
    {
        action = 1;
        lin_frame_ptr = &(lin_frame_tbl[frame_index]);
        /* PID belongs to this node, then check type of frame */
        if (LIN_FRM_EVNT == lin_frame_ptr->frm_type)
        {
            if (0 != lin_frame_flag_tbl[*(lin_frame_ptr->frame_data)])
            {
                /* Frame is updated */
                /* Get the PID of the associated unconditional frame */
                pid = lin_configuration_RAM[1 + *(lin_frame_ptr->frame_data)];
                /* Get the frame index in lin_frame_tbl[] */
                frame_index = lin_get_frame_index(pid);
                /* Create frame response */
                lin_make_res_evnt_frame(pid);
                /* Set response */
                action = 2;
            }
            else
            {
                action = 0;
            }
        }
        else
        {
            if (LIN_RES_PUB == lin_frame_ptr->frm_response)
            {
                if (LIN_FRM_UNCD == lin_frame_ptr->frm_type)
                {
                    lin_process_uncd_frame(pid, MAKE_UNCONDITIONAL_FRAME);
                    action = 2;
                }
                else
                {
                    if (0 == tl_slaveresp_cnt)
                    {
                        action = 0;
                    }
                    else
                    {
                        /* Check error in multi frames */
                        if (tl_service_status != LD_SERVICE_ERROR)
                        {
                            lin_make_res_diag_frame();
                            tl_slaveresp_cnt--;
                            action = 2;
                        }
                        else
                        {
                            /* Check is CF */
                            /* ignore response when error */
                            action = 0;
                        }
                    }
                }
            }
        }
    }
    /* Ignore diagnostic frame when interface is GPIO */
    switch (action)
    {
        case 1:
            /* Receive response */
            lin_lld_rx_response(lin_frame_ptr->frm_len);
            break;
        case 2:
            /* Set response */
            lin_lld_set_response(lin_frame_ptr->frm_len);
            break;
        default:
            /* ignore response */
            lin_lld_ignore_response();
            break;
    }
}

void lin_update_rx
(
    /* [IN] PID to process */
    l_u8 pid
)
{
    l_u8  flag_offset, flag_size, i;
    flag_offset = lin_frame_tbl[frame_index].flag_offset;
    flag_size = lin_frame_tbl[frame_index].flag_size;

    /* Set successful transfer */
    lin_successful_transfer = 1;
    /* PID belongs to this node, then check type of frame */
    if (LIN_FRM_UNCD == lin_frame_tbl[frame_index].frm_type)
    {
        lin_process_uncd_frame(pid, UPDATE_UNCONDITIONAL_FRAME);
    }
    /* Unuse for GPIO */
    else if (LIN_FRM_DIAG == lin_frame_tbl[frame_index].frm_type)
    {
        lin_update_rx_diag_frame();
    }
    /* Update rx frame flags */
    for (i = 0; i < flag_size; i++)
    {
        lin_flag_handle_tbl[flag_offset++] = 0xFF;
    }

    /* update word status */
    lin_update_word_status_lin21 (pid);
    Strart_next_rx();
}

void lin_update_tx
(
    /* [IN] PID to process */
    l_u8 pid
)
{
    /* Set successful transfer */
    lin_successful_transfer = 1;
    /* Clear frame flag */
    if (1 == frame_signal_error)
    {
        /* Set no error in response */
        lin_error_in_response = 0;
        frame_signal_error = 0;
    }
    /* Update again in case event triggered frame. The frame index has been modified */
    frame_index = lin_get_frame_index(pid);
    /* Update transmit flags */

    lin_update_tx_flags(frame_index);

    /* Update word status */

    lin_update_err_signal(frame_index);
    lin_update_word_status_lin21 (pid);

    /* Multi frame support */
    if (0x3D == pid)
    {
        /* process message */
        tl_tx_msg_size--;
        if (0 == tl_tx_msg_size)
        {
            tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
            tl_tx_msg_status = LD_COMPLETED;
            tl_service_status = LD_SERVICE_IDLE;
            tl_diag_state = LD_DIAG_IDLE;
        }
        else
        {
            tl_check_timeout = N_MAX_TIMEOUT_CNT;
            tl_check_timeout_type = LD_CHECK_N_AS_TIMEOUT;
            tl_diag_state = LD_DIAG_TX_PHY;
        }
    }
}

void lin_handle_error
(
    /* [IN] event id */
    lin_lld_event_id event_id,
    /* [IN] PID to process */
    l_u8 pid
)
{
    frame_index = lin_get_frame_index(pid);
    switch (event_id)
    {
        /* PID error */
        case LIN_LLD_PID_ERR:
            /* do nothing here */
            //break;  //xujun 20180531
        /* Frame error */
        case LIN_LLD_FRAME_ERR:
        case LIN_LLD_CHECKSUM_ERR:
        case LIN_LLD_READBACK_ERR:
        case LIN_LLD_NODATA_TIMEOUT:
            /* Set response error */
            lin_error_in_response = 1;
            /* Multi frame support */
            if (0x3C == pid)
            {
                tl_receive_msg_status = LD_FAILED;
                tl_rx_msg_status = LD_FAILED;
                lin_tl_rx_queue.queue_status = LD_RECEIVE_ERROR;
                tl_slaveresp_cnt = 0;
                tl_diag_state = LD_DIAG_IDLE;
            }
            else if (0x3D == pid)
            {
                tl_tx_msg_status = LD_FAILED;
                lin_tl_tx_queue.queue_status = LD_TRANSMIT_ERROR;
                tl_diag_state = LD_DIAG_IDLE;
            }
            tl_service_status = LD_SERVICE_ERROR;
            break;
        default:
            break;
    }
    /* Update word status */
    lin_update_err_signal(frame_index);
    lin_update_word_status_lin21 (pid);

}

void lin_bus_activity_timeout
(
    /* [IN] PID to process */
    l_u8 pid
)
{
    lin_update_word_status_lin21 (pid);
    /* Change to low power mode */
    lin_lld_set_low_power_mode();
}
void lin_update_tx_flags
(
    /* [IN] index of frame */
    l_u8 frm_id
)
{
    l_u8  flag_offset, flag_size, i;

    flag_offset = lin_frame_tbl[frm_id].flag_offset;
    flag_size = lin_frame_tbl[frm_id].flag_size;
    /* Update event triggered flags */
    if (LIN_FRM_EVNT == lin_frame_tbl[frm_id].frm_type)
    {
        /* Clear update flag for event trigger frame */
        lin_frame_flag_tbl[*(lin_frame_tbl[frm_id].frame_data)] = 0;
    }

    /* Find the signal id associated with frame */
    if (LIN_FRM_DIAG != lin_frame_tbl[frm_id].frm_type)
    {
        for (i = 0; i < flag_size; i++)
        {
            lin_flag_handle_tbl[flag_offset++] = 0xFF;
        }
        lin_frame_flag_tbl[frm_id] = 0;
    }


}

void lin_update_rx_diag_frame
(
)
{
    /* Check goto sleep */
    if (0x00 == lin_lld_response_buffer[1])
    {
        lin_goto_sleep_flg = 1;
        lin_lld_set_low_power_mode();
        return;
    }
    /* TL support */
    /* Single frame support */
    /* Process PDU income */
    lin_tl_handler();
}

void lin_make_res_diag_frame
(

)
{
    /* get data from tx queue to response buffer */
    lin_tl_get_pdu();
}
l_u8 lin_get_frame_index
(
    /* [IN] PID of frame */
    l_u8 pid
)
{
    l_u8 i;
    for (i = LIN_NUM_OF_FRMS; 0 < i; i--)
    {
        if (lin_configuration_RAM[i] == pid)
        {
            return (i - 1);
        }
    }
    return 0xFF;
}

void lin_process_uncd_frame
(
    /* [IN] PID to process */
    l_u8 pid,
    /* [IN] make or update */
    l_u8 type
)
{
    l_u8 frame_byte_offset, i;

    /* TODO: check signal error */
    l_signal_handle *ptr;
    /* Set frame length */
    lin_lld_response_buffer[0] = lin_frame_tbl[frame_index].frm_len;
    frame_byte_offset = lin_frame_tbl[frame_index].frm_offset;

    if (MAKE_UNCONDITIONAL_FRAME == type)
    {
        /* Check frame contain the response_error signal or not */
        ptr = (l_signal_handle *)lin_frame_tbl[frame_index].frame_data;
        /* the frame contains response_error signal */
        if (ptr != 0)
        {
            if (*ptr == response_error)
            {
                frame_signal_error = 1;
            }
        }
        /* get data from lin frame buffer */
        for (i = 1; i < lin_lld_response_buffer[0]+1; i++, frame_byte_offset++)
        {
            lin_lld_response_buffer[i] = lin_pFrameBuf[frame_byte_offset];
        }
    }
    else
    {
        for (i = 1; i < lin_lld_response_buffer[0]+1; i++, frame_byte_offset++)
        {
            lin_pFrameBuf[frame_byte_offset] = lin_lld_response_buffer[i];
        }
    }
}


