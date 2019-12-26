
/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           api.c
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
    CPMUAPICTL_APIFE = 0;   //辅助时钟中断失能
    CPMUAPICTL_APICLK = 0;   //使用辅助时钟
    CPMUACLKTR = 0xfc;
    CPMUAPIR = 0x61A7 ;//0xc34f;      //0x1387;//0xFFFF; //停止模式下定时10s
    CPMUAPICTL_APIE = 1;      //打开API中断请求
    CPMUAPICTL_APIF = 1;     //清除定时溢出标志
    CPMUAPICTL_APIFE = 1;    //辅助时钟中断使能
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
    CPMUAPICTL_APIF = 1;  //清除定时溢出标志
    API_Disable();  
    API_10s_Flag = 1;
    API_wake_up_Flag = 1;
    G_600ms_counter = 0;
    G_600msFlag = 0;      
}
