#include "config_parameter.h"


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
    
} tMlx75308_Config;

#define   SOFT_DC_COMP_VALUE0      300 
#define   DC_COMP_TH0             8100

#define   CHAN_NUM 2
#define   CHAN_A 0
#define   CHAN_B 1
#define   PD_WINDOW   6

extern uint16 RLS_Rain_Get_Measure(uint8 PD_chan,uint8 n,uint16 DC_cancel_th);
extern void MLX75308_Init(void);




