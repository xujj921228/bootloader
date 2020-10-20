#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"


/************ADAPT******************/
#define   CALI_PARAM_HIGH        45500
#define   CALI_PARAM_LOW         44500
#define   ADAPT_MEAS_CNT             3
#define   ADAPT_VALUE_DAC_LOW     0x10
#define   ADAPT_VALUE_DAC_HIGH    0xF0

extern void Self_Adapt_Var_Init(void);
extern bool_t RLS_Chan_Self_Adapt(uint8 PD_Chan);
extern void RLS_SelfAdaptTask(void);
