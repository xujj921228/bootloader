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

#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"


typedef struct
{
    uint16 dc_stage1;
    uint16 dc_stage2;
    uint16 dc_stage3;
    uint16 dc_stage4;
    
    uint16 stage_intensity1;
    uint16 stage_intensity2;
    uint16 stage_intensity3;
    uint16 stage_intensity4;
    uint16 stage_intensity5;
    
    uint8 meas_avg_cnt;
    
    uint8 park_high_meas_timer1;
    uint8 park_high_meas_timer2;
    uint8 park_low_meas_timer1;
    uint8 park_low_meas_timer2;
    
    uint8 park_timer[5];
    uint8 park_enter_low_th;
    uint8 park_enter_high_th;

    uint8 int_delay_timer;
    
    uint8 int_enter_period_cnt[5];
    uint8 int_enter_low_cnt; 
    
    uint8  u8_cnt_choose[5][4];
    uint8  u8_Int_Time[5][4];
    uint8 period_enter_low_cnt[5][4];
    uint8 period_enter_low_th;
    
    uint8 low_delaytimer[5][3];
    uint8 low_enter_high_cnt[5][3];
    
    uint8 high_delaytimer[5][3];
    uint8 high_hold_th[5][3];
}tRain_Stastegy_Config;

typedef enum
{
   PARK_MODE_No_Rain                 = 0,
   PARK_MODE_Rain_Wait               = 1,
   PARK_MODE_Raining                 = 2
}RLS_PARK_MODE_FSM_t;

typedef enum
{
   RLS_Continue_Msure                 = 0,
   RLS_Stop_Msure                     = 1
}RLS_StopMsureFlg_t;


typedef enum
{
	PARK_MODE            = 0,
	INT_SPEED_MODE       = 1,   
	PERIOD_SPEED_MODE    = 2,
	INT_DELAY_MODE       = 3,
	LOW_SPEED_MODE       = 4,
	HIGH_SPEED_MODE      = 5

}RLS_Wiper_State_FSM_t;

/************RAIN_INVALID***********/   
#define   DC_bef_dtTH           300     //300
#define   DC_aft_dtTH           300     //300
#define   DC_CHANGE_TH          300     //300

#define   DC_bef_dtTH_RAIN      500     //300
#define   DC_aft_dtTH_RAIN      500     //300
#define   DC_CHANGE_TH_RAIN     800     //300


#define   PERIOD_SPEED_TIMER   30   //3S

#define   DC_WINDOW   20
#define   Rain_WINDOW  3


#define   RAIN_DELTA          80

#define   PD_WINDOW   6

#define   RAIN_ACTIV_TH       40
#define   RAIN_ACTIV_CNT       3

extern void Auto_Wiper_Var_Init(void);
extern bool_t RLS_Rain_Module_Fault_Process(uint8 chan, uint8 PD_Temp);
extern uint8 RLS_Get_Rain_State(uint8 PD_chan);
extern void RLS_Get_Rain_RainIntensity(uint8 PD_chan);
extern void RLS_Get_Rain_ExpectStage();
extern void RLS_Mask_False_Operation(void);
extern void RLS_Invalid_DataProcess(void);
extern uint8 RLS_Period_Time_Choose();
extern void RLS_Rain_State_Mchaine(void);
extern void RLS_Wipe_Park_Process(void);
extern void RLS_Auto_Rain_Task(void);
extern void RLS_Lin_Diag_Fucntion(void);













