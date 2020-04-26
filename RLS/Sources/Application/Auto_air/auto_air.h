#include "config_parameter.h"

#define   SOLAR_CHAN_NUM 2
#define   SOLAR_CHAN_A 0
#define   SOLAR_CHAN_B 1

#define   SOLAR_AVG_N            2
#define   SOLAR_WINDOW           8
#define   Tab_IR_NUM             16 
#define   Tab_FW_NUM             16

extern uint16 Search_Table(uint32 in_x,uint32 *Tabx,uint16 *Taby,uint8 Tab_NUM);
extern void RLS_Auto_Solar_Task();
extern void Auto_Air_Var_Init(void);
