
/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           api.c
** Last modified Date:  2017-12-19
** Last Version:        V1.00
** Descriptions:        ȫ�ֲ���������
**
**--------------------------------------------------------------------------------------------------------
** Created by:          xujun
** Created date:        2017-12-19
** Version:             V1.00
** Descriptions:        �����ļ�
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
#include "api.h"
#include "global_parameter.h"

unsigned char API_10s_Flag;
unsigned char API_wake_up_Flag;

/*******************************************************
 * FUNCTION NAME : API_init()
 *   DESCRIPTION : API_init function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void API_init(void)
{
    CPMUAPICTL_APIFE = 0;   //����ʱ���ж�ʧ��
    CPMUAPICTL_APICLK = 0;   //ʹ�ø���ʱ��
    CPMUACLKTR = 0xfc;
    CPMUAPIR = 0x61A7 ;//0xc34f;      //0x1387;//0xFFFF; //ֹͣģʽ�¶�ʱ10s
    CPMUAPICTL_APIE = 1;      //��API�ж�����
    CPMUAPICTL_APIF = 1;     //�����ʱ�����־
    CPMUAPICTL_APIFE = 1;    //����ʱ���ж�ʹ��
}
/*******************************************************
 * FUNCTION NAME : API_init()
 *   DESCRIPTION : API_init function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void API_Disable(void)
{
    CPMUAPICTL_APIFE = 0;
}
 
/*******************************************************
 * FUNCTION NAME : API_init()
 *   DESCRIPTION : API_init function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/ 
void interrupt VectorNumber_Vapi api(void) 
{
    CPMUAPICTL_APIF = 1;  //�����ʱ�����־
    API_Disable();  
    API_10s_Flag = 1;
    API_wake_up_Flag = 1;
    G_600ms_counter = 0;
    G_600msFlag = 0;      
}
