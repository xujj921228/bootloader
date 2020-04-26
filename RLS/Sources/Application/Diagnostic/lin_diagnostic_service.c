/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2015 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup diagnostic_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      lin_diagnostic_service.c
*
* @author    xujun
*
* @brief     Diagnostic Service slave functions
*
******************************************************************************/
/******************************************************************************
 *
 * History:
 *
 * 20090718     v1.0    First version
 * 20111005     v1.1    Updated diagnostics service
 *
 *****************************************************************************/

#include "lin_commontl_proto.h"
#include "lin_diagnostic_service.h"
#include "eeprom.h"
#include "local_eep_data.h"
extern  local_info_t local_info;

/* Define functionality */
#ifndef MULTI_PDU_SUPPORT
#define MULTI_PDU_SUPPORT 0                        /**< multi PDU support */
#endif /* End MULTI_PDU_SUPPORT */

/********------------- Code supports SINGLE interface ----------------**********/
#if LIN_MODE == _SLAVE_MODE_
/*************************** FUNCTIONS *******************/
/* Unuse for GPIO */
#if ( _LIN_GPIO_ == 0 ) && !defined(_MC9S08SC4_H) && !defined(MCU_SKEAZN84)
#if LIN_PROTOCOL == PROTOCOL_21


l_u8 diagnostic_Session,diagnostic_Session_pre,diagnostic_Session_flg;
l_u16 diagnostic_Session_timer;

void Diagnostic_Var_init(void)
{
	diagnostic_Session = DIAGSRV_SESSION_DEFAULT;
	diagnostic_Session_timer = 0 ;
	diagnostic_Session_flg = 0;	
}

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

/************************
 * For APP up close
 * 
 * xujunjie@baolong.com
 * ********************/
typedef void(*JumpToPtr)(void);

void boot_jump_to_APP(uint16 *address)
{
	uint16 *pNewAppEntry = address;
	JumpToPtr	pJumpTo;
	pJumpTo = (JumpToPtr)(*pNewAppEntry);
	pJumpTo();
	for(;;) { ; }
}

uint8 boot_up_ret[2];
uint8 boot_seed[4];
uint8 boot_key[4];

Boot_Fsm_t boot_status_flag;

#define  boot_up_value          0x5a

l_u8 lin_diagservice_session_control(void)
{
	l_u8 id;
	l_u16 supid, fid;
	lin_tl_pdu_data *lin_tl_pdu;

	/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
	l_u16 length;
	l_u8 data[10];
	/* get pdu from rx queue */
	ld_receive_message(&length, data+2);
	lin_tl_pdu = (lin_tl_pdu_data *)data;
#else /* Single frame support */
	lin_tl_pdu = tl_current_rx_pdu_ptr;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

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
                      if(boot_status_flag == boot_fsm_getkey)
                      {
                        do
                         {
                               boot_up_ret[0] = boot_up_value;
                               Write_App_value_flag(boot_up_ret);
                               boot_up_ret[0] = 0;
                               Read_App_value_flag(boot_up_ret);
                         }while(boot_up_ret[0] != boot_up_value);
                          boot_jump_to_APP((uint16 *)(0));
                      }
                      /* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_SESSION_CONTROL, NEGATIVE, SERVICE_NOT_SUPPORTED_ACTIVE_SESSION);
					diagnostic_Session = DIAGSRV_SESSION_DEFAULT ;
                                        
				}
				break;
			case DIAGSRV_SESSION_EXTERN:
                                boot_status_flag = boot_session_extern;
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




void uds_calc_key(uint8 *seed,uint8 *key)
{
     uint8 i;
     uint32 mask;

     uint32 wort;     
     
     mask = 0x7FADEBFC;
     
     wort = (((uint32)seed[0])<<24) + (((uint32)seed[0])<<16) + (((uint32)seed[0])<<8) + ((uint32)seed[0]);
         
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
     key[0] = (uint8)(wort >> 24);
     key[1] = (uint8)(wort >> 16);
     key[2] = (uint8)(wort >> 8);
     key[3] = (uint8)wort;
}


void lin_diagservice_service_securityaccess(void)
{
	 l_u16 length;
	 l_u8 data[10];
	 uint8 i; 
	 /* get pdu from rx queue */
	 ld_receive_message(&length, data);
	 
	 if((data[1] == 1)&&( boot_status_flag == boot_session_extern))
         //if(data[1] == 1)
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











void lin_diagservice_read_data_by_identifier(void)
{
    l_u16 id;
    l_u16 supid, fid;
    lin_tl_pdu_data *lin_tl_pdu;
    l_u16 temp ;

    /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    lin_tl_pdu = (lin_tl_pdu_data *)data;
#else /* Single frame support */
    lin_tl_pdu = tl_current_rx_pdu_ptr;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

    temp =  (*lin_tl_pdu)[3] ;
    id = ((temp << 8)|(*lin_tl_pdu)[4]);
    if(length >= 3)
    {
		switch (id)
		{
			case LIN_PRODUCT_SERIAL_NUMBER0:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_PRODUCT_SERIAL_NUMBER0&0xFF));
				break;
			case LIN_PRODUCT_SERIAL_NUMBER1:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_PRODUCT_SERIAL_NUMBER1&0xFF));
				break;
			case LIN_PRODUCT_SERIAL_NUMBER2:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_PRODUCT_SERIAL_NUMBER2&0xFF));
				break;
			case LIN_PRODUCT_SERIAL_NUMBER3:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_PRODUCT_SERIAL_NUMBER3&0xFF));
				break;				
			case LIN_LS_FW_PARAM:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_LS_FW_PARAM&0xFF));
				break;
							  
			case LIN_LS_IR_PARAM:
				lin_tl_make_slaveres_pdu(SERVICE_READ_DATA_BY_IDENTIFY, POSITIVE, (LIN_LS_IR_PARAM&0xFF));
				break;
				
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
	l_u16 supid, fid;
	lin_tl_pdu_data *lin_tl_pdu;
	l_u16 temp ;

	/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
	l_u16 length;
	l_u8 data[10];
	/* get pdu from rx queue */
	ld_receive_message(&length, data+2);
	lin_tl_pdu = (lin_tl_pdu_data *)data;
#else /* Single frame support */
	lin_tl_pdu = tl_current_rx_pdu_ptr;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

	temp =  (*lin_tl_pdu)[3] ;
	id = ((temp << 8)|(*lin_tl_pdu)[4]);

	if(length >= 3)
	{
		switch (id)
		{
			case LIN_PRODUCT_SERIAL_NUMBER0:
				if(length != 6)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{
					// important write_data_from_EEPROM need place before lin_tl_make_slaveres_pdu
                                        Set_Data_To_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,&(*lin_tl_pdu)[5],EEPROM_SERIAL_NUMBER_LENTH);
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE, (LIN_PRODUCT_SERIAL_NUMBER0&0xff));	
				}
						
				break;
			case LIN_PRODUCT_SERIAL_NUMBER1:
				if(length != 6)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{
					// important write_data_from_EEPROM need place before lin_tl_make_slaveres_pdu
                                        Set_Data_To_EEPROM(EEPROM_SERIAL_NUMBER1_ADDR,&(*lin_tl_pdu)[5],EEPROM_SERIAL_NUMBER_LENTH);
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE,  (LIN_PRODUCT_SERIAL_NUMBER1&0xff));	
				}
				break;
			case LIN_PRODUCT_SERIAL_NUMBER2:
				if(length != 6)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{
					// important write_data_from_EEPROM need place before lin_tl_make_slaveres_pdu
                                        Set_Data_To_EEPROM(EEPROM_SERIAL_NUMBER2_ADDR,&(*lin_tl_pdu)[5],EEPROM_SERIAL_NUMBER_LENTH);
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE,  (LIN_PRODUCT_SERIAL_NUMBER2&0xff));		
				}	
				break;
			case LIN_PRODUCT_SERIAL_NUMBER3:
				if(length != 6)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{
					// important write_data_from_EEPROM need place before lin_tl_make_slaveres_pdu
                                        Set_Data_To_EEPROM(EEPROM_SERIAL_NUMBER3_ADDR,&(*lin_tl_pdu)[5],EEPROM_SERIAL_NUMBER_LENTH);
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE,  (LIN_PRODUCT_SERIAL_NUMBER3&0xff));
				}
				break;
				
			case LIN_LS_FW_PARAM:
				
				if(length != 4)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{
                                        Set_Data_To_EEPROM(EEPROM_BR_LIG_PER_ADDR,&(*lin_tl_pdu)[5],EEPROM_BR_LIG_PER_LENTH);
					if((*lin_tl_pdu)[5] == 0xFF)
					{
						local_info.Brightness_Light_Percentage = 100;
					}
					else
					{
						local_info.Brightness_Light_Percentage = (*lin_tl_pdu)[5];
					}
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE, (LIN_LS_FW_PARAM&0xff));
				}
				break;
							  
			case LIN_LS_IR_PARAM:
				if(length != 4)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{
                                        Set_Data_To_EEPROM(EEPROM_IR_PER_ADDR,&(*lin_tl_pdu)[5],EEPROM_IR_PER_LENTH);
					if((*lin_tl_pdu)[5] == 0xFF)
					{
						local_info.Brightness_Infrared_Percentage = 100;
					}
					else
					{
						local_info.Brightness_Infrared_Percentage = (*lin_tl_pdu)[5];
					}
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, POSITIVE, (LIN_LS_IR_PARAM&0xff));
				}
			    break;
				
			case LIN_RAIN_ADC_A_PARAM:
				if(length != 5)
				{
					/* Make a negative slave response PDU */
					lin_tl_make_slaveres_pdu(SERVICE_WRITE_DATA_BY_IDENTIFY, NEGATIVE, INVALID_FORMAT);
				}
				else
				{
                                        Set_Data_To_EEPROM(EEPROM_A_RAIN_ADC_ADDR,&(*lin_tl_pdu)[5],EEPROM_A_RAIN_ADC_LENTH);				
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
                                        Set_Data_To_EEPROM(EEPROM_B_RAIN_ADC_ADDR,&(*lin_tl_pdu)[5],EEPROM_B_RAIN_ADC_LENTH);				
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
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    lin_tl_pdu = (lin_tl_pdu_data *)data;
#else /* Single frame support */
    lin_tl_pdu = tl_current_rx_pdu_ptr;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
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
    l_u16 supid, fid;
    lin_tl_pdu_data *lin_tl_pdu;

    /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data+2);
    lin_tl_pdu = (lin_tl_pdu_data *)data;
#else /* Single frame support */
    lin_tl_pdu = tl_current_rx_pdu_ptr;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

#if 0
    /* Get supplier and function indentification in request */
    supid = (l_u16)(((*lin_tl_pdu)[5]) << 8);
    supid = supid |(l_u16)((*lin_tl_pdu)[4]);

    fid = (l_u16)(((*lin_tl_pdu)[7]) << 8);
    fid = fid |(l_u16)((*lin_tl_pdu)[6]);

    
    /* Check Supplier ID and Function ID */
    if (((supid != product_id.supplier_id) && (supid != LD_ANY_SUPPLIER)) || \
            ((fid != product_id.function_id) && (fid != LD_ANY_FUNCTION)))
    {
        tl_slaveresp_cnt = 0;
    #if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
        tl_service_status = LD_SERVICE_IDLE;
    #endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
        return;
    }
#endif
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
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    id      = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][3];
    byte    = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][4];
    mask    = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][5];
    invert  = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][6];
#else /* Single frame support */
    id      = (*tl_current_rx_pdu_ptr)[3];
    byte    = (*tl_current_rx_pdu_ptr)[4];
    mask    = (*tl_current_rx_pdu_ptr)[5];
    invert  = (*tl_current_rx_pdu_ptr)[6];
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

    /* Possible positive ID */
    if (id == 0)
    {
        /* Do a bitwise XOR with Invert and Do a bitwise AND with Mask */
        byte = (byte^invert)&mask;
        if (byte == 0)
        {
            /* If the final result is zero then change the NAD to New NAD */
        #if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
            lin_configured_NAD = lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][7];
        #else/* Single frame support */
            lin_configured_NAD = (*tl_current_rx_pdu_ptr)[7];
        #endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
        }
        lin_tl_make_slaveres_pdu(SERVICE_CONDITIONAL_CHANGE_NAD, POSITIVE, 0);
    }
}
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
#endif /* End ( _LIN_GPIO_ == 0 ) && !defined(_MC9S08SC4_H) */


#if LIN_PROTOCOL == PROTOCOL_21
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
void lin_diagsrv_functional_service(void)
{
    l_u16 length;
    l_u8 data[10];
    /* get pdu from rx queue */
    ld_receive_message(&length, data);

    /* do something here */
}
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */

#if LIN_PROTOCOL == PROTOCOL_J2602
void lin_diagservice_target_reset()
{
    l_u8 *signal_data_ptr;
    l_u8 nad;
    lin_tl_pdu_data *lin_tl_pdu;
    /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    lin_tl_pdu = (lin_tl_pdu_data *)&lin_lld_response_buffer[1];
#else /* Single frame support */
    lin_tl_pdu = tl_current_rx_pdu_ptr;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
    /* Set the reset flag within the J2602 Status Byte */
    /* Set error signal equal to error in response */
    lin_pFrameBuf[response_error_byte_offset] = (lin_pFrameBuf[response_error_byte_offset] &
                                                (~(0x07 << response_error_bit_offset))) |
                                                (0x01 << response_error_bit_offset);

    /* Create positive response */

    /* Get NAD of node */
    nad = (*lin_tl_pdu)[0];

    if (LD_BROADCAST != nad)
    {
        lin_tl_make_slaveres_pdu(SERVICE_TARGET_RESET, POSITIVE, 0);
    }
    else
    {
        tl_slaveresp_cnt = 0;
    }
}
#endif /* End (LIN_PROTOCOL == PROTOCOL_J2602) */

#endif /* End (LIN_MODE == _SLAVE_MODE_) */
/********------------ End of code for SINGLE Interface --------------**********/


/********------------- Code supports Multi interface ----------------**********/
#if LIN_MODE == _MASTER_MODE_
/*************************** FUNCTIONS *******************/


#if LIN_PROTOCOL == PROTOCOL_21

void lin_diagservice_assign_frame_id_range
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    const lin_configuration* conf;
    l_s8 j, i = 0;
    l_u8 start_index;
    l_u8 cfg_frame_num = 0;
    lin_tl_pdu_data *lin_tl_pdu;
    /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    l_u16 length;
    l_u8 NAD, data[10];
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
    /* Get current configuration */
    conf = &lin_ifc_configuration[iii];
    /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    /* receive message data */
    ld_receive_message(iii, &length, &NAD, data+2);

    lin_tl_pdu = (lin_tl_pdu_data *)data;
#else /* Single frame support */
    /* Get current PDU pointer of RX queue */
    lin_tl_pdu = (lin_tl_pdu_data *)&conf->response_buffer[1];
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

    /* Get start index in request */
    start_index = (*lin_tl_pdu)[3];

    /* Find the number of configurable frame */
    i = 1;
    while (0xFFFF != (conf->configuration_ROM)[i])
    {
        i++;
        cfg_frame_num++;
    }
    /* Check request validity */
    for (i = 7, j = start_index+4; j > start_index; i--, j-- )
    {
        if ((0xFF != (*lin_tl_pdu)[i]) && (j > cfg_frame_num))
        {
            lin_tl_make_slaveres_pdu(iii, SERVICE_ASSIGN_FRAME_ID_RANGE, NEGATIVE, GENERAL_REJECT);
            return;
        }
    }

    /* Store PIDs */
    for (i = 4, j = 1; i < 8; i++, j++)
    {
        switch ((*lin_tl_pdu)[i])
        {
            case 0x00:
                /* Unassign frame */
                (conf->configuration_RAM)[start_index + j] = 0xFF;
                break;

            case 0xFF:
                /* keep the previous assigned value of this frame */
                break;

            default:
                /* Calculate frame ID and Assign ID to frame */
                (conf->configuration_RAM)[start_index + j] = lin_process_parity((*lin_tl_pdu)[i], CHECK_PARITY);
                break;
        }
    } /* End of for statement */
    lin_tl_make_slaveres_pdu(iii, SERVICE_ASSIGN_FRAME_ID_RANGE, POSITIVE, 0);
}


void lin_diagservice_read_by_identifier
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    const lin_configuration* conf;
    const lin_node_attribute* node_conf;
    lin_product_id  ident;
    lin_tl_descriptor *tl_conf;
    lin_tl_pdu_data *lin_tl_pdu;
    l_u8 id;
    l_u16 supid, fid;
    /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    lin_tl_pdu_data pdu_data;
    l_u16 length;
    l_u8 NAD, data[10];
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

    /* Get current configuration */
    conf = &lin_ifc_configuration[iii];

    /* Get TL description */
    tl_conf = conf->tl_desc;

    /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    lin_tl_pdu = (lin_tl_pdu_data *)&pdu_data;
    /* receive message data */
    ld_receive_message(iii, &length, &NAD, data+2);

    lin_tl_pdu = (lin_tl_pdu_data *)data;
#else /* Single frame support */
    lin_tl_pdu = (lin_tl_pdu_data *)&conf->response_buffer[1];
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

    /* Get current PDU pointer of RX queue */


    /* Get the node attribute */
    node_conf = conf->node_attribute;

    /* Get the product identification */
    ident = node_conf->product_id;

    /* Get supplier and function indentification in request */
    supid = (l_u16)(((*lin_tl_pdu)[5]) << 8);
    supid = supid |(l_u16)((*lin_tl_pdu)[4]);

    fid = (l_u16)(((*lin_tl_pdu)[7]) << 8);
    fid = fid |(l_u16)((*lin_tl_pdu)[6]);


    /* Check Supplier ID and Function ID */
    if (((supid != ident.supplier_id) && (supid != LD_ANY_SUPPLIER)) || \
            ((fid != ident.function_id) && (fid != LD_ANY_FUNCTION)))
    {
        tl_conf->tl_slaveresp_cnt = 0;
        return;
    }

    /* Get the identifier of request */
    id = (*lin_tl_pdu)[3];

    switch (id)
    {
        case LIN_PRODUCT_IDENT:
            lin_tl_make_slaveres_pdu(iii, SERVICE_READ_BY_IDENTIFY, POSITIVE, 0);
            break;

        default:
            if (id >= LIN_READ_USR_DEF_MIN && id <= LIN_READ_USR_DEF_MAX)
            {
                /* Make a positive slave response PDU */
                lin_tl_make_slaveres_pdu(iii, SERVICE_READ_BY_IDENTIFY, POSITIVE, id);
            }
            else
            {
                /* Make a negative slave response PDU */
                lin_tl_make_slaveres_pdu(iii, SERVICE_READ_BY_IDENTIFY, NEGATIVE, SUBFUNCTION_NOT_SUPPORTED);
            }
            break;
    } /* end of switch */
}
/*FUNCTION**********************************************************************
 *
 * Function Name : lin_condittional_change_nad
 * Description   :
 *
 *END**************************************************************************/
void lin_condittional_change_nad(l_ifc_handle iii)
{
    l_u8 id, byte, mask, invert;
    const lin_configuration* conf;
    lin_node_attribute* node_conf;
    lin_tl_descriptor *tl_conf;
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    lin_transport_layer_queue *rx_queue;
#else /* Single frame support */
    lin_tl_pdu_data *lin_tl_pdu;
#endif
    /* Get current configuration */
    conf = &lin_ifc_configuration[iii];

    /* Get TL description */
    tl_conf = conf->tl_desc;
    /* Get the node attribute */
    node_conf = conf->node_attribute;

#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
    /* Get receive queue */
    rx_queue = tl_conf->tl_rx_queue;
    id = rx_queue->tl_pdu[rx_queue->queue_header][3];
    byte = rx_queue->tl_pdu[rx_queue->queue_header][4];
    mask = rx_queue->tl_pdu[rx_queue->queue_header][5];
    invert = rx_queue->tl_pdu[rx_queue->queue_header][6];
#else /* Single frame support */
    /* Get current PDU pointer of RX buffer */
    lin_tl_pdu = tl_conf->tl_current_rx_pdu_ptr;
    id         = (*lin_tl_pdu)[3];
    byte     = (*lin_tl_pdu)[4];
    mask      = (*lin_tl_pdu)[5];
    invert     = (*lin_tl_pdu)[6];
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */


    /* Possible positive ID */
    if (id == 0)
    {
        /* Do a bitwise XOR with Invert and Do a bitwise AND with Mask */
        byte = (byte^invert)&mask;
        if (byte == 0)
        {
            /* If the final result is zero then change the NAD to New NAD */
        #if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
            node_conf->configured_NAD = rx_queue->tl_pdu[rx_queue->queue_header][7];
        #else/* Single frame support */
            node_conf->configured_NAD = (*lin_tl_pdu)[7];
        #endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
        }
        lin_tl_make_slaveres_pdu(iii, SERVICE_CONDITIONAL_CHANGE_NAD, POSITIVE, 0);
    }
}
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */

#if LIN_PROTOCOL == PROTOCOL_J2602
void lin_diagservice_target_reset
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    const lin_configuration *conf;
    lin_tl_descriptor *tl_conf;
    lin_tl_pdu_data *pdu;
    l_u8 byte_offset_temp, bit_offset_temp;
    l_u8 nad;

    /* Get current configuration */
    conf = &lin_ifc_configuration[iii];

    /* Get TL configuration */
    tl_conf = conf->tl_desc;

    /* Get PDU from RX queue */

    /* Get current PDU pointer of RX queue */
    pdu = (lin_tl_pdu_data *)&conf->response_buffer[1];

    /* Set the reset flag within the J2602 Status Byte */
    byte_offset_temp = conf->node_attribute->response_error_byte_offset;
    bit_offset_temp = conf->node_attribute->response_error_bit_offset;

    /* Set error signal equal to error in response */
    lin_pFrameBuf[byte_offset_temp] = (lin_pFrameBuf[byte_offset_temp] &
                                        (~(0x07 << bit_offset_temp))) |
                                        (0x01 << bit_offset_temp);
    /* Create positive response */

    /* Get NAD of node */
    nad = (*pdu)[0];

    if (LD_BROADCAST != nad)
    {
        lin_tl_make_slaveres_pdu(iii, SERVICE_TARGET_RESET, POSITIVE, 0);
    }
    else
    {
        tl_conf->tl_slaveresp_cnt = 0;
    }
}
#endif /* End (LIN_PROTOCOL == PROTOCOL_J2602) */
#endif  /* End (LIN_MODE == _MASTER_MODE_) */
/* ---------------- End of code for Multi Interface ----------------- */
/**
 * @}
 */
