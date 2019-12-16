/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2015 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup common_core_api_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      lin_common_proto.h
*
* @author    FPT Software
*
* @brief     Common LIN protocol functions
*
******************************************************************************/
/******************************************************************************
 *
 * History:
 *
 * 20090407     v1.0    First version
 *
 *****************************************************************************/
#include "lin.h"

#define MAKE_UNCONDITIONAL_FRAME 0      /**< make unconditional frame */
#define UPDATE_UNCONDITIONAL_FRAME 1    /**< update unconditional frame */

void lin_process_pid (l_u8 pid);

void lin_update_rx (l_u8 pid);

void lin_update_tx (l_u8 pid);

void lin_handle_error (lin_lld_event_id event_id, l_u8 pid);

void lin_bus_activity_timeout (l_u8 pid);

void lin_update_tx_flags (l_u8 frm_id);

void lin_update_rx_diag_frame (void);

void lin_process_uncd_frame(l_u8 pid, l_u8 type);

void lin_make_res_diag_frame (void);

l_u8 lin_get_frame_index (l_u8 pid);




