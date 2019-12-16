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
  uint8  rsv0              :4;
  uint8  Ignition          :1;
  uint8  Status_SMA        :3;
  
  uint8  SCS_IntervalLevel :4;
  uint8  SCS_Automatic     :1;
  uint8  rsv2              :3;
  
  
  uint8  SCS_FrontWash     :1;
  uint8  rsv3              :7;
  
  uint8  rsv5  ;
  
  uint8  SPD_Vehicle        :8;
  
  uint8  rsv6  ;
  
  uint8  LS_Sensitivity     :3;
  uint8  RS_Deactivation    :1;
  uint8  RS_Sensitivity     :3;
  uint8  rsv7               :1;
};

struct BCM_02_Frame 
{
  uint8	Wiper_running      :1;
  uint8 rsv0               :1;
  uint8 BladesTurningPoint :1;
  uint8 ParkPosition       :1;
  uint8 rsv1               :4;
};


extern uint8 Lin_Busy_Flag;
extern uint8 Enter_Sleep_Flag;

extern struct BCM_01_Frame         Lin_BCM_01_Frame;
extern struct BCM_02_Frame         Lin_BCM_02_Frame;

extern void Lin_Busy_Process(void);
extern void message_cnt(void);
extern void RLS_Analysis_Master_Data(void);
extern void Lin_RLS_data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);

#endif    /* _ADC_H_ */
