/****************************************************************************************************
 *
 *   Copyright 2016 Shanghai Qunyin automotive Corp, All Rights Reserved.
 *
 * --------------------------------------------------------------------------------------------------
 * FILE             : DRV_IIC.c
 * LANGUAGE         : ANSI-C
 * HARDWARE VERSION : 
 * COMPILER VERSION : Freescale CodeWarrior for HCS08  V6.3
 * AUTHOR           : xujun 
 * CURRENT  VERSION : V1.0
 * ALTERED  DATE    : 2016.8.20
 * DESCRIPTION      : 1. IIC driver of MXP8500
 *                    2. IIC read and write operation function 
 * FUNCTION LIST    : 
 *                    1. DRV_IIC_Init()             : Init IIC moudle     
 *                    2. DRV_IIC_START()            : Start IIC comunication
 *                    3. DRV_IIC_STOP()             : Stop IIC comnunication
 *                    4. DRV_IIC_WRITE_BYTE()       : Wtites the timing of individual byte data
 *                    5. DRV_IIC_READ_BYTE()        : Reads the timing of individual byte data
 *                    6. DRV_IIC_WriteSignleData()  : Writes one byte of data through the IIC interface
 *                    7. DRV_IIC_WriteMultipleData(): writes multiple byte of data through the IIC interface
 *                    8. DRV_IIC_ReadSignleData()   : Reads one byte of data through the IIC interface
 *                    9. DRV_IIC_ReadMultipleData() : Reads multiple byte of data through the IIC interface
 *                     
 * --------------------------------------------------------------------------------------------------
 *   HISTORY        :  
 *        <AUTHOR>        <DATE>     <VERSION>    <DESCRIPTION> 
 *        xujun       2016.08.20     V1.0         first release                        
 ****************************************************************************************************/

/****************************************************************************************************
 * NOTE:
 * - When using DRV_IIC.C, should include DRV_IIC.h file.
 * - 1. 
 ****************************************************************************************************/
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"
#include "clock.h"
#include "IIC.h"

/*******************************************************
 * FUNCTION NAME : DRV_IIC_Init()
 *   DESCRIPTION : Initialize the IO port used by the IIC
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void DRV_IIC_Init(void)
{
    IIC_SCL_PULLUP  = 1;                    //Turns off the internal pull-up, using the external pull-up PTA
    IIC_SDA_PULLUP  = 1;                    //Turns off the internal pull-up, using the external pull-up PTB
        
    IIC_SCL_Output();                       //PA2  Humidity sensor SCL     output
    IIC_SDA_Input();                        //PB1  Humidity sensor SDA     output/input     Default input
    
    FUNC_HUM_SETTING(SHT30_ACQ_CMD);
}

/*******************************************************
 * FUNCTION NAME : DRV_IIC_START()
 *   DESCRIPTION : Start IIC comunication
 *         INPUT : void
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void DRV_IIC_START(void)
{
    IIC_SDA_Output();
    IIC_SCL_Output();
    
    IIC_SDA_High();
    IIC_SCL_High();
    
    IIC_SDA_Low(); 
    
    Delay_Nus(100);
    
    IIC_SCL_Low();
       
    Delay_Nus(100);
}

/*******************************************************
 * FUNCTION NAME : DRV_IIC_STOP()
 *   DESCRIPTION : Stop IIC comunication
 *         INPUT : void  
 *        OUTPUT : NONE  
 *        RETURN : void              
 *        OTHERS : NONE
 *******************************************************/
void DRV_IIC_STOP(void)
{
    IIC_SDA_Output();
    IIC_SCL_Output();
    
    IIC_SDA_Low();
    IIC_SCL_Low();
    
    IIC_SCL_High(); 
    
    Delay_Nus(100);
    
    IIC_SDA_High();
    
    Delay_Nus(100);   
}

/*******************************************************
 * FUNCTION NAME : write_Byte()
 *   DESCRIPTION : Write a Byte data
 *         INPUT : The data to be written  
 *        OUTPUT : NONE   
 *        RETURN : uint8  return slave response              
 *        OTHERS : NONE
 *******************************************************/
uint8 DRV_IIC_WRITE_BYTE(uint8 data)
{
  	uint8 i;
  	IIC_SDA_Output();
  	    
  	for(i = 0;i < 8;i++)             //Write 8bit data
  	{
  		///////////////////////////////////////////////////
  		if(data & 0x80)              //The MSB is sent first
  		{
  			IIC_SDA_High();	
  		}
  		else               
  		{
  			IIC_SDA_Low();
  		}
  		///////////////////////////////////////////////////
  		Delay_Nus(10); 
  		IIC_SCL_High();
      Delay_Nus(50); 
      IIC_SCL_Low();
      Delay_Nus(30); 	
  		data <<= 1;                  //The shift is used to write the next bit
  	}
  	IIC_SDA_High();
  	IIC_SDA_Input(); 
  	IIC_SCL_High();
  	Delay_Nus(10); 
    if(IIC_SDA)                      //Receive slave response
    {
        i = NACK;
    }
    else
    {
        i = ACK;
    }
    Delay_Nus(10);
    IIC_SCL_Low();
    Delay_Nus(100); 
    return i;
}

/*******************************************************
 * FUNCTION NAME : read_Byte()
 *   DESCRIPTION : Read one byte data 
 *         INPUT : uint8  Local response  
 *        OUTPUT : NONE
 *        RETURN : uint8  Read the data
 *        OTHERS : NONE
 *******************************************************/
uint8 DRV_IIC_READ_BYTE(uint8 AckValue)
{
	uint8  i;
	uint8  read_data;
	uint16 nCount;
	
	read_data = ZERO;
	nCount    = ZERO;
	IIC_SDA_Output();
	IIC_SCL_Low();
	IIC_SDA_High();
	IIC_SDA_Input();
	
	for(i = 0;i < 8;i++)                 //Read 8bit data
	{
	    IIC_SCL_High();
	    Delay_Nus(40); 
	    read_data <<= 1;                //The shift is used to store the next bit
		/////////////////////////////////////////////////
		if(IIC_SDA)                     //Read one bit data
		{
			read_data |= 0x01;	
		}                                
		else
		{
			read_data &= 0xFE;
		}
		////////////////////////////////////////////////
		IIC_SCL_Low();
		Delay_Nus(10); 
	}	
    IIC_SDA_Output();
    
    IIC_SDA = AckValue;                 //send local response
    Delay_Nus(10); 
    
    IIC_SCL_High();
    Delay_Nus(50); ;
    IIC_SDA_Output();
    IIC_SCL_Low();
    IIC_SDA_High();
    Delay_Nus(100); 
	return read_data; 	
}

/*******************************************************
 * FUNCTION NAME : DRV_IIC_WriteSignleData()
 *   DESCRIPTION : IIC write one byte data 
 *         INPUT : uint8 command     uint8 regester   uint8 data
 *        OUTPUT : NONE  
 *        RETURN : uint8   TRUE/FALSE
 *        OTHERS : NONE
 *******************************************************/
uint8 DRV_IIC_WriteSignleData(uint8 cmd,uint8 reg,uint8 data)
{
    DRV_IIC_START();                      //Start IIC communication
    if(ACK != DRV_IIC_WRITE_BYTE(cmd<<1)) //Write device ID and write signal
    {
        return FALSE;
    }
    if(ACK != DRV_IIC_WRITE_BYTE(reg))    //Config the regester
    {
        return FALSE;
    }
    if(ACK != DRV_IIC_WRITE_BYTE(data))   //Write data
    {
        return FALSE;
    }
    DRV_IIC_STOP();                       //Stop IIC communication
    Delay_Nus(100);
    return TRUE;
}

/*******************************************************
 * FUNCTION NAME : DRV_IIC_WriteMultipleData()
 *   DESCRIPTION : The IIC writes multiple bytes 
 *         INPUT : uint8 command     uint8 regester   uint8 buffer  
 *        OUTPUT : NONE  
 *        RETURN : uint8   TRUE/FALSE              
 *        OTHERS : NONE
 *******************************************************/
uint8 DRV_IIC_WriteMultipleData(uint8 cmd,uint8 reg,uint8 num,uint8 *data)
{
    uint8 ret;
    DRV_IIC_START();                      //Start IIC communication
    if(ACK != DRV_IIC_WRITE_BYTE(cmd<<1)) //Write device ID and write signal
    {
        return FALSE;
    }
    if(ACK != DRV_IIC_WRITE_BYTE(reg))    //Config the regester
    {
        return FALSE;
    }
    for(ret = 0;ret < (num - 1);ret++)    //Writes multiple bytes
    {      
        if(ACK != DRV_IIC_WRITE_BYTE(data[ret]))
        {
            return FALSE;
        }
    }
    DRV_IIC_STOP();                       //Stop IIC communication
    Delay_Nus(100);                         //Wait
    return TRUE;
}

/*******************************************************
 * FUNCTION NAME : DRV_IIC_ReadSingleData()
 *   DESCRIPTION : IIC read one byte 
 *         INPUT : uint8 command   uint8 regester  
 *        OUTPUT : NONE  
 *        RETURN : uint8  data              
 *        OTHERS : NONE
 *******************************************************/
uint8 DRV_IIC_ReadSingleData(uint8 cmd, uint8 reg)
{
    uint8 ret;
    
    DRV_IIC_START();                        //Start IIC communication
    (void)DRV_IIC_WRITE_BYTE(cmd<<1);       //Write device ID and write signal
    (void)DRV_IIC_WRITE_BYTE(reg);          //Config the regester
    DRV_IIC_START();                        //Start IIC communication
    (void)DRV_IIC_WRITE_BYTE((cmd<<1) + 1); //Write device ID and read signal
    if(ACK != DRV_IIC_WRITE_BYTE(cmd<<1))   //Write device ID and write signal
    {
        return FALSE;
    }
    ret = DRV_IIC_READ_BYTE(NACK);          //read data    
    DRV_IIC_STOP();                         //Stop IIC communication
    Delay_Nus(100);                          //Wait
    return ret;
} 

/*******************************************************
 * FUNCTION NAME : DRV_IIC_ReadMultipleData()
 *   DESCRIPTION : The IIC reads multiple bytes
 *         INPUT : uint8 command     uint8 regester   uint8 buffer  
 *        OUTPUT : NONE  
 *        RETURN : uint8              
 *        OTHERS : NONE
 *******************************************************/
uint8 DRV_IIC_ReadMultipleData(uint8 cmd, uint8 reg,uint8 num,uint8 *data)
{
    uint8 ret;
    
    DRV_IIC_START();                               //Start IIC communication
    (void)DRV_IIC_WRITE_BYTE(cmd<<1);              //Write device ID and write signal
    (void)DRV_IIC_WRITE_BYTE(reg);                 //Config the regester
    DRV_IIC_START();                               //Start IIC communication
    (void)DRV_IIC_WRITE_BYTE((cmd<<1) + 1);        //Write device ID and read signal
  
    for(ret = 0;ret < (num - 1);ret ++)            //reads multiple bytes
    {
        *(data + ret) = DRV_IIC_READ_BYTE(ACK);    
    }
    
    *(data + (num - 1)) = DRV_IIC_READ_BYTE(NACK); //read last data and return response    
    DRV_IIC_STOP();                                //Stop IIC communication
    Delay_Nus(100);                                 //Wait
    return ret;
} 
