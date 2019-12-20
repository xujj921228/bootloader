

/* MODULE LIN_LLD_UART. */

#include "lin_reg.h"
#include "lin_cfg.h"
#include "lin.h"


/*** MARCOS ***/

/* Lin status bit mask */
#define LIN_STA_SUCC_TRANSFER           1         /**< LIN status bit mask: success transfer */
#define LIN_STA_ERROR_RESP              2         /**< LIN status bit mask: error in response */
#define LIN_STA_BUS_ACTIVITY            4         /**< LIN status bit mask: bus activity */
#define LIN_STA_FRAME_ERR               8         /**< LIN status bit mask: frame error */
#define LIN_STA_CHECKSUM_ERR            16        /**< LIN status bit mask: checksum error */
#define LIN_STA_READBACK_ERR            32        /**< LIN status bit mask: readback error */
#define LIN_STA_PARITY_ERR              64        /**< LIN status bit mask: parity error */
#define LIN_STA_RESET                   128       /**< LIN status bit mask: reset */


void lin_lld_uart_init(l_ifc_handle iii);


void lin_lld_uart_deinit(void);


void lin_lld_uart_tx_wake_up(void);


void lin_lld_uart_int_enable(void);


void lin_lld_uart_int_disable(void);


void lin_lld_uart_ignore_response(void);


void lin_lld_uart_set_low_power_mode(void);


void lin_lld_uart_rx_response(l_u8  msg_length);


void lin_lld_uart_tx_response(void);


l_u8 lin_lld_uart_get_status(void);


l_u8 lin_lld_uart_get_state(void);



void lin_lld_uart_err_isr(void);


void lin_lld_uart_rx_isr(void);


void lin_goto_idle_state(void);

void lin_lld_uart_timeout();

