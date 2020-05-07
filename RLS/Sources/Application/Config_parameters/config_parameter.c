/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2018 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      config_parameter.c
*
* @author    xujun
*
* @version   1.0
*
* @date      Sat Aug 04 10:53:51 CST 2018
*
* @brief     Common LIN configuration, data structure
*
******************************************************************************/
#include "config_parameter.h"
#include "lin.h"
#include "lin_cfg.h"
#include "lin_diagnostic_service.h"
#include "lin_app.h"
#include "local_eep_data.h"
#include "mlx75308.h"

extern local_info_t local_info;
extern BCM_Frame_t         Lin_BCM_Frame;
extern tMlx75308_Config const Mlx75308_Config_Parameter;

const  uint8 Software_Versions[3] = {0x00, 0x01, 0x03};
const  uint8 Hardware_Versions[3] = {0x00, 0x01, 0x00};


void Globle_parameter_Init(void)
{
 	Get_All_data_From_EEPROM();
 	while(local_info.EEPmark != EEPromMark)
 	{
 		local_info.NUMBER0 = 0xF185;                                              //0.1.2
 		local_info.NUMBER1 = 0xF186;                                              //3.4.5
 		local_info.NUMBER2 = 0xF187;                                              //6.7.8
 		local_info.NUMBER3 = 0xF188;                                              //9.10.11
 		local_info.Brightness_Light_Percentage = 100;                            //12
 		local_info.Brightness_Infrared_Percentage = 100;                          //13
 		local_info.A_DAC_EEPdtata = Mlx75308_Config_Parameter.dac_a_default;   //14
 		local_info.B_DAC_EEPdtata = Mlx75308_Config_Parameter.dac_b_default;   //15
 		//local_info.A_RAIN_ADC_EEPdtata;                                           //16.17
 		//local_info.B_RAIN_ADC_EEPdtata;                                           //18.19
 		local_info.EEPmark = EEPromMark;                                          //20.21
 		
 		Set_Data_To_EEPROM(EEPROM_SERIAL_NUMBER0_ADDR,local_info.array,LOCAL_SIZE);
 		Get_All_data_From_EEPROM();
 	}	
}
