/******************************************************************************
*
* shanghai baolong Inc.
* (c) Copyright 2013-2019 shanghai baolong, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      main.c
*
* @author    xujun
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"
#include "lin_diagnostic_service.h"
#include "clock.h"
#include "lin.h"
#include "adc.h"
#include "gpio.h"
#include "eeprom.h"
#include "ftm.h"
#include "spi.h"
#include "pmc.h"
#include "rtc.h"
#include "rls_app.h"
#include "lin_app.h"
#include "iic.h"
#include "humid.h"
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
	Clk_Init();	
	FTM0_Init();
	ADC_Init();
	GPIO_Init();
	FLASH_Init(BUS_CLCOK);	
	PMC_Init();	
	SPI_Init();	
#ifdef ENABLE_HUMID 
	DRV_IIC_Init();
#endif	
	Globle_parameter_Init();
	Lin_Sys_Init();
	MLX75308_Init();	
	RTC_Init();
	
	for(;;) 
	{			
		WDOG_Feed();
		if((G_4sFlag == TRUE)||(u8_lin_cmd_sleep == TRUE)||(u8_auto_roof_rain_measure_sleep_flg == TRUE)||(u8_wakeup_bcm_1min_flg == TRUE))
		{
			if(u8_lin_cmd_sleep == TRUE)                    u8_lin_cmd_sleep = 0;
			if(u8_auto_roof_rain_measure_sleep_flg == TRUE) u8_auto_roof_rain_measure_sleep_flg = 0;
			if(u8_wakeup_bcm_1min_flg == TRUE)              u8_wakeup_bcm_1min_flg = 0;
			if(G_4sFlag == TRUE)
			{
				G_4sFlag = 0;
			    G_4s_counter = 0;
			}
			if((UART0_S2&UARTSR2_RAF_MASK)== 0)
			{
				Sleep_Process();
				Recover_Process();
			}
		}
		
#ifdef ENABLE_AUTO_ROOF
		Auto_Roof_Process();		
		RLS_remote_process();
#endif			
		switch(RLS_RunMode)
		{
			  case NORMAL:
			  {    
					if( G_10msFlag == TRUE)
					{
						G_10msFlag = FALSE;
						lin_diagservice_session_state();
					}		
					
					if( G_50msFlag == TRUE)
					{	
						G_50msFlag = FALSE;	
						RLS_Auto_Rain_Task();	
				        Lin_RLS_data();	
#ifdef ENABLE_AUTO_ROOF
				        Auto_Roof_Send_Wake_Up();
				        roof_error_process();
#endif
					}
					
					if( G_100msFlag == TRUE)
					{
						G_100msFlag = FALSE; 																		
						RLS_Battery_State();   						
						RLS_Auto_Light_Task();
						
#ifdef ENABLE_SOLAR
						RLS_Auto_Solar_Task();	
#endif
					}
					
					if( G_500msFlag == TRUE)
					{
						G_500msFlag = FALSE;	
						
						RLS_Tunnel_Detect_Task();
#ifdef ENABLE_HUMID 
						FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
						Humid_Avg_Function(); 
						Temp_Avg_Function() ; 
#endif
					}
			  }break;
			  
			  case SLEFADAPT:
			  {
					RLS_SelfAdaptTask();
#ifdef ENABLE_HUMID 
					FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
					Humid_Avg_Function(); 
					Temp_Avg_Function() ; 
#endif
			  }break;
			  
			  default: 
					 RLS_RunMode = NORMAL; 
					 break;
		}
				
	 }	
}
