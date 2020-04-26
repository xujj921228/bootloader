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



typedef struct BCM_Frame 
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
    
}BCM_Frame_t;


typedef struct
{
  uint8  RS_Error              :1;
  uint8  LS_Error              :1;
  uint8  IR_Error              :1;
  uint8  rsv0                  :5;
  
  uint8  RS_Error_Cnt[2];
  uint8  LS_Error_Cnt ;
  uint8  IR_Error_Cnt[2] ;
} Rls_Error_t;

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
