/**************************************************************************//**
 *
 * @file      lin_lin21tl_api.c
 *
 * @author    FPT Software
 *
 * @brief     LIN21 LIN transport layer and configuration functions
 *
 ******************************************************************************/

#include "lin_lin21tl_api.h"

/* get diagnostic flag */
l_u8 diag_get_flag(l_u8 flag_order)
{
    if (flag_order >= _DIAG_NUMBER_OF_SERVICES_)
    {
        return 0;
    }
    else
    {
        return (l_u8) lin_diag_services_flag[flag_order];
    }

}

void diag_clear_flag(l_u8 flag_order)
{
    if (flag_order < _DIAG_NUMBER_OF_SERVICES_)
    {
        lin_diag_services_flag[flag_order] = 0;
    }
}

