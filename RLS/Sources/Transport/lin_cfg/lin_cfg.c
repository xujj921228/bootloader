/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      lin_cfg.c
*
* @author    xujun
*
* @version   1.0
*
* @date      Fri Sep 07 16:59:12 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include "lin_cfg.h"
#include "lin.h"
/* Mapping interface with hardware */
const lin_hardware_name lin_virtual_ifc = UART0;
l_u8 lin_lld_response_buffer[10];
l_u8 lin_successful_transfer;
l_u8 lin_error_in_response;
l_u8 lin_goto_sleep_flg;
/* Save configuration flag */
l_u8 lin_save_configuration_flg = 0;
lin_word_status_str lin_word_status;
l_u8 lin_current_pid;

const l_signal_handle LI0_response_error_signal = LI0_RLS_RainSensorError;
const l_u8 response_error_byte_offset = LIN_BYTE_OFFSET_LI0_RLS_RainSensorError;
const l_u8 response_error_bit_offset = LIN_BIT_OFFSET_LI0_RLS_RainSensorError;


/* definition and initialization of signal array */
l_u8    lin_pFrameBuf[LIN_FRAME_BUF_SIZE] =
{


  0x80 /* 0 : 10000000 */ /* start of frame LI0_BCM_01 */

  ,0x00 /* 1 : 00000000 */
  ,0xff /* 2 : 11111111 */
  ,0xff /* 3 : 11111111 */
  ,0xff /* 4 : 11111111 */
  ,0xff /* 5 : 11111111 */
  ,0xff /* 6 : 11111111 */
  ,0xff /* 7 : 11111111 */


  ,0x00 /* 8 : 00000000 */ /* start of frame LI0_RLS_01 */

  ,0x00 /* 9 : 00000000 */
  
  ,0x00 /* 10 : 00000000 */
  
  ,0x00 /* 11 : 00000000 */
  
  ,0xff /* 12 : 11111111 */
  
  ,0xff /* 13 : 11111111 */
  
  ,0xff /* 14 : 11111111 */
  
  ,0xff /* 15 : 11111111 */
  
};

/* definition and initialization of signal array */
l_u8    lin_flag_handle_tbl[LIN_FLAG_BUF_SIZE] =
{


  0x00 /* 0: start of flag frame LI0_BCM_01 */



  ,0x00 /* 1: start of flag frame LI0_RLS_01 */

  ,0x00 /* 2: */
  
};

/*************************** Flag set when signal is updated ******************/
/* Diagnostic signal */
l_u8 lin_diag_signal_tbl[16];
/*****************************event trigger frame*****************************/

/**********************************  Frame table **********************************/
const lin_frame_struct lin_frame_tbl[LIN_NUM_OF_FRMS] ={

    { LIN_FRM_UNCD, 8, LIN_RES_SUB, 0, 0, 1   , (l_u8*)0 }

   ,{ LIN_FRM_UNCD, 8, LIN_RES_PUB, 8, 1, 2 , (l_u8*)&LI0_response_error_signal }
  
   ,{ LIN_FRM_DIAG, 8, LIN_RES_SUB, 0, 0, 0 , (l_u8*)0 }
  
   ,{ LIN_FRM_DIAG, 8, LIN_RES_PUB, 0, 0, 0 , (l_u8*)0 }
  
};

/*********************************** Frame flag Initialization **********************/
l_bool lin_frame_flag_tbl[LIN_NUM_OF_FRMS] = {0, 0, 0, 0};

/**************************** Lin configuration Initialization ***********************/
/* max_response_frame_timeout = round((1.4x(10+Nx10)xTbit)/Tbase_period) + 3 */

const l_u16 lin_max_frame_res_timeout_val[8]={

6, 7, 9, 10, 12, 13, 15, 16

};


l_u8 lin_configuration_RAM[LIN_SIZE_OF_CFG]= {0x00, 0x28, 0x29, 0x3C, 0x3D ,0xFF};
const l_u16  lin_configuration_ROM[LIN_SIZE_OF_CFG]= {0x00, 0x28, 0x29, 0x3C, 0x3D ,0xFFFF};

/***************************************** Node Attribute*****************************************/

l_u8 lin_configured_NAD = 0x29;    /*<configured_NAD>*/
const l_u8 lin_initial_NAD    =0x29;    /*<initial_NAD>*/
const lin_product_id product_id = {0x0066, 0x0000, 0x00FF };  /* {<supplier_id>,<function_id>,<variant>} */
const l_signal_handle response_error =  LI0_RLS_RainSensorError;

/************************** TL Layer and Diagnostic: SINGLE interface **************************/
/* QUEUE information */
lin_tl_pdu_data tl_tx_queue_data[MAX_QUEUE_SIZE];    /*transmit queue data */
lin_tl_pdu_data tl_rx_queue_data[MAX_QUEUE_SIZE];    /*receive queue data */

lin_transport_layer_queue lin_tl_tx_queue = {
0,                                                /* the first element of queue */
0,                                                /* the last element of queue */
LD_QUEUE_EMPTY,                                   /* status of queue */
0,                                                /* curernt size of queue */
MAX_QUEUE_SIZE,                                   /* size of queue */
tl_tx_queue_data,                                 /* data of queue */
};
lin_transport_layer_queue lin_tl_rx_queue = {
0,                                                /* the first element of queue */
0,                                                /* the last element of queue */
LD_QUEUE_EMPTY,                                   /* status of queue */
0,                                                /* curernt size of queue */
MAX_QUEUE_SIZE,                                   /* size of queue */
tl_rx_queue_data,                                 /* data of queue */
};
/* message information in transmit queue */
l_u16 tl_rx_msg_index;                                /* index of message in queue */
l_u16 tl_rx_msg_size;                                 /* Size of message in queue */
/* message information in receive queue */
l_u16 tl_tx_msg_index;                                /* index of message in queue */
l_u16 tl_tx_msg_size;                                 /* Size of message in queue */
lin_last_cfg_result tl_last_cfg_result;               /* Status of the last configuration service in LIN 2.0, J2602 */
l_u8 tl_last_RSID;                                    /* RSID of the last node configuration service */
l_u8 tl_ld_error_code;                                /* Error code in case of positive response */
l_u8 tl_no_of_pdu;                                    /* number of received pdu */
l_u8 tl_frame_counter;                                /* frame counter in received message */
lin_message_timeout_type tl_check_timeout_type;       /* timeout type */
l_u16 tl_check_timeout;                               /* timeout counter*/
l_u8 *tl_ident_data;                                  /* To store address of RAM area contain response */

lin_diagnostic_state tl_diag_state = LD_DIAG_IDLE;
lin_service_status tl_service_status =  LD_SERVICE_IDLE ; /* service status */
lin_message_status tl_receive_msg_status;             /* receive message status */
lin_message_status tl_rx_msg_status;                  /* cooked rx status */
lin_message_status tl_tx_msg_status;                  /* cooked tx status */










/****************************Support SID Initialization ***********************/

const l_u8 lin_diag_services_supported[_DIAG_NUMBER_OF_SERVICES_] = {0xB2,0xB6,0xB7,0x22,0x10,0xB3,0xB0,0x2E,0x27};
l_u8 lin_diag_services_flag[_DIAG_NUMBER_OF_SERVICES_] = {0,0,0,0,0,0,0,0,0};
l_u8 tl_slaveresp_cnt = 0;
/* This function is an example of response; real implementation is application-dependent */
/* You can use one of the following define to set PCI of response frame for */
/* this service to the correct value */
l_u8 ld_read_by_id_callout(l_u8 id, l_u8 *data){
    l_u8 retval = LD_ID_NO_RESPONSE;
    /* Following code is an example - Real implementation is application-dependent */
    /*
     * the handling does essentially depend on the id of the
     * requested item
     */
    /* This example implement with ID = 32 - LIN_READ_USR_DEF_MIN */
    if (id == LIN_READ_USR_DEF_MIN)
    {
      /*
       * id received is user defined 32
       */
      /* A positive response is ready to be sent to the user defined request */

      data[0] = (l_u8) (id + 1);    /* Data user define */
      data[1] = (l_u8) (id + 2);    /* Data user define */
      data[2] = (l_u8) (id + 3);    /* Data user define */
      data[3] = (l_u8) (id + 4);    /* Data user define */
      data[4] = (l_u8) (id + 5);    /* Data user define */
      retval = LD_POSITIVE_RESPONSE;
    }
    else
    {
      /*
       * id received is user defined 63 - no response
       */
    }
    return retval;
}