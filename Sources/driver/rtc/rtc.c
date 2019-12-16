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
#include "RTC.h"
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

/***********************************************************************************************
*
* @brief    RTC_Init - Initialize RTC counter 
* @param    none
* @return   none
*
************************************************************************************************/

void RTC_EnableInt(void)
{   
	RTC_SC |= RTC_SC_RTIE_MASK;	
}

void RTC_DisableInt(void)
{   
	RTC_SC &= ~RTC_SC_RTIE_MASK;
}

void RTC_Init(void)  //10S
{
	SIM_SCGC |=  SIM_SCGC_RTC_MASK;		/* Enable clock for RTC*/
	RTC_SC|=RTC_SC_RTCLKS(0x01);		/* 1K clock selected*/
	RTC_SC|=RTC_SC_RTCPS(0x06);		/* RTC prescaler of 100, 1Khz/100, RTC counter increases every 100ms */
	RTC_MOD = 140;  					/* Interrupts every 100*XX us = XX ms*/
	
   /* Set the ICPR and ISER registers accordingly */
	NVIC_ICPR |= 1 << ((INT_RTC-16)%32);
	NVIC_ISER |= 1 << ((INT_RTC-16)%32);
			
	RTC_DisableInt();	
}


void RTC_IRQHandler(void)
{	
	RTC_SC |= RTC_SC_RTIF_MASK ;
}
