/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
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
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "global_parameter.h"
#include "clock.h"
#include "TIM.h"
#include "gpio.h"
#include "sci.h"
#include "lin_app.h"
#include "rls_app.h"
#include "IIC.h"
#include "humid.h"
#include "HCS12EEPROM.h"

/*******************************************************
 * FUNCTION NAME : main()
 *   DESCRIPTION : main function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void main(void) 
{
  /* put your own code here */
    MCU_CLOCK_Init();
    TIM_Init();
    GPIO_Init();
    HCS12_EE_Init(); 
    global_parameter_init(); 
    Lin_Prameter_Init();
    MLX75308_Init();
    SCI_Init();
    ADC_Init();
    #ifdef FOUR_TO_ONE
           DRV_IIC_Init();
    #endif
    
  	EnableInterrupts;
  	
    while(!DR);
    
    Lin_RLS_Frame.Light_ready = 1;
    
    for(;;) 
    {
        _FEED_COP(); /* feeds the dog */
    
    #ifdef ROOF_FUNCTION_ENABLE
    
        RLS_Roof_Task();
        
    #endif 
        
    #ifdef SLEEP_ENABLE
    
	    if(G_4sFlag == 1)
  		{
			G_4sFlag = 0;

			Sleep_Process();
			Recover_Process();
  		}
  		
  		if(u8_lin_cmd_sleep_flg == 1)
  		{
  	     	u8_lin_cmd_sleep_flg = 0;
  		    Sleep_Process();
  		    Recover_Process();
  		}
  		
    #endif  
   
        switch(RLS_RunMode)
        {
          case NORMAL:
          {
              if( G_10msFlag == TRUE)
              {
                  G_10msFlag = FALSE;
              }
              
              if( G_20msFlag == TRUE)
              {
                  G_20msFlag = FALSE;                  
              }

              if( G_50msFlag == TRUE)
              {
                  G_50msFlag = FALSE;
                  RLS_Battery_State(); 
                  RLS_Lin_Diag_Fucntion();               
              }

              if( G_100msFlag == TRUE)
              {
                  G_100msFlag = FALSE;  
                  
                  RLS_Auto_Light_Task();
                  RLS_Auto_Rain_Task();
                  Lin_RLS_data();
              }
              
              if( G_500msFlag == TRUE)
              {
                  G_500msFlag = FALSE;
                  #ifdef FOUR_TO_ONE 
                        FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
                        Humid_Avg_Function(); 
                        Temp_Avg_Function() ; 
                  #endif
               }
          } break;
          
          case SLEFADAPT:
          {
              RLS_SelfAdaptTask();
              #ifdef FOUR_TO_ONE
                    FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
                    Humid_Avg_Function(); 
                    Temp_Avg_Function() ;
              #endif
          }break;
          default: 
               RLS_RunMode = NORMAL; 
               break;
        }
    } /* loop forever */
    /* please make sure that you never leave main */
}
