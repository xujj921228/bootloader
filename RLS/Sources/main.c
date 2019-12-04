#include <SKEAZN642.h>
#include <math.h> 
#include "clock.h"
#include "gpio.h"
#include "eeprom.h"
#include "lin_common_api.h"
#include "lin_common_proto.h"
#include "lin_lld_uart.h"

/***********************************************************************************************
* name :  main
* input:  none
* output: none
* introduction:For lin-boot
* author:xujunjie@bb.com
*2019/10/17
************************************************************************************************/  


/************** var   ******************/
uint8 boot_eraser_flag;
l_u16 updata_flash_ID;
l_u16 updata_length;
uint8 DRIVE_flag;
uint8 tx_ok;
uint8 boot_reboot;



/************************
 * For all Var init
 * 
 * xujunjie@baolong.com
 * ********************/
void boot_Var_init(void)
{
   boot_eraser_flag = 0;
   updata_flash_ID = 0;
   updata_length = 0;
   DRIVE_flag = 0;
   tx_ok = 0;
   boot_reboot = 0;
}


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



/************************
 * For all sys init
 * 
 * xujunjie@baolong.com
 * ********************/
void boot_sysinit(void)
{
	Clk_Init();	                           //time for MCU;
    GPIO_Init();                           //Setting the LDO of LIN to control Power.   
	FLASH_Init(BUS_CLCOK);                 /*Initialize the Flash Memory module */
}


/************************
 * For APP up close
 * 
 * xujunjie@baolong.com
 * ********************/
typedef void(*JumpToPtr)(void);

void boot_jump_to_APP(void)
{
	uint16_t *pNewAppEntry = APP_start_address;
	JumpToPtr	pJumpTo;
	pJumpTo = *pNewAppEntry;
	pJumpTo();
	for(;;) { ; }
}

uint16_t u16Err_1 = FLASH_ERR_SUCCESS;

void main(void)
{	
	
	uint32 flash_eraser_cn = 0;
	uint16 boot_up_ret = 0xffff;
	
	boot_sysinit();
	boot_Var_init();

	//FLASH_EraseSector((VERIFIED_SECTOR+87)*FLASH_SECTOR_SIZE); // for debug eraser flag 
	//case 0: normal start jump to app
    if((boot_up_check() != boot_up_value)
       &&(boot_APP_check() == APP_VALUE))//if flag is equal to 1,jump to app.else doing updata
    {
	   //Jump to app
       boot_jump_to_APP();
    }  
    
    
    //case 1: need to reload APP SDK
    Lin_Sys_Init();
    
    for(;;) 
	{				
    	WDOG_Feed();
		if((boot_eraser_flag == 1)&&(tx_ok == 1))//≤¡≥˝flash…»«¯
		{
			if(flash_eraser_cn >= 88)
			{
				flash_eraser_cn = 0;
				boot_eraser_flag = 2;	
				do
				{
					write_data_from_EEPROM(0x10000020,&boot_up_ret,2,ENABLE);
				}while(boot_up_check() == boot_up_value);
			}
			else
			{
				u16Err_1 = FLASH_EraseSector((VERIFIED_SECTOR+flash_eraser_cn++)*FLASH_SECTOR_SIZE);
			}
		}
		if(boot_reboot == 1)//÷ÿ∆Ù√¸¡Ó
		{
			while(1);
		}
		 

	} 	 
}



















