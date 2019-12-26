/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           config_parameter.c
** Last modified Date:  2017-12-19
** Last Version:        V1.00
** Descriptions:        全局参数声明。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          xujun
** Created date:        2017-12-19
** Version:             V1.00
** Descriptions:        创建文件
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/
#include "config_parameter.h"

const  uint8 Software_Versions[3] = {0x01, 0x03, 0x05};
const  uint8 Hardware_Versions[3] = {0x00, 0x01, 0x01};
const  uint8 Part_Versions[3] = {0x04, 0x00, 0x00};


tMlx75308_Config const Mlx75308_Config_Parameter[1] =
{
    {
       0x0b, //np
       0x02, //t_dem
       0x02, //t_dc
       0x00, //bw_adj_a
       0x00, //bw_adj_b
       0x01, //gain_adj_a
       0x01, //gain_adj_b
       0x03, //bw_sel_lp_a
       0x03, //bw_sel_lp_b
       0x04, //rf
       0x03, //dc_comp_ic1
       0x05, //dc_comp_ic2
       0x04, //dc_comp_ic3
       0x02, //dc_comp_ic4
       0x01, //dc_comp_ic5
       0x01, //dc_comp_en
       0xA8, //dac_a_default
       0xA8  //dac_b_default
    }
} ;

tRain_Stastegy_Config const  Rain_Stastegy_Parameter[1] =
{
    {
		8100, //dc_stage1
		8400, //dc_stage2
		8700, //dc_stage3
		9000, //dc_stage4
		
		80,  //stage_intensity1
		100,  //stage_intensity2
		150,  //stage_intensity3
		200,  //stage_intensity4
		250,  //stage_intensity5
		
		8, // meas_avg_cnt
		
		4,//park position  high_speed meas timer
		16,//park position high_speed meas timer
		4,// park position low_speed meas timer
		26,//park position low_speed meas timer
	
		40, // park_timer(u8_Rain_Sensitivity = 4)
		2,  // park_enter_low_th;
		11,  // park_enter_high_th;

		30, // int_delay_timer;
		
		3,  // int_enter_period_cnt;
		30, // int_enter_low_cnt; 
		 
		12,  //period_enter_low_cnt;
		6,  //period_enter_low_th;
		
		20, //low_delaytimer41;    (u8_Rain_Sensitivity = 4)
		35, //low_enter_high_cnt41;
		70, //low_delaytimer42;
		35, //low_enter_high_cnt42;
		90, //low_delaytimer43;
		35, //low_enter_high_cnt43;
		
		20, //low_delaytimer31;    (u8_Rain_Sensitivity = 3)
		35, //low_enter_high_cnt31;
		70, //low_delaytimer32;
		35, //low_enter_high_cnt32;
		90, //low_delaytimer33;
		35, //low_enter_high_cnt33;
		
		20, //low_delaytimer21;    (u8_Rain_Sensitivity = 2)
		35, //low_enter_high_cnt21;
		70, //low_delaytimer22;
		35, //low_enter_high_cnt22;
		90, //low_delaytimer23;
		35, //low_enter_high_cnt23;
		
		20, //low_delaytimer11;    (u8_Rain_Sensitivity = 1)
		35, //low_enter_high_cnt11;
		70, //low_delaytimer12;
		35, //low_enter_high_cnt12;
		90, //low_delaytimer13;
		35, //low_enter_high_cnt13;
		
		30, //high_delaytimer41;    (u8_Rain_Sensitivity = 4)
		5, //high_hold_th41;
		60, //high_delaytimer42;
		3, //high_hold_th42;
		70, //high_delaytimer43;
		3, //high_hold_th43;
		
		30, //high_delaytimer31;    (u8_Rain_Sensitivity = 3)
		5, //high_hold_th431;
		60, //high_delaytimer32;
		3, //high_hold_th32;
		70, //high_delaytimer33;
		3, //high_hold_th33;
		
		30, //high_delaytimer21;    (u8_Rain_Sensitivity = 2)
		5, //high_hold_th21;
		60, //high_delaytimer22;
		3, //high_hold_th22;
		70, //high_delaytimer23;
		3,//high_hold_th23;
		
		30,// high_delaytimer11;    (u8_Rain_Sensitivity = 1)
		5,// high_hold_th11;
		60,// high_delaytimer12;
		3,// high_hold_th12;
		70,// high_delaytimer13;
		3,// high_hold_th13; 
    }
} ;

tLight_Stastegy_Config const  Light_Stastegy_Parameter[1] =
{
    {
        55,  //off_timer
        166, //Lowbean_on_th
        233, //Lowbean_off_th
        233, //PositionLamp_on_th
        266  //PositionLamp_off_th
    }
} ;


/*********************************************************************************************************
  End Of File
*********************************************************************************************************/

