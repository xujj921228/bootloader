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
    
    uint8 park_timer;
    uint8 park_enter_low_th;
    uint8 park_enter_high_th;

    uint8 int_delay_timer;
    
    uint8 int_enter_period_cnt;
    uint8 int_enter_low_cnt; 
      
    uint8 period_enter_low_cnt;
    uint8 period_enter_low_th;
    
    uint8 low_delaytimer41;
    uint8 low_enter_high_cnt41;
    uint8 low_delaytimer42;
    uint8 low_enter_high_cnt42;
    uint8 low_delaytimer43;
    uint8 low_enter_high_cnt43;
    
    uint8 low_delaytimer31;
    uint8 low_enter_high_cnt31;
    uint8 low_delaytimer32;
    uint8 low_enter_high_cnt32;
    uint8 low_delaytimer33;
    uint8 low_enter_high_cnt33;
    
    uint8 low_delaytimer21;
    uint8 low_enter_high_cnt21;
    uint8 low_delaytimer22;
    uint8 low_enter_high_cnt22;
    uint8 low_delaytimer23;
    uint8 low_enter_high_cnt23;
    
    uint8 low_delaytimer11;
    uint8 low_enter_high_cnt11;
    uint8 low_delaytimer12;
    uint8 low_enter_high_cnt12;
    uint8 low_delaytimer13;
    uint8 low_enter_high_cnt13;
    
    uint8 high_delaytimer41;
    uint8 high_hold_th41;
    uint8 high_delaytimer42;
    uint8 high_hold_th42;
    uint8 high_delaytimer43;
    uint8 high_hold_th43;
    
    uint8 high_delaytimer31;
    uint8 high_hold_th31;
    uint8 high_delaytimer32;
    uint8 high_hold_th32;
    uint8 high_delaytimer33;
    uint8 high_hold_th33;
    
    uint8 high_delaytimer21;
    uint8 high_hold_th21;
    uint8 high_delaytimer22;
    uint8 high_hold_th22;
    uint8 high_delaytimer23;
    uint8 high_hold_th23;
    
    uint8 high_delaytimer11;
    uint8 high_hold_th11;
    uint8 high_delaytimer12;
    uint8 high_hold_th12;
    uint8 high_delaytimer13;
    uint8 high_hold_th13;
    
}tRain_Stastegy_Config;


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
#define   DC_bef_dtTH           200     //300
#define   DC_aft_dtTH           200     //300
#define   DC_CHANGE_TH          300     //300




#define   PERIOD_SPEED_TIMER   30   //3S

#define   DC_WINDOW   20
#define   Rain_WINDOW  3


#define   RAIN_DELTA          80

#define   PD_WINDOW   6



extern void Auto_Wiper_Var_Init(void);
extern void RLS_Rain_Module_Fault_Process(uint8 chan);
extern uint8 RLS_Get_Rain_State(uint8 PD_chan);
extern void RLS_Get_Rain_RainIntensity(uint8 PD_chan);
extern void RLS_Get_Rain_ExpectStage(uint8 PD_chan);
extern void RLS_Mask_False_Operation(void);
extern void RLS_Invalid_DataProcess(void);
extern uint8 RLS_Period_Mode(uint8 Int_Timer, uint8 Wiper_Timer);
extern uint8 RLS_Park_Mode_DelayTime(void);
extern void RLS_Rain_State_Mchaine(void);
extern void RLS_Wipe_Park_Process(void);
extern void RLS_Auto_Rain_Task(void);
extern void RLS_Single_Wipe_Function(void);
extern void RLS_Lin_Diag_Fucntion(void);













