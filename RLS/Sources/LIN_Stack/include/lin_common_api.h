/**************************************************************************//**
*
* @file      lin_common_api.h
*
* @author    FPT Software
*
* @brief     Common LIN API functions
*
******************************************************************************/


#include "lin.h"
/*FUNCTION*--------------------------------------------------------------*//**
* @fn l_bool l_sys_init ( void )
* @brief This function performs the initialization of the LIN core
*
* @return #l_bool
*
* @SDD_ID LIN_SDD_238
* @endif
*
* @details
*   This function performs the initialization of the LIN core
*
* @see  #lin_lld_setup_xgate
* @see  #lin_lld_timer_init
*
* @addtogroup driver_cluster_group
*//*END*----------------------------------------------------------------------*/
l_bool        l_sys_init (void);

l_bool        l_ifc_init (l_ifc_handle iii);


void          l_ifc_wake_up (l_ifc_handle iii);

void          l_ifc_rx (l_ifc_handle iii);

void          l_ifc_tx (l_ifc_handle iii);

l_u16         l_ifc_read_status (l_ifc_handle iii);

void          l_ifc_aux (l_ifc_handle iii);

l_u16         l_sys_irq_disable (l_ifc_handle iii);

void          l_sys_irq_restore (l_ifc_handle iii);

