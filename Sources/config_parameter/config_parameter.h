#ifndef __CONFIG_PARAMETER_H
#define __CONFIG_PARAMETER_H

#include "global_parameter.h"

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

extern tMlx75308_Config const Mlx75308_Config_Parameter[1];
extern tRain_Stastegy_Config const  Rain_Stastegy_Parameter[1];
extern tLight_Stastegy_Config const  Light_Stastegy_Parameter[1];

extern const  uint8 Software_Versions[3] ;
extern const  uint8 Hardware_Versions[3] ;
extern const  uint8 Part_Versions[3] ;


#endif /* __GLOBAL_PARAMETER_H */

/*********************************************************************************************************
  End Of File
*********************************************************************************************************/
