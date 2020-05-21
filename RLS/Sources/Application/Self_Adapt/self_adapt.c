#include "mlx75308.h"
#include "local_eep_data.h"
#include "self_adapt.h"
#include "spi.h"
#include "watchdog.h"
#include "clock.h"
#include "auto_wiper.h"

extern Main_Fsm_t  RLS_RunMode;
extern local_info_t local_info;
extern uint16 u16_Pd_Measure_Value;
extern uint16 PD_WIN_AVG[CHAN_NUM][PD_WINDOW];
extern uint8  u8_RainIntensity_Win[Rain_WINDOW];
extern uint8  u8_IntSpeedEnterCnt;
/*****************************************************
 *      self_adpt
 * 
 * 
 */
void RLS_Chan_Self_Adapt(uint8 PD_Chan)
{
	uint8   i;
	uint8 Chan_Temp = CHAN_A;
	uint8 DAC_Temp = DACA;
	
	if(PD_Chan == PDB)
	{
	  Chan_Temp = CHAN_B;
	  DAC_Temp = DACB;
	}
	
	for(i = 0; i < 20; i++)
	{
		WDOG_Feed();
		u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PD_Chan, 1, 600);
		if(0 != u16_Pd_Measure_Value) 
			break;
	}
	
	if(u16_Pd_Measure_Value < CALI_PARAM_LOW)
	{
		for(; local_info.DAC_EEPdtata[Chan_Temp] < ADAPT_VALUE_DAC_HIGH; local_info.DAC_EEPdtata[Chan_Temp]++)
		{
			WDOG_Feed();
			MLX75308_SetPara(DAC_Temp, local_info.DAC_EEPdtata[Chan_Temp]);
			Delay_Ms(5);
			u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PD_Chan,ADAPT_MEAS_CNT, 1000);
			if((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH)) 
							break;
		}
	} 
	else if(u16_Pd_Measure_Value > CALI_PARAM_HIGH)
	{
		for(;ADAPT_VALUE_DAC_LOW < local_info.DAC_EEPdtata[Chan_Temp];local_info.DAC_EEPdtata[Chan_Temp]--)
		{
			WDOG_Feed();
			MLX75308_SetPara(DAC_Temp, local_info.DAC_EEPdtata[Chan_Temp]);
			Delay_Ms(5);
			u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PD_Chan,ADAPT_MEAS_CNT, 1000);
			if((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH))  
							break;
		}
	}
	else
	{
		
	}
	
		for(i = 0;i < PD_WINDOW;i++) 
	{                   
		/*将最新的数据压入滑动窗口  */          
		PD_WIN_AVG[Chan_Temp][i] = u16_Pd_Measure_Value;            
	}
	
	if(PD_Chan == PDB)
	Set_Data_To_EEPROM(EEPROM_B_DAC_ADDR,&local_info.DAC_EEPdtata[1],EEPROM_B_DAC_ADDR_LENTH);
	else
    Set_Data_To_EEPROM(EEPROM_A_DAC_ADDR,&local_info.DAC_EEPdtata[0],EEPROM_A_DAC_ADDR_LENTH);
	
	
}

/*******************************************************
 * FUNCTION NAME : RLS_SelfAdaptTask()
 *   DESCRIPTION : RLS_SelfAdaptTask function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/       
void RLS_SelfAdaptTask(void)
{
    uint8   i;

   /* add intia*/
    RLS_Chan_Self_Adapt(PDA);
    RLS_Chan_Self_Adapt(PDB);
  
/*********MODE CHANGE TO NORMAL*******************/
    for(i = 0;i < Rain_WINDOW ;i ++) 
    {
        u8_RainIntensity_Win[i] = 0;
    }
    
    RLS_RunMode = MAIN_NORMAL;     
}
