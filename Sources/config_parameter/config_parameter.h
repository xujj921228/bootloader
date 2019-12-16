/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      _CONFIG_PARAMETER.h 
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


#define  ENABLE_INTERRUPT  asm("CPSIE i");
#define  DISABLE_INTERRUPT asm("CPSID i");
/*
typedef  unsigned char   uint8;      //unsigned 8 bit definition
typedef  unsigned int    uint16;     //unsigned 16 bit definition
typedef  unsigned long   uint32;     //unsigned 32 bit definition
*/
#define TRUE  1
  /*!< Definitioni for TRUE. */
#define FALSE 0


#define EEPROM_BOOT_REFRESH             0x10000020

#define EEPROM_BOOT_REFRESH_LENTH        2

