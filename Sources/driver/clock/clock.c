/***************************************************************************//*!
*
* @file      clock.c
*
* @author    FPT Software
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include <derivative.h>
#include "clock.h"


/***********************************************************************************************
*
* @brief    CLK_Init - Initialize the clocks to run at 20 MHz from the 10Mhz external XTAL
* @param    none
* @return   none
*
************************************************************************************************/  
void Clk_Init(void)
{
	ICS_C1|=ICS_C1_IRCLKEN_MASK; 		/* Enable the internal reference clock*/ 
	//ICS_C3= 0x50;						/* Reference clock frequency = 39.0625 KHz*/		
	/* System clock initialization */

	if ( *((uint8_t*) 0x03FFU) != 0xFFU) {
		ICS_C3 = *((uint8_t*) 0x03FFU);
		ICS_C4 = (ICS_C4 & 0xFEU) | ((*((uint8_t*) 0x03FEU)) & 0x01U);
	}
	while(!(ICS_S & ICS_S_LOCK_MASK));   /* Wait for PLL lock, now running at 40 MHz (1024 * 39.0625Khz) */		
	ICS_C2|=ICS_C2_BDIV(1)  ; 			/*BDIV=2, Bus clock = 20 MHz*/
	ICS_S |= ICS_S_LOCK_MASK ; 			/* Clear Loss of lock sticky bit */		
}

