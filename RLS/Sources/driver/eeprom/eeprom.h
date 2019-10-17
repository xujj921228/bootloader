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
#ifndef    _EEPROM_H_  
#define    _EEPROM_H_  

#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"


#define     ENABLE                        1
#define     DISABLE                       0


#define FTMRE_FSTAT_MGSTAT0_MASK  (1)						/* FTMRE FSTAT MGSTAT0 MASK */
#define FTMRE_FSTAT_MGSTAT1_MASK  (1<<1)					/* FTMRE FSTAT MGSTAT1 MASK */
/*! @} End of flash_MGSTAT_list                                                */

#define FLASH_SECTOR_SIZE			512						/* FTMRE sector size*/
#define FLASH_START_ADDRESS			0						/* FTMRE start address */
#define EEPROM_START_ADDRESS		0x10000000				/* EEPRON start address*/
#define EEPROM_END_ADDRESS		    0x100000FF				/* EEPRON start address*/
/******************************************************************************
* flash and eeprom driver error status
*
*//*! @addtogroup flash_error_list
* @{
*******************************************************************************/
#define FLASH_ERR_BASE				0x3000										/* FTMRE error base */
#define FLASH_ERR_SUCCESS			0											/* FTMRE sucess */
#define FLASH_ERR_INVALID_PARAM		(FLASH_ERR_BASE+1)							/* Invalid parameter error code */
#define EEPROM_ERR_SINGLE_BIT_FAULT	(FLASH_ERR_BASE+2)							/* EEPROM single bit fault error code */
#define EEPROM_ERR_DOUBLE_BIT_FAULT	(FLASH_ERR_BASE+4)							/* EEPROM double bits fault error code */
#define FLASH_ERR_ACCESS			(FLASH_ERR_BASE+8)							/* Flash access error code */
#define FLASH_ERR_PROTECTION		(FLASH_ERR_BASE+0x10)						/* Flash protection error code */
#define FLASH_ERR_MGSTAT0			(FLASH_ERR_BASE+0x11)						/* Flash verification error code */
#define FLASH_ERR_MGSTAT1			(FLASH_ERR_BASE+0x12)						/* Flash non-correctable error code */
#define FLASH_ERR_INIT_CCIF			(FLASH_ERR_BASE+0x14)						/* Flash driver init error with CCIF = 1 */
#define FLASH_ERR_INIT_FDIV			(FLASH_ERR_BASE+0x18)						/* Flash driver init error with wrong FDIV */
/*! @} End of flash_error_list                                                */

/******************************************************************************
* Flash and EEPROM commands
*
*//*! @addtogroup flash_command_list
* @{
*******************************************************************************/
#define FTMRE_CMD_ERASE_VERIFY_ALL						0x01					/* FTMRE erase verify all command */
#define FTMRE_CMD_ERASE_VERIFY_BLOCK					0x02					/* FTMRE erase verify block command */
#define FTMRE_CMD_ERASE_ALL								0x08					/* FTMRE erase all command */
#define FTMRE_CMD_ERASE_BLOCK							0x09					/* FTMRE erase blockcommand */
#define FTMRE_CMD_UNSECURE								0x0B					/* FTMRE unsecure command */
#define FTMRE_CMD_SET_USER_MARGIN						0x0D					/* FTMRE set usermargin command */

#define FLASH_CMD_ERASE_VERIFY_SECTION					0x03					/* FTMRE erase verify section command */
#define FLASH_CMD_READONCE								0x04					/* FTMRE read once command */
#define FLASH_CMD_PROGRAM								0x06					/* FTMRE program command */
#define FLASH_CMD_PROGRAMONCE							0x07					/* FTMRE program once command */
#define FLASH_CMD_ERASE_SECTOR							0x0A					/* FTMRE erase sector command */
#define FLASH_CMD_BACKDOOR_ACCESS						0x0C					/* FTMRE backdoor key access command */
#define FLASH_CMD_SET_USER_MARGIN_LEVEL					0x0D					/* FTMRE set user margin level command */

#define EEPROM_CMD_ERASE_VERIFY_SECTION					0x10					/* EEPROM erase berify section command */
#define EEPROM_CMD_PROGRAM								0x11					/* EEPROM program command */
#define EEPROM_CMD_ERASE_SECTOR 						0x12					/* EEPROM erase sector command */
/*! @} End of flash_command_list                                              */




extern uint16 FLASH_Init(uint32 u32BusClock);
extern uint16_t FLASH_EraseSector(uint32_t u32NVMTargetAddress);
extern void FLASH_LaunchCMD(uint8 bWaitComplete);
extern uint16 FLASH_Program2LongWords(uint32 u32NVMTargetAddress, uint32 u32DwData0, uint32 u32DwData1);
extern uint16 FLASH_Program(uint32 u32NVMTargetAddress, uint8 *pData, uint16 u16SizeBytes)£»
extern uint16 EEPROM_ProgramWord(uint32 u32NVMTargetAddress, uint16 u16DwData);
extern uint8 write_data_from_EEPROM(uint32 startAddr, uint8 *p_data, uint16 len,uint8 checksumEnable);
extern uint8 read_data_from_EEPROM(uint32 startAddr,uint8 *p_data,uint16 len, uint8 checksumEnable); 
#endif    /* _ADC_H_ */
