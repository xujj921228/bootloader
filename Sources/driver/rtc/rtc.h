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
* @file     rtc.h
*
* @author   Freescale
*
* @brief    Real-time counter (RTC) driver head file.  
*
******************************************************************************/
#ifndef RTC_H_
#define RTC_H_

/*******************************************************************************
* Includes
********************************************************************************/
#include "derivative.h"

/*******************************************************************************
* Constants
********************************************************************************/


/*******************************************************************************
* Macros
********************************************************************************/

                
/*******************************************************************************
* Types
********************************************************************************/


/*******************************************************************************
* Variables
********************************************************************************/


/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/

/***********************************************************************************************
*
* @brief    RTC_Init - Initialize RTC counter 
* @param    none
* @return   none
*
************************************************************************************************/
extern void RTC_Init(void);
extern void RTC_EnableInt(void);
extern void RTC_DisableInt(void);
#endif /* RTC_H_ */