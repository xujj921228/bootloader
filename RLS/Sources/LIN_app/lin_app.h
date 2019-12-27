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
* @author    xujun
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



struct BCM_Frame 
{
  uint8  Status_IGN        :2;
  uint8  CMD_AutoWiper     :1;
  uint8  RQ_FrontWash      :1;
  uint8  ParkPosition      :1;
  uint8  RainSensitivity   :3;
  
  uint8  CMD_AutoLight     :1;
  uint8  BladesTurningPoint:1;
  uint8  RoofStatus        :1;
  uint8  rsv0              :5;
  
  uint8  SPD_Vehicle_L  ;
  
  uint8  SPD_Vehicle_H     :5;
  uint8  rsv1              :3;
  
  uint8  OutsideTemp;
};


extern uint8 Lin_Busy_Flag;
extern uint8 Enter_Sleep_Flag;
extern uint16 u16_DC_checkValue;

extern struct BCM_Frame         Lin_BCM_Frame;


extern void Lin_Sys_Init(void);
extern void Lin_Busy_Process(void);
extern void message_cnt(void);
extern void RLS_Analysis_Master_Data(void);
extern void Lin_RLS_data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);

#endif    /* _ADC_H_ */
