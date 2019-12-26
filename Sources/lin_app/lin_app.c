/*********************************************Copyright (c)***********************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lin_app.c
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

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "lin.h"
#include "spi.h"
#include "gpio.h"
#include "lin_app.h" 
#include "rls_app.h"
#include "HCS12EEPROM.h"
#include "config_parameter.h"

struct Lin_message       msg_send,msg_get,Diagnostic_Response,msg_config;
struct Lin_frame         rx;
struct RLS_Frame         Lin_RLS_Frame;
struct RLS_TEST_Frame    Lin_RLS_TEST_Frame ;
struct BCM_Frame         Lin_BCM_Frame;
struct BCM_CFG_Frame     Lin_CFG_Frame;
struct Window_Frame      Lin_Window_Frame;
struct Lin_Diagnostic    Diagnostic_R; 

uint8  u8_Sci_Reg_Status,u8_Lin_identifier,u8_LinErrorCnt,u8_Cmd_Execution;
uint8  u8_Lin_Data_Check;
uint8  u8_Rain_Sensitivity;

uint8  u8_SPD_Vehicle;

uint8  Diagnostic_6s_cnt;
uint8  Diagnostic_Extended_En;
uint8  Diagnostic_KEY_Locked;
uint8  Diagnostic_2s_cnt;
uint8  Diagnostic_60s_cnt;
uint8  Diagnostic_Key_Wrong_Num;

uint8  Gain_Prm;

uint8  Gain_Val;
uint8  Gain_Val_Pre;

uint16 Brightness_Light_Percentage[2];
uint16 Brightness_Infrared_Percentage[2];
uint16 Scuttle_Control[2];

uint32 Diagnostic_Seed,Diagnostic_Key;

/*******************************************************
 * FUNCTION NAME : Lin_Prameter_Init()
 *   DESCRIPTION : Lin_Prameter_Init function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void Lin_Prameter_Init(void)
{
    rx.protected_id = 0;
    rx.state = IDLE;
    rx.error = 0;
    rx.check = 0;

    Diagnostic_R.Diagnostic_receive = FALSE;
    Diagnostic_R.SID = 0;
    Diagnostic_R.Response_type = FALSE;
    Diagnostic_R.Access_OK = FALSE;
    Diagnostic_R.RSID = 0;
    Diagnostic_R.RLon = 0;
    Diagnostic_R.state = 0;        //Default Mode
    Diagnostic_Key_Wrong_Num = 0;
    Diagnostic_KEY_Locked = TRUE;  //Power On Lock KEY
    Diagnostic_Extended_En = FALSE;
    Diagnostic_6s_cnt = 0;
    Diagnostic_60s_cnt = 0;
    u8_LinErrorCnt = 0;
}
/*******************************************************
 * FUNCTION NAME : LinConfig()
 *   DESCRIPTION : LinConfig function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void LinConfig(void)
{
	int sbr;
	uint16  temp_data[2] ;

    LIN_EN = 1;
	//  Calculates SCI Baud rate value
	SCI0SR2 = 0;
	sbr = (SCI_CLOCK / SCI_BAUDRATE / 16);
	SCI0BDH  = (uint8)(sbr >> 8);
	SCI0BDL  = (uint8)sbr;
	SCI0SR2  = 0x80;

	SCI0ACR1 = 0x03U;////////////  80

	SCI0ACR2 = 0x84;   //Enable bit error detect circuit
	SCI0CR2  = 0x2C;   //RIE = 1, Enable Recieve intterupt ,TE = 1 Enable TXD, RE = 1 Enable RXD
	SCI0SR2  = 0x84;   //Clear LBKDIF, RXEDGIF, Break character is 13 or 14 bit long (发送使用)

	if((SCI0ASR1 & 0x02))
	{
		SCI0ASR1 = SCI0ASR1 | 0x02;
	}

}

/*******************************************************
 * FUNCTION NAME : Seed_To_Key()
 *   DESCRIPTION : Seed_To_Key function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
uint32 Seed_To_Key(uint32 seed)
{ 
    uint32 key=0; 
    uint8 i;
   
    if(seed != 0) 
    { 
        for (i=0; i < 35; i++) 
        { 
            if (seed & 0x80000000) 
            { 
                seed = seed << 1; 
                seed = seed ^ RLS_MASK; 
            }
            else 
            { 
                seed = seed << 1; 
            } 
        } 
        key = seed; 
    } 
    return key; 
}




/*******************************************************
 * FUNCTION NAME : Analysis_Master_Data()
 *   DESCRIPTION : Analysis_Master_Data function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void Analysis_Master_Data(void)
{   
    
    Lin_BCM_Frame.Status_IGN      = (rx.data[0] & 0x06)>>1;   
    Lin_BCM_Frame.CMD_AutoWiper   = (rx.data[0] & 0x08)>>3;
    Lin_BCM_Frame.ParkPosition    = (rx.data[7] & 0x20)>>5;
    Lin_BCM_Frame.RainSensitivity = (rx.data[7] & 0x1C)>>2;
    Lin_BCM_Frame.SPD_Vehicle     = rx.data[4];  
    
    u8_SPD_Vehicle = Lin_BCM_Frame.SPD_Vehicle;
    
    switch(Lin_BCM_Frame.RainSensitivity)
    {
        case 1: u8_Rain_Sensitivity = 1;break;
        case 2: u8_Rain_Sensitivity = 2;break;                                 
        case 3: u8_Rain_Sensitivity = 3;break;
        case 4: u8_Rain_Sensitivity = 4;break;

        default:u8_Rain_Sensitivity = 4;break;                
    }

    u8_Rain_Delta =  RAIN_DELTA;
}



/*******************************************************
 * FUNCTION NAME : Analysis_BCM_Config()
 *   DESCRIPTION : Analysis_BCM_Config function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void Analysis_BCM_Config(void)
{   
    uint8 temp_PRM[2];
    
    Lin_CFG_Frame.WR_Status    = rx.data[0] & 0x01;
    Lin_CFG_Frame.Parameter_1  = rx.data[1];
    Lin_CFG_Frame.Parameter_2  = rx.data[2];
    
    if(Lin_CFG_Frame.Parameter_1 <= 20 && Lin_CFG_Frame.Parameter_1 > 0)
    {
        Gain_Prm = 0;
    } 
    
    else if(Lin_CFG_Frame.Parameter_1 > 20 && Lin_CFG_Frame.Parameter_1 <= 50)
    {
        Gain_Prm = 1;
    } 
    
    else if(Lin_CFG_Frame.Parameter_1 > 50 && Lin_CFG_Frame.Parameter_1 <= 100)
    {
        Gain_Prm = 2;
    }
    
    else 
    {
        Gain_Prm = 1;
    }
    
    
    Gain_Val = Lin_CFG_Frame.Parameter_1;
    temp_PRM[0] = Gain_Prm;
    
    if(Lin_CFG_Frame.WR_Status == 1)
    {
        if(Gain_Val != Gain_Val_Pre)
        {
            HCS12_EE_Write_2Word(EEPROM_GAIN_PRM_ADDR, temp_PRM);
            Gain_Val_Pre = Gain_Val;
        }
    }
}



/*******************************************************
 * FUNCTION NAME : Lin_TransStatus()
 *   DESCRIPTION : Lin_TransStatus function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : 1:LIN_NO_ERROR  0:LIN_ERROR             
 *        OTHERS : NONE
 *******************************************************/
uint8 Lin_TransStatus(void) 
{
    unsigned volatile char ch;
    // State of the LIN receive channel
    switch(rx.state++) 
    {
        case IDLE: 
        {  
            u8_Sci_Reg_Status = SCI0SR1;  
            
            if(!(u8_Sci_Reg_Status & 0x22))      
                return(FALSE);

            ch = LIN_DATA;

            if(!((u8_Sci_Reg_Status & 0x20) && (u8_Sci_Reg_Status & 0x02) && (ch == 0))) 
                rx.state = IDLE;   //间隔场  FE = 1
        }
        break;
        
        case _BREAK:
        {
            u8_Sci_Reg_Status = SCI0SR1; 
            ch = LIN_DATA;
        
            if((u8_Sci_Reg_Status & 0x20) && (u8_Sci_Reg_Status & 0x02) && (ch == 0))
            {
                rx.state = _BREAK;   //间隔场  FE = 1 
                break;
            }

            if((!(u8_Sci_Reg_Status & 0x20)) || (u8_Sci_Reg_Status & 0x02)) 
                return(FALSE);

            if(ch != 0x55)
            {               
                return(FALSE);
            }
            else
            {
                u8_receive_break_flag = 1 ;
            }

        }
        break;
        
        case SYNCH: 
        {
            u8_Sci_Reg_Status = SCI0SR1; 
            ch = LIN_DATA;
       
            if((u8_Sci_Reg_Status & 0x20) && (u8_Sci_Reg_Status & 0x02) && (ch == 0))
            {
                rx.state = _BREAK;   //  FE = 1 
                break;
            }
      
            if((!(u8_Sci_Reg_Status & 0x20)) || (u8_Sci_Reg_Status & 0x02)) 
                return(FALSE);
      
            if(!(Lin_chkparity(ch))) 
                return (FALSE);                       //parity error
      
            rx.protected_id = ch;         
            u8_Lin_identifier = rx.protected_id & 0x3f;   
    
            switch(u8_Lin_identifier) 
            {
                case RLS_ID:
                {
                    Diagnostic_R.state = 0;        //Default talk goto Default Mode
                    
                    rx.error = LinSndMsg(msg_send,0x8);

                    if(rx.error == FALSE) 
                        return (FALSE);
                        
                    msg_send.data_field[2] = (msg_send.data_field[2] & 0xF7);
                    
                    Lin_RLS_Frame.REP_Error = 0;
                    
                    u8_Cmd_Execution = 0;
                    rx.state = IDLE;
                    u8_LinErrorCnt = 0;
                    
                    msg_send.data_field[0] = (msg_send.data_field[0] & 0xf0) | Lin_RLS_Frame.MsgCounter;

                    if(Lin_RLS_Frame.MsgCounter > 0x0E) 
                        Lin_RLS_Frame.MsgCounter = 0;
                    else  
                        Lin_RLS_Frame.MsgCounter ++;
                }
                break;
                
                case RLS_ASK:
                {
                    Diagnostic_R.state = 0;
                    msg_config.data_field[0] = Lin_CFG_Frame.Parameter_1;
                    msg_config.data_field[1] = Lin_CFG_Frame.Parameter_2;
                    rx.error = LinSndMsg(msg_config,0x8);
                    
                    rx.state = IDLE;
                }
                break;
                
                case BCM_FLW_ID:                
                case BCM_FRW_ID:                
                case BCM_BLW_ID:
                case BCM_BRW_ID:
                case BCM_ROOF_ID:
                case BCM_CFG:
                case BCM_ID:
                {
                }
                break;

                case 0x3c:
                {
                }                      
                break;

                case 0x3d:
                {
                    Diagnostic_RESP_Process();    //  Diagnostic Flag
                    rx.state = IDLE;
                }
                break;
        
                default:
                    rx.state = IDLE;
                break;
            }
        }
        break;
        
        case PROTECTED_IDENTIFIER: 
        {
          
            u8_Sci_Reg_Status = SCI0SR1;
            ch = LIN_DATA; 
            
            if((u8_Sci_Reg_Status & 0x20) && (u8_Sci_Reg_Status & 0x02) && (ch == 0)) 
            {
                rx.state = _BREAK;   //间隔场  FE = 1 
                break;
            }
      
      
            if((!(u8_Sci_Reg_Status & 0x20)) || (u8_Sci_Reg_Status & 0x02)) 
                return(FALSE);
      
            rx.data[0] = ch;
                    
            if((u8_Lin_identifier == 0x3c) && ((ch & 0x3f) != RLS_NAD) && (ch != 0))    //NAD or Sleep CMD @ DTC
                rx.state = IDLE;
        }
        break;
      
        case DATA_0:
        case DATA_1:
        case DATA_2:
        case DATA_3:
        case DATA_4:
        case DATA_5:
        case DATA_6: 
        {
            u8_Sci_Reg_Status = SCI0SR1;
            ch = LIN_DATA;  
      
            if((u8_Sci_Reg_Status & 0x20) && (u8_Sci_Reg_Status & 0x02) && (ch == 0)) 
            {
                rx.state = _BREAK;   //间隔场  FE = 1 
                break;
            }
      
            if((!(u8_Sci_Reg_Status & 0x20)) || (u8_Sci_Reg_Status & 0x02)) 
                return(FALSE);
      
            rx.data[rx.state-DATA_0] = ch;
            
            if((rx.state + 1 - DATA_0) == MAX_DATA)
                rx.state = DATA_7;
        }
        break;
        
        case DATA_7:
        {              
            //校验场
            u8_Sci_Reg_Status = SCI0SR1;
            ch = LIN_DATA;
              
            if((u8_Sci_Reg_Status & 0x20) && (u8_Sci_Reg_Status & 0x02) && (ch == 0))  
            {
                rx.state = _BREAK;   //间隔场  FE = 1 
                break;
            }
                    
            if((!(u8_Sci_Reg_Status & 0x20)) || (u8_Sci_Reg_Status & 0x02)) 
                return(FALSE);
      
            rx.check = ch;
            
            rx.state = IDLE;
           //--------------------------------------------
          
            switch(u8_Lin_identifier) 
            {
                case BCM_ID: 
                {
                      u8_Lin_Data_Check = EnhancedLinCalcChecksum(rx.data,rx.protected_id);
                      
                      if(u8_Lin_Data_Check != rx.check) 
                          return(FALSE);
                      
                      Analysis_Master_Data();
                      RLS_Wipe_Park_Process();
                }
                break;
                
                
                case BCM_CFG:
                {
                      u8_Lin_Data_Check = EnhancedLinCalcChecksum(rx.data,rx.protected_id);
                      
                      if(u8_Lin_Data_Check != rx.check) 
                          return(FALSE);
                      
                      Analysis_BCM_Config();
                      
                }
                break;
                
                case BCM_FLW_ID:
                {
                       u8_Lin_Data_Check = EnhancedLinCalcChecksum(rx.data,rx.protected_id);
                      
                       if(u8_Lin_Data_Check != rx.check) 
                          return(FALSE);
                       
                       Lin_Window_Frame.flw_status =  (rx.data[0]&0x0F);
                }
                break;
                
                case BCM_FRW_ID:
                {
                        u8_Lin_Data_Check = EnhancedLinCalcChecksum(rx.data,rx.protected_id);
                      
                        if(u8_Lin_Data_Check != rx.check) 
                          return(FALSE);
                        
                        Lin_Window_Frame.frw_status =  (rx.data[0]&0x0F);
                }
                break;
                
                case BCM_BLW_ID:
                {
                        u8_Lin_Data_Check = EnhancedLinCalcChecksum(rx.data,rx.protected_id);
                      
                        if(u8_Lin_Data_Check != rx.check) 
                          return(FALSE);
                        
                        Lin_Window_Frame.blw_status =  (rx.data[0]&0x0F);
                }
                break;
                
                case BCM_BRW_ID:
                {
                        u8_Lin_Data_Check = EnhancedLinCalcChecksum(rx.data,rx.protected_id);
                      
                        if(u8_Lin_Data_Check != rx.check) 
                          return(FALSE);
                        
                        Lin_Window_Frame.brw_status =  (rx.data[0]&0x0F);
                }
                break;
                
                case BCM_ROOF_ID:
                {
                        u8_Lin_Data_Check = EnhancedLinCalcChecksum(rx.data,rx.protected_id);
                      
                        if(u8_Lin_Data_Check != rx.check) 
                          return(FALSE);
                        
                        Lin_Window_Frame.roof_status =  (rx.data[0]&0x0F);
                }
                break;
                
                case 0x3c:    //Diagnostic
                {
                    u8_Lin_Data_Check = LinCalcChecksum(rx.data);
                    if(u8_Lin_Data_Check != rx.check) 
                        return(FALSE); 
                    
                    if((rx.data[0] == 0)&&
                     (rx.data[1] == 0xFF)&&
                     (rx.data[2] == 0xFF)&&
                     (rx.data[3] == 0xFF)&&
                     (rx.data[4] == 0xFF)&&
                     (rx.data[5] == 0xFF)&&
                     (rx.data[6] == 0xFF)&&
                     (rx.data[7] == 0xFF))
                    {    
                        u8_lin_cmd_sleep_flg = 1;
                    }
                    
                    Diagnostic_Process();
                    Diagnostic_6s_cnt = 0;
                    if(Diagnostic_R.state == 0)  //timer 6s go back to default mode ,60s key lock
                        Diagnostic_Extended_En = FALSE;   
                    else 
                        Diagnostic_Extended_En = TRUE;                    
                }
                break;
                
                default: break;
            }
            rx.state = IDLE;      
        }
        break;
        
        case CHECKSUM:
        {
            return(FALSE);
        }
        break;
              
    }
    
    return(TRUE);
}

/*******************************************************
 * FUNCTION NAME : Diagnostic_Process()
 *   DESCRIPTION : Diagnostic_Process function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void Diagnostic_Process(void)
{
    uint32  Diagnostic_Bcm_Key = 0, j = 0;

    Diagnostic_R.Diagnostic_receive = TRUE;
    Diagnostic_R.SID         = rx.data[2];
    
    if(rx.data[1] == 0x01)
    {
        Diagnostic_R.Response_type = FALSE;           
        Diagnostic_R.RD[0] = 0x13;    //Incorrect Message Length Or Invalid Format

        if((Diagnostic_R.state == 2) && (rx.data[2] == 0x27))
        {
            Diagnostic_R.state = 1;
        }
    }
    else
    {
        switch(Diagnostic_R.state)
        {
            //default mode
            case 0:                        
            {
                switch(rx.data[2])
                {        
                    //SID
                    case 0x10:
                    {                            
                        //SID 0x10 Function 0x01 0x03
                        if(rx.data[1] == 0x02) 
                        {   
                            //PCI
                            switch(rx.data[3])
                            {       
                                //0x16021001L  go to Diagnostic_R.state = 0
                                case 0x01:
                                {
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF; 
                      
                                    Diagnostic_R.state = 0;
                                }
                                break;
                                
                                //0x16021003L  go to Diagnostic_R.state = 1
                                case 0x03:
                                {            
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x03;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF;

                                    if(Diagnostic_KEY_Locked == TRUE) 
                                        Diagnostic_R.state = 4; 
                                    
                                    else 
                                        Diagnostic_R.state = 1;
                                }
                                break;
                                
                                case 0x81:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                              
                                case 0x83:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                                
                                default:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                            }
                        }
                         
                        else   
                        {
                            Diagnostic_R.Response_type = FALSE;           
                            Diagnostic_R.RD[0] = 0x13;     //Incorrect Message Length Or Invalid Format
                        }
                    }
                    break;
                    
                    case 0x27:
                    {
                        Diagnostic_R.Response_type = FALSE;
                        Diagnostic_R.RD[0] = 0x7F;    //Sub function not supported in active mode 
                    } 
                    break;
                    
                    case 0x2e: 
                    {
                        Diagnostic_R.Response_type = FALSE;
                        Diagnostic_R.RD[0] = 0x7F;    //Sub function not supported in active mode
                    }
                    break;
                    
                    //读出数据
                    case 0x22:
                    {              
                        if(rx.data[1] == 0x03)
                        {
                          //日照百分比
                            if((rx.data[3] == 0x13) && (rx.data[4] == 0x00))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x05;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x00;
                                Diagnostic_R.RD[2] = Brightness_Infrared_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                          //光线百分比    
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x01))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x01;
                                Diagnostic_R.RD[2] = Brightness_Light_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                           
                           //自动关天窗配置 
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x02))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x02;
                                Diagnostic_R.RD[2] = Scuttle_Control[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                           //软件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x95))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x95;
                                  Diagnostic_R.RD[2] = Software_Versions[0];
                                  Diagnostic_R.RD[3] = Software_Versions[1];
                                  Diagnostic_R.RD[4] = Software_Versions[2];
                            }
                           
                           //硬件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x93))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x93;
                                  Diagnostic_R.RD[2] = Hardware_Versions[0];
                                  Diagnostic_R.RD[3] = Hardware_Versions[1];
                                  Diagnostic_R.RD[4] = Hardware_Versions[2];
                            }
                           
                           //零件号
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x87))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x87;
                                  Diagnostic_R.RD[2] = Part_Versions[0];
                                  Diagnostic_R.RD[3] = Part_Versions[1];
                                  Diagnostic_R.RD[4] = Part_Versions[2];
                            }

                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0A))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x04;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0x13;
                                  Diagnostic_R.RD[1] = 0x0A;
                                  Diagnostic_R.RD[2] = Mnrval.IR_A;
                                  Diagnostic_R.RD[3] = Mnrval.IR_A >> 8;
                                  Diagnostic_R.RD[4] = 0xFF;
                            }
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0B))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0B;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_B);
                                Diagnostic_R.RD[3] = Mnrval.IR_B >> 8;
                                Diagnostic_R.RD[4] = 0xFF;                                        
                            } 
                            
                            else
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x31;
                            }
                        }
                        
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                    
                    case 0x3E: 
                    {
                        if(rx.data[1] == 0x02)
                        {
                            if((rx.data[3] == 0x00) || (rx.data[3] == 0x80))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x02;
                                Diagnostic_R.RSID = 0x7E;
                                Diagnostic_R.RD[0] = 0x00;
                                Diagnostic_R.RD[1] = 0xFF;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            } 
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12;
                            }
                        }
                        
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break; 
          
                    default:
                    {
                        Diagnostic_R.Response_type = FALSE; 
                        Diagnostic_R.RD[0] = 0x11;
                    }
                    break;
                } 
            }
            break;
                     
            //extended mode ,not get seed
            case 1:
            {        
                //SID
                switch(rx.data[2])
                {        
                    //extended mode ,not get seed
                    case 0x10:
                    {                           
                        //PCI
                        if(rx.data[1] == 0x02) 
                        {   
                            //0x16021001L  go to Diagnostic_R.state = 0  
                            switch(rx.data[3])
                            {       
                                case 0x01:
                                {
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF; 

                                    Diagnostic_R.state = 0;
                                }
                                break;
                                
                                //0x16021003L  go to Diagnostic_R.state = 1
                                case 0x03:
                                {            
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x03;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF;

                                    Diagnostic_R.state = 1;
                                }
                                break;
                                
                                case 0x81:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                
                                case 0x83:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                                
                                default:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                            }
                        }
                         
                        else   
                        {
                            Diagnostic_R.Response_type = FALSE;           
                            Diagnostic_R.RD[0] = 0x13;     //Incorrect Message Length Or Invalid Format
                        }
                    }
                    break;
                    
                    //extended mode ,not get seed         
                    case 0x27:
                    {                       
                        switch(rx.data[3])
                        {
                            case 0x01:
                            {
                                if(rx.data[1] == 2)
                                {
                                    Diagnostic_Seed = Mnrval.IR_A ++;
                                    Diagnostic_Seed = ((Diagnostic_Seed << 16)| TCNT);
                                    #ifdef STATIC_SEED 
                                        Diagnostic_Seed = 0x55555555;
                                    #endif
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon = 0x06;
                                    Diagnostic_R.RSID = 0x67;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = (uint8)((Diagnostic_Seed & 0xff000000) >> 24);
                                    Diagnostic_R.RD[2] = (uint8)((Diagnostic_Seed & 0x00ff0000) >> 16);
                                    Diagnostic_R.RD[3] = (uint8)((Diagnostic_Seed & 0x0000ff00) >> 8);
                                    Diagnostic_R.RD[4] = (uint8)((Diagnostic_Seed & 0x000000ff));
                                    Diagnostic_Key  = Seed_To_Key(Diagnostic_Seed);
                                    Diagnostic_R.state = 2;
                                } 
                                
                                else 
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x13;
                                }
                            }
                            break;
                            
                            case 0x02:
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x24;
                            }
                            break;
                            
                            default:
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12; 
                            }
                            break;
                        }
                    } 
                    break;
                    
                    //extended mode ,not get seed         
                    case 0x2e: 
                    {                      
                        Diagnostic_R.Response_type = FALSE;
                        Diagnostic_R.RD[0] = 0x33;    //Sub function not supported in active mode
                    }
                    break;
                    
                    //读出数据    //extended mode ,not get seed
                    case 0x22:
                    {              
                        if(rx.data[1] == 0x03)
                        {
                            //日照百分比
                            if((rx.data[3] == 0x13) && (rx.data[4] == 0x00))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x05;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x00;
                                Diagnostic_R.RD[2] = Brightness_Infrared_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                          //光线百分比    
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x01))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x01;
                                Diagnostic_R.RD[2] = Brightness_Light_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //自动关天窗配置 
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x02))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x02;
                                Diagnostic_R.RD[2] = Scuttle_Control[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //软件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x95))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x95;
                                  Diagnostic_R.RD[2] = Software_Versions[0];
                                  Diagnostic_R.RD[3] = Software_Versions[1];
                                  Diagnostic_R.RD[4] = Software_Versions[2];
                            }
                           
                           //硬件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x93))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x93;
                                  Diagnostic_R.RD[2] = Hardware_Versions[0];
                                  Diagnostic_R.RD[3] = Hardware_Versions[1];
                                  Diagnostic_R.RD[4] = Hardware_Versions[2];
                            }
                           
                           //零件号
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x87))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x87;
                                  Diagnostic_R.RD[2] = Part_Versions[0];
                                  Diagnostic_R.RD[3] = Part_Versions[1];
                                  Diagnostic_R.RD[4] = Part_Versions[2];
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0A))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0A;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_A);
                                Diagnostic_R.RD[3] = Mnrval.IR_A >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0B))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0B;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_B);
                                Diagnostic_R.RD[3] = Mnrval.IR_B >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                             
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x31;
                            }
                        }
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                    
                    //extended mode ,not get seed
                    case 0x3E: 
                    {                      
                        if(rx.data[1] == 0x02)
                        {
                            if((rx.data[3] == 0x00) || (rx.data[3] == 0x80))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x02;
                                Diagnostic_R.RSID  = 0x7E;
                                Diagnostic_R.RD[0] = 0x00;
                                Diagnostic_R.RD[1] = 0xFF;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                             
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12;
                            }
                        }
                        
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                    
                    //extended mode ,not get seed
                    default:
                    {                    
                        Diagnostic_R.Response_type = FALSE; 
                        Diagnostic_R.RD[0] = 0x11;
                    }
                    break;
                } 
            } 
            break;
            
            //extended mode ,not check key
            case 2:
            {            
                //SID
                switch(rx.data[2])
                {        
                    //extended mode ,not check key
                    case 0x10:
                    {                           
                        //PCI
                        if(rx.data[1] == 0x02) 
                        {   
                            //0x16021001L  go to Diagnostic_R.state = 0  
                            switch(rx.data[3])
                            {       
                                case 0x01:
                                {
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF; 

                                    Diagnostic_R.state = 0;
                                }
                                break;
                
                                //0x16021003L  go to Diagnostic_R.state = 1                
                                case 0x03:
                                {            
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x03;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF;

                                    Diagnostic_R.state = 1;
                                }
                                break;
                
                                case 0x81:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                
                                case 0x83:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                
                                default:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                            }
                        } 
                        else   
                        {
                            Diagnostic_R.Response_type = FALSE;           
                            Diagnostic_R.RD[0] = 0x13;     //Incorrect Message Length Or Invalid Format
                        }
                    }
                    break;
           
                    //extended mode ,not check key
                    case 0x27:
                    {                        
                        switch(rx.data[3])
                        {
                            case 0x01:
                            {
                                if(rx.data[1] == 2)
                                {
                                    Diagnostic_Seed = Mnrval.IR_A ++;
                                    Diagnostic_Seed = ((Diagnostic_Seed << 16)| TCNT);
                                    Diagnostic_Key  = Seed_To_Key(Diagnostic_Seed);
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon = 0x06;
                                    Diagnostic_R.RSID = 0x67;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = (uint8)((Diagnostic_Seed & 0xff000000) >> 24);
                                    Diagnostic_R.RD[2] = (uint8)((Diagnostic_Seed & 0x00ff0000) >> 16);
                                    Diagnostic_R.RD[3] = (uint8)((Diagnostic_Seed & 0x0000ff00) >> 8);
                                    Diagnostic_R.RD[4] = (uint8)((Diagnostic_Seed & 0x000000ff));
                                }
                                 
                                else 
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x13;
                                    Diagnostic_R.state = 1;
                                }
                            }
                            break;
                            
                            case 0x02:
                            {
                                if(rx.data[1] == 6)
                                {
                                    Diagnostic_Bcm_Key = rx.data[7];
                                    j = rx.data[6];  
                                    Diagnostic_Bcm_Key |= ((j << 8) & 0x0000ff00);
                                    j = rx.data[5];
                                    Diagnostic_Bcm_Key |= ((j << 16) & 0x00ff0000);
                                    j = rx.data[4];
                                    Diagnostic_Bcm_Key |= ((j << 24) & 0xff000000);
                            
                                    //正确KEY
                                    if(Diagnostic_Bcm_Key == Diagnostic_Key)
                                    {       
                                        Diagnostic_R.Access_OK = TRUE;
                                        Diagnostic_R.Response_type = TRUE;
                                        Diagnostic_R.RLon = 0x02;
                                        Diagnostic_R.RSID = 0x67;
                                        Diagnostic_R.RD[0] = 0x02;
                                        Diagnostic_R.RD[1] = 0xFF;
                                        Diagnostic_R.RD[2] = 0xFF;
                                        Diagnostic_R.RD[3] = 0xFF;
                                        Diagnostic_R.RD[4] = 0xFF;
                                        Diagnostic_Key_Wrong_Num = 0;
                                        Diagnostic_R.state = 3;
                                    }
                            
                                    //错误的KEY         
                                    else           
                                    {
                                        Diagnostic_R.Response_type = FALSE;

                                        Diagnostic_Key_Wrong_Num ++;

                                        if(Diagnostic_Key_Wrong_Num >= 3)
                                        {
                                            Diagnostic_R.RD[0] = 0x36;   //KEY input incorrect 3 times
                                            Diagnostic_R.state = 4;
                                            Diagnostic_60s_cnt = 0;
                                            Diagnostic_KEY_Locked = TRUE;
                                            Diagnostic_Key_Wrong_Num = 0; 
                                        }
                                        
                                        else 
                                        {
                                            Diagnostic_R.RD[0] = 0x35;   
                                            Diagnostic_R.state = 1;
                                        }
                                    }
                                } 
                                
                                else 
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x13;
                                    Diagnostic_R.state = 1;
                                }
                            }
                            break;
                            
                            default:
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12; 
                                Diagnostic_R.state = 1;
                            }
                            break;
                        }
                    } 
                    break;
                    
                    //extended mode ,not check key
                    case 0x2e: 
                    {                  
                        Diagnostic_R.Response_type = FALSE;
                        Diagnostic_R.RD[0] = 0x33;    //Sub function not supported in active mode
                    }
                    break;
                    
                    //读出数据   //extended mode ,not check key
                    case 0x22:
                    {              
                        if(rx.data[1] == 0x03)
                        {
                            //日照百分比
                            if((rx.data[3] == 0x13) && (rx.data[4] == 0x00))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x05;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x00;
                                Diagnostic_R.RD[2] = Brightness_Infrared_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                          //光线百分比    
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x01))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x01;
                                Diagnostic_R.RD[2] = Brightness_Light_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //自动关天窗配置 
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x02))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x02;
                                Diagnostic_R.RD[2] = Scuttle_Control[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //软件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x95))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x95;
                                  Diagnostic_R.RD[2] = Software_Versions[0];
                                  Diagnostic_R.RD[3] = Software_Versions[1];
                                  Diagnostic_R.RD[4] = Software_Versions[2];
                            }
                           
                           //硬件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x93))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x93;
                                  Diagnostic_R.RD[2] = Hardware_Versions[0];
                                  Diagnostic_R.RD[3] = Hardware_Versions[1];
                                  Diagnostic_R.RD[4] = Hardware_Versions[2];
                            }
                           
                           //零件号
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x87))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x87;
                                  Diagnostic_R.RD[2] = Part_Versions[0];
                                  Diagnostic_R.RD[3] = Part_Versions[1];
                                  Diagnostic_R.RD[4] = Part_Versions[2];
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0A))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0A;
                                Diagnostic_R.RD[2] = Mnrval.IR_A;
                                Diagnostic_R.RD[3] = Mnrval.IR_A >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0B))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0B;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_B);
                                Diagnostic_R.RD[3] = Mnrval.IR_B >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x31;
                            }
                        }        
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                    
                    //extended mode ,not check key
                    case 0x3E: 
                    {                     
                        if(rx.data[1] == 0x02)
                        {
                            if((rx.data[3] == 0x00) || (rx.data[3] == 0x80))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x02;
                                Diagnostic_R.RSID  = 0x7E;
                                Diagnostic_R.RD[0] = 0x00;
                                Diagnostic_R.RD[1] = 0xFF;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                             
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12;
                            }
                        }
                        
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                     
                    //extended mode ,not check key
                    default:
                    {                    
                        Diagnostic_R.Response_type = FALSE; 
                        Diagnostic_R.RD[0] = 0x11;
                    }
                    break;
                }  
            }
            break;
            
            //SecuiryAccess
            case 3:
            {                             
                //SID
                switch(rx.data[2])
                {        
                    //SecuiryAccess
                    case 0x10:
                    {                            
                        //PCI
                        if(rx.data[1] == 0x02) 
                        {   
                            //0x16021001L  go to Diagnostic_R.state = 0  
                            switch(rx.data[3])
                            {       
                                case 0x01:
                                {
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon = 0x02;
                                    Diagnostic_R.RSID = 0x50;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF; 

                                    Diagnostic_R.state = 0;
                                }
                                break;
                
                                //0x16021003L  go to Diagnostic_R.state = 1                
                                case 0x03:
                                {            
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon = 0x02;
                                    Diagnostic_R.RSID = 0x50;
                                    Diagnostic_R.RD[0] = 0x03;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF;

                                    Diagnostic_R.state = 1;
                                }
                                break;
                
                                case 0x81:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                
                                case 0x83:
                                {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                
                                default:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                            }
                        } 
                        
                        else   
                        {
                            Diagnostic_R.Response_type = FALSE;           
                            Diagnostic_R.RD[0] = 0x13;     //Incorrect Message Length Or Invalid Format
                        }
                    }
                    break;
                    
                    //SecuiryAccess
                    case 0x27:
                    {                     
                        switch(rx.data[3])
                        {
                            case 0x01:
                            {
                                if(rx.data[1] == 2)
                                {
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon = 0x06;
                                    Diagnostic_R.RSID = 0x67;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = 0;
                                    Diagnostic_R.RD[2] = 0;
                                    Diagnostic_R.RD[3] = 0;
                                    Diagnostic_R.RD[4] = 0;
                                    Diagnostic_Key  = Seed_To_Key(Diagnostic_Seed);
                                } 
                                else 
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x13;
                                }
                            }
                            break;
                            
                            case 0x02:
                            {
                                if(rx.data[1] == 6)
                                {
                                    Diagnostic_Bcm_Key = rx.data[7];
                                    j = rx.data[6];  
                                    Diagnostic_Bcm_Key |= ((j << 8) & 0x0000ff00);
                                    j = rx.data[5];
                                    Diagnostic_Bcm_Key |= ((j << 16) & 0x00ff0000);
                                    j = rx.data[4];
                                    Diagnostic_Bcm_Key |= ((j << 24) & 0xff000000);
                            
                                    //正确KEY
                                    if(Diagnostic_Bcm_Key == Diagnostic_Key)
                                    {       
                                        Diagnostic_R.Access_OK = TRUE;
                                        Diagnostic_R.Response_type = TRUE;
                                        Diagnostic_R.RLon = 0x02;
                                        Diagnostic_R.RSID = 0x67;
                                        Diagnostic_R.RD[0] = 0x02;
                                        Diagnostic_R.RD[1] = 0xFF;
                                        Diagnostic_R.RD[2] = 0xFF;
                                        Diagnostic_R.RD[3] = 0xFF;
                                        Diagnostic_R.RD[4] = 0xFF;
                                        Diagnostic_Key_Wrong_Num = 0;
                                    } 
                            
                                    //错误的KEY
                                    else           
                                    {
                                        Diagnostic_R.Response_type = FALSE;
                                        Diagnostic_R.RD[0] = 0x35;   
                                    }
                                }
                                
                                else 
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x13;
                                }
                            }    
                            break;
                            
                            default:
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12; 
                            }
                            break;
                        }
                    } 
                    break;
          
                    //SecuiryAccess
                    case 0x2e: 
                    {                  
                        if((rx.data[1] >= 1) && (rx.data[1] <= 6)) 
                        {

                            //日照百分比
                            if((rx.data[3] == 0x13) && (rx.data[4] == 0x00))
                            {
                                Brightness_Infrared_Percentage[0] = rx.data[5];
                                HCS12_EE_Write_2Word(EEPROM_BR_INF_PER_ADDR,Brightness_Infrared_Percentage);

                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x03;
                                Diagnostic_R.RSID = 0x6e;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x00;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            //光线百分比
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x01))
                            {
                                Brightness_Light_Percentage[0] = rx.data[5];
                                HCS12_EE_Write_2Word(EEPROM_BR_LIG_PER_ADDR,Brightness_Light_Percentage);

                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x03;
                                Diagnostic_R.RSID = 0x6e;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x01;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //关天窗控制
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x02))
                            {
                                Scuttle_Control[0] = rx.data[5];
                                HCS12_EE_Write_2Word(EEPROM_SCUTTLE_CONTROL_ADDR,Scuttle_Control);

                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x03;
                                Diagnostic_R.RSID = 0x6e;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x02;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            else
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x31;
                            }   
                        }
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                    
                    //读出数据  //SecuiryAccess
                    case 0x22:
                    {              
                        if(rx.data[1] == 0x03)
                        {
                            //日照百分比
                            if((rx.data[3] == 0x13) && (rx.data[4] == 0x00))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x05;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x00;
                                Diagnostic_R.RD[2] = Brightness_Infrared_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                          //光线百分比    
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x01))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x01;
                                Diagnostic_R.RD[2] = Brightness_Light_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //自动关天窗配置 
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x02))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x02;
                                Diagnostic_R.RD[2] = Scuttle_Control[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //软件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x95))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x95;
                                  Diagnostic_R.RD[2] = Software_Versions[0];
                                  Diagnostic_R.RD[3] = Software_Versions[1];
                                  Diagnostic_R.RD[4] = Software_Versions[2];
                            }
                           
                           //硬件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x93))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x93;
                                  Diagnostic_R.RD[2] = Hardware_Versions[0];
                                  Diagnostic_R.RD[3] = Hardware_Versions[1];
                                  Diagnostic_R.RD[4] = Hardware_Versions[2];
                            }
                           
                           //零件号
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x87))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x87;
                                  Diagnostic_R.RD[2] = Part_Versions[0];
                                  Diagnostic_R.RD[3] = Part_Versions[1];
                                  Diagnostic_R.RD[4] = Part_Versions[2];
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0A))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x04;
                                Diagnostic_R.RSID = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0A;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_A);
                                Diagnostic_R.RD[3] = Mnrval.IR_A >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0B))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x04;
                                Diagnostic_R.RSID = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0B;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_B);
                                Diagnostic_R.RD[3] = Mnrval.IR_B >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            } 
                            
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x31;
                            }
                        }
                          
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                    
                    //SecuiryAccess
                    case 0x3E: 
                    {                    
                        if(rx.data[1] == 0x02)
                        {
                            if((rx.data[3] == 0x00) || (rx.data[3] == 0x80))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x02;
                                Diagnostic_R.RSID = 0x7E;
                                Diagnostic_R.RD[0] = 0x00;
                                Diagnostic_R.RD[1] = 0xFF;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            } 
                            
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12;
                            }
                        }
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                     
                    //SecuiryAccess
                    default: 
                    {                  
                        Diagnostic_R.Response_type = FALSE; 
                        Diagnostic_R.RD[0] = 0x11;
                    }
                    break;
                }  
            }
            break;
            
            //KEY LOCKED
            case 4:
            {                             
                //SID
                switch(rx.data[2])
                {        
                    //KEY LOCKED
                    case 0x10:
                    {                           
                        //PCI
                        if(rx.data[1] == 0x02) 
                        {   
                            //0x16021001L  go to Diagnostic_R.state = 0
                            switch(rx.data[3])
                            {       
                                
                                case 0x01:
                                {
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x01;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF;
                                    Diagnostic_R.state = 0; 
                                }
                                break;
                                
                                //0x16021003L  go to Diagnostic_R.state = 1
                                case 0x03:
                                {            
                                    Diagnostic_R.Response_type = TRUE;
                                    Diagnostic_R.RLon  = 0x02;
                                    Diagnostic_R.RSID  = 0x50;
                                    Diagnostic_R.RD[0] = 0x03;
                                    Diagnostic_R.RD[1] = 0xFF;
                                    Diagnostic_R.RD[2] = 0xFF;
                                    Diagnostic_R.RD[3] = 0xFF;
                                    Diagnostic_R.RD[4] = 0xFF;
                                }
                                break;
                                
                                case 0x81:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }

                                case 0x83:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                    Diagnostic_R.state = 0; 
                                }
                                break;
                
                                default:
                                {
                                    Diagnostic_R.Response_type = FALSE;
                                    Diagnostic_R.RD[0] = 0x12;    //Sub function not supported
                                }
                                break;
                            }
                        }
                         
                        else   
                        {
                            Diagnostic_R.Response_type = FALSE;           
                            Diagnostic_R.RD[0] = 0x13;     //Incorrect Message Length Or Invalid Format
                        }
                    }
                    break;
                    
                    //KEY LOCKED
                    case 0x27:
                    {                       
                        switch(rx.data[3])
                        {
                            case 0x01:
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x37;
                            }
                            break;
                            
                            case 0x02:
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x24;
                            }
                            break;
                            
                            default:
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12; 
                            }
                            break;
                        }
                    } 
                    break;
                    
                    //KEY LOCKED
                    case 0x2e: 
                    {                       
                        Diagnostic_R.Response_type = FALSE;
                        Diagnostic_R.RD[0] = 0x7F;    //Sub function not supported in active mode
                    }
                    break;
                    
                    //读出数据      //KEY LOCKED
                    case 0x22:
                    {             
                        if(rx.data[1] == 0x03)
                        {
                            //日照百分比
                            if((rx.data[3] == 0x13) && (rx.data[4] == 0x00))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x05;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x00;
                                Diagnostic_R.RD[2] = Brightness_Infrared_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                          //光线百分比    
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x01))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x01;
                                Diagnostic_R.RD[2] = Brightness_Light_Percentage[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //自动关天窗配置 
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x02))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x02;
                                Diagnostic_R.RD[2] = Scuttle_Control[0];
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            //软件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x95))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x95;
                                  Diagnostic_R.RD[2] = Software_Versions[0];
                                  Diagnostic_R.RD[3] = Software_Versions[1];
                                  Diagnostic_R.RD[4] = Software_Versions[2];
                            }
                           
                           //硬件版本
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x93))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x93;
                                  Diagnostic_R.RD[2] = Hardware_Versions[0];
                                  Diagnostic_R.RD[3] = Hardware_Versions[1];
                                  Diagnostic_R.RD[4] = Hardware_Versions[2];
                            }
                           
                           //零件号
                            else if((rx.data[3] == 0xF1) && (rx.data[4] == 0x87))
                            {
                                  Diagnostic_R.Response_type = TRUE;
                                  Diagnostic_R.RLon  = 0x06;
                                  Diagnostic_R.RSID  = 0x62;
                                  Diagnostic_R.RD[0] = 0xF1;
                                  Diagnostic_R.RD[1] = 0x87;
                                  Diagnostic_R.RD[2] = Part_Versions[0];
                                  Diagnostic_R.RD[3] = Part_Versions[1];
                                  Diagnostic_R.RD[4] = Part_Versions[2];
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0A))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon  = 0x04;
                                Diagnostic_R.RSID  = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0A;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_A);
                                Diagnostic_R.RD[3] = Mnrval.IR_A >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                            
                            else if((rx.data[3] == 0x13) && (rx.data[4] == 0x0B))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x04;
                                Diagnostic_R.RSID = 0x62;
                                Diagnostic_R.RD[0] = 0x13;
                                Diagnostic_R.RD[1] = 0x0B;
                                Diagnostic_R.RD[2] = (uint8)(Mnrval.IR_B);
                                Diagnostic_R.RD[3] = Mnrval.IR_B >> 8;
                                Diagnostic_R.RD[4] = 0xFF;
                            }
                             
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x31;
                            }
                        } 
                         
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break;
                    
                    //KEY LOCKED
                    case 0x3E: 
                    {                          
                        if(rx.data[1] == 0x02)
                        {
                            if((rx.data[3] == 0x00) || (rx.data[3] == 0x80))
                            {
                                Diagnostic_R.Response_type = TRUE;
                                Diagnostic_R.RLon = 0x02;
                                Diagnostic_R.RSID = 0x7E;
                                Diagnostic_R.RD[0] = 0x00;
                                Diagnostic_R.RD[1] = 0xFF;
                                Diagnostic_R.RD[2] = 0xFF;
                                Diagnostic_R.RD[3] = 0xFF;
                                Diagnostic_R.RD[4] = 0xFF;
                            } 
                            
                            else 
                            {
                                Diagnostic_R.Response_type = FALSE;
                                Diagnostic_R.RD[0] = 0x12;
                            }
                        }
                        
                        else
                        {
                            Diagnostic_R.Response_type = FALSE;
                            Diagnostic_R.RD[0] = 0x13;
                        }
                    }
                    break; 
                    
                    //KEY LOCKED
                    default:
                    {                        
                        Diagnostic_R.Response_type = FALSE; 
                        Diagnostic_R.RD[0] = 0x11;
                    }
                    break;
                } 
            }
            break;
            
            default:
            break;
            
        }
    }
}

/*******************************************************
 * FUNCTION NAME : Diagnostic_RESP_Process()
 *   DESCRIPTION : Diagnostic_RESP_Process function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
uint8 Diagnostic_RESP_Process(void)
{
    if(Diagnostic_R.Diagnostic_receive)
    {
        Diagnostic_6s_cnt = 0;
        Diagnostic_R.Diagnostic_receive = 0;
        
        if(Diagnostic_R.Response_type)
        {
            Diagnostic_Response.data_field[0] = 0x22;
            Diagnostic_Response.data_field[1] = Diagnostic_R.RLon;
            Diagnostic_Response.data_field[2] = Diagnostic_R.RSID;
            Diagnostic_Response.data_field[3] = Diagnostic_R.RD[0];
            Diagnostic_Response.data_field[4] = Diagnostic_R.RD[1];
            Diagnostic_Response.data_field[5] = Diagnostic_R.RD[2];
            Diagnostic_Response.data_field[6] = Diagnostic_R.RD[3];
            Diagnostic_Response.data_field[7] = Diagnostic_R.RD[4];
        }
        else
        {
            Diagnostic_Response.data_field[0] = 0x22;
            Diagnostic_Response.data_field[1] = 0x03;
            Diagnostic_Response.data_field[2] = 0x7F;
            Diagnostic_Response.data_field[3] = Diagnostic_R.SID;
            Diagnostic_Response.data_field[4] = Diagnostic_R.RD[0];
            Diagnostic_Response.data_field[5] = 0xFF;   
            Diagnostic_Response.data_field[6] = 0xFF;
            Diagnostic_Response.data_field[7] = 0xFF;
        }
      
        rx.error = LinSndMsg(Diagnostic_Response,0xff);       //诊断需要发送校验
        if(rx.error == FALSE) return (FALSE); 
    }
}

/*******************************************************
 * FUNCTION NAME : Lin_RLS_data()
 *   DESCRIPTION : Lin_RLS_data function
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void Lin_RLS_data(void)
{  
    RLS_Wipe_Auto_On_Function();
    RLS_Wipe_Sensitivity_Up_Function(); 
    
    if((Mnrval.IR_A == 0xFFFF) || (Mnrval.IR_B == 0xFFFF))
    {
        Lin_RLS_Frame.RQ_WiperSPD = 0;
    }
    
    #ifdef TEST_MODE
        Lin_RLS_TEST_Frame.adc_A_L = Mnrval.IR_A ;
        Lin_RLS_TEST_Frame.adc_A_H = Mnrval.IR_A >>8;
        
        Lin_RLS_TEST_Frame.adc_B_L = Mnrval.IR_B ;
        Lin_RLS_TEST_Frame.adc_B_H = Mnrval.IR_B >>8;
        
        Lin_RLS_TEST_Frame.IR_L = Mnrval.Amb_D ;
        Lin_RLS_TEST_Frame.IR_H = Mnrval.Amb_D >>8;
        
        Lin_RLS_TEST_Frame.FW_L = Mnrval.Amb_C ;
        Lin_RLS_TEST_Frame.FW_H = Mnrval.Amb_C >>8;
        memcpy(&msg_send.data_field[0],&Lin_RLS_TEST_Frame,MAX_DATA);
    #else
       
        msg_send.data_field[0] = (Lin_RLS_Frame.RQ_WiperSPD << 5) | (Lin_RLS_Frame.Light_ready << 4) | (msg_send.data_field[0] & 0x0f);                          
        msg_send.data_field[1] = (Lin_RLS_Frame.RQ_LowBeam << 3) | (Lin_RLS_Frame.RQ_LowBeam_Invers << 4) | (Lin_RLS_Frame.RQ_PositionLamp << 6) | (Lin_RLS_Frame.RQ_PositionLamp_Invers << 7);                   
        msg_send.data_field[2] = Lin_RLS_Frame.Genaration |(Lin_RLS_Frame.Fault_Light << 1) | (Lin_RLS_Frame.Fault_Rain << 2) | (Lin_RLS_Frame.VOLT_Error <<4) |(msg_send.data_field[2]&0x08);
        msg_send.data_field[3] = Lin_RLS_Frame.Brightness_IR;
        msg_send.data_field[4] = Lin_RLS_Frame.Brightness_FW_L;                            
        msg_send.data_field[5] = (Lin_RLS_Frame.Brightness_FW_H) | (Lin_RLS_Frame.Rain_Intensity << 4);                                       
        msg_send.data_field[6] = (uint8)(Mnrval.IR_A);
        msg_send.data_field[7] = (uint8)(Mnrval.IR_A >> 8); 
        
    #endif
}


