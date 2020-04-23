
#include "derivative.h" /* include peripheral declarations */
#include "config_parameter.h"
//#include <math.h> 
#include "clock.h"
#include "iic.h"
#include "humid.h"
#include "lin_app.h"


uint16   Temp_measure_TP,Hum_measure_TP;
uint8    Temp_measure;
uint8    Hum_measure;
//float    f_Dew_Point,f_acture_temp,f_acture_hum;
uint16   Dew_Point;
uint8    Humid_buffer[HUMID_NUM],Humid_Avg ;
uint8    Temp_buffer[TEMP_NUM],Temp_Avg;  
uint16   Temp_error_cnt,Hum_error_cnt,iic_error_cnt;

uint8 Humid_Temp_Error;
/****************************************************************************************************
 * FUNCTION NAME : crc8()
 *   DESCRIPTION : crc8校验
 *         INPUT : NONE
 *        OUTPUT : NONE  
 *        RETURN : 校验和                
 *        OTHERS : NONE
 ****************************************************************************************************/
 
unsigned char  crc8(unsigned char *ptr,unsigned char len) // ptr 为数据指针，len 为数据长度
{
    unsigned char i,crc;

    crc = 0xff;
    while(len--)
    {
      	for(i=0x80; i!=0; i>>=1)
      	{
        		if((crc&0x80)!=0) 
        		{
        			crc<<=1; 
        			crc^=G_Poly;
        		} 
        		else 
        			crc<<=1;
        		
        		if((*ptr & i)!=0) 
        			crc ^= G_Poly; 
      	}
      	ptr++;
    }
    return(crc);
}

/****************************************************************************************************
 * FUNCTION NAME : FUNC_HUM_RESET()
 *   DESCRIPTION : 湿度重启
 *         INPUT : NONE
 *        OUTPUT : NONE  
 *        RETURN : uint8         TRUE：重启成功    FALSE：重启失败              
 *        OTHERS : NONE
 ****************************************************************************************************/
static uint8 FUNC_HUM_RESET(void)                    
{
    uint8 ret = FALSE;
    
    DRV_IIC_Init();
    DRV_IIC_START();                      //start I2C
    if(DRV_IIC_WRITE_BYTE(SHT30_ADDR << 1) == ACK)  //I2C address + write
    {
        (void)DRV_IIC_WRITE_BYTE(SHT30_RESET_CMD_H);
        (void)DRV_IIC_WRITE_BYTE(SHT30_RESET_CMD_L);
        ret = TRUE;                         //soft reset
    }
    
    DRV_IIC_STOP();                       //stop I2C
    
    return ret;
}

/****************************************************************************************************
 * FUNCTION NAME : FUNC_HUM_SETTING()
 *   DESCRIPTION : 湿度设置
 *         INPUT : NONE
 *        OUTPUT : NONE  
 *        RETURN : uint8                    
 *        OTHERS : NONE
 ****************************************************************************************************/
uint8 FUNC_HUM_SETTING(uint16 cmd)
{
    DRV_IIC_START();
    if(DRV_IIC_WRITE_BYTE(SHT30_ADDR << 1)==ACK)
    {
        if(DRV_IIC_WRITE_BYTE(cmd>>8)==ACK)                      //Command
        {
            if(DRV_IIC_WRITE_BYTE(cmd&0xFF)==ACK)
            {
               return 1 ;
            }
            else
            {
               return 0 ;
            }
        }
        else
        {
            return 0 ;
        }
    }
    else
    {   
        return 0 ;
    }
    DRV_IIC_STOP();
}


/****************************************************************************************************
 * FUNCTION NAME : FUNC_READ_HUMDATA()
 *   DESCRIPTION : 湿度温度读取
 *         INPUT : cmd，
 *        OUTPUT : Temp_measure,Hum_measure 
 *        RETURN : uint8                    
 *        OTHERS : NONE
 ****************************************************************************************************/
void FUNC_READ_HUMDATA(uint16 cmd)
{
        unsigned char Temper[2],TempCrc,HumCrc;
        unsigned long temp = 0;
        unsigned char i = 0 ;
       

        DRV_IIC_START();
        if(DRV_IIC_WRITE_BYTE(SHT30_ADDR << 1)==ACK)                  //I2C address + write + ACK
        {        
            if(DRV_IIC_WRITE_BYTE(cmd>>8)==ACK)                      //Command
            {
                if(DRV_IIC_WRITE_BYTE(cmd&0xFF)==ACK)
                {
                	iic_error_cnt = 0;
                	
                    do
                    {
                        Delay_Nus(200);
                        DRV_IIC_START();
                        Delay_Nus(1);  
                        i++;
                        if(i >= 100) break;
                    }while(DRV_IIC_WRITE_BYTE(((SHT30_ADDR<<1)|0x01))==NACK);     //I2C address + read        + NACK 

                    Temper[0] = DRV_IIC_READ_BYTE(ACK);                                              //Data(MSB)
                    Temper[1] = DRV_IIC_READ_BYTE(ACK);
                    TempCrc = DRV_IIC_READ_BYTE(ACK);
                    
                    if(TempCrc == crc8(Temper,2))
                    {
						Temp_error_cnt = 0;
						Temp_measure_TP = Temper[0]<<8|Temper[1];
						temp         = (unsigned long)Temp_measure_TP*175;
#if 0
						f_acture_temp =  (float)(temp/65534 - 45); //f_acture_temp
#endif						
						Temp_measure = (uint16)(temp/65534 + 5 ); 
						
						if(Temp_measure >= 254)  Temp_measure = 254;
						
                    }
                    else
                    {
                          Temp_error_cnt++ ;  
                          if(Temp_error_cnt == 4) Temp_error_cnt = 4;
                    }
                    
                    Temper[0] = DRV_IIC_READ_BYTE(ACK);                      //Data(MSB)
                    Temper[1] = DRV_IIC_READ_BYTE(ACK);
                    HumCrc = DRV_IIC_READ_BYTE(ACK);                                              
                    
                    if(HumCrc == crc8(Temper,2))                   
                    {
                          Hum_error_cnt = 0;
                          Hum_measure_TP =  Temper[0]<<8|Temper[1];
                          temp = (unsigned long)Hum_measure_TP*100;                    
                          Hum_measure = temp/65534;
#if 0
                          f_acture_hum =  (float)(temp/65534);
#endif	                         
                    }
                    else
                    {
                          Hum_error_cnt++;  
                          if(Hum_error_cnt == 4) Hum_error_cnt = 4;
                    }
                    
                    DRV_IIC_READ_BYTE(NACK);                                                          //Checksum  + NACK 
                    DRV_IIC_STOP();                                                                              //Stop I2C
                    
                }
                else
                {
                	iic_error_cnt++;
                }
                
                if((Hum_error_cnt >= 4)||(Temp_error_cnt >= 4))
                {
                    Humid_Temp_Error = 1;
                    FUNC_HUM_RESET();
                }
                else
                {
                    Humid_Temp_Error = 0;
                }
                
            }
            else
            {
            	iic_error_cnt++ ;
            }
        }
        else
        {
        	iic_error_cnt++;
        }
        
        if(iic_error_cnt >= 4)
        {
        	iic_error_cnt = 4;
        	Humid_Temp_Error = 1;
        	FUNC_HUM_RESET();
        }
        
        DRV_IIC_STOP();
        
}

/****************************************************************************************************
 * FUNCTION NAME : Humid_Avg_Function()
 *   DESCRIPTION : 湿度平均
 *         INPUT : cmd，
 *        OUTPUT : Temp_measure,Hum_measure 
 *        RETURN : uint8                    
 *        OTHERS : NONE
 ****************************************************************************************************/
void  Humid_Avg_Function(void)
{
    uint8 i ;
    uint16 sum = 0;
    for(i = 1;i <= HUMID_NUM;i++)
    {      
        Humid_buffer[HUMID_NUM - 1] =  Hum_measure;
        if(i < HUMID_NUM)   Humid_buffer[i - 1] = Humid_buffer[i] ;
    }
    
    for(i = 0;i < HUMID_NUM;i++)
    {
         sum += Humid_buffer[i] ;
    }
    Humid_Avg = sum / HUMID_NUM;    
}

/****************************************************************************************************
 * FUNCTION NAME : Temp_Avg_Function()
 *   DESCRIPTION : 温度平均
 *         INPUT : cmd，
 *        OUTPUT : Temp_measure,Hum_measure 
 *        RETURN : uint8                    
 *        OTHERS : NONE
 ****************************************************************************************************/
void  Temp_Avg_Function(void)
{
    uint8 i ;
    uint32 sum = 0;
    for(i = 1;i <= TEMP_NUM;i++)
    {      
        Temp_buffer[TEMP_NUM - 1] =  Temp_measure;
        if(i < TEMP_NUM)   Temp_buffer[i - 1] = Temp_buffer[i] ;
    }
    
    for(i = 0;i < TEMP_NUM;i++)
    {
         sum += Temp_buffer[i] ;
    }
    Temp_Avg = sum / TEMP_NUM;   
}

/****************************************************************************************************
 * FUNCTION NAME : float Dew_Point_Cal(float temp , float hum)
 *   DESCRIPTION : 露点计算
 *         INPUT : cmd，
 *        OUTPUT : Temp_measure,Hum_measure 
 *        RETURN : uint8                    
 *        OTHERS : NONE
 ****************************************************************************************************/
#if 0
	float Dew_Point_Cal(float temp , float hum)
	{
		float h_temp,rt_value;
		
		h_temp =  (log10f(hum) - 2.0) / 0.4343 + (17.62 * temp)/(243.12 + temp) ;
		
		rt_value = (243.12 *  h_temp)/(17.62 - h_temp) ;
		
		return   rt_value ;
	}
#endif
