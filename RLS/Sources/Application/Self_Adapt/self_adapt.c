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
extern uint8  u8_IntSpeedEnterCnt,u8_LowSpeedCnt;

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

/******************Chanl A*********************/   
    for(i = 0; i < 20; i++)
    {
    	WDOG_Feed();
        u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDA, 1, 600);
        if(0 != u16_Pd_Measure_Value) 
            break;
    }

    if(u16_Pd_Measure_Value < CALI_PARAM_LOW)
    {
    	for(; local_info.A_DAC_EEPdtata < ADAPT_VALUE_DAC_HIGH; local_info.A_DAC_EEPdtata++)
    	{
    		WDOG_Feed();
    		MLX75308_SetPara(DACA, local_info.A_DAC_EEPdtata);
    		Delay_Ms(5);
    		u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDA,ADAPT_MEAS_CNT, 1000);
    		if((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH)) 
    		                break;
    	}
    } 
    else if(u16_Pd_Measure_Value > CALI_PARAM_HIGH)
    {
    	for(;ADAPT_VALUE_DAC_LOW < local_info.A_DAC_EEPdtata;local_info.A_DAC_EEPdtata--)
    	{
    		WDOG_Feed();
    		MLX75308_SetPara(DACA, local_info.A_DAC_EEPdtata);
			Delay_Ms(5);
			u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDA,ADAPT_MEAS_CNT, 1000);
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
        PD_WIN_AVG[CHAN_A][i] = u16_Pd_Measure_Value;            
    }
    
    Set_Data_To_EEPROM(EEPROM_A_DAC_ADDR,&local_info.A_DAC_EEPdtata,EEPROM_A_DAC_ADDR_LENTH);

/******************Chanl B*********************/ 
   
    for(i = 0 ;i < 20;i++)
    {
    	WDOG_Feed();
        u16_Pd_Measure_Value =  RLS_Rain_Get_Measure(PDB, 1, 1000);
        if(0 != u16_Pd_Measure_Value) 
            break;
    }
      
    if(u16_Pd_Measure_Value < CALI_PARAM_LOW)
    {
        for(;local_info.B_DAC_EEPdtata < ADAPT_VALUE_DAC_HIGH;local_info.B_DAC_EEPdtata++)
        {
        	WDOG_Feed();
            MLX75308_SetPara(DACB, local_info.B_DAC_EEPdtata);
            Delay_Ms(5);
            u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDB,ADAPT_MEAS_CNT,1000);
             
            if((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH))
                break;         
        }                                  
    }
    
    else if(u16_Pd_Measure_Value > CALI_PARAM_HIGH)
    {
        for(;ADAPT_VALUE_DAC_LOW < local_info.B_DAC_EEPdtata;local_info.B_DAC_EEPdtata--)
        {
        	WDOG_Feed();
            MLX75308_SetPara(DACB, local_info.B_DAC_EEPdtata);
            Delay_Ms(5);
            u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PDB,ADAPT_MEAS_CNT,1000);
             
            if((u16_Pd_Measure_Value >= CALI_PARAM_LOW) && (u16_Pd_Measure_Value <= CALI_PARAM_HIGH)) 
                break;
        }      
    }
       
    
    for(i = 0;i < PD_WINDOW;i++) 
    {   
        /*将最新的数据压入滑动窗口*/             
        PD_WIN_AVG[CHAN_B][i] = u16_Pd_Measure_Value;            
    }
    
    Set_Data_To_EEPROM(EEPROM_B_DAC_ADDR,&local_info.B_DAC_EEPdtata,EEPROM_B_DAC_ADDR_LENTH);
   
/*********MODE CHANGE TO NORMAL*******************/
    for(i = 0;i < Rain_WINDOW ;i ++) 
    {
        u8_RainIntensity_Win[i] = 0;
    }
    
    RLS_RunMode = MAIN_NORMAL;
    u8_IntSpeedEnterCnt = 0;
    u8_LowSpeedCnt = 0;      
}
