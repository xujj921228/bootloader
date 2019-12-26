#ifndef __GLOBAL_PARAMETER_H
#define __GLOBAL_PARAMETER_H


typedef  unsigned char   uint8;      //unsigned 8 bit definition
typedef  unsigned int    uint16;     //unsigned 16 bit definition
typedef  unsigned long   uint32;     //unsigned 32 bit definition


typedef  signed char     sint8;       //signed 8 bit definition
typedef  short           sint16;      //signed 16 bit definition
typedef  long int        sint32;      //signed 32 bit definition


#define ROOF_FUNCTION_ENABLE
#define SLEEP_ENABLE
//#define FOUR_TO_ONE   //ÅäÖÃËÄºÏÒ»
//#define TEST_MODE

#define SCI_BAUDRATE    19200         // 4800 ok@RTX_OFF DTR_ON >4800 LIN_WRONG  //19200    //SCI Baud rate
#define SCI_CLOCK       16000000      //Bus Clock 16MHz in Hz

#define  MAX_DATA   8

#define BIT(A,B)  ((A>>B)&0x01)   //A is the variable while
                                  //B is the bit number
#define NOP()      asm("nop")



/************RAIN_INVALID***********/   
#define   DC_bef_dtTH           200     
#define   DC_aft_dtTH           200 
#define   DC_CHANGE_TH          300

#define   RAIN_INVALID_NUM     1

#define   PERIOD_SPEED_TIMER   30   //3S

/************DC_COMP***********/
#define   DC_COMP_TH0             8100
#define   SOFT_DC_COMP_VALUE0      300 

#define   RAIN_DELTA          80

#define   DtABS_MAX    5000


/************ADAPT******************/
#define   CALI_PARAM_HIGH        45500
#define   CALI_PARAM_LOW         44500
#define   ADAPT_MEAS_CNT             3
#define   ADAPT_VALUE_DAC_LOW     0x10
#define   ADAPT_VALUE_DAC_HIGH    0xF0



extern uint8 G_10msFlag ;
extern uint8 G_20msFlag ;
extern uint8 G_50msFlag ;
extern uint8 G_100msFlag ;
extern uint8 G_500msFlag ;
extern uint8 G_150msFlag ;
extern uint8 G_4sFlag ;
extern uint8 G_600msFlag;

extern uint16 G_4s_counter;
extern uint8 G_150ms_counter;
extern uint8 G_600ms_counter;

extern const  uint8 Software_Versions[3] ;
extern const  uint8 Hardware_Versions[3] ;
extern const  uint8 Part_Versions[3] ;


#endif /* __GLOBAL_PARAMETER_H */

/*********************************************************************************************************
  End Of File
*********************************************************************************************************/
