/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      clock.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Sat Aug 04 10:53:51 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#define   BUS_CLCOK 20000000

typedef  unsigned char   uint8;      //unsigned 8 bit definition
typedef  unsigned int    uint16;     //unsigned 16 bit definition
typedef  unsigned long   uint32;     //unsigned 32 bit definition

extern void Clk_Init(void);
//extern void Delay_Nus(uint8 n);
//extern void Delay_Ms(uint16 Ms);
