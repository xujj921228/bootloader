/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           clock.c
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
#include "clock.h"

/*******************************************************
 * FUNCTION NAME : MCU_CLOCK_Init()
 *   DESCRIPTION : init CLOCK reg
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : set MCU CLK:32MHz VCO, 32MHz PLL, 16MHz Bus clk, 1MHz internal clk
 *******************************************************/
void MCU_CLOCK_Init(void) 
{
  
  
   CPMUOSC_OSCE = 0;         // fREF = fIRC1M= 1MHz
   
   CPMUSYNR = 0x0f;         //fvco=2*fREF*(SYNDIV+1)=2*1MHz*(15+1)=32MHz
                            //VCOFRQ[1:0] = 0, 32MHz<=fvco<=48MHz
                            //SYNDIV[5:0] = 15
                            
   CPMUREFDIV_REFFRQ = 0;   // 1MHz<=fREF<=2MHz
   
   CPMUPOSTDIV = 0;         //fPLL=fvco/(POSTDIV + 1) = 32MHz/(0 + 1) = 32MHz
                                                  
   while(!CPMUFLG_LOCK)
   {
      ;                    //  Wait for VCO to stabilize                    
   }			 
 
   CPMUCLKS_PLLSEL = 1; // Switch clk to use PLL,fbus=fPLL/2=16MHz                    
   
}

/*************************************************************/
/*                        初始化看门狗                       */
/*************************************************************/
void COP_Init(void)
{
    CPMUCOP |= 0x05;     //设置看门狗复位间隔为4s
}

/*******************************************************
 * FUNCTION NAME : Delay_Ms()
 *   DESCRIPTION : Delay function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : 
 *******************************************************/
void Delay_Ms(uint16 Ms)
{
	 uint16 i;
	 uint16 j;
	 
	 for(i=0; i<Ms; i++)
	 {
	 	  for(j=0; j<(2700); j++)      //BUS CLOCK = 32MHz
	 	  {
	 	 	   ;
	 	  }
	 }
}

/*******************************************************
 * FUNCTION NAME : Delay_Nus()
 *   DESCRIPTION : Delay function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : 
 *******************************************************/
void Delay_Nus(uint8 n) //1us
{
   uint8 i;
   for(i=0; i<n; i++)
   asm nop ;
}
