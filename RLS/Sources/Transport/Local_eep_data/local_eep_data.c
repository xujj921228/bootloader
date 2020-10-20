/***************************************************************************//*!
*
* #company  Shanghai baolong
*
* #author   xujunjie@bb.com
*
* #brief    local data set in eep  
*
* #time    2020/04/01
*
******************************************************************************/
#include "local_eep_data.h"


local_info_t local_info;

void Get_All_data_From_EEPROM(void)
{
  read_data_from_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,local_info.array,LOCAL_SIZE,ENABLE);
}

bool_t Set_All_Data_TO_EEPROM(void)
{
	local_info_t local_info_Compare;
	uint16 cn;
	
	write_data_from_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,local_info.array,LOCAL_SIZE,ENABLE);
	read_data_from_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,local_info_Compare.array,LOCAL_SIZE,ENABLE);
	for(cn = 0;cn < LOCAL_SIZE; cn++ )
	{
		 if(local_info_Compare.array[cn] != local_info.array[cn])
		 {
			  return FALSE;
		 }
	}
		
	return TRUE;	
}


bool_t Set_Data_To_EEPROM(uint32 startAddr,uint8 *p_data,uint16 len)
{
    uint8 add;
    uint16 cn;
    local_info_t local_info_Compare;
    
    add = (uint8)(startAddr - EEPROM_SERIAL_NUMBER0_ADDR);
    for(cn = 0;cn < len; cn++ )
    {
          local_info.array[cn + add] = *(p_data + cn);
    }
    write_data_from_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,local_info.array,LOCAL_SIZE,ENABLE);
    read_data_from_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,local_info_Compare.array,LOCAL_SIZE,ENABLE);
    for(cn = 0;cn < LOCAL_SIZE; cn++ )
    {
     if(local_info_Compare.array[cn] != local_info.array[cn])
     {
          return FALSE;
     }
    }
    
    return TRUE;
}


void Write_App_value_flag(uint8 *data)
{
    write_data_from_EEPROM(EEPROM_BOOT_REFRESH,data,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
}

void Read_App_value_flag(uint8 *data)
{
    read_data_from_EEPROM(EEPROM_BOOT_REFRESH,data,EEPROM_BOOT_REFRESH_LENTH,ENABLE);
}
                




