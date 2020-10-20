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
* @author    xujun
*  
* @version   1.0 
*  
* @date      Sat Aug 04 10:53:51 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _CONFIG_PARAMETER_H_  
#define    _CONFIG_PARAMETER_H_  

#include "derivative.h" /* include peripheral declarations */


typedef enum
{
	MAIN_SLEFADAPT = 0,
	MAIN_NORMAL = 1,
	MAIN_SLEEP_Mode = 2
}Main_Fsm_t;


 typedef enum
 {
      FALSE = 0,
      TRUE = 1
 }bool_t;

 typedef unsigned char   uint8;      /* unsigned 8 bit definition */
 typedef unsigned short  uint16;     /* unsigned 16 bit definition */
 typedef unsigned long   uint32;     /* unsigned 32 bit definition */
 typedef signed char     int8;       /* signed 8 bit definition */
 typedef short           int16;      /* signed 16 bit definition */
 typedef long int        int2;      /* signed 32 bit definition */
 typedef void(*pt2Func)(void);		  /* Pointer to Functions, void argument */
 typedef void(*pt2FuncU8)(uint8);	  /* Pointer to Functions, UINT8 argument */

 
 
#define ENABLE_SOLAR

#define  ENABLE_INTERRUPT  asm("CPSIE i");
#define  DISABLE_INTERRUPT asm("CPSID i");

 

/************DC_COMP***********/
#define   DtABS_MAX    5000








extern void Globle_Eep_parameter_Init(void);
#endif    /* _ADC_H_ */
