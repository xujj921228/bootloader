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
	MAIN_SLEEP_Mode
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

 
 
 
 
//#define FOUR_TO_ONE
#define ENABLE_AUTO_ROOF  //使能自动开天窗功能
#define ENABLE_SOLAR

#define  ENABLE_INTERRUPT  asm("CPSIE i");
#define  DISABLE_INTERRUPT asm("CPSID i");


 
#define MEAS_NUM 3

#define   AVG_N  2

 
 

/************DC_COMP***********/
#define   DtABS_MAX    5000


/************ADAPT******************/
#define   CALI_PARAM_HIGH        45500
#define   CALI_PARAM_LOW         44500
#define   ADAPT_MEAS_CNT             3
#define   ADAPT_VALUE_DAC_LOW     0x10
#define   ADAPT_VALUE_DAC_HIGH    0xF0






extern void Globle_parameter_Init(void);
#endif    /* _ADC_H_ */
