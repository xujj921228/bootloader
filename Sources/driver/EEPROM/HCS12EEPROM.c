/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           eeprom.c
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

#include "derivative.h" /* include peripheral declarations */
#include <hidef.h> /* for EnableInterrupts macro */
#include "HCS12EEPROM.h"
#include "global_parameter.h"

/*******************************************************
 * FUNCTION NAME : HCS12_EE_Init()
 *   DESCRIPTION : init EEPROM reg
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
 
void HCS12_EE_Init(void) 
{
  while(!FSTAT_CCIF)  ;
  
  if(FCLKDIV_FDIVLD == 0) 
  {
     FCLKDIV_FDIV = (uint8)((SCI_CLOCK/1000000) - 1); //16000000/1000000 - 1 = 15(0x0f)
    // FCLKDIV_FDIVLCK = 1;       //lock
  }
}

/*******************************************************
 * FUNCTION NAME : HCS12_EE_Cmd()
 *   DESCRIPTION : 
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
 
void HCS12_EE_Cmd(uint16 EEPROM_ADDR,uint8 Cmd,uint16 index,uint16 *data,uint8 n)   //0x400-0x7FF
{
     uint16 EE_ADDRESS;
     uint8 i = 0;
     
     EE_ADDRESS = index + EEPROM_ADDR;
     
     while(!FSTAT_CCIF);
     
     if(FSTAT_ACCERR) FSTAT_ACCERR = 1;
     
     if(FSTAT_FPVIOL) FSTAT_FPVIOL = 1;
     
     FCCOBIX = 0;
     FCCOBHI = Cmd;
     FCCOBLO = 0;
     
     FCCOBIX = 1;
     FCCOB = EE_ADDRESS;
          
     if(n > 0) 
     {      
         for(i = 0;i < n;i++)
         {
            FCCOBIX = i + 2;
            FCCOB = *(data + i);
         }
     }

     FSTAT_CCIF = 1; 
     while(!FSTAT_CCIF); 
     
}

/*******************************************************
 * FUNCTION NAME : HCS12_EE_Write_2Word()
 *   DESCRIPTION : 
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void HCS12_EE_Write_2Word(uint16 EEPROM_ADDR,uint16 *data) //Write 2 Word
{    

   DisableInterrupts;
   EE_Erase_Section(EEPROM_ADDR,0);
   HCS12_EE_Cmd(EEPROM_ADDR,Cmd_EEProgram,0,data,2);
   EnableInterrupts;

}

/*******************************************************
 * FUNCTION NAME : HCS12_EE_Read_2Word()
 *   DESCRIPTION : 
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void HCS12_EE_Read_2Word(uint16 EEPROM_ADDR,uint16 *data)
{
     *data = EE_Byte_Read(EEPROM_ADDR,0);
     *(data + 1) = EE_Byte_Read(EEPROM_ADDR,1); 
}
/*******************************************************
 * FUNCTION NAME : EE_Erase_Section()
 *   DESCRIPTION : 
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void EE_Erase_Section(uint16 EEPROM_ADDR,uint16 index)
{     
     HCS12_EE_Cmd(EEPROM_ADDR,Cmd_Erase_Section,index,NULL,0);
}
/*******************************************************
 * FUNCTION NAME : EE_Byte_Read()
 *   DESCRIPTION : 
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/

uint16 EE_Byte_Read(uint16 EEPROM_ADDR,uint16 index) 
{ 
    while(!FSTAT_CCIF);
    return *((uint16 *)((index << 1) + EEPROM_ADDR)); 
} 
