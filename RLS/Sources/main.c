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
#define VERIFIED_SECTOR				32
#define BUS_CLK_HZ					24000000

uint8  u8DataBuff[256];
uint8  u8DataBuff_read[512];
void main(void)
{	
	char ch;
	uint32 i;
	Clk_Init();	
	FTM0_Init();
	GPIO_Init();//Setting the LDO of LIN to control Power.   
	RTC_Init();
	//Lin_Sys_Init();
	/*Initialize the Flash Memory module */
	    FLASH_Init(BUS_CLCOK);

	    /* Erase 32th sector */
	    FLASH_EraseSector(VERIFIED_SECTOR*FLASH_SECTOR_SIZE);

	    /* Initialize the variable */
	    for(i=0;i<256;i++)
	    {
	        u8DataBuff[i] = (uint8_t)i;
	    }

	    /* Write data to erased sector */
	    FLASH_Program( VERIFIED_SECTOR*FLASH_SECTOR_SIZE,&u8DataBuff[0],256 );
	    FLASH_Program( VERIFIED_SECTOR*FLASH_SECTOR_SIZE+256,&u8DataBuff[0],256 );

	    //printf("\nReading the newly written sector\n\r");

	    /* Read data from the newly written sector */
	    for( i=0;i<512/16;i++ )
	    {
	        for(ch =0;ch<16;ch++)
	        {
	        	u8DataBuff_read[i*16+ch] = *((uint8_t *)(i*16+ch+VERIFIED_SECTOR*FLASH_SECTOR_SIZE));
	            //printf("0x%x,",*((uint8_t *)(i*16+ch+VERIFIED_SECTOR*FLASH_SECTOR_SIZE)));
	        }
	       // printf("\n\r");
	    }

	    //printf("All data has been read.\n\r");
	
	
	for(;;) 
	{	
		WDOG_Feed();
		
				
	 }	
}
