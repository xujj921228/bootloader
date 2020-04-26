#include "config_parameter.h"
#include "auto_wiper.h"


typedef enum
{
	Roof_RAIN_CHECK = 0,
	Roof_Wake_Up = 1,
	Roof_CLOSED_WINDOWS
}Auto_Roof_FSM_t;

void Sleep_Var_Init(void);
extern void Sleep_check(void);
extern void Auto_Roof_Process(void);
extern void Sleep_Process(void);
extern void Recover_Process(void);
