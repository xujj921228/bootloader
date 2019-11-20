/******************************************************************************
 *
 * History:
 *
 * 20090407     v1.0    First version
 * 20111005     v1.1    Added extern functions
 *
 *****************************************************************************/


#include "lin.h"

/* define PCI type */
#define PCI_SF                            0x00      /**< Single Frame */
#define PCI_FF                            0x01      /**< First Frame */
#define PCI_CF                            0x02      /**< Consecutive Frame */

/* For J2602 */
#define SERVICE_TARGET_RESET              0xB5      /**< target reset service */
#define RES_POSITIVE                      0x40      /**< positive response */

/* For negative response */
#define RES_NEGATIVE                      0x7F      /**< negative response */
#define GENERAL_REJECT                    0x10      /**< Error code raised when request for service not supported comes  */
#define SERVICE_NOT_SUPPORTED             0x11      /**< Error code in negative response for not supported service */
#define SUBFUNCTION_NOT_SUPPORTED         0x12      /**< Error code in negative response for not supported subfunction  */
#define INVALID_FORMAT                    0x13
#define REQ_OUT_RANGE                     0x31
#define SERVICE_NOT_SUPPORTED_ACTIVE_SESSION 0x7F

/* Response type from Slave */
#define NEGATIVE 0                                  /**< negative response */
#define POSITIVE 1                                  /**< positive response */
/* multi frame support */

/* Transmission direction */
#define TRANSMISSION 0                              /**< transmission */
#define RECEIVING    1                              /**< receiveing */

/* Define wildcards */
#define LD_BROADCAST                      0x7F   /**< NAD */
#define LD_FUNCTIONAL_NAD                 0x7E   /**< functional NAD */
#define LD_ANY_SUPPLIER                   0x7FFF /**< Supplier */
#define LD_ANY_FUNCTION                   0xFFFF /**< Function */
#define LD_ANY_MESSAGE                    0xFFFF /**< Message */

/* Identifiers of node read by identifier service */
#define LIN_PRODUCT_IDENT                 0x00   /**< Node product identifier */
#define SERIAL_NUMBER                     0x01   /**< Serial number */

/* Identifiers of node read data by identifier service */
#define LIN_PRODUCT_SERIAL_NUMBER0           0xF185
#define LIN_PRODUCT_SERIAL_NUMBER1           0xF186
#define LIN_PRODUCT_SERIAL_NUMBER2           0xF187
#define LIN_PRODUCT_SERIAL_NUMBER3           0xF188

#define LIN_LS_FW_PARAM                     0x1301
#define LIN_LS_IR_PARAM                     0x1302

#define LIN_RAIN_ADC_A_PARAM                0x130A
#define LIN_RAIN_ADC_B_PARAM                0x130B



extern l_u8 ld_read_by_id_callout(l_u8 id, l_u8 *data);

void lin_tl_make_slaveres_pdu(l_u8 sid, l_u8 res_type, l_u8 error_code);


void lin_tl_attach_service(void);

void lin_tl_get_pdu(void);

void lin_tl_put_pdu(void);

void lin_tl_handler(void);


void tl_put_raw(const l_u8* const data,lin_transport_layer_queue *queue,l_u8 direction);

void tl_get_raw(l_u8* const data,lin_transport_layer_queue *queue,l_u8 direction);

