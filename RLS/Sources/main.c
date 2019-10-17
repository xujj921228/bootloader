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
#include "gpio.h"
#include "eeprom.h"
#include "ftm.h"
#include "rtc.h"
#include "watchdog.h"
#include "lin_app.h"
#include "humid.h"

#define VERIFIED_SECTOR				32
/***********************************************************************************************
* name :  main
* input:  none
* output: none
* introduction:For lin-boot
* author:xujunjie@bb.com
*2019/10/17
************************************************************************************************/  
uint8  u8DataBuff[256];
uint8  u8DataBuff_read[512];
void main(void)
{	
	char ch;
	uint32 i;
	Clk_Init();	  //time for MCU;
	FTM0_Init();  //TIM
	GPIO_Init();  //Setting the LDO of LIN to control Power.   
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
	        }
	    }

	
	
	for(;;) 
	{	
		 WDOG_Feed();	
		
	}	
}
