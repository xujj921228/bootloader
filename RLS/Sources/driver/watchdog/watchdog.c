/***************************************************************************//*!
*
* #company  Shanghai baolong
*
* #author   xujunjie@bb.com
*
* #brief    Watchdog for code  
*
* #time    2020/04/01
*
******************************************************************************/
#include "watchdog.h"
#include "config_parameter.h"

/***************************************************************************//*!
*
* #company  Shanghai baolong
*
* #author   xujunjie@bb.com
*
* #brief    WDOG_Unlock  
*
* #time    2020/04/01
* 
* #input   none
*
* #output   none
*
******************************************************************************/
void WDOG_Unlock(void)
{
	WDOG_CNT = 0x20C5; WDOG_CNT = 0x28D9 ;
}

/***************************************************************************//*!
*
* #company  Shanghai baolong
*
* #author   xujunjie@bb.com
*
* #brief    WDOG_Init  
*
* #time    2020/04/01
* 
* #input   none
*
* #output   none
*
******************************************************************************/
void WDOG_Init(void)
{
	DISABLE_INTERRUPT; // disable global interrupt
	
	WDOG_Unlock();
	WDOG_TOVAL = 4000; // setting timeout value
	WDOG_CS2 = 0x01; // setting 1-kHz clock source
	WDOG_CS1 = WDOG_CS1_EN_MASK |WDOG_CS1_INT_MASK|WDOG_CS1_UPDATE_MASK| WDOG_CS1_STOP_MASK | WDOG_CS1_WAIT_MASK | WDOG_CS1_DBG_MASK; // enable counter running
	
	ENABLE_INTERRUPT;
}

/***************************************************************************//*!
*
* #company  Shanghai baolong
*
* #author   xujunjie@bb.com
*
* #brief    WDOG_Feed  
*
* #time    2020/04/01
* 
* #input   none
*
* #output   none
*
******************************************************************************/
void WDOG_Feed(void)
{
     DISABLE_INTERRUPT;
     WDOG_CNT = 0x02A6;
     WDOG_CNT = 0x80B4;
     ENABLE_INTERRUPT;
}


/***************************************************************************//*!
*
* #company  Shanghai baolong
*
* #author   xujunjie@bb.com
*
* #brief    WDOG_EnableUpdate  
*
* #time    2020/04/01
* 
* #input   none
*
* #output   none
*
******************************************************************************/
void WDOG_EnableUpdate(void)
{
    uint8_t u8Cs1 =  WDOG_CS1;  
    uint8_t u8Cs2 =  WDOG_CS2;  
    uint16_t u16TOVAL =  WDOG_TOVAL;  
    uint16_t u16WIN =  WDOG_WIN;  

    u8Cs1 |= WDOG_CS1_UPDATE_MASK;

	/* First unlock the watchdog so that we can write to registers */
    WDOG_Unlock(); 
    WDOG_CS2    =  u8Cs2;
    WDOG_TOVAL  =  u16TOVAL;
    WDOG_WIN    =  u16WIN;
    WDOG_CS1    =  u8Cs1;  
}



void WDG_IRQHandler(void) 
{
	/* Clear WDOG flag*/
	WDOG_CS2 |= WDOG_CS2_FLG_MASK;   

}
