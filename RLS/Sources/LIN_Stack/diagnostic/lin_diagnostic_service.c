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
		  case 0x01c1:
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


l_u16 updata_flash_ID;
l_u16 updata_length;
uint8 DRIVE_flag = 0;
void lin_diagservice_request_download(void)
{
    lin_tl_pdu_data *lin_tl_pdu;

    /* Multi frame support */
    l_u16 length;
    l_u8 data[20];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    
    
    DRIVE_flag = data[3];
    if(DRIVE_flag != 0)
    {
    	lin_tl_make_slaveres_pdu(SERVICE_REQUEST_DOWNLOAD, POSITIVE, RES_POSITIVE);
    }
    else
    {
     updata_flash_ID = (((l_u16)data[5])<<8) + (l_u16)data[6];
     updata_length = (((l_u16)data[8])<<8) + (l_u16)data[9];
     lin_tl_make_slaveres_pdu(SERVICE_REQUEST_DOWNLOAD, POSITIVE, RES_POSITIVE);
    }
    
}



void lin_diagservice_transfer_data(void)
{
	l_u8 i;
    lin_tl_pdu_data *lin_tl_pdu;
    l_u16 length;
    l_u8 data[128];
    l_u8 data_read[128]={0};
    l_u8 check_add = 0;
    
    
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    lin_tl_pdu = (lin_tl_pdu_data *)data+2;
    
    
    if(DRIVE_flag != 0)
    {
    	lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, POSITIVE, RES_POSITIVE);
    }
    else
    {
    	if((updata_length == (length + 1))|| updata_flash_ID == 0)
    	{
    		check_add = check_add + (l_u8)(updata_length>>8) + (l_u8)updata_length;
    		check_add = check_add + (l_u8)(updata_flash_ID>>8) + (l_u8)updata_flash_ID;
        	for(i = 0;i < (updata_length - 3);i++)
        	{
        	   check_add = check_add+data[3+i];		
        	}
        	check_add = 0xFF - check_add;
        	if(check_add == data[updata_length])
        	{
        		FLASH_Program( (uint32)updata_flash_ID,data[3],updata_length-3);
        		
        		for(i = 0;i < (updata_length-3);i++)
        		{
        			data_read[i] = *((uint8_t *)(updata_flash_ID+i));
        			/*if(data_read[i] != data[3+i])
        			{
        				lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, NEGATIVE, INVALID_FORMAT);
        				return;
        			}*/
        		}
        		lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, POSITIVE, RES_POSITIVE);
        		updata_length = 0;
        		updata_flash_ID = 0;	
        	}
        	else
        	{
        		lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, NEGATIVE, INVALID_FORMAT);
        	}
    	}
    	else
    	{
    	  lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, NEGATIVE, INVALID_FORMAT);
    	}
    }
    
}
