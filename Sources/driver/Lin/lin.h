#ifndef __LIN_H__
#define __LIN_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"


#define LIN_DATA  SCI0DRL



extern uint8 LinSendChar(uint8 brk, uint8 ch);
extern uint8 LinCalcParity(uint8 id);
extern uint8 LinCalcChecksum(uint8 *data);
extern uint8 EnhancedLinCalcChecksum(uint8 *data, uint8 val);
extern uint8 LinSndMsg(struct Lin_message msg,uint8 DTC);
extern uint8 Lin_chkparity(uint8 parity_id);
extern void  Lin_send_break(void);

#endif