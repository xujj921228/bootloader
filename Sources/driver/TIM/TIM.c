/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           tim.c
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
#include "TIM.h"
#include "lin_app.h"

uint8  G_10ms_counter = FALSE;
uint8  G_20ms_counter = FALSE;
uint8  G_50ms_counter = FALSE;
uint8  G_100ms_counter = FALSE;
uint8  G_500ms_counter = FALSE;
uint8  G_600ms_counter = FALSE;
uint8  G_150ms_counter = FALSE;

uint8  G_10msFlag = FALSE;
uint8  G_20msFlag = FALSE;
uint8  G_50msFlag = FALSE;
uint8  G_100msFlag = FALSE;
uint8  G_500msFlag = FALSE;
uint8  G_600msFlag = FALSE;
uint8  G_150msFlag = FALSE;



uint8   G_4sFlag = 0;
uint16  G_4s_counter = 0;


/*******************************************************
 * FUNCTION NAME : TIM_Init()
 *   DESCRIPTION : init TIM reg
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
  
void TIM_Init(void)
{
      OCPD_OCPD4 = 1;
      TSCR1_TEN = 0;                      // Disable Timer module before adjusting registers.
      TIOS_IOS4 = 1;                      // Set Channel 0 as output compare.
      TCTL1_OM4 = 0;                      // Set channel 0 to toggle when a Timer match occurs.
      TCTL1_OL4 = 1;                      // Set channel 0 to toggle when a Timer match occurs.
      TC4 = 0x61A8;//TIM0_VOF_TIME * TIM0_CLK/128; //0x61A8; // Set a value for channel 0 timer compare. 
      TIE_C4I = 1;                        // Enable channel 0 interrupt， handled by function TIM0ISR.
      TSCR1_TSWAI = 1;                    // Disables the timer module while in wait mode.
      TSCR1_TSFRZ = 1;                    //Disables the timer counter while in freeze mode.
      TSCR2_PR = 0x7;                     // Set prescaler to divide by 128 
      
      /********ch5*******************/
      
      OCPD_OCPD0 = 1;
      TIOS_IOS0 = 1;                      // Set Channel 0 as output compare.
      TCTL2_OM0 = 0;                      // Set channel 0 to toggle when a Timer match occurs.
      TCTL2_OL0 = 1;                      // Set channel 0 to toggle when a Timer match occurs.
      TC0 = 1250;//TIM0_VOF_TIME * TIM0_CLK/128; //0x61A8; // Set a value for channel 0 timer compare. 
      TIE_C0I = 1;                        // Enable channel 0 interrupt， handled by function TIM0ISR.
      TSCR1_TSWAI = 1;                    // Disables the timer module while in wait mode.
      TSCR1_TSFRZ = 1;                    //Disables the timer counter while in freeze mode.
      TSCR2_PR = 0x7;                     // Set prescaler to divide by 128 
      TSCR1_TEN = 1;                      // Timer Enable
      //中断周期：1250*128/16MHz = 10ms                
}


/*******************************************************
 * FUNCTION NAME : TIM4_ISR()
 *   DESCRIPTION : tim4 interrupt function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void interrupt VectorNumber_Vtimch4 TIM4_ISR(void)
{         
     TC4 = 0x61A8+TCNT;
     
     if(Diagnostic_Extended_En == TRUE) 
     {        //Diagnostic进入扩展模式
        if(Diagnostic_6s_cnt == 30) 
        {
            Diagnostic_Extended_En = FALSE;
            Diagnostic_6s_cnt = 0;
            Diagnostic_R.state = 0;
        }
        else  Diagnostic_6s_cnt++;
     }
     
     
     if(Diagnostic_KEY_Locked == TRUE) 
     {          //Diagnostic KEY has locked
      
        if(Diagnostic_2s_cnt < 10)
        {        
            Diagnostic_2s_cnt++;
        }
        else if(Diagnostic_2s_cnt == 10) 
        {
            Diagnostic_KEY_Locked = FALSE;
            if(Diagnostic_R.state == 4) Diagnostic_R.state = 1;
            Diagnostic_2s_cnt++;
        }
        else  
        {
             if(Diagnostic_60s_cnt == 300) 
             {
                Diagnostic_60s_cnt = 0;
                Diagnostic_KEY_Locked = FALSE;
                Diagnostic_Key_Wrong_Num = 0;
                if(Diagnostic_R.state == 4) Diagnostic_R.state = 1;
             }
             else 
             {
                Diagnostic_60s_cnt++;
             }
         
        }
     }     
     TFLG1 = TFLG1_C4F_MASK;
}


/*******************************************************
 * FUNCTION NAME : TIM0_ISR()
 *   DESCRIPTION : tim0 interrupt function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
 
void interrupt VectorNumber_Vtimch0 TIM0_ISR(void)  //10ms
{
     TC0 = 1250 + TCNT;
     TFLG1 |= TFLG1_C0F_MASK; /* Clear channel 0 flag. */
     
    G_10ms_counter++;
    G_20ms_counter++;
    G_50ms_counter++;
    G_100ms_counter++;
    G_500ms_counter++;
    G_4s_counter++;
    G_150ms_counter++;
    G_600ms_counter++;
    
    if(G_4s_counter >= 400) //4s
    {
        G_4s_counter = 0;
        G_4sFlag = 1;
    }
     
    if(G_10ms_counter >= 1)
    {
        G_10ms_counter = 0;
        G_10msFlag = 1;
    }
    
    if(G_20ms_counter >= 2)
    {
        G_20ms_counter = 0;
        G_20msFlag = 1;  
    }
    
    if(G_50ms_counter >= 5)
    {
        G_50ms_counter = 0;
        G_50msFlag = 1;
    }
    
    if(G_100ms_counter >= 10)
    {
        G_100ms_counter = 0;
        G_100msFlag = 1;     
    }
    
    if(G_150ms_counter>= 15)
    {
        G_150ms_counter=0;
        G_150msFlag=1;    
    }
    
    if(G_500ms_counter>= 50)
    {
        G_500ms_counter=0;
        G_500msFlag=1;    
    } 
    
    if(G_600ms_counter>= 50)
    {
        G_600ms_counter=0;
        G_600msFlag=1;    
    }   
}


