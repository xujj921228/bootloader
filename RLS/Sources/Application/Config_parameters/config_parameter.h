/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      _CONFIG_PARAMETER.h 
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
#ifndef    _CONFIG_PARAMETER_H_  
#define    _CONFIG_PARAMETER_H_  

#include "derivative.h" /* include peripheral declarations */


 typedef enum
 {
      FALSE = 0,
      TRUE = 1
 }bool_t;

  typedef unsigned char   uint8;      /* unsigned 8 bit definition */
  typedef unsigned short  uint16;     /* unsigned 16 bit definition */
  typedef unsigned long   uint32;     /* unsigned 32 bit definition */
  typedef signed char     int8;       /* signed 8 bit definition */
  typedef short           int16;      /* signed 16 bit definition */
  typedef long int        int2;      /* signed 32 bit definition */
  typedef void(*pt2Func)(void);		  /* Pointer to Functions, void argument */
  typedef void(*pt2FuncU8)(uint8);	  /* Pointer to Functions, UINT8 argument */

//#define FOUR_TO_ONE
#define ENABLE_AUTO_ROOF  //使能自动开天窗功能
#define ENABLE_SOLAR

#define  ENABLE_INTERRUPT  asm("CPSIE i");
#define  DISABLE_INTERRUPT asm("CPSID i");


/************RAIN_INVALID***********/   
#define   DC_bef_dtTH           200     //300
#define   DC_aft_dtTH           200     //300
#define   DC_CHANGE_TH          300     //300

#define   RAIN_INVALID_NUM     1

#define   PERIOD_SPEED_TIMER   30   //3S

/************DC_COMP***********/
#define   DC_COMP_TH0             8100
#define   SOFT_DC_COMP_VALUE0      300 

#define   RAIN_DELTA          80

#define   DtABS_MAX    5000


/************ADAPT******************/
#define   CALI_PARAM_HIGH        45500
#define   CALI_PARAM_LOW         44500
#define   ADAPT_MEAS_CNT             3
#define   ADAPT_VALUE_DAC_LOW     0x10
#define   ADAPT_VALUE_DAC_HIGH    0xF0


typedef struct
{
    uint8  np;
    uint8  t_dem;
    uint8  t_dc;       
    uint8  bw_adj_a; 
    uint8  bw_adj_b; 
    uint8  gain_adj_a; 
    uint8  gain_adj_b;
    uint8  bw_sel_lp_a; 
    uint8  bw_sel_lp_b; 
    uint8  rf;
    uint8  dc_comp_ic1;
    uint8  dc_comp_ic2;
    uint8  dc_comp_ic3;
    uint8  dc_comp_ic4;
    uint8  dc_comp_ic5;
    uint8  dc_comp_en;
    
    uint8  dac_a_default;
    uint8  dac_b_default;
    
}tMlx75308_Config ;

typedef struct
{
    uint16 dc_stage1;
    uint16 dc_stage2;
    uint16 dc_stage3;
    uint16 dc_stage4;
    
    uint8 stage_intensity1;
    uint8 stage_intensity2;
    uint8 stage_intensity3;
    uint8 stage_intensity4;
    uint8 stage_intensity5;
    
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

typedef struct
{
    uint8 off_timer;
    uint16 Lowbean_on_th;
    uint16 Lowbean_off_th;
    uint16 PositionLamp_on_th;
    uint16 PositionLamp_off_th;
}tLight_Stastegy_Config;


extern const  uint8 Software_Versions[3];
extern const  uint8 Hardware_Versions[3];

extern tMlx75308_Config const Mlx75308_Config_Parameter[1];
extern tRain_Stastegy_Config const  Rain_Stastegy_Parameter[1];
extern tLight_Stastegy_Config const  Light_Stastegy_Parameter[1];


extern void Globle_parameter_Init(void);
#endif    /* _ADC_H_ */
