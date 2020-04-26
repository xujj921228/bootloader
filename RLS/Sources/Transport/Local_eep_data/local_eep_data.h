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
#include "config_parameter.h"
#include "eeprom.h"

#define EEPromMark 0x5aa5
#define LOCAL_SIZE 26
typedef union
{   
 struct
 {
        uint32 NUMBER0;                         //0.1.2.3
        uint32 NUMBER1;                         //4.5.6.7
        uint32 NUMBER2;                         //8.9.10.11
        uint32 NUMBER3;                         //12.13.14.15
        uint8 Brightness_Light_Percentage;         //16
        uint8 Brightness_Infrared_Percentage;      //17
        uint8 A_DAC_EEPdtata;                      //18
        uint8 B_DAC_EEPdtata;                      //19
        uint16 A_RAIN_ADC_EEPdtata;                //20.21
        uint16 B_RAIN_ADC_EEPdtata;                //22.23
        uint16 EEPmark;                            //24.25
 };
  uint8 array[LOCAL_SIZE];
}local_info_t;


#define EEPROM_BOOT_REFRESH             0x10000020  //程序有效标志位

#define EEPROM_BOOT_REFRESH_LENTH        2


#define EEPROM_SERIAL_NUMBER0_ADDR       0x10000000
#define EEPROM_SERIAL_NUMBER1_ADDR       0x10000003
#define EEPROM_SERIAL_NUMBER2_ADDR       0x10000006
#define EEPROM_SERIAL_NUMBER3_ADDR       0x10000009

#define EEPROM_BR_LIG_PER_ADDR          0x1000000c
#define EEPROM_IR_PER_ADDR              0x1000000d

#define EEPROM_A_DAC_ADDR               0x1000000e
#define EEPROM_B_DAC_ADDR               0x1000000f

#define EEPROM_A_RAIN_ADC_ADDR          0x10000010
#define EEPROM_B_RAIN_ADC_ADDR          0x10000012


#define EEPROM_SERIAL_NUMBER_LENTH     3
#define EEPROM_BR_LIG_PER_LENTH        1
#define EEPROM_IR_PER_LENTH            1

#define EEPROM_A_DAC_ADDR_LENTH        1
#define EEPROM_B_DAC_ADDR_LENTH        1

#define EEPROM_A_RAIN_ADC_LENTH        2
#define EEPROM_B_RAIN_ADC_LENTH        2

extern void Get_All_data_From_EEPROM(void);

extern bool_t Set_Data_To_EEPROM(uint32 startAddr,uint8 *p_data,uint16 len);

extern void Write_App_value_flag(uint8 *data);

extern void Read_App_value_flag(uint8 *data);

