/**************************************************************************//**
*
* @file      lin_commontl_proto.c
*
* @author    FPT Software
*
* @brief     Common Handle LIN transport layer and configuration functions
*
******************************************************************************/

#include "lin_commontl_proto.h"
#include "lin_diagnostic_service.h"
#include "eeprom.h"
#include "lin_commontl_api.h"
/* Define functionality */
#ifndef MULTI_PDU_SUPPORT
#define MULTI_PDU_SUPPORT 0             /**< multi PDU support */
#endif  /* MULTI_PDU_SUPPORT */

/********------------- Code supports SINGLE interface ----------------**********/

/*************************** FUNCTIONS *******************/


void lin_tl_make_slaveres_pdu
(
    /* [IN] service identifier */
    l_u8 sid,
    /* [IN] type of response */
    l_u8 res_type,
    /* [IN] Error code in case of negative response, if positive = 0 */
    l_u8 error_code

)
{
    lin_tl_pdu_data lin_tl_pdu;
    l_u8 i;
    l_u8 temp_data[64];

    lin_tl_pdu[0] = lin_configured_NAD;                /* NAD */
    lin_tl_pdu[1] = 0x03;                              /* PCI */
    lin_tl_pdu[2] = RES_NEGATIVE;                      /* SID */
    lin_tl_pdu[3] = sid;                               /* D0  */
    lin_tl_pdu[4] = error_code;                        /* D1  */
    lin_tl_pdu[5] = 0xFF;                              /* D2  */
    lin_tl_pdu[6] = 0xFF;                              /* D3  */
    lin_tl_pdu[7] = 0xFF;                              /* D4  */


    switch (sid)
    {
        case SERVICE_SESSION_CONTROL:   
        	if (POSITIVE == res_type)
        	{
				/* PCI type */
				lin_tl_pdu[1] = PCI_SESSION_CONTROL_BY_IDENTIFY;
				/* SID */
				lin_tl_pdu[2] = RES_POSITIVE + sid;  
						   
				lin_tl_pdu[3] = error_code ;
				lin_tl_pdu[4] = 0xFF ;
        	}
        	break;
        case SERVICE_READ_DATA_BY_IDENTIFY:
        	if (POSITIVE == res_type)
			{				
				/* SID */
				lin_tl_pdu[2] = RES_POSITIVE + sid;

				//if (error_code == (LIN_PRODUCT_SERIAL_NUMBER0&0xFF))
				{
					/* PCI type */
				    lin_tl_pdu[1] = PCI_READ_SERIAL_BY_IDENTIFY;
					/* Get Identifier infor */
					lin_tl_pdu[3] = (LIN_PRODUCT_SERIAL_NUMBER0>>8) ;
					lin_tl_pdu[4] = (l_u8)(LIN_PRODUCT_SERIAL_NUMBER0&0xFF);
					lin_tl_pdu[5] = (l_u8)(temp_data[0]);
					lin_tl_pdu[6] = (l_u8)(temp_data[1]);
					lin_tl_pdu[7] = (l_u8)(temp_data[2]);					
	
				}
			}
        	break;
        case  SERVICE_REQUEST_DOWNLOAD:
        	if (POSITIVE == res_type)
        	{				
      		 /* SID */
        	 lin_tl_pdu[2] = RES_POSITIVE + sid;
			 /* PCI type */
			 lin_tl_pdu[1] = 0x06;
			 /* Get Identifier infor */
			 lin_tl_pdu[3] = 0x10;
			 lin_tl_pdu[4] = 0x23;				
			}
        case SERVICE_TRANSFER_DATA:
        	if (POSITIVE == res_type)
        	 {			
        		
             }
        	break;
        default:
            break;
    }/* end of switch statement */
    /* Multi frame support */
    lin_tl_tx_queue.queue_status = LD_QUEUE_FULL;
    lin_tl_tx_queue.queue_current_size = 1;

    /* Put to transmit queue */
    for (i = 0; i < 8; i++)
    {
        lin_tl_tx_queue.tl_pdu[lin_tl_tx_queue.queue_header][i] = lin_tl_pdu[i];
    }
    /* Set check N_As Timeout */
    tl_tx_msg_index = lin_tl_tx_queue.queue_tail;
    tl_tx_msg_size = 1;
    tl_tx_msg_status = LD_IN_PROGRESS;

    /* set number of SlaveResp response data */
    tl_slaveresp_cnt = 1;
}

void lin_tl_get_pdu()
{
    l_u8 i;
    /* Multi frame support */

    lin_tl_pdu_data lin_tl_pdu;

    tl_get_raw(lin_tl_pdu, &lin_tl_tx_queue, TRANSMISSION);
    /* Copy PDU to response buffer */
    for (i = 1; i < 9; i++)
    {
        lin_lld_response_buffer[i] = lin_tl_pdu[i - 1];
    }

}

/* Single frame support */

static void lin_process_pdu(lin_tl_pdu_data *pdu)
{
    l_u8 pci_type;
    l_u16 length;
    l_u8 tmp_frame_counter;

    /* get PCI type */
    pci_type = ((*pdu)[1] & 0xF0) >> 4;
    switch (pci_type)
    {
        case PCI_SF:
            length = ((*pdu)[1]) & 0x0F;
            /* check length of SF. If not valid, ignore this PDU */
            if (length <= 6)
            {
                tl_receive_msg_status = LD_COMPLETED;
                tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
                tl_service_status = LD_REQUEST_FINISHED;
                /* put PDU to rx queue */
                lin_tl_rx_queue.queue_header = 0;
                lin_tl_rx_queue.queue_tail = 0;
                lin_tl_rx_queue.queue_current_size = 0;
                lin_tl_rx_queue.queue_status = LD_NO_DATA;
                tl_put_raw(&(lin_lld_response_buffer[1]), &lin_tl_rx_queue,   RECEIVING);
                tl_frame_counter = 1;
                tl_no_of_pdu = 1;
                if (tl_diag_state != LD_DIAG_RX_FUNCTIONAL)
                {
                    tl_diag_state = LD_DIAG_TX_PHY;
                }
                lin_tl_attach_service();
            }
            else
            {
                tl_diag_state = LD_DIAG_IDLE;
            }
            break;
        case PCI_FF:
            length = ((*pdu)[1] & 0x0F) * 256 + ((*pdu)[2]);
            /* check length of FF. If not valid, ignore this PDU */
            if (length >= 7 && length <= (MAX_QUEUE_SIZE*6 - 1))
            {
                /* Set check N_Cr timeout */
                tl_check_timeout = N_MAX_TIMEOUT_CNT;
                tl_check_timeout_type = LD_CHECK_N_CR_TIMEOUT;
                /* put PDU to rx queue */
                lin_tl_rx_queue.queue_header = 0;
                lin_tl_rx_queue.queue_tail = 0;
                lin_tl_rx_queue.queue_current_size = 0;
                lin_tl_rx_queue.queue_status = LD_NO_DATA;
                tl_put_raw(lin_lld_response_buffer + 1, &lin_tl_rx_queue, RECEIVING);

                /* canculate number of PDU for this message */
                if ((length-5)%6 == 0)
                {
                    tl_no_of_pdu = (l_u8)((length - 5) / 6);
                }
                else
                {
                    tl_no_of_pdu = (l_u8)((length - 5) / 6) + 1;
                }
                /* set frame counter = 1 */
                tl_frame_counter = 1;
                tl_service_status = LD_SERVICE_BUSY;
                if (tl_diag_state != LD_DIAG_RX_FUNCTIONAL)
                {
                    tl_diag_state = LD_DIAG_RX_PHY;
                }
            }
            else
            {
                tl_diag_state = LD_DIAG_IDLE;
            }
            break;
        case PCI_CF:
            /* Set check N_Cr timeout */
            tl_check_timeout = N_MAX_TIMEOUT_CNT;
            tl_check_timeout_type = LD_CHECK_N_CR_TIMEOUT;
            /* get frame counter of this PDU */
            tmp_frame_counter = ((*pdu)[1] & 0x0F);
            /* Check valid frame counter */
            if (tmp_frame_counter == tl_frame_counter)
            {
                /* increase frame counter */
                tl_frame_counter++;
                if (tl_frame_counter > 15)
                {
                    tl_frame_counter = 0;
                }
                /* decrease number of PDU to check message is complete */
                tl_no_of_pdu--;
                /* put PDU to rx queue */
                tl_put_raw(&(lin_lld_response_buffer[1]), &lin_tl_rx_queue,   RECEIVING);
                if (tl_diag_state != LD_DIAG_RX_FUNCTIONAL)
                {
                    tl_diag_state = LD_DIAG_RX_PHY;
                }
            }
            else
            {
                /* abort this message */
                tl_receive_msg_status = LD_WRONG_SN;
                tl_rx_msg_status = LD_WRONG_SN;
                tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
            }
            if (0 == tl_no_of_pdu)
            {
                /* message is received completely */
                /* set status is IDLE to receive new message */

                tl_receive_msg_status = LD_COMPLETED;
                tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;

                tl_service_status = LD_REQUEST_FINISHED;
                if (tl_diag_state != LD_DIAG_RX_FUNCTIONAL)
                {
                    tl_diag_state = LD_DIAG_TX_PHY;
                }
                lin_tl_attach_service();
            }
            break;
        default:
            /* ignore this PDU */
            break;
    }
}

void lin_tl_handler()
{
    l_u8 NAD, SID;

    l_u8 frame_type;
    NAD = lin_lld_response_buffer[1];
    SID = lin_lld_response_buffer[3];
    frame_type = (l_u8)((lin_lld_response_buffer[2] & 0xF0) >> 4);
    /* check NAD whether or not belongs to this slave node */
    /* receive both broadcast NAD and functional NAD */
    if ((LD_BROADCAST != NAD) && \
            (LD_FUNCTIONAL_NAD != NAD) && \
            (((lin_configured_NAD != NAD) && \
              (SERVICE_ASSIGN_NAD != SID)) || \
             ((lin_initial_NAD != NAD) && \
              (SERVICE_ASSIGN_NAD == SID))))
    {
        /* ignore any response */
        tl_slaveresp_cnt = 0;
        return;
    }
    /* check if  functional request is received while transmitting response */
    if ((tl_diag_state == LD_DIAG_TX_PHY || tl_diag_state == LD_DIAG_RX_PHY) && NAD == LD_FUNCTIONAL_NAD && tl_service_status == LD_SERVICE_BUSY)
    {
        tl_check_timeout = N_MAX_TIMEOUT_CNT;
        tl_check_timeout_type = LD_CHECK_N_CR_TIMEOUT;
        /* ignore request */
        NAD = 0x00;
        return;
    }
    /* check if slave node is transmitting response while receive functional request */
    if (tl_diag_state == LD_DIAG_TX_PHY && NAD != LD_FUNCTIONAL_NAD)
    {
        /* clear received request & response */
        tl_service_status = LD_SERVICE_BUSY;
        /* clear queue */
        lin_tl_tx_queue.queue_tail = 0;
        lin_tl_tx_queue.queue_header = 0;
        lin_tl_tx_queue.queue_current_size = 0;
        lin_tl_tx_queue.queue_status = LD_QUEUE_EMPTY;

        lin_tl_rx_queue.queue_tail = 0;
        lin_tl_rx_queue.queue_header = 0;
        lin_tl_rx_queue.queue_current_size = 0;
        lin_tl_rx_queue.queue_status = LD_NO_DATA;
        /* transmit status */
        tl_tx_msg_status = LD_COMPLETED;
        /* receive status */
        tl_receive_msg_status = LD_NO_MSG;
        tl_rx_msg_status = LD_COMPLETED;

        tl_slaveresp_cnt = 0;
        /* then receive and process new request */
    }

    if (tl_service_status == LD_SERVICE_ERROR && frame_type == PCI_CF)
    {
        return;
    }

    if (NAD != LD_FUNCTIONAL_NAD)
    {
        tl_diag_state = LD_DIAG_RX_PHY;
    }
    else
    {
        tl_diag_state = LD_DIAG_RX_FUNCTIONAL;
    }
    /* call process pdu */
    lin_process_pdu((lin_tl_pdu_data *)&(lin_lld_response_buffer[1]));

}

void lin_tl_attach_service()
{
    l_u8 sid;
    l_u8 i;
    l_u8 sid_supported_flag = 0;
    l_u8 did;


    l_u8 frame_type, NAD;

    /* get frame type */
    frame_type = (lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][1] & 0xF0) >> 4;
    NAD = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][0];
    /* check if request is functional request */
    if (NAD == LD_FUNCTIONAL_NAD)
    {
        lin_diagsrv_functional_service();
        /* update service state */
        tl_diag_state = LD_DIAG_IDLE;
        tl_service_status = LD_SERVICE_IDLE;
        /* ignore response */
        tl_no_of_pdu = 0;
        tl_frame_counter = 0;
        return;
    }

    /* Get SID information */
    if (frame_type == PCI_FF)
    {
        sid = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][3];
    }
    else
    {
        sid = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][2];
    }


    for (i = 0; i < _DIAG_NUMBER_OF_SERVICES_; i++)
    {
        if (lin_diag_services_supported[i] == sid)
        {
            lin_diag_services_flag[i] = 1;
            sid_supported_flag = 1;
            break;
        }
    }   
    
    if (sid_supported_flag == 1)
    {
        /*Clear sid_supported_flag */
        sid_supported_flag = 0;
        switch (sid)
        {
            case SERVICE_TRIGGER_CHECK:
            case SERVICE_REQUEST_DOWNLOAD:
            	 lin_diagservice_request_download();
            	 break;
            case SERVICE_TRANSFER_DATA:
            	lin_diagservice_transfer_data();
            	break;
            case SERVICE_EXIT_TRANSFER_DATA:
            case SERVICE_SESSION_CONTROL:
                    	
                lin_diagservice_session_control();
			    break;        
            case SERVICE_READ_DATA_BY_IDENTIFY:   
            	
            	lin_diagservice_read_data_by_identifier();
            	break;
           /* case SERVICE_WRITE_DATA_BY_IDENTIFY:
            	if(diagnostic_Session == DIAGSRV_SESSION_DEFAULT)
                {
            		 lin_tl_make_slaveres_pdu(sid, NEGATIVE, SERVICE_NOT_SUPPORTED_ACTIVE_SESSION);
                }
            	else
                {
            		lin_diagservice_write_data_by_identifier();
                }
				break;  */
            default:
                break;
        }/* end of switch */
    }
    else
    {
        lin_tl_make_slaveres_pdu(sid, NEGATIVE, SERVICE_NOT_SUPPORTED);
    }
}


/********------------ End of code for SINGLE Interface --------------**********/


/* ------------- End of code for Multi Interface --------------- */
/* multi frame support */
/* COMMON FUNCTIONS */
void tl_put_raw
(
    /* [IN] buffer for the data */
    const l_u8* const data,
    /* [IN] queue for containing data */
    lin_transport_layer_queue *queue,
    /* [IN] Direction */
    l_u8 direction
)
{
    lin_tl_pdu_data           *queue_data;
    l_u8                      i;

    /* Get transmit queue */
    queue_data = queue->tl_pdu;

    /* check status of queue */
    if (LD_QUEUE_FULL != queue->queue_status)
    {
        /* prcess queue tail */
        if ((LD_QUEUE_EMPTY == queue->queue_status) || (LD_NO_DATA == queue->queue_status))
        {
            /* Set status of queue */
            if (TRANSMISSION == direction)
            {
                queue->queue_status = LD_QUEUE_AVAILABLE;
            }
            else
            {
                queue->queue_status = LD_DATA_AVAILABLE;
            }
        }
        else
        {
            /* Check if queue size equal to queue tail */
            if (queue->queue_max_size == queue->queue_tail + 1)
            {
                queue->queue_tail = 0;
            }
            else
            {
                queue->queue_tail++;
            }
        }
        /* copy data to queue */
        for (i = 0; i < 8; i++)
        {
            queue_data[queue->queue_tail][i] = data[i];
        }
        /* update queue status */
        queue->queue_current_size++;
        if (queue->queue_current_size >= queue->queue_max_size)
        {
            queue->queue_status = LD_QUEUE_FULL;
        }
    }
}

void tl_get_raw
(
    /* [OUT] buffer for store data received */
    l_u8* const data,
    /* queue for containing data */
    lin_transport_layer_queue *queue,
    /* direction for transmission */
    l_u8 direction
)
{

    lin_transport_layer_queue *tl_queue;
    lin_tl_pdu_data           *queue_data;
    l_u8                      i;
    l_u16                      queue_header;

    tl_queue = queue;
    /* Get queue */
    queue_data = tl_queue->tl_pdu;

    /* Check queue status (is the queue contains data? if yes: get data from queue and put them to buffer) */
    if ((LD_NO_DATA != tl_queue->queue_status) && (LD_QUEUE_EMPTY != tl_queue->queue_status))
    {
        /* get data from head queue */
        queue_header = tl_queue->queue_header;
        for (i = 0; i < 8; i++)
        {
            *(data+i) = queue_data[queue_header][i];
        }

        /* update queue status */
        if (0 == (--queue->queue_current_size))
        {
            if (TRANSMISSION == direction)
            {
                queue->queue_status = LD_QUEUE_EMPTY;
            }
            else
            {
                queue->queue_status = LD_NO_DATA;
            }
        }
        else
        {
            if (TRANSMISSION == direction)
            {
                queue->queue_status = LD_QUEUE_AVAILABLE;
            }
            else
            {
                queue->queue_status = LD_DATA_AVAILABLE;
            }
        }

        /* change queue header */
        if (0 != queue->queue_current_size)
        {
            if (queue->queue_header == queue->queue_max_size - 1)
            {
                queue->queue_header = 0;
            }
            else
            {
                queue->queue_header++;
            }
        }
    }
}
