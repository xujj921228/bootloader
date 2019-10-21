/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include <math.h> 

#include "clock.h"
#include "gpio.h"
#include "eeprom.h"




#define VERIFIED_SECTOR				12
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
uint8  u8refresh_flag;// 1:normal app else:updata

typedef void(*JumpToPtr)(void);
uint32_t *pNewAppEntry = 0x3004;
JumpToPtr	pJumpTo;
void main(void)
{	
	char ch;
	uint32 i;
	Clk_Init();	  //time for MCU;
	GPIO_Init();  //Setting the LDO of LIN to control Power.   
	/*Initialize the Flash Memory module */
    FLASH_Init(BUS_CLCOK);
    read_data_from_EEPROM(EEPROM_BOOT_REFRESH,&u8refresh_flag,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
    if(u8refresh_flag != 1)//if flag is equal to 1,jump to app.else doing updata
    {
    	//jump to app
		  //Jump to app
		   pJumpTo = *pNewAppEntry;
		   pJumpTo();
		   while(1)
		   {
		    	  i++;
		   }
    	        for(;;) { ; }
    }
 
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
	/* Read data from the newly written sector */
	for( i=0;i<512/16;i++ )
	{
	  for(ch =0;ch<16;ch++)
	   {
	     u8DataBuff_read[i*16+ch] = *((uint8_t *)(i*16+ch+VERIFIED_SECTOR*FLASH_SECTOR_SIZE));
	   }
	}
	
	 for( u8refresh_flag = 0; u8refresh_flag < 50 ; u8refresh_flag++ )
	 {
		 write_data_from_EEPROM(EEPROM_BOOT_REFRESH,&u8refresh_flag,EEPROM_BOOT_REFRESH_LENTH,1);
		 	read_data_from_EEPROM(EEPROM_BOOT_REFRESH,&u8refresh_flag,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
	 }
	
    for(;;) 
	{		

	}	
}
