#ifndef __LIN_APP_H__
#define __LIN_APP_H__

#include <hidef.h>
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"



#define RLS_ID          0x27
#define BCM_ID          0x10
#define RLS_ASK         0x28
#define BCM_CFG         0x1A
#define RLS_NAD         0x22 
#define RLS_MASK        0xB49CA38E

#define BCM_FLW_ID     0x21
#define BCM_FRW_ID     0x22
#define BCM_BLW_ID     0x23
#define BCM_BRW_ID     0x24
#define BCM_ROOF_ID    0x25

enum Lin_state 
{ 
    IDLE, 
    _BREAK, 
    SYNCH, 
    PROTECTED_IDENTIFIER, 
    DATA_0, 
    DATA_1,
    DATA_2, 
    DATA_3, 
    DATA_4, 
    DATA_5, 
    DATA_6, 
    DATA_7, 
    CHECKSUM 
};

struct Lin_message 
{
    uint8 identifier;
    uint8 data_field[MAX_DATA];
};

struct Lin_frame 
{
    uint8 protected_id;
    uint8 data[MAX_DATA];
    uint8 check;
    enum  Lin_state state;
    uint8 error;
    uint8 LinByteCnt;      //Lin Bytes Count
};

struct Lin_Diagnostic 
{
    uint8  Diagnostic_receive;
    uint8  Response_type;
    uint8  Access_OK;
    uint8  state;
    uint8  RLon;
    uint8  SID;
    uint8  RSID;
    uint8  RD[5]; 
};

struct RLS_Frame 
{
  uint8  MsgCounter               :4; //bit0
  uint8  Light_ready              :1;
  uint8  RQ_WiperSPD              :3; //bit7
  
  uint8  rsv0                     :3;
  uint8  RQ_LowBeam               :1; 
  uint8  RQ_LowBeam_Invers        :1;
  uint8  rsv1                     :1;
  uint8  RQ_PositionLamp          :1;
  uint8  RQ_PositionLamp_Invers   :1;
   
  uint8  Genaration               :1;
  uint8  Fault_Light              :1;
  uint8  Fault_Rain               :1;        
  uint8  REP_Error                :1;
  uint8  VOLT_Error               :2;
  uint8  Humid_Temp_Error         :1;
  uint8  rsv2                     :1;
  
  
  uint8  Brightness_IR      ; 
  uint8  Brightness_FW_L    ;
  
  uint8  Brightness_FW_H    :2;
  uint8  Rain_Intensity     :4;
  uint8  rsv3               :2;  
  
  uint8  Temperature       ;
  uint8  Humid             ;
};

struct RLS_TEST_Frame 
{
  uint8 adc_A_L;
  uint8 adc_A_H;
  uint8 adc_B_L;
  uint8 adc_B_H;
  uint8 IR_L;
  uint8 IR_H;
  uint8 FW_L;
  uint8 FW_H;
};



struct BCM_Frame 
{
  uint8  rsv0              :1;   
  uint8  Status_IGN        :2;
  uint8  CMD_AutoWiper     :1;
  uint8  rsv1              :4;
  
  uint8  rsv2              ;
  uint8  rsv3              ;
  uint8  rsv4              ;
  
  uint8  SPD_Vehicle     ;
  
  uint8  rsv5              ;
  uint8  rsv6              ;

  
  uint8  rsv7              :2;
  uint8  ParkPosition      :1;
  uint8  RainSensitivity   :3;
  uint8  rsv8              :2;
    
};

struct BCM_CFG_Frame
{
    uint8  WR_Status       :1;
    uint8  rsv0            :7;
    
    uint8  Parameter_1     :8;
    
    uint8  Parameter_2     :8;
};




struct Window_Frame 
{
    uint8  roof_status    ;   
    uint8  flw_status     ;
    uint8  frw_status     ;
    uint8  blw_status     ;
    uint8  brw_status     ;
};

extern uint8  u8_LinErrorCnt;

extern uint8  u8_Lin_identifier;
extern uint8  u8_RLS_StopMsureFlg ;
extern uint8  u8_Cmd_Execution;

extern uint8  Diagnostic_Extended_En;
extern uint8  Diagnostic_6s_cnt;
extern uint8  Diagnostic_KEY_Locked;
extern uint8  Diagnostic_2s_cnt;
extern uint8  Diagnostic_60s_cnt;
extern uint8  Diagnostic_Key_Wrong_Num;

extern uint16 Brightness_Light_Percentage[2];
extern uint16 Brightness_Infrared_Percentage[2];
extern uint16 Scuttle_Control[2];

extern uint8  u8_SPD_Vehicle;

extern uint8  Gain_Prm;
extern uint8  Gain_Val;
extern uint8  Gain_Val_Pre;

extern struct Lin_message msg_send,msg_get,Diagnostic_Response;
extern struct Lin_frame rx;
extern struct Lin_Diagnostic    Diagnostic_R;
extern struct RLS_Frame         Lin_RLS_Frame;
extern struct BCM_Frame         Lin_BCM_Frame;
extern struct BCM_CFG_Frame     Lin_CFG_Frame;
extern struct Window_Frame      Lin_Window_Frame;
extern struct MLX75308_Mnrval   Mnrval;


extern uint8 Diagnostic_RESP_Process(void);
extern  void    Diagnostic_Process(void);
extern  uint8   Lin_TransStatus(void); 
extern  void    Lin_RLS_data(void);
extern  void    Lin_Prameter_Init(void);
extern  void    LinConfig(void);

#endif