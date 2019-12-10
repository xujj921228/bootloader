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
#include "lin.h"


/********------------- Code supports SINGLE interface ----------------**********/
/*************************** FUNCTIONS *******************/


l_u8 diagnostic_Session,diagnostic_Session_pre,diagnostic_Session_flg;
l_u16 diagnostic_Session_timer;

extern uint8_t boot_up_ret[2];

extern Boot_Fsm_t boot_status_flag;
uint32_t updata_flash_ID = 0;
uint16_t updata_length = 0;
uint8_t boot_seed[4];
uint8_t boot_key[4];
l_u8 APP_check_value[4]={0xa5,0x5a,0xa4,0x4a};
l_u8 boot_write_flash[100];
l_u8 service_flash_read[100]={0};
l_u8 data_cn1;   //4n
l_u8 data_cn2;   //4n + m
l_u16 boot_flashdata_cn ;
l_u16 boot_flashdata_last_cn ; 

/************************
 * For APP check
 * 
 * xujunjie@baolong.com
 * ********************/
APP_check_t boot_APP_check(void)
{
	uint8_t i;
	APP_check_t ret = APP_VALUE;
	uint8_t temp[4] ={ 0 };
	
	for(i = 0;i < 4; i++)
	{
		temp[i] = *((uint8_t *)(APP_check_ADDRESS+i));
		if(APP_check_value[i] != temp[i])
		{
			ret = APP_INVALUE;
		}
	}
	
	return  ret;
}

/************************
 * For APP up check
 * 
 * xujunjie@baolong.com
 * ********************/
uint8_t boot_up_check()
{
	read_data_from_EEPROM(EEPROM_BOOT_REFRESH,boot_up_ret,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
		
	if(boot_up_value == boot_up_ret[0])
	{
		return 1;
	}
	else if(boot_up_ret[0] == 0xff)
	{
		boot_up_ret[0] = 0;
		boot_up_ret[1] = 0;
		write_data_from_EEPROM(EEPROM_BOOT_REFRESH,boot_up_ret,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
	}
	else
	{
		if(((boot_up_ret[1] >> 4) > 4)||((boot_up_ret[1]&0x0f) > 4))
		{
			boot_up_ret[1] = 0;
		}
		write_data_from_EEPROM(EEPROM_BOOT_REFRESH,boot_up_ret,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
	}
	return 0;
}

void lin_diagservice_session_control(void)
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
		diagnostic_Session_pre = boot_up_ret[0] >> 4;
		diagnostic_Session = boot_up_ret[0] & 0x0f;
		switch (id)
		{
			case DIAGSRV_SESSION_DEFAULT:	
				if(boot_APP_check() == APP_INVALUE)
				{
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, NEGATIVE, SERVICE_NOT_SUPPORTED_ACTIVE_SESSION);
				}
				else
				{
					boot_up_ret[1] = 0;
					boot_status_flag = boot_fsm_reboot;
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, POSITIVE, DIAGSRV_SESSION_DEFAULT);
					diagnostic_Session =  DIAGSRV_SESSION_DEFAULT;
				}
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
				/*if(boot_APP_check() == APP_INVALUE)
				{
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, NEGATIVE, SERVICE_NOT_SUPPORTED_ACTIVE_SESSION);
				}
				else
				{
					boot_up_ret[1] = 0;
					boot_status_flag = boot_fsm_reboot;
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, POSITIVE, DIAGSRV_SESSION_EXTERN);
					diagnostic_Session =  DIAGSRV_SESSION_EXTERN;
				}*/
				lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, POSITIVE, DIAGSRV_SESSION_EXTERN);
				diagnostic_Session =  DIAGSRV_SESSION_EXTERN;
				break;
			case DIAGSRV_SESSION_RESTART:
				boot_status_flag = boot_fsm_reboot;
				lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, POSITIVE, DIAGSRV_SESSION_RESTART);
				break;
			default:
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, NEGATIVE, SUBFUNCTION_NOT_SUPPORTED);
				break;
		} /* End of switch */
		if(diagnostic_Session_pre != diagnostic_Session)
		{	
			boot_up_ret[1] = diagnostic_Session_pre|diagnostic_Session;
			write_data_from_EEPROM(EEPROM_BOOT_REFRESH,boot_up_ret,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
		}
		diagnostic_Session_pre = diagnostic_Session;
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



void uds_calc_key(uint8_t *seed,uint8_t *key)
{
     uint8_t i;
     uint32_t mask;

     uint32_t wort;     
     
     mask = 0x7FADEBFC;
     
     wort = (((uint32_t)seed[0])<<24) + (((uint32_t)seed[0])<<16) + (((uint32_t)seed[0])<<8) + ((uint32_t)seed[0]);
         
     for(i = 0 ;i<35;i++)
     {
        if(wort&0x80000000)
        {
            wort = wort<<1;
            wort = wort^mask;
        }
        else
        {
            wort = wort<<1; 
        }
        
     } 
     key[0] = (uint8_t)(wort >> 24);
     key[1] = (uint8_t)(wort >> 16);
     key[2] = (uint8_t)(wort >> 8);
     key[3] = (uint8_t)wort;
}


void lin_diagservice_service_securityaccess(void)
{
	 l_u16 length;
	 l_u8 data[10];
	 uint8_t i; 
	 /* get pdu from rx queue */
	 ld_receive_message(&length, data);
	 
	 if(data[1] == 1)
	 {
		 boot_status_flag = boot_fsm_sendseed;
		 boot_seed[0] = rand();
		 boot_seed[1] = rand();
		 boot_seed[2] = rand();
		 boot_seed[3] = rand();
		 lin_tl_make_slaveres_pdu(SERVICE_SECURITYACCESS, POSITIVE, RES_POSITIVE);
	 }
	 else if((data[1] == 2)&&(boot_status_flag == boot_fsm_sendseed))
	 {
		 uds_calc_key(boot_seed,boot_key);
		 for(i = 0; i < 4;i++ )
		 {
			 if(boot_key[i] != data[2 + i])
			 {
				 boot_status_flag = boot_fsm_sendseed;
				 lin_tl_make_slaveres_pdu(SERVICE_SECURITYACCESS, NEGATIVE, SUBFUNCTION_NOT_SUPPORTED);
				 return;
			 }
         }
		 boot_status_flag = boot_fsm_getkey;
		 lin_tl_make_slaveres_pdu(SERVICE_SECURITYACCESS, POSITIVE, RES_POSITIVE);
	 }
	 else
	 {
		 lin_tl_make_slaveres_pdu(SERVICE_SECURITYACCESS, NEGATIVE, SUBFUNCTION_NOT_SUPPORTED);
	 }
	
	
}
void lin_diagservice_request_download(void)
{

    l_u16 length;
    l_u8 data[20];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    
    
    if((data[3] == 1) && (boot_status_flag == boot_fsm_getkey))
    {
    	boot_status_flag = boot_fsm_requestdriver;
    	lin_tl_make_slaveres_pdu(SERVICE_REQUEST_DOWNLOAD, POSITIVE, RES_POSITIVE);
    }
    
    
    if((boot_status_flag == boot_fsm_enderaser) && (data[3] == 0))
    {
     updata_flash_ID = (((l_u16)data[5])<<8) + (l_u16)data[6];
     updata_length = (((l_u16)data[8])<<8) + (l_u16)data[9];
     if(updata_flash_ID == APP_code_start)
     {
    	 lin_tl_make_slaveres_pdu(SERVICE_REQUEST_DOWNLOAD, POSITIVE, RES_POSITIVE);
    	 boot_flashdata_cn = 1;
    	 boot_flashdata_last_cn = 0; 
    	 boot_status_flag = boot_fsm_startdownload;
     }
     else
     {
    	 lin_tl_make_slaveres_pdu(SERVICE_REQUEST_DOWNLOAD, NEGATIVE, REQ_OUT_RANGE);
     }
    }
    
}

void lin_diagservice_transfer_data(void)
{
	uint32_t i;
    static l_u16 length;
    l_u8 data[50];
    uint16_t sum = 0;
    
    if( boot_status_flag == boot_fsm_requestdriver ) //�������ݴ���
    {
    	lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, POSITIVE, RES_POSITIVE);
    }
    else if( boot_status_flag == boot_fsm_startdownload )//Ӧ�ó�����
    {
    		
		/* �Ӷ����л�ȡ���� */
		ld_receive_message(&length, data);
		for(i = 0;i < (length - 2);i++)
		{
			sum = sum + data[1 + i];
			if ((sum & 0xFF00)!=0)
				sum = (l_u8)((sum & 0x00FF) + 1); 
		}
		sum =sum ^ 0x00FF;
		if(data[length - 1] == (l_u8)sum)
		{
			length = length - 4;
					
					
			boot_flashdata_cn =  ((l_u16)data[1]<<8) + (l_u16)data[2];
			
			if(boot_flashdata_cn == (boot_flashdata_last_cn + 1))
			{
				for(i=0 ; i<length ; i++)
				{
				   boot_write_flash[data_cn2+i] = data[i + 3];
				}
				length = data_cn2 + length ;
			
				data_cn1 = length/4;
				data_cn2 = length%4;
					
				FLASH_Program(updata_flash_ID,&boot_write_flash[0],(uint16_t)(4*data_cn1));
				for(i = 0;i < 4*data_cn1;i++)
				{
					service_flash_read[i] = *((uint8_t *)(i+updata_flash_ID));
					if(service_flash_read[i] != boot_write_flash[i])
					{
						lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, NEGATIVE, INVALID_FORMAT);
						return;
					}			
				}
							 
				
				updata_flash_ID = updata_flash_ID + 4*data_cn1;
				
				for(i = 0;i < data_cn2;i++ )
				{
					boot_write_flash[i] = boot_write_flash[4*data_cn1 + i];
				}
				
				boot_flashdata_last_cn = boot_flashdata_cn;
				lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, POSITIVE, RES_POSITIVE);
			}
			else if(boot_flashdata_cn == boot_flashdata_last_cn)
			{
				boot_flashdata_last_cn = boot_flashdata_cn;
				lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, POSITIVE, RES_POSITIVE);
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
	else
	{
	  lin_tl_make_slaveres_pdu(SERVICE_TRANSFER_DATA, NEGATIVE, INVALID_FORMAT);
	}
    
}

void lin_diagservice_service_trigger_check(void)
{
    l_u16 length;
	l_u8 data[20];
	
    /* get pdu from rx queue */
	ld_receive_message(&length, data+2);
	   

	if(data[3] == 0x01)//����
	{
		if((data[5] == 0x00) && ( boot_status_flag = boot_fsm_requestdriver))//��������flash
		{
		  lin_tl_make_slaveres_pdu(SERVICE_TRIGGER_CHECK, POSITIVE, RES_POSITIVE);
		  boot_status_flag = boot_fsm_start_eraser;
		}
		else if(data[5] == 0x01)//������ѯ��Ч����֤
		{
			lin_tl_make_slaveres_pdu(SERVICE_TRIGGER_CHECK, POSITIVE, RES_POSITIVE);
		}
		else
		{
			lin_tl_make_slaveres_pdu(SERVICE_TRIGGER_CHECK, NEGATIVE, RES_NEGATIVE);
		}
			

	}
	else if(data[3] == 0x03)
	{
		if((data[5] == 0x00)&&(boot_status_flag == boot_fsm_enderaser))//��ѯ�������
		{
			lin_tl_make_slaveres_pdu(SERVICE_TRIGGER_CHECK, POSITIVE, RES_POSITIVE);
		}
		else if(data[5] == 0x01)//��ѯ��֤���
		{
			lin_tl_make_slaveres_pdu(SERVICE_TRIGGER_CHECK, POSITIVE, RES_POSITIVE);
		}
		else
		{
			lin_tl_make_slaveres_pdu(SERVICE_TRIGGER_CHECK, NEGATIVE, RES_NEGATIVE);
		}
			
		
		
	}
	else
	{
		lin_tl_make_slaveres_pdu(SERVICE_TRIGGER_CHECK, NEGATIVE, RES_NEGATIVE);	
	}
		 	


}


void lin_diagservice_exit_transfer(void)
{
	    
	if( boot_status_flag == boot_fsm_requestdriver ) //�������ݴ���
	{
		lin_tl_make_slaveres_pdu(SERVICE_EXIT_TRANSFER_DATA, POSITIVE, RES_POSITIVE);
	}
	else if( boot_status_flag == boot_fsm_startdownload )//Ӧ�ó�����
	{
	
		//д��flash���ݲ������������д���������Աȣ����д��Ͷ����Ĳ�һ����ô��������
		FLASH_Program(APP_check_ADDRESS,&APP_check_value[0],4);
		if(boot_APP_check() == APP_INVALUE)
		{
			lin_tl_make_slaveres_pdu(SERVICE_EXIT_TRANSFER_DATA, NEGATIVE, INVALID_FORMAT);
	     	return;
		}
		lin_tl_make_slaveres_pdu(SERVICE_EXIT_TRANSFER_DATA, POSITIVE, RES_POSITIVE);
	}
	else
	{
		lin_tl_make_slaveres_pdu(SERVICE_EXIT_TRANSFER_DATA, NEGATIVE, INVALID_FORMAT);
	}
	
}








