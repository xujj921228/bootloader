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

#include "config_parameter.h"




#define   AMB_FW_CH   9
#define   AMB_UP_CH   8





#define   DC_WINDOW   20




#define   LIGHT_TYPE       2
#define   LIGHT            0
#define   TWILIGHT         1




#define   Rain_WINDOW  3


#define   PARK_MODE         0
#define   INT_SPEED_MODE    1
#define   PERIOD_SPEED_MODE 2
#define   INT_DELAY_MODE    3
#define   LOW_SPEED_MODE    4
#define   HIGH_SPEED_MODE   5



struct Rls_Error 
{
  uint8  RS_Error              :1;
  uint8  LS_Error              :1;
  uint8  IR_Error              :1;
  uint8  rsv0                  :5;
  
  uint8  RS_Error_Cnt[2];
  uint8  LS_Error_Cnt ;
  uint8  IR_Error_Cnt[2] ;
};

extern uint8 u8_MsgCounter;
extern uint8 u8_light_on_req,u8_light_on_invent_req,u8_twilight_on_req,u8_twilight_on_invent_req;

extern uint8  u8_Rain_Value,u8_MeasureSureTime;
extern uint8  u8_Rain_Sensitivity,u8_Rain_Delta;
extern uint8  u8_Battery_status;
extern uint8  u8_WiperSpeed_Expert,u8_IntSpeedCnt,u8_IntSpeedEnterCnt,u8_WiperSpeed;

extern uint16 u16_Brightness_FW,u16_Brightness_UP;


extern uint8  u8_Wipe_Automatic_On_Pre;
extern uint8  u8_Rain_SensitivityPre,Rain_Sensitivity; 

extern uint8  Light_on_cnt[LIGHT_TYPE];
extern uint8  Light_off_cnt[LIGHT_TYPE];

extern uint8  MLX75308_A_Gain,MLX75308_B_Gain,MLX75308_A_Adc,MLX75308_B_Adc;

extern uint8  u8_Cmd_Execution;
extern uint16 u16_SPD_Vehicle;
extern uint8  u8_Battery_status,u8_Rain_Valid;

extern uint8 u8_RTC_10S_Flg;
extern uint8 u8_polling_mode_enter,Mcu_wakeup_state,u8_wakeup_bcm_timer,u8_wakeup_cnt,u8_wakeup_timer;
extern uint8 u8_lin_cmd_sleep,u8_auto_roof_rain_measure_sleep_flg,u8_wakeup_bcm_cnt_sleep_flg;

extern uint8  u8_Rain_Flg;
extern uint16 u16_RainWindow_Cnt;
extern uint8  u8_enter_period_cnt;
extern uint8 u8_enter_period_flg;
extern uint8  u8_Vehicle_State,u8_Vehicle_State_Pre;
extern uint8  u8_Int_Cnt;
extern uint16 u16_IntWindow_Cnt;

extern uint8  u8_Lin_Diag_Enable;
extern uint8  u8_Lin_Diag_Enable_Cnt;

extern struct Rls_Error       App_Rls_Error;
extern struct MLX75308_Frame  MLX75308_RxFrame;
extern struct MLX75308_Mnrval Mnrval;


extern void RLS_Wipe_Sensitivity_Up_Function(void);
extern void RLS_Wipe_Auto_On_Function(void);
extern void MLX75308_Init(void);
extern uint16 RLS_Rain_Get_Measure(uint8 PD_chan,uint8 n,uint16 DC_cancel_th);
extern void RLS_Auto_Light_Task(void);
extern void RLS_Auto_Rain_Task(void);
extern void RLS_Wipe_Park_Process(void);
extern void RLS_Battery_State(void);
extern void RLS_Battery_State(void);
extern void RLS_Auto_Light_Task(void);
extern void RLS_SelfAdaptTask(void);
extern void Sleep_Process(void);
extern void Recover_Process(void);
extern void Auto_Roof_Process(void);
extern void RLS_Auto_Solar_Task();
extern void RLS_Lin_Diag_Fucntion(void);


