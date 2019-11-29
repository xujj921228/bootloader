#include <SKEAZN642.h>
#include <math.h> 
#include "clock.h"
#include "gpio.h"
#include "eeprom.h"
#include "lin_common_api.h"
#include "lin_common_proto.h"
#include "lin_lld_uart.h"


/********************************
 * define  APP check  address
 * add by xujunjie
 * *****************************/
#define  APP_check_ADDRESS      0XFFFC
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

/**********************
 * updata  flag (eeprom) 0x5a:should updata  else:no need to updata
 * app check flag (last two byte in flash )
 * ****************************/

typedef enum
{
 APP_INVALUE = 0 ,
 APP_VALUE   = 1   
}APP_check_t;

uint8 APP_check_value[4]={0xa5,0x5a,0xa4,0x4a};


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
 * For APP check
 * 
 * xujunjie@baolong.com
 * ********************/
APP_check_t boot_APP_check(void)
{
	uint8 i;
	APP_check_t ret = APP_VALUE;
	uint8 temp[4] ={ 0 };
	
	for(i = 0;i < 4; i++)
	{
		temp[i] = *((uint8_t *)(APP_check_ADDRESS+i));
		if(APP_check_value[i] != temp[i])
		{
			ret = APP_INVALUE;
		}
	}
	
	return  ret;
}
/************************
 * For APP up check
 * 
 * xujunjie@baolong.com
 * ********************/
uint8 boot_up_check(void)
{
	uint8 ret = 0xFF;
	
	read_data_from_EEPROM(EEPROM_BOOT_REFRESH,&ret,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
	
	return ret;
}

/************************
 * For APP up close
 * 
 * xujunjie@baolong.com
 * ********************/
typedef void(*JumpToPtr)(void);

void boot_jump_to_APP(void)
{
	uint16_t *pNewAppEntry = 0x5004;
	JumpToPtr	pJumpTo;
	pJumpTo = *pNewAppEntry;
	pJumpTo();
	for(;;) { ; }
}


void main(void)
{	
	uint8 flash_eraser_cn;
	uint32 id_add;
	
	boot_sysinit();
	boot_Var_init();

	
	//case 0: normal start jump to app
    if((boot_up_check() != 0x5a)
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
		if(boot_eraser_flag == 1)//²Á³ýflashÉÈÇø
		{
			if(flash_eraser_cn >= 88)
			{
				flash_eraser_cn = 0;
				boot_eraser_flag = 0;
				
			}
			else
			{
				FLASH_EraseSector((VERIFIED_SECTOR+boot_eraser_flag++)*FLASH_SECTOR_SIZE);
			}
		}
		 

	} 	 
}



















