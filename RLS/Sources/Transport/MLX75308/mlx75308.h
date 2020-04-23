#include "spi.h"
#include "watchdog.h"
#include "gpio.h"
#include "clock.h"
#include "config_parameter.h"


#define   PD_WINDOW   6

extern uint16 RLS_Rain_Get_Measure(uint8 PD_chan,uint8 n,uint16 DC_cancel_th);
extern void MLX75308_Init(void);




