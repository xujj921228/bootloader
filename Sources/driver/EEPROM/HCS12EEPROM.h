
#ifndef __HCS12EEPROM_H__
#define __HCS12EEPROM_H__

#include "global_parameter.h" 

#define  EEPROM_START_ADDR 0x400

#define  Cmd_Erase_Section 0x12
#define  Cmd_EEProgram     0x11

#define  EEPROM_A_DAC_ADDR            0x404
#define  EEPROM_A_GAIN_ADDR           0x408

#define  EEPROM_B_DAC_ADDR            0x40C
#define  EEPROM_B_GAIN_ADDR           0x410

#define  EEPROM_FW_ADDR               0x414
#define  EEPROM_IR_ADDR               0x418
#define  EEPROM_BR_LIG_PER_ADDR       0x41C
#define  EEPROM_BR_INF_PER_ADDR       0x420
#define  EEPROM_SCUTTLE_CONTROL_ADDR  0x424

#define  EEPROM_LIGHT_CAL_ADDR  0x428

#define  EEPROM_GAIN_PRM_ADDR   0x42C

extern void HCS12_EE_Cmd(uint16 EEPROM_ADDR,uint8 Cmd,uint16 index,uint16 *data,uint8 n);
extern void HCS12_EE_Init(void);
extern uint16 EE_Byte_Read(uint16 EEPROM_ADDR,uint16 index); 
extern void EE_Erase_Section(uint16 EEPROM_ADDR,uint16 index);
extern void HCS12_EE_Read_2Word(uint16 EEPROM_ADDR,uint16 *data);
extern void HCS12_EE_Write_2Word(uint16 EEPROM_ADDR,uint16 *data);

#endif