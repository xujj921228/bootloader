#ifndef __RLS_APP_H__
#define __RLS_APP_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */

#define   PD_WINDOW   6
#define   DC_WINDOW   20

#define   SLEFADAPT 0
#define   NORMAL    1

#define   CHAN_NUM 2
#define   CHAN_A 0
#define   CHAN_B 1


#define   LIGHT_TYPE       2
#define   LIGHT            0
#define   TWILIGHT         1

#define   Rain_WINDOW  3

#define   AVG_N  2
#define   Tab_FW_NUM             16
#define   Tab_IR_NUM             16 


#define   PARK_MODE         0
#define   INT_SPEED_MODE    1
#define   PERIOD_SPEED_MODE 2
#define   INT_DELAY_MODE    3
#define   LOW_SPEED_MODE    4
#define   HIGH_SPEED_MODE   5

#define VOLTAGE_NORMAL   0
#define VOLTAGE_LOW      1
#define VOLTAGE_HIGH     2


#define  API_OVERTIME_CNT  3857  //2037//6H * 3600/10.6
//#define  API_OVERTIME_CNT  3  //just test





struct Rls_Error 
{
  uint8  RS_Error              :1;
  uint8  LS_Error              :1;
  uint8  IR_Error              :1;
  uint8  rsv0                  :5;
  
  uint8  LS_Error_Cnt ;
  uint8  IR_Error_Cnt[2];
  uint8  RS_Error_Cnt[2];
};

extern uint8  u8_rain_detect_flg;
extern uint8  u8_receive_data_flg;
extern uint8  u8_lin_cmd_sleep_flg,u8_rls_wake_up_bcm_flg,u8_receive_break_flag,u8_send_break_cnt;
extern uint16 API_6h_Cnt;


extern uint8  u8_Rain_Value;
extern uint8  u8_Rain_Sensitivity,u8_Rain_Delta;
extern uint8  RLS_RunMode;
extern uint8  u8_WiperSpeed_Expert,u8_IntSpeedCnt,u8_IntSpeedEnterCnt;

extern uint8 u8_Wipe_Automatic_On_Pre;
extern uint8 u8_Rain_SensitivityPre; 

extern uint8   Light_on_cnt[LIGHT_TYPE];
extern uint8   Light_off_cnt[LIGHT_TYPE];

extern uint8  u8_Lin_Diag_Enable;
extern uint8  u8_Lin_Diag_Enable_Cnt;
extern struct MLX75308_Frame  MLX75308_RxFrame;
extern struct MLX75308_Mnrval Mnrval;
extern struct RLS_Frame    Lin_RLS_Frame;
extern struct BCM_Frame    Lin_BCM_Frame;
extern struct Rls_Error    App_Rls_Error;

extern uint8  MLX75308_A_Gain,MLX75308_B_Gain,MLX75308_A_Adc,MLX75308_B_Adc;

extern void RLS_Wipe_Sensitivity_Up_Function(void);
extern void RLS_Wipe_Auto_On_Function(void);
extern void MLX75308_Init(void);
extern uint16 RLS_Rain_Get_Measure(uint8 PD_chan,uint8 n,uint16 DC_cancel_th);
extern void RLS_Auto_Light_Task(void);
extern void RLS_Auto_Rain_Task(void);
extern void RLS_Wipe_Park_Process(void);
extern void RLS_Battery_State(void);
extern void Sleep_Process(void);
extern void Recover_Process(void);
extern void RLS_Roof_Task (void);
extern void RLS_Lin_Diag_Fucntion(void);

#endif