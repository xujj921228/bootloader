#ifndef __HUMID_H__
#define __HUMID_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */

#define  HUMID_NUM 3
#define  TEMP_NUM  3

extern uint8  Humid_buffer[HUMID_NUM],Humid_Avg ,Temp_buffer[TEMP_NUM],Temp_Avg;


extern void  Humid_Avg_Function(void);
extern void  Temp_Avg_Function(void);
extern void FUNC_READ_HUMDATA(uint16 cmd);
extern uint8 FUNC_HUM_SETTING(uint16 cmd);
#endif