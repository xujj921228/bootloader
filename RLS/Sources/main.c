#include <SKEAZN642.h>
#include <math.h> 

#include "clock.h"
#include "gpio.h"
#include "eeprom.h"
#include "lin_common_api.h"

/*******************************************************
 * FUNCTION NAME : Lin_Busy_Process()
 *   DESCRIPTION : Lin_Busy_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Lin_Sys_Init(void)
{
	uint8 ret = 0 ;
	uint8 vector_number = 0;
	
    ret = l_sys_init();
	ret = l_ifc_init(LI0);
	
	vector_number = INT_UART0 -16;
	
	NVIC_ICPR |= 1 << (vector_number%32);
	NVIC_ISER |= 1 << (vector_number%32);
}

#define VERIFIED_SECTOR				64
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

uint8  u8refresh_flag;// 0x5a:updata app else:normal
uint8  u8App_value_flag;

typedef void(*JumpToPtr)(void);
uint16_t *pNewAppEntry = 0x3004;
uint16_t *pFlashlastflag = 0xFFFF;
JumpToPtr	pJumpTo;

void Var_int(void)
{
	u8refresh_flag = 0xff;
	u8App_value_flag = 0;
}

/*
void FLASH_Erase_APPSector(void)
{
   uint16_t u16Err = 0;
   uint8 i;
   u16Err += FLASH_EraseSector(VERIFIED_SECTOR*FLASH_SECTOR_SIZE);
 
}
*/
uint8 app_flagvalue;
uint8 APP_CRC_value;
void main(void)
{	
	char ch;
	uint32 i;
	

	Clk_Init();	  //time for MCU;
	GPIO_Init();  //Setting the LDO of LIN to control Power.   
	/*Initialize the Flash Memory module */
    FLASH_Init(BUS_CLCOK);
    Var_int();
    read_data_from_EEPROM(EEPROM_BOOT_REFRESH,&u8refresh_flag,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
    
    
    
    
    
   /* //FLASH_EraseSector(VERIFIED_SECTOR*FLASH_SECTOR_SIZE);
     Write data to erased sector 
   	FLASH_Program( VERIFIED_SECTOR*FLASH_SECTOR_SIZE,&u8DataBuff[0],256 );
   	FLASH_Program( VERIFIED_SECTOR*FLASH_SECTOR_SIZE+256,&u8DataBuff[0],256 );
   	 Read data from the newly written sector 
   	for( i=0;i<512/16;i++ )
   	{
   	  for(ch =0;ch<16;ch++)
   	   {
   	     u8DataBuff_read[i*16+ch] = *((uint8_t *)(i*16+ch+VERIFIED_SECTOR*FLASH_SECTOR_SIZE));
   	   }
   	}
    */
    
    
    
    
    /*****************************************
     * 软件有效标志位测试，在flash最后一位标记A5
     * ***************************************/
    APP_CRC_value = 0xa5;
    FLASH_Program( VERIFIED_SECTOR*FLASH_SECTOR_SIZE,&APP_CRC_value,1 );//FLASH写最后一个字节
    app_flagvalue = *((uint8_t *)(pFlashlastflag));
    
    
    
    if( app_flagvalue!= 0xff)
    {
        u8App_value_flag = 1;  //mark APP value
    }
  
    if((u8refresh_flag != 0x5a)&&(u8App_value_flag == 1))//if flag is equal to 1,jump to app.else doing updata
    {
	   //Jump to app
	   pJumpTo = *pNewAppEntry;
	   pJumpTo();
       for(;;) { ; }
    }
    
    Lin_Sys_Init();
    
    for(;;) 
	{		
    	
    	

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
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
}



















