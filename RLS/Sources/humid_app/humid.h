#ifndef __HUMID_H__
#define __HUMID_H__

#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"

#define  HUMID_NUM 3
#define  TEMP_NUM  3

extern uint8  Humid_buffer[HUMID_NUM],Humid_Avg ;
extern uint8  Temp_buffer[TEMP_NUM],Temp_Avg;
extern uint16  Temp_measure_TP;
extern uint16  Dew_Point;
extern uint8   Temp_measure;
extern uint8   Hum_measure;
extern uint8  Humid_Temp_Error;
//extern  float f_Dew_Point,f_acture_temp,f_acture_hum;
extern void   Humid_Avg_Function(void);
extern void   Temp_Avg_Function(void);
extern void   FUNC_READ_HUMDATA(uint16 cmd);
extern uint8  FUNC_HUM_SETTING(uint16 cmd);
extern float Dew_Point_Cal(float temp , float hum);
#endif
