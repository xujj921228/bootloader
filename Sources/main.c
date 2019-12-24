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
#include "pmc.h"
#include "rtc.h"
#include "rls_app.h"
#include "lin_app.h"
#include "watchdog.h"


/***********************************************************************************************
*
* @brief    main - Initialize 
* @param    none
* @return   none
*
************************************************************************************************/  
void main(void)
{	
	unsigned char ret = 0 ;
	unsigned char vector_number = 0;
	
	//Clk_Init();	
	FTM0_Init();
	ADC_Init();
	GPIO_Init();
	FLASH_Init(BUS_CLCOK);	
	PMC_Init();
	Globle_parameter_Init();
	MLX75308_Init();
	RTC_Init();
	ret = l_sys_init();
	ret = l_ifc_init(LI0);
	
	vector_number = INT_UART0 -16;
	
	NVIC_ICPR |= 1 << (vector_number%32);
	NVIC_ISER |= 1 << (vector_number%32);
	
	while(!DR);

	for(;;) 
	{			
		WDOG_Feed();
		if(G_4sFlag == TRUE)
		{
			G_4sFlag = 0;
			G_4s_counter = 0;
			if (Lin_Busy_Flag == 0)
			{				
				Sleep_Process();
			}
		}
		
		if((u8_lin_cmd_sleep == 1)||(u8_auto_roof_rain_measure_sleep_flg == 1)||(u8_wakeup_bcm_cnt_sleep_flg == 1))
		{
			if(u8_lin_cmd_sleep == 1)                    u8_lin_cmd_sleep = 0;
			if(u8_auto_roof_rain_measure_sleep_flg == 1) u8_auto_roof_rain_measure_sleep_flg = 0;
			if(u8_wakeup_bcm_cnt_sleep_flg == 1)         u8_wakeup_bcm_cnt_sleep_flg = 0;
			Sleep_Process();
		}
		
		
		if (Lin_Busy_Flag == 1)
		{
			Lin_Busy_Flag = 0;			
		}
		
		if (Enter_Sleep_Flag == 1) 
		{
			Enter_Sleep_Flag = 0;  
			Recover_Process();
		}
									
		switch(RLS_RunMode)
		{
			  case NORMAL:
			  {                                       		
					if( G_10msFlag == TRUE)
					{
						G_10msFlag = FALSE;
						lin_diagservice_session_state();
#ifdef ENABLE_AUTO_ROOF
						if(u8_polling_mode_enter == 1)
						{
							Auto_Roof_Process();
						}
#endif
					}		
					
					if( G_50msFlag == TRUE)
					{
						G_50msFlag = FALSE;
						RLS_Battery_State();                
					}
					
					if( G_100msFlag == TRUE)
					{
						G_100msFlag = FALSE;  			
						RLS_Auto_Light_Task();
						RLS_Auto_Rain_Task();	
						Lin_RLS_data();
					}
					
					if( G_500msFlag == TRUE)
					{
						G_500msFlag = FALSE;	
					}
			  }break;
			  
			  case SLEFADAPT:
			  {
				  RLS_SelfAdaptTask();
			  }break;
			  
			  default: 
					 RLS_RunMode = NORMAL; 
					 break;
		}
				
	 }	
}
