/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file     rtc.c
*
* @author   Freescale
*
* @brief    Real-time counter (RTC) driver source code.  
*
******************************************************************************/
#include "watchdog.h"
#include "config_parameter.h"
/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/


/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/


/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/


/**********************************************************************************************
* Global functions
**********************************************************************************************/
void WDOG_Unlock(void)
{
	WDOG_CNT = 0x20C5; WDOG_CNT = 0x28D9 ;
}

/*****************************************************************************//*!
*
* @brief initialize watchdog.
*        
* @param[in]   pConfig  poiner to watchdog configuration strcture.
*
* @return none
*
* @ Pass/ Fail criteria: none
* 
* @warning make sure that WDOG is not initialized after reset or WDOG update is enabled 
* after reset by calling WDOG_EnableUpdate / WDOG_DisableWDOGEnableUpdate.
*
* @see WDOG_EnableUpdate, WDOG_DisableWDOGEnableUpdate
*
*****************************************************************************/

void WDOG_Init(void)
{
	DISABLE_INTERRUPT; // disable global interrupt
	
	WDOG_Unlock();
	WDOG_TOVAL = 4000; // setting timeout value
	WDOG_CS2 = 0x01; // setting 1-kHz clock source
	WDOG_CS1 = WDOG_CS1_EN_MASK |WDOG_CS1_INT_MASK|WDOG_CS1_UPDATE_MASK| WDOG_CS1_STOP_MASK | WDOG_CS1_WAIT_MASK | WDOG_CS1_DBG_MASK; // enable counter running
	
	ENABLE_INTERRUPT;
}

/*****************************************************************************//*!
*
* @brief feed/refresh watchdog.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

void WDOG_Feed(void)
{
	DISABLE_INTERRUPT;
    WDOG_CNT = 0x02A6;
    WDOG_CNT = 0x80B4;
    ENABLE_INTERRUPT;
}



/*****************************************************************************//*!
*
* @brief enable update of WDOG. 
*        
* @param  none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @warning  this must be the last step of writing control bits sequence.
*****************************************************************************/

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
