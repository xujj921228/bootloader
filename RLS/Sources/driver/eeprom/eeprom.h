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
#include <SKEAZN642.h>



#define  ENABLE_INTERRUPT  asm("CPSIE i");
#define  DISABLE_INTERRUPT asm("CPSID i");

#define TRUE  1
  /*!< Definitioni for TRUE. */
#define FALSE 0

#define EEPROM_BOOT_REFRESH             0x10000020

#define EEPROM_BOOT_REFRESH_LENTH        2
/********************************
 * define  APP check  address
 * add by xujunjie
 * *****************************/
#define  APP_check_ADDRESS      0xFFFC
#define  boot_up_value          0x5aa5
#define  APP_code_start         0x5000
#define  APP_start_address      APP_code_start+4


/**********************
 * updata  flag (eeprom) 0x5a:should updata  else:no need to updata
 * app check flag (last two byte in flash )
 * ****************************/
typedef enum
{
 APP_INVALUE = 0 ,
 APP_VALUE   = 1   
}APP_check_t;


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



extern void WDOG_Feed(void);
extern uint16_t FLASH_Init(uint32_t u32BusClock);
extern uint16_t FLASH_EraseSector(uint32_t u32NVMTargetAddress);
extern void FLASH_LaunchCMD(uint8_t bWaitComplete);
extern uint16_t FLASH_Program2LongWords(uint32_t u32NVMTargetAddress, uint32_t u32DwData0, uint32_t u32DwData1);
extern uint16_t FLASH_Program(uint32_t u32NVMTargetAddress, uint8_t *pData, uint16_t u16SizeBytes);
extern uint16_t FLASH_Program1LongWord(uint32_t u32NVMTargetAddress, uint32_t u32DwData);
extern uint16_t EEPROM_ProgramWord(uint32_t u32NVMTargetAddress, uint16_t u16DwData);
extern uint8_t write_data_from_EEPROM(uint32_t startAddr, uint8_t *p_data, uint16_t len,uint8_t checksumEnable);
extern uint8_t read_data_from_EEPROM(uint32_t startAddr,uint8_t *p_data,uint16_t len, uint8_t checksumEnable); 
extern APP_check_t boot_APP_check(void);
extern  uint8_t boot_up_check(uint16_t temp);

