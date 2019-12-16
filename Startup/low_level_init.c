/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2014
 *
 *    File name   : low_level_init.c
 *    Description : Low level init procedure
 *
 *
 *    $Revision: 16 $
 **************************************************************************/
#include <derivative.h>

extern uint32_t __vector_table[];

/*************************************************************************
 * Function Name: low_level_init
 * Parameters: none
 *
 * Return: none
 *
 * Description: This function is used for low level initialization
 *
 *************************************************************************/
int __low_level_init(void)
{
  SCB_VTOR = (uint32_t)__vector_table; /* Set the interrupt vector table position */
  WDOG_CS1 = 0x23;//A4 WDOG_CS1_EN_MASK |WDOG_CS1_INT_MASK|WDOG_CS1_UPDATE_MASK| WDOG_CS1_STOP_MASK | WDOG_CS1_WAIT_MASK | WDOG_CS1_DBG_MASK; // enable counter running               
  WDOG_CS2 = 0x01; // setting 1-kHz clock source
  WDOG_TOVALH = 0x0F;
  WDOG_TOVALL = 0xA0;
  return 1;
}
