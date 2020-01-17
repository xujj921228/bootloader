/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"
#include "lin_diagnostic_service.h"
#include "clock.h"
#include "lin.h"
#include "adc.h"
#include "gpio.h"
#include "eeprom.h"
#include "ftm.h"
#include "watchdog.h"
#include "spi.h"
#include "pmc.h"
#include "rtc.h"
#include "watchdog.h"
#include "rls_app.h"
#include "lin_app.h"
#include "iic.h"
#include "humid.h"


/************gloable  var*****************/
uint8  Timer_10ms;
uint8  Timer_50ms;
uint8  Timer_100ms;
uint8  Timer_500ms;
uint8  Timer_600ms;
uint8  Timer_4s;
uint32  Timer_6h;
Main_Fsm_t  RLS_RunMode;
extern uint8  u8windows_err;
extern uint8 Mcu_wakeup_state;
/*****************************************
 * Gloable_Var_Init
 * ***************************************/
void Gloable_Var_Init(void)
{
    Timer_10ms = 0;
	Timer_50ms = 0;
	Timer_100ms = 0;
    Timer_500ms = 0;
    Timer_600ms = 0;
    Timer_4s = 0;
}
/***********************************************************************************************
*
* @brief    main - Initialize 
* @param    none
* @return   none
*
************************************************************************************************/  
void main(void)
{	
	Clk_Init();	
	FTM0_Init();
	ADC_Init();
	GPIO_Init();
	FLASH_Init(BUS_CLCOK);	
	PMC_Init();		
	SPI_Init();	
#ifdef FOUR_TO_ONE 
	DRV_IIC_Init();
#endif	
	Globle_parameter_Init();
	Gloable_Var_Init();
	Lin_Sys_Init();
	MLX75308_Init();	
	RTC_Init();
	
	
	for(;;) 
	{			
		WDOG_Feed();
		/***********here check for sleep*************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************/
		if((Timer_4s >= 8) //no lin data for 4s
			||(u8_lin_cmd_sleep == TRUE)  //recive the signal of sleep from BCM
			||(u8_auto_roof_rain_measure_sleep_flg == TRUE)
			||(u8_wakeup_bcm_cnt_sleep_flg == TRUE))
		{
			u8_lin_cmd_sleep = 0;
			u8_auto_roof_rain_measure_sleep_flg = 0;
			u8_wakeup_bcm_cnt_sleep_flg = 0;
			Timer_4s = 0;
				
			Sleep_Process();
			Recover_Process();
			Gloable_Var_Init();
		}
		
					
		switch(RLS_RunMode)
		{
		/***********RLS NORMAL MODE*************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************/
		  case MAIN_NORMAL:
		  {    
		    Timer_6h = 0;
			if( Timer_10ms == TRUE)//   10ms Task
			{
			  Timer_10ms = 0;
			  Timer_50ms++;
			  lin_diagservice_session_state();

			  if(Timer_50ms >= 5) //   50ms Task
			  {
				Timer_50ms = 0;
				Timer_100ms++;
				RLS_Auto_Rain_Task();	
				Lin_RLS_data();	
				if(Timer_100ms >= 2)  //   100ms Task
				{
					Timer_100ms = 0;  
					Timer_500ms++;
					
					RLS_Battery_State();
					RLS_Auto_Light_Task();
					RLS_Lin_Diag_Fucntion();
#ifdef ENABLE_SOLAR
					RLS_Auto_Solar_Task();	
#endif
					if(Timer_500ms >= 5) //   500ms  Task
					{
						Timer_500ms = 0;
						Timer_4s++;
#ifdef FOUR_TO_ONE 
						FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
						Humid_Avg_Function(); 
						Temp_Avg_Function() ; 
#endif
						
					}
				}		
			  }
			}
		  }break;

		  
		  
		/***********RLS SLEEP MODE*************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************/	  
		  case MAIN_SLEEP_Mode:
		  {
			if( Timer_10ms == TRUE)//   10ms Task
			{
			  Timer_10ms = 0;
			  Timer_50ms++;
	
			  if(Timer_50ms >= 5) //   50ms Task
			  {
				Timer_50ms = 0;
				Timer_100ms++;
#ifdef ENABLE_AUTO_ROOF
				if((Lin_BCM_Frame.BCM_Ignition == 1)&&((Mcu_wakeup_state == 1)))
				{
					u8windows_err = 0;
					RLS_RunMode =  MAIN_NORMAL;
				}
				else
				{
					RLS_Auto_Rain_Task();
					Auto_Roof_Process();
				}
#endif
	
				if(Timer_100ms >= 2)  //   100ms Task
				{
					Timer_100ms = 0;  
					Timer_600ms++;
					if(Timer_600ms >= 6) //   500ms Task
					{
						Timer_600ms = 0;
						u8_auto_roof_rain_measure_sleep_flg = 1;
					}
				}		
			  }
			}
		  }break;
		  
		  
		  /***********RLS SLEFADAPT MODE*************************************************************************************************
		 * ******************************************************************************************************************************
		 * ******************************************************************************************************************************
		 * ******************************************************************************************************************************/	  
		  case MAIN_SLEFADAPT:
		  {
			RLS_SelfAdaptTask();
#ifdef FOUR_TO_ONE 
				FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
				Humid_Avg_Function(); 
				Temp_Avg_Function() ; 
#endif
		  }break;
		  	  
		  default: 
		 RLS_RunMode = MAIN_NORMAL; 
		 break;
		}				
	 }	
}
