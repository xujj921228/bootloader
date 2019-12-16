/**************************************************************************//**
*
* @file      lin_common_api.c
*
* @author    xujunjie
*
* @brief     Common LIN API functions
*
*
******************************************************************************/


#include "lin_common_api.h"
#include "lin_common_proto.h"
#include "lin.h"


/* -------------------------------FUNCTION COMMON --------------------------- */
/** @addtogroup driver_cluster_group
* @{ */
l_bool l_sys_init ()
{
    lin_lld_timer_init();
    return 0;
} /* end of l_sys_init() */
/** @} */

/** @addtogroup interface_management_group
* @{ */
l_bool l_ifc_init
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    return lin_lld_init();
} /* end of l_ifc_init() */

void l_ifc_goto_sleep
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{

} /* end of l_ifc_goto_sleep() */

void l_ifc_wake_up
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    lin_lld_tx_wake_up();
} /* end of l_ifc_wake_up() */

void l_ifc_rx
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{

} /* end of l_ifc_rx() */

void l_ifc_tx
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{

} /* end of l_ifc_tx() */

void l_ifc_aux
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{

} /* end of l_ifc_aux() */
l_u16 l_ifc_read_status
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    static l_u16 tmp_word_status;

    tmp_word_status = lin_word_status.word;
    /* Clear word status */
    lin_word_status.word = 0;
    /* Clear save configuration flag value */
    lin_save_configuration_flg = 0;

    return (tmp_word_status);
} /* end of l_ifc_read_status() */
/** @} */

/** @addtogroup call_out_group
* @{ */
l_u16 l_sys_irq_disable
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    return lin_lld_int_disable();
} /* end of l_sys_irq_disable() */

void l_sys_irq_restore
(
    /* [IN] interface name */
    l_ifc_handle iii
)
{
    lin_lld_int_enable();
} /* end of l_sys_irq_restore() */
/** @} */
