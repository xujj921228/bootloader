
#include "battery.h"








uint16 u16_Battery_Volt;
uint8  u8_Battery_Low_Cnt;
uint8  u8_Battery_High_Cnt;
uint8  u8_Battery_status;

uint8 u8_low_voltage_cnt;
uint8 u8_high_voltage_cnt;


/*******************************************************
 * FUNCTION NAME : LS_Battery_Measurement()
 *   DESCRIPTION : LS_Battery_Measurement  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Battery_Measurement(void)
{
    uint32 temp;
    temp = get_adc_times(VOLT_CH,MEAS_NUM); //V_VCC/1024 = x*(13/113)/3.3 
    u16_Battery_Volt = ((temp*113*33/13)>>12) + 8;
}

/*******************************************************
 * FUNCTION NAME : LS_Battery_Measurement()
 *   DESCRIPTION : LS_Battery_Measurement  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Battery_State(void)
{
	RLS_Battery_Measurement();	
	
	if(u16_Battery_Volt <= 75) //7.5v
	{
		u8_high_voltage_cnt = 0;
		u8_low_voltage_cnt++;
		if(u8_low_voltage_cnt >= 20) //1s
		{
			u8_Battery_status = VOLTAGE_LOW;
		}
	}
	else if((u16_Battery_Volt >= 80)&&(u16_Battery_Volt <= 180))
	{
		u8_low_voltage_cnt = 0;
		u8_high_voltage_cnt = 0;
		u8_Battery_status = VOLTAGE_NORMAL;
	}
	else if(u16_Battery_Volt > 185)
	{
		u8_low_voltage_cnt = 0;
		u8_high_voltage_cnt++;
		if(u8_high_voltage_cnt >= 20) //1s
		{
			u8_Battery_status = VOLTAGE_HIGH;
		}
	}
	else
	{
		
	}
}






