#include "config_parameter.h"

typedef struct
{
    uint8 off_timer;
    uint16 Lowbean_on_th;
    uint16 Lowbean_off_th;
    uint16 PositionLamp_on_th;
    uint16 PositionLamp_off_th;
}tLight_Stastegy_Config;


#define   AMB_FW_CH   9
#define   AMB_UP_CH   8

#define   LIGHT_TYPE       2
#define   LIGHT            0
#define   TWILIGHT         1

extern void Auto_light_Var_Init(void);
extern void RLS_AutoLightControl(void);
extern void RLS_Light_Module_Fault_Process(void);
extern void RLS_Auto_Light_Task(void);
