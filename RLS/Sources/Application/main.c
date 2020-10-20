/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"
#include "eeprom.h"
#include "clock.h"
#include "pmc.h"
#include "ftm.h"
#include "gpio.h"
#include "RTC.h"
#include "watchdog.h"
#include "iic.h"
#include "spi.h"
#include "lin_app.h"
#include "mlx75308.h"

#include "sleep.h"
#include "auto_air.h"
#include "auto_light.h"
#include "auto_humid.h"
#include "battery.h"
#include "lin_diagnostic_service.h"
#include "self_adapt.h"
#include "app_data.h"


/************gloable  var*****************/
uint8  Timer_50ms;
uint8  Timer_100ms;
uint8  Timer_500ms;

uint8  Timer_4s;
uint8  Timer_10ms_flag;
uint8  Timer_50ms_flag;
uint8  Timer_100ms_flag;
uint8  Timer_500ms_flag;

extern BCM_APP_Value_t     BCM_APP_Value;
extern RLS_APP_Value_t     RLS_APP_Value;

Main_Fsm_t  RLS_RunMode;
/*****************************************
 * Gloable_Var_Init
 * ***************************************/
void Gloable_Var_Init(void)
{
    Timer_50ms = 0;
    Timer_100ms = 0;
    Timer_500ms = 0;
    Timer_4s = 0;
    Timer_10ms_flag = 0;
    Timer_50ms_flag = 0;
    Timer_100ms_flag = 0;
    Timer_500ms_flag = 0;
    

    RLS_RunMode = MAIN_SLEFADAPT;
    
    Self_Adapt_Var_Init();
    Sleep_Var_Init();//var for sleep 
    Auto_Air_Var_Init();//var for Solar
    Auto_light_Var_Init();//var for light
    Battery_Var_init();//var for battery
    Auto_Wiper_Var_Init();//var for rain
    Diagnostic_Var_init();//var for Diagnostic
    Lin_Var_Init();//var for lin
    Auto_Humid_Var_Init();/*var for Humid*/
}
/***********************************************************************************************
*
* @brief    main - Initialize 
* @param    none
* @return   none
*
************************************************************************************************/ 
int main(void)
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
	Globle_Eep_parameter_Init();/*read all eep data for all task */
	Gloable_Var_Init();  /*init all var for all task*/
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
		Sleep_check();		
		switch(RLS_RunMode)
		{
		/***********RLS NORMAL MODE*************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************/
		  case MAIN_NORMAL:
		  {  
			if(Timer_10ms_flag == 1)
			{
			  Timer_10ms_flag = 0;
			  lin_diagservice_session_state();
			}
			 if(Timer_50ms_flag == 1)
			{
			  Timer_50ms_flag = 0;
			  RLS_Auto_Rain_Task();
			}
			 if(Timer_100ms_flag == 1)
			{
			  Timer_100ms_flag = 0;
			  RLS_Battery_State();
			  RLS_Auto_Light_Task();
			  RLS_Lin_Diag_Fucntion();
#ifdef ENABLE_SOLAR
			  RLS_Auto_Solar_Task();	
#endif
              }
			 if(Timer_500ms_flag == 1)
			{
			  Timer_500ms_flag = 0;
			  Timer_4s ++;
#ifdef FOUR_TO_ONE 
			  FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
			  Humid_Avg_Function(); 
			  Temp_Avg_Function() ; 
#endif
			}
		  }break;

		  
		  
		/***********RLS SLEEP MODE*************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************
		 * ************************************************************************************************************************/	  
		  case MAIN_SLEEP_Mode:
		  {     
			  if(BCM_APP_Value.BCM_APP_ModReq == APP_Polling_Mode)//BCM没有主动唤醒 
			  {
				  if(Timer_50ms_flag == 1)
				  {
					  Timer_50ms_flag = 0;
					  Auto_Roof_Process();
				  } 
			  }
			  else//BCM主动唤醒，就退出polling模式
			  {
				  boot_jump_to_APP((uint16 *)APP_start_address); 
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
