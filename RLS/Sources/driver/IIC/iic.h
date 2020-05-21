/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      adc.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Sat Aug 04 10:53:51 CST 2018
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _IIC_H_  
#define    _IIC_H_  

#include "config_parameter.h"
#include "gpio.h"


#define G_Poly  0x31

#define  ACK    0
#define  NACK   1

#define ZERO    0

#define SHT30_ADDR 0x44
#define SHT30_RESET_CMD_H   0x30
#define SHT30_RESET_CMD_L   0xA2

#define SHT30_MEASU_CMD   0xE000
#define SHT30_ACQ_CMD     0x2322
#define SHT30_SACQ_CMD     0x240B


#define IIC_SDA_PULLUP      PORT_PUEL  |= 0x00000004       
#define IIC_SDA             ((GPIOA_PDIR&0x00000004)>>2)
#define IIC_SDA_Output()    {GPIOA_PDDR |= 0x00000004 ; GPIOA_PSOR |= 0x00000004 ;} //PTA2-output  SDA
#define IIC_SDA_Input()     {CONFIG_PIN_AS_GPIO(PTA,PTA2,INPUT);	ENABLE_INPUT(PTA,PTA2);}    
#define IIC_SDA_High()      GPIOA_PSOR |= 0x00000004
#define IIC_SDA_Low()       GPIOA_PCOR |= 0x00000004

#define IIC_SCL_PULLUP      PORT_PUEL  |= 0x00000008  
#define IIC_SCL_Output()    {GPIOA_PDDR |= 0x00000008 ; GPIOA_PSOR |= 0x00000008 ;} //PTA3-output  SCK 
#define IIC_SCL_Input()     {CONFIG_PIN_AS_GPIO(PTA,PTA3,INPUT);	ENABLE_INPUT(PTA,PTA3);}
#define IIC_SCL_High()      GPIOA_PSOR |= 0x00000008
#define IIC_SCL_Low()       GPIOA_PCOR |= 0x00000008

extern uint8 FUNC_HUM_SETTING(uint16 cmd);
extern void  DRV_IIC_Init(void);

extern void  DRV_IIC_START(void);
extern void  DRV_IIC_STOP(void);

extern uint8 DRV_IIC_WRITE_BYTE(uint8 data);
extern uint8 DRV_IIC_READ_BYTE(uint8 AckValue);

extern uint8 DRV_IIC_WriteSignleData(uint8 cmd,uint8 reg,uint8 data);
extern uint8 DRV_IIC_WriteMultipleData(uint8 cmd,uint8 reg,uint8 num,uint8 *data);

extern uint8 DRV_IIC_ReadSingleData(uint8 cmd, uint8 reg); 
extern uint8 DRV_IIC_ReadMultipleData(uint8 cmd, uint8 reg,uint8 num,uint8 *data);

#endif    /* _ADC_H_ */
