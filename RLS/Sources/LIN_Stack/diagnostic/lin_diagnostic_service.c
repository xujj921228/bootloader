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



/********------------- Code supports SINGLE interface ----------------**********/
/*************************** FUNCTIONS *******************/


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
		  case 1:
			  lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, RES_POSITIVE);
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




void lin_diagsrv_functional_service(void)
{
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data);

    /* do something here */
}

