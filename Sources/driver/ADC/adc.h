#ifndef __ADC_H__
#define __ADC_H__


////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"

#define VOLT_CH 2
#define MEAS_NUM 4

extern void ADC_Init(void);
extern uint16 get_adc(uint8 num);
extern uint16 get_adc_times(uint8 ch,uint8 convert_times);


                
#endif