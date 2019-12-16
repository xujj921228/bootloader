
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
* @file pmc.c
*
* @author Freescale
*
* @brief providing APIs for configuring PMC. 
*
*******************************************************************************
*
* provide APIs for configuring PMC
******************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "pmc.h"
#include "config_parameter.h"

/******************************************************************************
* Constants
******************************************************************************/
/******************************************************************************
* Macros
******************************************************************************/
/******************************************************************************
* Types
******************************************************************************/
/******************************************************************************
* Global variables
******************************************************************************/
/******************************************************************************
* Global functions
******************************************************************************/

void PMC_Init(void)
{
	uint8 ret;
	PMC_SPMSC1  = 0;

	PMC_SPMSC1 |= PMC_SPMSC1_BGBE_MASK;	/* Enable Bandgap buffer */
	PMC_SPMSC1 &= ~PMC_SPMSC1_LVDSE_MASK;	/* Disable Low-Voltage Detect(LVD) in Stop mode */
	PMC_SPMSC1 &= ~PMC_SPMSC1_LVDRE_MASK;	/* LVD events do not generate hardware resets. */
	
	PMC_SPMSC1 &= ~PMC_SPMSC1_LVWIE_MASK;
	
	ret = PMC_SPMSC1 & PMC_SPMSC1_LVWF_MASK ;
}
/*! @} End of pmc_api_list                                                    */

