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
/******
 * DRIVE_flag
 * 0:init
 * 1:about driver
 * 2.about start eraser 
 * 3.about eraser tx ok
 * 4.about end eraser
 * 5.about start data
 * 6.flash write 
 * 7.reboot 
 * 8.request seed 
 * 9.send key 
 * ***********/
Boot_Fsm_t boot_status_flag;
uint8_t boot_rx_ok_id;
uint8_t boot_up_ret[2];

/************************
 * For all Var init
 * 
 * xujunjie@baolong.com
 * ********************/
void boot_Var_init(void)
{
   boot_status_flag = boot_fsm_idle;
   boot_rx_ok_id = 0;
   boot_up_ret[0] = 0;
   boot_up_ret[1] = 0;
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
	uint8_t vector_number = 0;
	
    l_sys_init();
	l_ifc_init(LI0);
	
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


/******************************************************************************
* protect bootloader section from 0 to 3FFF.
******************************************************************************/
void Flash_bootloader_protect(void)
{
	//Flash Protection Operation Enable
	FTMRH_FPROT |= FTMRH_FPROT_FPOPEN_MASK;
	//Flash Protection Higher Address Range Disable
	FTMRH_FPROT |= FTMRH_FPROT_FPHDIS_MASK;
	//Flash Protection Lower Address Range Disable
	FTMRH_FPROT &= ~FTMRH_FPROT_FPLDIS_MASK;
	//Flash Protection Lower Address Size, from 0 to 0x3FFF
	FTMRH_FPROT |= FTMRH_FPROT_FPLS_MASK;
}
/************************
 * For APP up close
 * 
 * xujunjie@baolong.com
 * ********************/
typedef void(*JumpToPtr)(void);

void boot_jump_to_APP(void)
{
	uint16_t *pNewAppEntry = (uint16_t)APP_start_address;
	JumpToPtr	pJumpTo;
	pJumpTo = (JumpToPtr)(*pNewAppEntry);
	pJumpTo();
	for(;;) { ; }
}

uint16_t u16Err_1 = FLASH_ERR_SUCCESS;

int main(void)
{	
	uint32_t flash_eraser_cn = 0;
	
	boot_sysinit();
	boot_Var_init();
	//Flash_bootloader_protect();

	//FLASH_EraseSector((VERIFIED_SECTOR+87)*FLASH_SECTOR_SIZE); // for debug eraser flag 
	//case 0: normal start jump to app
    if((boot_up_check() != 1)
       &&(boot_APP_check() == APP_VALUE))//if flag is equal to 1,jump to app.else doing updata
    {
	   //Jump to app
       boot_jump_to_APP();
	  // ((void (*)())0x5004)();
    }  
    
    
    //case 1: need to reload APP SDK
    Lin_Sys_Init();
    
    for(;;) 
	{			
    	
    	WDOG_Feed();
    	if(boot_rx_ok_id != 0) //rx ok 
    	{
    		//DISABLE_INTERRUPT;
            /* trigger callback */
            lin_update_rx(boot_rx_ok_id);
            boot_rx_ok_id = 0;
           // ENABLE_INTERRUPT;
    	}
    	
    	
		if(boot_status_flag == boot_fsm_erasering)//²Á³ýflashÉÈÇø
		{
			if(flash_eraser_cn >= 88)
			{
				flash_eraser_cn = 0;
				boot_status_flag = boot_fsm_enderaser;	
				do
				{
					boot_up_ret[0] = 0;
					write_data_from_EEPROM(0x10000020,boot_up_ret,2,ENABLE);
				}while(boot_up_check());
			}
			else
			{
				flash_eraser_cn++;
				u16Err_1 = FLASH_EraseSector((VERIFIED_SECTOR+flash_eraser_cn++)*FLASH_SECTOR_SIZE);
			}
		}
		if(boot_status_flag == boot_fsm_reboot)
		{
			((void (*)())0x0)();
			for(;;) { ; }
		}
		 

	} 	 
}



















