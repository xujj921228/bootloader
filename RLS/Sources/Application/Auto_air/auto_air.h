#include "config_parameter.h"



#define   SOLAR_WINDOW 8
#define   Tab_IR_NUM             16 
#define   Tab_FW_NUM             16

uint16 Search_Table(uint32 in_x,uint32 *Tabx,uint16 *Taby,uint8 Tab_NUM);
extern void RLS_AutoLightControl(void);
extern uint16 Search_Table(uint32 in_x,uint32 *Tabx,uint16 *Taby,uint8 Tab_NUM);
