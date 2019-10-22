/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      adc.h 
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
#ifndef    _LIN_APP_H_  
#define    _LIN_APP_H_  

#include "config_parameter.h"



struct BCM_01_Frame 
{
  
	uint8  Ignition          :2;
	uint8  Status_SMA        :2;
	uint8  S_Wash			 :1;
	uint8  SCS_Automatic     :1;
	uint8  S_High			 :1;
	uint8  S_LOW			 :1;
	uint8  rsv0				 :1;
	
	uint8  rsv1				 :4;
	uint8  S_SENS_Vaild		 :1;
	uint8  S_Sens			 :3;
 
	uint8  S_Trans_550nm	 :8;
	uint8  S_Trans_880nm	 :8;
};

struct BCM_02_Frame 
{
	uint8   ParkPosition      :1;
	uint8   S_Wash_Mode		  :1;
	uint8   rsv0              :1;
	uint16  SPD_Vehicle       :13;
};


extern uint8 Lin_Busy_Flag;
extern uint8 Enter_Sleep_Flag;

extern struct BCM_01_Frame         Lin_BCM_WIPSW;
extern struct BCM_02_Frame         Lin_BCM_MOTOR;


extern void Lin_Sys_Init(void);
extern void Lin_Busy_Process(void);
extern void message_cnt(void);
extern void RLS_Analysis_Master_Data(void);
extern void Lin_RLS_data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);

#endif    /* _ADC_H_ */
