#ifndef __IIC_H__
#define __IIC_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */


#define G_Poly  0x31

#define  ACK    0
#define  NACK   1

#define ZERO    0

#define SHT30_ADDR 0x44
#define SHT30_RESET_CMD_H   0x30
#define SHT30_RESET_CMD_L   0xA2

#define SHT30_MEASU_CMD   0xE000
#define SHT30_ACQ_CMD     0x2322


/*
#define IIC_SDA_PULLUP      PER01AD_PER1AD6
#define IIC_SDA             PT01AD_PT1AD6
#define IIC_SDA_Output()    DDR01AD_DDR1AD6 = 1 
#define IIC_SDA_Input()     DDR01AD_DDR1AD6 = 0  
#define IIC_SDA_Low()       PT01AD_PT1AD6   = 0
#define IIC_SDA_High()      PT01AD_PT1AD6   = 1 

#define IIC_SCL_PULLUP      PER01AD_PER1AD7
#define IIC_SCL_Output()    DDR01AD_DDR1AD7 = 1 
#define IIC_SCL_Input()     DDR01AD_DDR1AD7 = 0
#define IIC_SCL_High()      PT01AD_PT1AD7   = 1
#define IIC_SCL_Low()       PT01AD_PT1AD7   = 0
*/

#define IIC_SDA_PULLUP      PERT_PERT0      
#define IIC_SDA             PTT_PTT0
#define IIC_SDA_Output()    DDRT_DDRT0 = 1 
#define IIC_SDA_Input()     DDRT_DDRT0 = 0  
#define IIC_SDA_Low()       PTT_PTT0   = 0
#define IIC_SDA_High()      PTT_PTT0   = 1 

#define IIC_SCL_PULLUP      PERT_PERT1
#define IIC_SCL_Output()    DDRT_DDRT1 = 1 
#define IIC_SCL_Input()     DDRT_DDRT1 = 0
#define IIC_SCL_High()      PTT_PTT1   = 1
#define IIC_SCL_Low()       PTT_PTT1   = 0

extern void  DRV_IIC_Init(void);

extern void  DRV_IIC_START(void);
extern void  DRV_IIC_STOP(void);

extern uint8 DRV_IIC_WRITE_BYTE(uint8 data);
extern uint8 DRV_IIC_READ_BYTE(uint8 AckValue);

extern uint8 DRV_IIC_WriteSignleData(uint8 cmd,uint8 reg,uint8 data);
extern uint8 DRV_IIC_WriteMultipleData(uint8 cmd,uint8 reg,uint8 num,uint8 *data);

extern uint8 DRV_IIC_ReadSingleData(uint8 cmd, uint8 reg); 
extern uint8 DRV_IIC_ReadMultipleData(uint8 cmd, uint8 reg,uint8 num,uint8 *data);

#endif