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
  uint8  BCM_WiperPosition     :1;

  uint8  BCM_WiperSwitch       :3;
    
  uint8  BCM_Washer            :1;
    
  uint8  BCM_WindowStatus      :1;
    
  uint8  BCM_Ignition          :1;
    
  uint8  BCM_RainSensitivity   :3;
    
  uint16  BCM_VehicleSpeed     ;
    
  uint8  BCM_Transmision550nm    ;
    
  uint8  BCM_Transmision880nm    ;
    
};


extern uint8 Lin_Busy_Flag;
extern uint8 Enter_Sleep_Flag;
extern uint16 u16_DC_checkValue;


extern void Lin_Sys_Init(void);
extern void Lin_Busy_Process(void);
extern void message_cnt(void);
extern void RLS_Analysis_Master_Data(void);
extern void Lin_RLS_data(void);
extern void MLX75308_Init(void);
extern void Lin_RLS_Wakeup_BCM(void);

#endif    /* _ADC_H_ */
