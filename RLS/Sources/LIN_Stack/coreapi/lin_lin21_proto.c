/**************************************************************************//**
*
* @file      lin_lin21_proto.c
*
* @author    FPT Software
*
* @brief     Common LIN 2.1 protocol functions
*
******************************************************************************/


#include "lin_lin21_proto.h"
#include "lin_common_proto.h"
#include "lin.h"

/* Extern globle variable */
extern l_u8         etf_collision_flag;

/* ---------------------------- For 1 interface ----------------------------------- */
extern l_u8 frame_index;


void lin_update_word_status_lin21
(
    /* [IN] PID of frame */
    l_u8 pid
)
{
    lin_word_status.word = ((lin_error_in_response) | (lin_successful_transfer << 1) |
                            ((lin_error_in_response | lin_successful_transfer) << 2)|
                            (lin_goto_sleep_flg << 3) |
                            (lin_save_configuration_flg << 6) |
                            (pid << 8)) & 0xFF4F;
}



void lin_update_err_signal
(
    /* [IN] index of frame */
    l_u8 frm_id
)
{

    /* Set error signal equal to error in response */
    if (LIN_FRM_EVNT != lin_frame_tbl[frm_id].frm_type)
    {
        lin_pFrameBuf[response_error_byte_offset] = (lin_pFrameBuf[response_error_byte_offset] &
                                                    (~(1 << response_error_bit_offset))) |
                                                    (lin_error_in_response << response_error_bit_offset);

    }
}
void lin_make_res_evnt_frame
(
    /* [IN] PID of frame */
    l_u8 pid
)
{
    /* Create response */
    lin_process_uncd_frame(pid, MAKE_UNCONDITIONAL_FRAME);
    lin_lld_response_buffer[1] = lin_process_parity(pid, MAKE_PARITY);
}


