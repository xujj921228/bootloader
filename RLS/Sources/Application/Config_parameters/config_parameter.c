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

const  uint8 Software_Versions[3] = {0x00, 0x01, 0x00};
const  uint8 Hardware_Versions[3] = {0x00, 0x01, 0x00};


void Globle_Eep_parameter_Init(void)
{
 	Get_All_data_From_EEPROM();
 	while(local_info.EEPmark != EEPromMark)
 	{
 		local_info.NUMBER0[0]= 0x00; /*0     */
 		local_info.NUMBER0[1]= 0xF1; /*1    */
 		local_info.NUMBER0[2]= 0x85; /*2     */
 		
 		local_info.NUMBER1[0] = 0x00;/*3    */
 		local_info.NUMBER1[1] = 0xF1;/*4     */
 		local_info.NUMBER1[2] = 0x86;/*5     */
 		
 		local_info.NUMBER2[0] = 0x00;/*6     */
 		local_info.NUMBER2[1] = 0xF1;/*7     */
 		local_info.NUMBER2[2] = 0x87;/*8     */
 		
 		local_info.NUMBER3[0] = 0x00;/*9     */
 		local_info.NUMBER3[1] = 0xF1;/*10    */
 		local_info.NUMBER3[2] = 0x88;/*11     */
 		
 		local_info.Brightness_Light_Percentage = 100; /*12     */
 		local_info.Brightness_Infrared_Percentage = 100;/*13     */
 		local_info.DAC_EEPdtata[0] = Mlx75308_Config_Parameter.dac_a_default; /*14     */
 		local_info.DAC_EEPdtata[1] = Mlx75308_Config_Parameter.dac_b_default; /*15     */
 		local_info.A_RAIN_ADC_EEPdtata = 0x130A;  /*16.17    */
 		local_info.B_RAIN_ADC_EEPdtata = 0x130B; /*18.19    */
 		local_info.EEPmark = EEPromMark;  /*20.21 */
 		local_info.Vehicle_Speed_Gear0 = 5;
 		local_info.Vehicle_Speed_Gear1 = 30;
 		local_info.Vehicle_Speed_Gear2 = 60;
 		local_info.Vehicle_Speed_Gear3 = 80;
 		local_info.BooT_Mark = 0xFFFF;
 		local_info.APP_Self_Reset_Cn = 0;
 		
        while(Set_All_Data_TO_EEPROM() == FALSE);
 	}	
}


/*******»¬¶¯¿ò¼ÆËã********/

uint32 Cyclic_average_cal(uint16 *array_temp ,uint8 array_length,uint16 Data_temp)
{
	uint8 i;
	uint32 Temp_sum = 0;
	
    for(i = 0;i < array_length - 1;i++)
	{
		array_temp[i] = array_temp[i + 1];
		Temp_sum += array_temp[i];
	}
	array_temp[array_length - 1] = Data_temp;
	
	Temp_sum += Data_temp;
	
	Temp_sum = Temp_sum/array_length;
	
	return  (uint16)Temp_sum;
}



