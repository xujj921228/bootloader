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



struct BCM1_Frame 
{	
  uint8  rsv1              :5;
  uint8  rsv3              :1;
  uint8  VehicleSpeedValid :2;
  
  uint8  STAT_Terminal     :3;
  uint8  Day     :5;
  
  uint8  Month     :4;
  uint8  vehicleSpeed_l     :4;
  
  uint8  vehicleSpeed_h     :8;
  
  uint8  rsv2               :7;
  uint8  remote             :1;
};

struct BCM3_Frame 
{	
  uint8  FrontWiperSwitch    :3;
  uint8  FrontWasherSwitch  :2;
  uint8  FrontWiperInterval :3;
  
  uint8  MasterLightSwitch     :3;
  uint8  FrontWiperPosition     :1;
  uint8  rsv                    :4;
};

struct BCM2_Frame 
{	
  uint8  AmbientTemp    ;
  
  uint8  RoofStatus    :2;
  uint8  remote       :1;
  uint8  rsv                      :5;

};


extern struct BCM1_Frame         Lin_BCM1_Frame;
extern struct BCM2_Frame         Lin_BCM2_Frame;
extern struct BCM3_Frame         Lin_BCM3_Frame;

extern void Lin_Sys_Init(void);
extern void Lin_Busy_Process(void);
extern void message_cnt(void);
extern void RLS_Analysis_Master_Data(void);
extern void Lin_RLS_data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);
extern void RLS_Wipe_Park_Process(void);

#endif    /* _ADC_H_ */
