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
#define LOCAL_SIZE 22
typedef union
{   
 struct
 {
        uint8 NUMBER0[3];                   //0.1.2
        uint8 NUMBER1[3];                   //3.4.5
        uint8 NUMBER2[3];                   //6.7.8
        uint8 NUMBER3[3];                   //9.10.11
        uint8 Brightness_Light_Percentage;         //12
        uint8 Brightness_Infrared_Percentage;      //13
        uint8 A_DAC_EEPdtata;                      //14
        uint8 B_DAC_EEPdtata;                      //15
        uint16 A_RAIN_ADC_EEPdtata;                //16.17
        uint16 B_RAIN_ADC_EEPdtata;                //18.19
        uint16 EEPmark;                            //20.21
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

