#include "mlx75308.h"
#include "local_eep_data.h"
#include "self_adapt.h"
#include "spi.h"
#include "watchdog.h"
#include "clock.h"
#include "auto_wiper.h"
#include "app_data.h"

extern Main_Fsm_t  RLS_RunMode;
extern local_info_t local_info;
extern Rls_Error_t       App_Rls_Error;
extern uint16 PD_WIN_AVG[CHAN_NUM][PD_WINDOW];
extern uint8  u8_RainIntensity_Win[Rain_WINDOW];

void Self_Adapt_Var_Init(void)
{
	App_Rls_Error.RS_Error = FALSE;	
}
/*****************************************************
 *      self_adpt
 * 
 * 
 */
bool_t RLS_Chan_Self_Adapt(uint8 PD_Chan)
{
	uint8   i = 0;
	uint8 Chan_Temp = CHAN_A;
	uint8 DAC_Temp = DACA;
	uint16 Pd_Temp;
	
	if(PD_Chan == PDB)//通道选择
	{
	  Chan_Temp = CHAN_B;
	  DAC_Temp = DACB;
	}

	/*do
	{
		i++;
		WDOG_Feed();
	    Pd_Temp = RLS_Rain_Get_Measure(PD_Chan, 1, 600);
	    if(i >= 20)  return TRUE;
	}while(0 != Pd_Temp);*/
	
	
	do
	{
		WDOG_Feed();
		Pd_Temp = RLS_Rain_Get_Measure(PD_Chan,ADAPT_MEAS_CNT, 1000);
		if(Pd_Temp < CALI_PARAM_LOW)
		{
			if(local_info.DAC_EEPdtata[Chan_Temp] >= ADAPT_VALUE_DAC_HIGH)
			{
				return TRUE;
			}
			else
			{
				local_info.DAC_EEPdtata[Chan_Temp]++;
			}
		}
		else
		{
			if(local_info.DAC_EEPdtata[Chan_Temp] <= ADAPT_VALUE_DAC_LOW)
			{
				return TRUE;
			}
			else
			{
				local_info.DAC_EEPdtata[Chan_Temp]--;
			}
		}
		MLX75308_SetPara(DAC_Temp, local_info.DAC_EEPdtata[Chan_Temp]);
		Delay_Ms(5);
	}while((Pd_Temp < CALI_PARAM_LOW)||(Pd_Temp > CALI_PARAM_HIGH));
	
	
	
		for(i = 0;i < PD_WINDOW;i++) 
	{                   
		/*将最新的数据压入滑动窗口  */          
		PD_WIN_AVG[Chan_Temp][i] = Pd_Temp;            
	}
	
	return FALSE;
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

    if(local_info.APP_Self_Reset_Cn < 3)
    {
    	/* add intia*/
		if((RLS_Chan_Self_Adapt(PDA)== TRUE)||(RLS_Chan_Self_Adapt(PDB) == TRUE))/*自适应失败*/
		{
			App_Rls_Error.RS_Error = TRUE;
			if(local_info.APP_Self_Reset_Cn >= 2)
			{
				local_info.APP_Self_Reset_Cn--;
			}
		}
		else /*自适应成功*/
		{
			App_Rls_Error.RS_Error = FALSE; 
			while(Set_All_Data_TO_EEPROM() == FALSE); 
		}  
		/*********MODE CHANGE TO NORMAL*******************/
		for(i = 0;i < Rain_WINDOW ;i ++) 
		{
		    u8_RainIntensity_Win[i] = 0;
		} 
    }
    RLS_RunMode = MAIN_NORMAL; 
}
