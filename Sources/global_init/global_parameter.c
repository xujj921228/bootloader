/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           global_parameter.c
** Last modified Date:  2017-12-19
** Last Version:        V1.00
** Descriptions:        全局参数声明。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          xujun
** Created date:        2017-12-19
** Version:             V1.00
** Descriptions:        创建文件
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/
#include "global_parameter.h"
#include "lin_app.h"
#include "HCS12EEPROM.h"
#include "rls_app.h" 
#include "config_parameter.h"

/*******************************************************
 * FUNCTION NAME : global_parameter_init()
 *   DESCRIPTION : init global_parameter function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void global_parameter_init(void)
{
    uint8 i;
    uint16 temp_data[2];
    
    for (i = 0;i < MAX_DATA ; i++)
    {
        msg_send.data_field[i] = 0;
        rx.data[i] = 0;
    }

    for (i = 0;i < LIGHT_TYPE ; i++)
    {
        Light_on_cnt[i] = 0; 
        Light_off_cnt[i] = 0;  
    }
   
    HCS12_EE_Read_2Word(EEPROM_BR_LIG_PER_ADDR,Brightness_Light_Percentage);
    if(Brightness_Light_Percentage[0] == 0xFFFF) 
    {
        Brightness_Light_Percentage[0] = 100;
    }
    
    HCS12_EE_Read_2Word(EEPROM_BR_INF_PER_ADDR,Brightness_Infrared_Percentage); 
    if(Brightness_Infrared_Percentage[0] == 0xFFFF) 
    {
        Brightness_Infrared_Percentage[0] = 100;
    }
    
    HCS12_EE_Read_2Word(EEPROM_SCUTTLE_CONTROL_ADDR,Scuttle_Control); 
    
    /**************Set ProType and Param****************************/
   
    HCS12_EE_Read_2Word(EEPROM_A_DAC_ADDR,temp_data);   /****_DAC********/
   
    if(temp_data[0] == 0xFFFF)
    {
        MLX75308_A_Adc = Mlx75308_Config_Parameter[0].dac_a_default;
    }
    
    else
    {
        MLX75308_A_Adc = (uint8)(temp_data[0]);
    }
  
   /* HCS12_EE_Read_2Word(EEPROM_A_GAIN_ADDR,temp_data);  
   
    if(temp_data[0] == 0xFFFF)
    {
        MLX75308_A_Gain = Mlx75308_Config_Parameter[0].gain_adj_a ;
    }
    
    else
    {
        MLX75308_A_Gain =  (uint8)(temp_data[0]);
    } */
   
    HCS12_EE_Read_2Word(EEPROM_B_DAC_ADDR,temp_data);  
   
    if(temp_data[0] == 0xFFFF)
    {
        MLX75308_B_Adc = Mlx75308_Config_Parameter[0].dac_b_default ;
    }
    
    else
    {
        MLX75308_B_Adc =  (uint8)(temp_data[0]);
    }
  
    /*HCS12_EE_Read_2Word(EEPROM_B_GAIN_ADDR,temp_data);  
   
    if(temp_data[0] == 0xFFFF)
    {
        MLX75308_B_Gain = Mlx75308_Config_Parameter[0].gain_adj_b ;
    }
    else
    {
        MLX75308_B_Gain =  (uint8)(temp_data[0]);
    } */


    u8_WiperSpeed_Expert = 0;

    RLS_RunMode = SLEFADAPT;
    u8_Rain_Delta = RAIN_DELTA;
    u8_Rain_SensitivityPre = 4;
    u8_Rain_Sensitivity = 4;
    Lin_RLS_Frame.Genaration = 1;

    Lin_BCM_Frame.RainSensitivity = 4 ;

    u8_IntSpeedCnt = 0;
    u8_IntSpeedEnterCnt = 0;

    Lin_BCM_Frame.CMD_AutoWiper = 1;
    Lin_BCM_Frame.ParkPosition = 1;
    u8_Wipe_Automatic_On_Pre = 1;

    u8_lin_cmd_sleep_flg = 0;
    u8_rls_wake_up_bcm_flg = 0;
    u8_receive_data_flg = 0;

    API_6h_Cnt = 0;
    u8_send_break_cnt = 0;
    u8_receive_break_flag = 0;
    u8_rain_detect_flg = 0;
    u8_LinErrorCnt = 0;
	u8_Lin_Diag_Enable = 0;
	u8_Lin_Diag_Enable_Cnt = 0;
}

/*********************************************************************************************************
  End Of File
*********************************************************************************************************/

