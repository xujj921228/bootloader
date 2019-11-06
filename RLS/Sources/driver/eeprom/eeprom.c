/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      adc.c
*
* @author    FPT Software
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include "config_parameter.h"
#include "eeprom.h"
#include "clock.h"


uint16 FLASH_Init(uint32 u32BusClock)
{
	uint16 u16Err = FLASH_ERR_SUCCESS;
	uint8 clkDIV = u32BusClock/1000000L - 1;
	
	if(!(FTMRH_FSTAT & FTMRH_FSTAT_CCIF_MASK))
	{
		u16Err |= FLASH_ERR_INIT_CCIF;
		return u16Err;
	}
	/* initialize the flash clock to be within spec 1MHz 
	 * 
	 */
	if(!(FTMRH_FCLKDIV & FTMRH_FCLKDIV_FDIVLCK_MASK))
	{
		/* FCLKDIV register is not locked */
		if((FTMRH_FCLKDIV & FTMRH_FCLKDIV_FDIVLD_MASK) &&
                  ((FTMRH_FCLKDIV & FTMRH_FCLKDIV_FDIV_MASK) != FTMRH_FCLKDIV_FDIV(clkDIV)))
		{
			/* flash clock prescaler is loaded but with wrong value */
			u16Err |= FLASH_ERR_INIT_FDIV;
			return (u16Err);
		}
		FTMRH_FCLKDIV = (FTMRH_FCLKDIV & ~(FTMRH_FCLKDIV_FDIV_MASK)) | FTMRH_FCLKDIV_FDIV(clkDIV);
                
#if 0
		FTMRE_FCLKDIV  |= FTMRE_FCLKDIV_FDIVLCK_MASK; /* lock the prescaler */
#endif
	}
	else
	{
		/* FCLKDIV register is locked */
		if((FTMRH_FCLKDIV & FTMRH_FCLKDIV_FDIV_MASK) != FTMRH_FCLKDIV_FDIV(clkDIV))
		{
			/* flash clock prescaler is wrong */
			u16Err |= FLASH_ERR_INIT_FDIV;
		}
	}
	return (u16Err);	
}

/*****************************************************************************//*!
  *
  * @brief erase flash sector, each flash sector is of 512 bytes long.
  *      
  *        
  * @param[in]   u32NVMTargetAddress erase sector address.
  *
  * @return error status.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/
uint16_t FLASH_EraseSector(uint32_t u32NVMTargetAddress)
{
	uint16_t u16Err = FLASH_ERR_SUCCESS;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(u32NVMTargetAddress & 0x03)
	{
		u16Err = FLASH_ERR_INVALID_PARAM;
		return (u16Err);
	}
	// Clear error flags
	FTMRH_FSTAT = 0x30;
	
	// Write index to specify the command code to be loaded
	FTMRH_FCCOBIX = 0x0;
	// Write command code and memory address bits[23:16]	
	FTMRH_FCCOBHI = FLASH_CMD_ERASE_SECTOR;// EEPROM FLASH command
	FTMRH_FCCOBLO = u32NVMTargetAddress>>16;// memory address bits[23:16]
	// Write index to specify the lower byte memory address bits[15:0] to be loaded
	FTMRH_FCCOBIX = 0x1;
	// Write the lower byte memory address bits[15:0]
	FTMRH_FCCOBLO = u32NVMTargetAddress;
	FTMRH_FCCOBHI = u32NVMTargetAddress>>8;
	
	// Launch the command
	FLASH_LaunchCMD(TRUE);
	
	// Check error status
	if(FTMRH_FSTAT & FTMRH_FSTAT_ACCERR_MASK)
	{
		u16Err |= FLASH_ERR_ACCESS;
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_FPVIOL_MASK)
	{
		u16Err |= FLASH_ERR_PROTECTION;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT0;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT1;		
	}	

	return (u16Err);
}

void FLASH_LaunchCMD(uint8 bWaitComplete)

{
    MCM_PLACR |= MCM_PLACR_ESFC_MASK;          /* enable stalling flash controller when flash is busy */
    FTMRH_FSTAT = 0x80;
    if(bWaitComplete)
    {
      // Wait till command is completed
      while (!(FTMRH_FSTAT & FTMRH_FSTAT_CCIF_MASK));
    }
}


/*****************************************************************************//*!
  *
  * @brief program flash routine, program 2long word to flash.
  *        
  * @param[in]   u32NVMTargetAddress programed flash address.
  * @param[in]   u32DwData0 programming data0.
  * @param[in]   u32DwData1 programming data1.
  *
  * @return flash error status.
  *
  * @ Pass/ Fail criteria: none
*****************************************************************************/

uint16 FLASH_Program2LongWords(uint32 u32NVMTargetAddress, uint32 u32DwData0, uint32 u32DwData1)
{
	uint16 u16Err = FLASH_ERR_SUCCESS;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(u32NVMTargetAddress & 0x03)
	{
		u16Err = FLASH_ERR_INVALID_PARAM;
		return (u16Err);
	}
	// Clear error flags
	FTMRH_FSTAT = 0x30;
	
	// Write index to specify the command code to be loaded
	FTMRH_FCCOBIX = 0x0;
	// Write command code and memory address bits[23:16]	
	FTMRH_FCCOBHI = FLASH_CMD_PROGRAM;// program FLASH command
	FTMRH_FCCOBLO = u32NVMTargetAddress>>16;// memory address bits[23:16]
	// Write index to specify the lower byte memory address bits[15:0] to be loaded
	FTMRH_FCCOBIX = 0x1;
	// Write the lower byte memory address bits[15:0]
	FTMRH_FCCOBLO = u32NVMTargetAddress;
	FTMRH_FCCOBHI = u32NVMTargetAddress>>8;
        
	// Write index to specify the word0 (MSB word) to be programmed
	FTMRH_FCCOBIX = 0x2;
	// Write the word 0

	//FTMRH_FCCOB = (u32DwData0) & 0xFFFF;
	FTMRH_FCCOBHI = (u32DwData0) >>8;
	FTMRH_FCCOBLO = (u32DwData0);
        
	// Write index to specify the word1 (LSB word) to be programmed
	FTMRH_FCCOBIX = 0x3;
	// Write word 1
	FTMRH_FCCOBHI = (u32DwData0>>16)>>8;
	FTMRH_FCCOBLO = (u32DwData0>>16);
	
	// Write index to specify the word0 (MSB word) to be programmed
	FTMRH_FCCOBIX = 0x4;
	// Write the word2
	//FTMRE_FCCOB = (u32DwData1) & 0xFFFF;
	FTMRH_FCCOBHI = (u32DwData1) >>8;
	FTMRH_FCCOBLO = (u32DwData1);
        
	// Write index to specify the word1 (LSB word) to be programmed
	FTMRH_FCCOBIX = 0x5;
	// Write word 3
	//FTMRH_FCCOB = (u32DwData1>>16) & 0xFFFF;
	FTMRH_FCCOBHI = (u32DwData1>>16)>>8;
	FTMRH_FCCOBLO = (u32DwData1>>16);
 
	// Launch the command
	FLASH_LaunchCMD(TRUE);
	
	// Check error status
	if(FTMRH_FSTAT & FTMRH_FSTAT_ACCERR_MASK)
	{
		u16Err |= FLASH_ERR_ACCESS;
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_FPVIOL_MASK)
	{
		u16Err |= FLASH_ERR_PROTECTION;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT0;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT1;		
	}	
	
	return (u16Err);
}
 /*        
  * @param[in]   u32NVMTargetAddress programed flash address.
  * @param[in]   pData programming data pointer.
  * @param[in]   u16SizeBytes programming data length.
  *
  * @return flash error status.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/

uint16 FLASH_Program(uint32 u32NVMTargetAddress, uint8 *pData, uint16 u16SizeBytes)
{
	uint16 u16Err = FLASH_ERR_SUCCESS;
	uint16 u16w2LongWordCount = u16SizeBytes>>3;
	uint8  u8WrLeftBytes = (u16SizeBytes & 0x07);
	uint16 u16WrLeftLongWords = u8WrLeftBytes>>2;
	uint32 u32WrTargetAddress = u32NVMTargetAddress;
	uint32 u32DwData0,u32DwData1;
	uint32 *pDwData = (uint32_t*)pData;
	int  i;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(u32NVMTargetAddress & 0x03)
	{
		u16Err = FLASH_ERR_INVALID_PARAM;
		return (u16Err);
	}
	// Loop for the two longwords (8 bytes) programming
	for(i = 0; i < u16w2LongWordCount; i++)
	{
		u32DwData0 = *pDwData++;
		u32DwData1 = *pDwData++;
		u16Err = FLASH_Program2LongWords(u32WrTargetAddress, u32DwData0, u32DwData1);
		if(u16Err)
		{
			goto EndP;
			//break;
		}
		u32WrTargetAddress += 8;
	}
	// Loop for the single longword (4 bytes) programming
	for(i = 0; i < u16WrLeftLongWords; i++)
	{
		u32DwData0 = *pDwData++;
		u16Err = FLASH_Program1LongWord(u32WrTargetAddress, u32DwData0);
		if(u16Err)
		{			
			goto EndP;
			//break;
		}
		u32WrTargetAddress += 4;
	}
	u8WrLeftBytes = (u8WrLeftBytes-(u16WrLeftLongWords<<2));	// calculate the # of bytes that are not programmed
	if(!u8WrLeftBytes){
		return (u16Err);
	}
        
	u32DwData0 = 0xFFFFFFFFL;        
	pData = (uint8_t*)pDwData+u8WrLeftBytes-1;	// pointer to the left bytes
	for(i = u8WrLeftBytes; i >0; i--)
	{
		u32DwData0 <<= 8;
		u32DwData0 |= *pData--;	// MSB byte first
	}
	// Now program the last longword
	u16Err = FLASH_Program1LongWord(u32WrTargetAddress, u32DwData0);	
EndP:	
	return (u16Err);
}


/*****************************************************************************//*!
  *
  * @brief program flash routine, program 1 long word to flash.
  *        
  * @param[in]   u32NVMTargetAddress programed flash address.
  * @param[in]   u32DwData programming data.
  *
  * @return flash error status.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/

uint16_t FLASH_Program1LongWord(uint32_t u32NVMTargetAddress, uint32_t u32DwData)
{
	uint16_t u16Err = FLASH_ERR_SUCCESS;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(u32NVMTargetAddress & 0x03)
	{
		u16Err = FLASH_ERR_INVALID_PARAM;
		return (u16Err);
	}
	// Clear error flags
	FTMRH_FSTAT = 0x30;
	
	// Write index to specify the command code to be loaded
	FTMRH_FCCOBIX = 0x0;
	// Write command code and memory address bits[23:16]	
	FTMRH_FCCOBHI = FLASH_CMD_PROGRAM;// program FLASH command
	FTMRH_FCCOBLO = u32NVMTargetAddress>>16;// memory address bits[23:16]
	// Write index to specify the lower byte memory address bits[15:0] to be loaded
	FTMRH_FCCOBIX = 0x1;
	// Write the lower byte memory address bits[15:0]
	FTMRH_FCCOBLO = u32NVMTargetAddress;
	FTMRH_FCCOBHI = u32NVMTargetAddress>>8;
	// Write index to specify the word0 (MSB word) to be programmed
	FTMRH_FCCOBIX = 0x2;
#if     defined(BIG_ENDIAN)        
	// Write the word  0
	FTMRH_FCCOBHI = (u32DwData>>16)>>8;
	FTMRH_FCCOBLO = (u32DwData>>16);
#else        
	FTMRH_FCCOBHI = (u32DwData) >>8;
	FTMRH_FCCOBLO = (u32DwData);
#endif        
	// Write index to specify the word1 (LSB word) to be programmed
	FTMRH_FCCOBIX = 0x3;
	// Write the word1 
#if     defined(BIG_ENDIAN)        
	FTMRH_FCCOBHI = (u32DwData) >>8;
	FTMRH_FCCOBLO = (u32DwData);
#else
	FTMRH_FCCOBHI = (u32DwData>>16)>>8;
	FTMRH_FCCOBLO = (u32DwData>>16);
#endif        
	// Launch the command
	FLASH_LaunchCMD(TRUE);
	
	// Check error status
	if(FTMRH_FSTAT & FTMRH_FSTAT_ACCERR_MASK)
	{
		u16Err |= FLASH_ERR_ACCESS;
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_FPVIOL_MASK)
	{
		u16Err |= FLASH_ERR_PROTECTION;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT0;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT1;		
	}	
	
	return (u16Err);
}
/*****************************************************************************//*!
  *
  * @brief erase flash sector, each flash sector is of 512 bytes long.
  *      
  *        
  * @param[in]   u32NVMTargetAddress erase sector address.
  *
  * @return error status.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/
uint16 EEPROM_EraseSector(uint32 u32NVMTargetAddress)
{
	uint16 u16Err = FLASH_ERR_SUCCESS;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	/*if(u32NVMTargetAddress & 0x03)
	{
		u16Err = FLASH_ERR_INVALID_PARAM;
		return (u16Err);
	}*/
	// Clear error flags
	FTMRH_FSTAT = 0x30;
	
	// Write index to specify the command code to be loaded
	FTMRH_FCCOBIX = 0x0;
	// Write command code and memory address bits[23:16]	
	FTMRH_FCCOBHI = EEPROM_CMD_ERASE_SECTOR;// EEPROM FLASH command
	FTMRH_FCCOBLO = u32NVMTargetAddress>>16;// memory address bits[23:16]
	// Write index to specify the lower byte memory address bits[15:0] to be loaded
	FTMRH_FCCOBIX = 0x1;
	// Write the lower byte memory address bits[15:0]
	FTMRH_FCCOBLO = u32NVMTargetAddress;
	FTMRH_FCCOBHI = u32NVMTargetAddress>>8;
	
	// Launch the command
	FLASH_LaunchCMD(TRUE);
	
	// Check error status
	if(FTMRH_FSTAT & FTMRH_FSTAT_ACCERR_MASK)
	{
		u16Err |= FLASH_ERR_ACCESS;
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_FPVIOL_MASK)
	{
		u16Err |= FLASH_ERR_PROTECTION;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT0;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT1;		
	}	

	return (u16Err);
}


/*****************************************************************************//*!
  *
  * @brief program flash routine, program 1 long word to flash.
  *        
  * @param[in]   u32NVMTargetAddress programed flash address.
  * @param[in]   u32DwData programming data.
  *
  * @return flash error status.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/

uint16 EEPROM_ProgramWord(uint32 u32NVMTargetAddress, uint16 u16DwData)
{
	uint16 u16Err = FLASH_ERR_SUCCESS;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
/*	if(u32NVMTargetAddress & 0x03)
	{
		u16Err = FLASH_ERR_INVALID_PARAM;
		return (u16Err);
	}*/
	// Clear error flags
	FTMRH_FSTAT = 0x30;
	
	// Write index to specify the command code to be loaded
	FTMRH_FCCOBIX = 0x0;
	// Write command code and memory address bits[23:16]	
	FTMRH_FCCOBHI = EEPROM_CMD_PROGRAM;// program FLASH command
	FTMRH_FCCOBLO = u32NVMTargetAddress>>16;// memory address bits[23:16]
	// Write index to specify the lower byte memory address bits[15:0] to be loaded
	FTMRH_FCCOBIX = 0x1;
	// Write the lower byte memory address bits[15:0]
	FTMRH_FCCOBLO = u32NVMTargetAddress;
	FTMRH_FCCOBHI = u32NVMTargetAddress>>8;
	// Write index to specify the word0 (MSB word) to be programmed
	FTMRH_FCCOBIX = 0x2;
	// Write the word0
	FTMRH_FCCOBLO = (u16DwData) >>8;
	
	FTMRH_FCCOBIX = 0x3;
	FTMRH_FCCOBLO = (u16DwData);
     
	// Launch the command
	FLASH_LaunchCMD(TRUE);
	
	// Check error status
	if(FTMRH_FSTAT & FTMRH_FSTAT_ACCERR_MASK)
	{
		u16Err |= FLASH_ERR_ACCESS;
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_FPVIOL_MASK)
	{
		u16Err |= FLASH_ERR_PROTECTION;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT0;		
	}
	if(FTMRH_FSTAT & FTMRH_FSTAT_MGSTAT_MASK)
	{
		u16Err |= FLASH_ERR_MGSTAT1;		
	}	
	
	return (u16Err);
}


/*****************************************************************************//*!
  *
  * @brief program flash routine.
  *        
  * @param[in]   u32NVMTargetAddress programed flash address.
  * @param[in]   pData programming data pointer.
  * @param[in]   u16SizeBytes programming data length.
  *
  * @return flash error status.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/

uint8 write_data_from_EEPROM(uint32 startAddr, uint8 *p_data, uint16 len,uint8 checksumEnable)
{
	   uint8 checksum = 0;
	   uint8 sectorBackup[2] = {0};
	   uint16  sectorBackup_word = 0;
	   uint32 startSectorAddr,i;
	   uint8  offsetAddr;
	   	  	   
	   
	   if(0 == p_data || 0 == len)
	   {
	        return FALSE;
	   }
	   else if((startAddr < EEPROM_START_ADDRESS) || ((startAddr + len - 1) > EEPROM_END_ADDRESS))
	   {
	        return FALSE;
	   }
	   else
	   {
	     if(checksumEnable == ENABLE)
	     {
	        len++;
	     }

	     if(checksumEnable == ENABLE)
	     {
	       for(i=0;i<len-1;i++)   //all data not contain checksum
	       {
	         checksum += *(p_data+i);
	       }
	       checksum = ~checksum + 1;
	     }
	     
	     startSectorAddr = startAddr&0xfffffffe;       //start address of sector to operate
	     offsetAddr = startAddr - startSectorAddr; //start offset
	     
	     //write first sector
	     if(!read_data_from_EEPROM(startSectorAddr, sectorBackup, 2, DISABLE))  //backup data
	       return FALSE;
	     if((2-offsetAddr) >= len)
	     {//have enough space to store data in first sector  
	       do
	       {
	         sectorBackup[offsetAddr++] = *p_data++;
	         len--;
	         if(len == 1)
	         {
	           if(checksumEnable == ENABLE) 
	              sectorBackup[offsetAddr] = checksum;  //save checksum
	           else
	              sectorBackup[offsetAddr] = *p_data;   //save last data
	           len--;  
	         }
	       }while(len>0);
	     }else
	     {
	       for(i=offsetAddr;i<2;i++)                 //updata first sector data
	       {
	         sectorBackup[i] = *p_data++;
	         len--;
	       } 
	     }
	     
	     sectorBackup_word =  sectorBackup[0];
	     sectorBackup_word =  (sectorBackup_word<<8 )| sectorBackup[1];
	     if(EEPROM_EraseSector(startSectorAddr))
	       return FALSE;
	     if(EEPROM_ProgramWord(startSectorAddr, sectorBackup_word))
	       return FALSE; 
	     startSectorAddr += 2; 
	     
	     //write sectors
	     while(len>2)
	     {      
	       for(i=0;i<2;i++)                        
	       {
	          sectorBackup[i] = *p_data++;
	       }
	       
	       sectorBackup_word =  sectorBackup[0];
	       sectorBackup_word =  (sectorBackup_word<<8 )| sectorBackup[1];
	       	     
	       if(EEPROM_EraseSector(startSectorAddr))
	          return FALSE;
	       if(EEPROM_ProgramWord(startSectorAddr, sectorBackup_word))
	          return FALSE; 
	       startSectorAddr += 2; 
	       len -= 2;
	     }
	     
	     //write last secotrs
	     i=0;
	     if(len>0)
	     {      
	       if(!read_data_from_EEPROM(startSectorAddr, sectorBackup, 2, DISABLE))  //backup data
	         return FALSE;

	       while(len>0)
	       {
	         if(len == 1)
	         {//the last byte
	           if(checksumEnable == ENABLE) 
	             sectorBackup[i] = checksum;  //save checksum
	           else
	             sectorBackup[i] = *p_data;   //save last data
	           len--;
	           break;
	         }
	         sectorBackup[i++] = *p_data++;
	         len--;
	       };
	       
	       sectorBackup_word =  sectorBackup[0];
	       sectorBackup_word =  (sectorBackup_word<<8 )| sectorBackup[1];
	       	       
	       if(EEPROM_EraseSector(startSectorAddr))
	         return FALSE;
	       if(EEPROM_ProgramWord(startSectorAddr, sectorBackup_word))
	         return FALSE;    
	     }
	     return TRUE;
	   }
}

/****************************************************************************************************
 * FUNCTION NAME : read_data_from_EEPROM(uint16 address,uint8 *p_data,uint16 len, uint8 checksumEnable)
 *   DESCRIPTION : read_data_from_EEPROM.
 *         INPUT : NONE. 
 *        OUTPUT : NONE
 *        RETURN : TRUE or FALSE.
 *        OTHERS : NONE.
 ****************************************************************************************************/
 uint8 read_data_from_EEPROM(uint32 startAddr,uint8 *p_data,uint16 len, uint8 checksumEnable) 
 {
   uint8 checksum=0;
   
   if(checksumEnable == ENABLE)
   {
     len++;
   }
   
   if (0 == p_data || 0 == len)
   {
     return FALSE;
   }
   else if((startAddr < EEPROM_START_ADDRESS) || ((startAddr + len - 1) > EEPROM_END_ADDRESS))
   {
     return FALSE;
   }
   else
   {
     while(len>0)
     {      
       if(!(FTMRH_FSTAT & FTMRH_FSTAT_CCIF_MASK)) {               // Is reading from EEPROM possible? 
           return FALSE;               // If no then error 
       }
       *p_data++ = *(volatile uint8 *)startAddr++;
       checksum += *(p_data-1); 
       len--;
       if(len==1)
       { 
         if(!(FTMRH_FSTAT & FTMRH_FSTAT_CCIF_MASK)) {               // Is reading from EEPROM possible? 
             return FALSE;               // If no then error 
         }
         if(checksumEnable == ENABLE)
         {
           checksum += *(volatile uint8 *)startAddr++;
           if(checksum==0) return TRUE;
           else return FALSE; 
         }else  
         {
           *p_data = *(volatile uint8 *)startAddr;
         }
       }
     }
     return TRUE;
   }
 }
 

