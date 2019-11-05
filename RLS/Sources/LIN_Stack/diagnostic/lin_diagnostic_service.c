/**************************************************************************//**
*
* @file      lin_diagnostic_service.c
*
* @author    FPT Software
*
* @brief     Diagnostic Service slave functions
*
******************************************************************************/

#include "lin_commontl_proto.h"
#include "lin_diagnostic_service.h"
#include "eeprom.h"

/* Define functionality */
#ifndef MULTI_PDU_SUPPORT
#define MULTI_PDU_SUPPORT 0                        /**< multi PDU support */
#endif /* End MULTI_PDU_SUPPORT */

/********------------- Code supports SINGLE interface ----------------**********/
/*************************** FUNCTIONS *******************/
/* Unuse for GPIO */
#if ( _LIN_GPIO_ == 0 ) && !defined(_MC9S08SC4_H) && !defined(MCU_SKEAZN84)


l_u8 diagnostic_Session,diagnostic_Session_pre,diagnostic_Session_flg;
l_u16 diagnostic_Session_timer;

void lin_diagservice_session_state(void)
{
	if(diagnostic_Session_flg == 1)
	{
		if(diagnostic_Session_timer >= 500) //5s
		{
			diagnostic_Session =  DIAGSRV_SESSION_DEFAULT;
			diagnostic_Session_flg = 0;
			diagnostic_Session_timer = 0;
		}
		else
		{
			diagnostic_Session_timer++;
		}
	}
	
	diagnostic_Session_pre = diagnostic_Session;
}

l_u8 lin_diagservice_session_control(void)
{
	l_u8 id;
	lin_tl_pdu_data *lin_tl_pdu;

	/* Multi frame support */
	l_u16 length;
	l_u8 data[10];
	/* get pdu from rx queue */
	ld_receive_message(&length, data+2);
	lin_tl_pdu = (lin_tl_pdu_data *)data;


	id = (*lin_tl_pdu)[3];
    
	if(length == PCI_SESSION_CONTROL_BY_IDENTIFY)
	{
		switch (id)
		{
			case DIAGSRV_SESSION_DEFAULT:			
				lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, POSITIVE, DIAGSRV_SESSION_DEFAULT);
				diagnostic_Session =  DIAGSRV_SESSION_DEFAULT;
				break;
			case DIAGSRV_SESSION_PROGRAM:
				if(diagnostic_Session_pre == DIAGSRV_SESSION_DEFAULT)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, NEGATIVE, SERVICE_NOT_SUPPORTED_ACTIVE_SESSION);
					diagnostic_Session = DIAGSRV_SESSION_DEFAULT ;
				}
				else
				{
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, POSITIVE, DIAGSRV_SESSION_PROGRAM);
					diagnostic_Session =  DIAGSRV_SESSION_PROGRAM;
				}
				break;
			case DIAGSRV_SESSION_EXTERN:
				lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, POSITIVE, DIAGSRV_SESSION_EXTERN);
				diagnostic_Session =  DIAGSRV_SESSION_EXTERN;
				break;
			default:
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, NEGATIVE, SUBFUNCTION_NOT_SUPPORTED);
				break;
		} /* End of switch */
	}
	else
	{
		/* Make a negative slave response PDU */
		lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, NEGATIVE, INVALID_FORMAT);
	}
}



void lin_diagservice_read_data_by_identifier(void)
{
    l_u16 id;
    lin_tl_pdu_data *lin_tl_pdu;
    l_u16 temp ;

    /* Multi frame support */
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    lin_tl_pdu = (lin_tl_pdu_data *)data;

    temp =  (*lin_tl_pdu)[3] ;
    id = ((temp << 8)|(*lin_tl_pdu)[4]);
    if(length >= 3)
    {
		switch (id)
		{
			case LIN_RAIN_ADC_A_PARAM:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_RAIN_ADC_A_PARAM&0xFF));
				break;
							  
			case LIN_RAIN_ADC_B_PARAM:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_RAIN_ADC_B_PARAM&0xFF));
				break;
	
			default:
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, NEGATIVE, REQ_OUT_RANGE);
				break;
		} /* End of switch */
    }
    else
    {
    	/* Make a negative slave response PDU */
        lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
    }
    
}


void lin_diagservice_write_data_by_identifier(void)
{
	l_u16 id;
	lin_tl_pdu_data *lin_tl_pdu;
	l_u16 temp ;

	/* Multi frame support */

	l_u16 length;
	l_u8 data[10];
	/* get pdu from rx queue */
	ld_receive_message(&length, data+2);
	lin_tl_pdu = (lin_tl_pdu_data *)data;

	temp =  (*lin_tl_pdu)[3] ;
	id = ((temp << 8)|(*lin_tl_pdu)[4]);

	if(length >= 3)
	{
		switch (id)
		{
				
			case LIN_RAIN_ADC_A_PARAM:
				if(length != 5)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{		
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE, (LIN_RAIN_ADC_A_PARAM&0xff));
				}
				break;
							  
			case LIN_RAIN_ADC_B_PARAM:
				if(length != 5)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{			
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE, (LIN_RAIN_ADC_B_PARAM&0xff));
				}
				break;
	
			default:
				/* Make a negative slave response PDU */
				lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, REQ_OUT_RANGE);
				break;
		} /* End of switch */
	}
	else
	{
		/* Make a negative slave response PDU */
		lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
	}
}
void lin_diagservice_assign_frame_id_range()
{
    l_u8 start_index;
    l_s8 j, i = 7;
    lin_tl_pdu_data *lin_tl_pdu;
    /* Multi frame support */
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    lin_tl_pdu = (lin_tl_pdu_data *)data;
    /* Get start index in request */
    start_index = (*lin_tl_pdu)[3];

    for (i = 7, j = start_index+4; j > start_index; i--, j-- )
    {
        if ((0xFF != (*lin_tl_pdu)[i]) && (j > LIN_CFG_FRAME_NUM))
        {
            lin_tl_make_slaveres_pdu(SERVICE_ASSIGN_FRAME_ID_RANGE, NEGATIVE, GENERAL_REJECT);
            return;
        }
    }

    /* Store PIDs */
    for (i = 4, j = start_index + 1; i < 8; i++, j++)
    {
        switch ((*lin_tl_pdu)[i])
        {
            case 0x00:
                /* Unassign frame */
                lin_configuration_RAM[j] = 0xFF;
                break;

            case 0xFF:
                /* keep the previous assigned value of this frame */
                break;

            default:
                /* Calculate frame ID & Assign ID to frame */
                lin_configuration_RAM[j] = lin_process_parity((*lin_tl_pdu)[i], CHECK_PARITY);
                break;
        }
    } /* End of for statement */

    lin_tl_make_slaveres_pdu(SERVICE_ASSIGN_FRAME_ID_RANGE, POSITIVE, 0);
}



void lin_diagservice_read_by_identifier()
{
    l_u8 id;
    lin_tl_pdu_data *lin_tl_pdu;

    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    lin_tl_pdu = (lin_tl_pdu_data *)data;

    id = (*lin_tl_pdu)[3];

    switch (id)
    {
        case LIN_PRODUCT_IDENT:
            lin_tl_make_slaveres_pdu(SERVICE_READ_BY_IDENTIFY, POSITIVE, 0);
            break;
        #if _DIAG_CLASS_SUPPORT_ == _DIAG_CLASS_III_
        case SERIAL_NUMBER:
            lin_tl_make_slaveres_pdu(SERVICE_READ_BY_IDENTIFY, POSITIVE, 1);
            break;
        #endif  /* End _DIAG_CLASS_ == _DIAG_CLASS_III_ */

        default:
            if (id >= LIN_READ_USR_DEF_MIN && id <= LIN_READ_USR_DEF_MAX)
            {
                lin_tl_make_slaveres_pdu(SERVICE_READ_BY_IDENTIFY, POSITIVE, id);
            }
            else
            {
                /* Make a negative slave response PDU */
                lin_tl_make_slaveres_pdu(SERVICE_READ_BY_IDENTIFY, NEGATIVE, SUBFUNCTION_NOT_SUPPORTED);
            }
            break;
    } /* End of switch */
}

void lin_condittional_change_nad()
{
    l_u8 id, byte, mask, invert;
    id      = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][3];
    byte    = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][4];
    mask    = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][5];
    invert  = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][6];


    /* Possible positive ID */
    if (id == 0)
    {
        /* Do a bitwise XOR with Invert and Do a bitwise AND with Mask */
        byte = (byte^invert)&mask;
        if (byte == 0)
        {
            /* If the final result is zero then change the NAD to New NAD */
            lin_configured_NAD = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][7];
        }
        lin_tl_make_slaveres_pdu(SERVICE_CONDITIONAL_CHANGE_NAD, POSITIVE, 0);
    }
}
#endif /* End ( _LIN_GPIO_ == 0 ) && !defined(_MC9S08SC4_H) */



void lin_diagsrv_functional_service(void)
{
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data);

    /* do something here */
}

