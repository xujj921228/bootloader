#include "RTC.h"
/***********************************************************************************************
*
* @brief    RTC_Init - Initialize RTC counter 
*           Shanghai baolong  
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
	RTC_SC|=RTC_SC_RTCLKS(1);		/* 1K clock selected*/
	RTC_SC|=RTC_SC_RTCPS(6);		/* RTC prescaler of 100, 1Khz/100, RTC counter increases every 100ms */
	RTC_MOD = 70;  					/* Interrupts every 100*XX us = XX ms*/
	
   /* Set the ICPR and ISER registers accordingly */
	NVIC_ICPR |= 1 << ((INT_RTC-16)%32);
	NVIC_ISER |= 1 << ((INT_RTC-16)%32);
			
	RTC_DisableInt();	
}


void RTC_IRQHandler(void)
{	
	RTC_SC |= RTC_SC_RTIF_MASK ;
}
