
/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           sci.c
** Last modified Date:  2017-12-19
** Last Version:        V1.00
** Descriptions:        全局参数声明。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          xujun
** Created date:        2017-12-19
** Version:             V1.00
** Descriptions:        创建文件
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"
#include "sci.h"
#include "gpio.h" /* include peripheral declarations */
#include "lin_app.h"
#include "rls_app.h"
#include "api.h"

/*******************************************************
 * FUNCTION NAME : SCI_Init()
 *   DESCRIPTION : init sci reg
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/

void SCI_Init(void)
{
    uint16 sbr;
    //  Calculates SCI Baud rate value
    SCI0SR2 = 0;
    sbr = (SCI_CLOCK / SCI_BAUDRATE / 16);
    SCI0BDH  = (uint8)(sbr >> 8);
    SCI0BDL  = (uint8)sbr;
    SCI0SR2  = 0x80;
    SCI0ACR2 = 0x04;   //Enable bit error detect circuit
    SCI0CR2  = 0x2C;   //RIE = 1, Enable Recieve intterupt ,TE = 1 Enable TXD, RE = 1 Enable RXD 
    SCI0SR2  = 0x84;   //Clear LBKDIF, RXEDGIF, Break character is 13 or 14 bit long (发送使用)  

    if((SCI0ASR1 & 0x02))
    {
        SCI0ASR1 = SCI0ASR1 | 0x02;
    }
}


/*******************************************************
 * FUNCTION NAME : SCI1_RX()
 *   DESCRIPTION : sci receive interrupt 
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/

void interrupt VectorNumber_Vsci0 SCI1_RX(void) 
{
    LIN_EN = 1;
    

	CPMUAPICTL_APIF = 1;  //清除定时溢出标志
	API_Disable();
	API_wake_up_Flag = 0;
	API_6h_Cnt = 0; 
	API_10s_Flag = 0;
	G_600msFlag = 0;
    G_600ms_counter = 0;
    
    u8_receive_data_flg = 1;
      
#ifdef SLEEP_ENABLE
    G_4sFlag = 0;       //当接收到外界中断时则清除4s标志
    G_4s_counter = 0;   //当接收到外界中断时则清除4s计数
	SCI0SR2 = 0x84;  // SCI0ASR1: RXEDGIF=1,BERRV=0,BERRIF=1,BKDIF=1 **
	SCI0ASR1 = 0x83;  //
#endif

    if(!Lin_TransStatus()) 
    {   
        u8_LinErrorCnt++;
        if(u8_LinErrorCnt >= 3)
        {
            u8_LinErrorCnt = 0;
            rx.state = IDLE;

            if(u8_Lin_Diag_Enable == 1)
            {                
                rx.error = 1;
                Lin_RLS_Frame.REP_Error = 1;
                
                msg_send.data_field[2] |= (Lin_RLS_Frame.REP_Error << 3);
            }
            else
            {
                msg_send.data_field[2] = (msg_send.data_field[2] & 0xF7);
            }
        }

    }    
}



