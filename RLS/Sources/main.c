/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include <math.h> 
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
#include "watchdog.h"
#include "rls_app.h"
#include "lin_app.h"
#include "humid.h"
#include "iic.h"

/***********************************************************************************************
*
* @brief    main - Initialize 
* @param    none
* @return   none
*
************************************************************************************************/  
//#define VERIFIED_SECTOR				32
//#define BUS_CLK_HZ					24000000

//uint8  u8DataBuff[256];

void main(void)
{	
//	char ch;
//	uint32 i;
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
	Lin_Sys_Init();
	MLX75308_Init();
	
	
	RTC_Init();
	
	
	
	
	Lin_Sys_Init();
	
	
	/*
	 Initialize the Flash Memory module 
	    FLASH_Init(BUS_CLK_HZ);
	  
	    //FLASH_Init(BUS_CLCOK);
	    
	     Erase 99th sector 
	    FLASH_EraseSector(VERIFIED_SECTOR*FLASH_SECTOR_SIZE);

	     Initialize the variable 
	    for(i=0;i<256;i++)
	    {
	        u8DataBuff[i] = (uint8)i;
	    }

	     Write data to erased sector 
	    FLASH_Program( VERIFIED_SECTOR*FLASH_SECTOR_SIZE,&u8DataBuff[0],256 );
	    FLASH_Program( VERIFIED_SECTOR*FLASH_SECTOR_SIZE+256,&u8DataBuff[0],256 );

	    printf("\nReading the newly written sector\n\r");

	     Read data from the newly written sector 
	    for( i=0;i<512/16;i++ )
	    {
	        for(ch =0;ch<16;ch++)
	        {
	            printf("0x%x,",*((uint8_t *)(i*16+ch+VERIFIED_SECTOR*FLASH_SECTOR_SIZE)));
	        }
	        printf("\n\r");
	    }

	    printf("All data has been read.\n\r");*/
	
	
	for(;;) 
	{	
		WDOG_Feed();
		if(G_4sFlag == TRUE)
		{
			G_4sFlag = 0;
			G_4s_counter = 0;
			
			if((UART0_S2&UARTSR2_RAF_MASK)== 0)
			{
				Sleep_Process();
				Recover_Process();
			}
		}
		
		if((u8_lin_cmd_sleep == 1)||(u8_auto_roof_rain_measure_sleep_flg == 1)||(u8_wakeup_bcm_cnt_sleep_flg == 1))
		{
			if(u8_lin_cmd_sleep == 1)                    u8_lin_cmd_sleep = 0;
			if(u8_auto_roof_rain_measure_sleep_flg == 1) u8_auto_roof_rain_measure_sleep_flg = 0;
			if(u8_wakeup_bcm_cnt_sleep_flg == 1)         u8_wakeup_bcm_cnt_sleep_flg = 0;
			if((UART0_S2&UARTSR2_RAF_MASK)== 0)
			{
				Sleep_Process();
				Recover_Process();
			}
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
						if(u8_Rain_Flg == 1)
						{
							u16_RainWindow_Cnt++;
						}
						else 
						{
							u16_RainWindow_Cnt = 0;
						}
						
						if(u16_RainWindow_Cnt >= 800)
						{
							u8_Rain_Flg = 0;
						}
						
						RLS_Auto_Rain_Task();
						Lin_RLS_data();
						RLS_Battery_State();                
					}
					
					if( G_100msFlag == TRUE)
					{
						G_100msFlag = FALSE;  			
						RLS_Auto_Light_Task();
						//RLS_Auto_Rain_Task();	
						//Lin_RLS_data();
					}
					
					if( G_500msFlag == TRUE)
					{
						G_500msFlag = FALSE;
						FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
						Humid_Avg_Function(); 
						Temp_Avg_Function();
						Cal_F_Avg_Function();
						f_Dew_Point = Dew_Point_Cal(f_Temp_Avg,f_Humid_Avg);
						Dew_Point =  (uint16)(f_Dew_Point*10 + 396) ;
					}
			  }break;
			  
			  case SLEFADAPT:
			  {
				RLS_SelfAdaptTask();
				  RLS_RunMode = NORMAL;
				  
				  FUNC_READ_HUMDATA(SHT30_MEASU_CMD);
				  Humid_Avg_Function(); 
				  Temp_Avg_Function();
				  Cal_F_Avg_Function();
				  f_Dew_Point = Dew_Point_Cal(f_acture_temp,f_acture_hum);
				  Dew_Point =  (uint16)(f_Dew_Point*10 + 396) ;
			  }break;
			  
			  default: 
					 RLS_RunMode = NORMAL; 
					 break;
		}
				
	 }	
}
