#include "lin.h"

/* Node configuration */
#define LD_READ_OK                        0x33   /**< Read OK */
#define LD_LENGTH_TOO_SHORT               0x34   /**< Lenghth too short */

#define LD_DATA_ERROR                     0x43   /**< Data error */
#define LD_LENGTH_NOT_CORRECT             0x44   /**< Lenghth not correct */
#define LD_SET_OK                         0x45   /**< Set OK */


void ld_init(void);

void ld_put_raw(const l_u8* const data);

void ld_get_raw(l_u8* const data);

l_u8 ld_raw_tx_status(void);

l_u8 ld_raw_rx_status(void);

void ld_send_message(l_u16 length, const l_u8* const data);
void ld_receive_message(l_u16* const length, l_u8* const data);

l_u8 ld_tx_status(void);

l_u8 ld_rx_status(void);



l_u8 ld_read_configuration(l_u8* const data, l_u8* const length);

l_u8 ld_set_configuration(const l_u8* const data, l_u16 length);

