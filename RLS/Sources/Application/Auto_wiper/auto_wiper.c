/******************************************************************************
*
* @file      ls_app.c
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
#include "auto_wiper.h"
#include "adc.h"
#include "lin_app.h"
#include "lin.h"
#include "lin_cfg.h"
#include "spi.h"
#include "gpio.h"
#include "eeprom.h"
#include "clock.h"
#include "rtc.h"
#include "ftm.h"
#include "watchdog.h"
#include "local_eep_data.h"
#include "mlx75308.h"
#include "self_adapt.h"


extern Main_Fsm_t             RLS_RunMode;
//this frame is for APP 
extern RLS_APP_Value_t     RLS_APP_Value;
extern BCM_APP_Value_t     BCM_APP_Value;

extern RLS_APP_Value_t     RLS_APP_Value;
extern MLX75308_Frame_t       MLX75308_RxFrame;
extern MLX75308_Mnrval_t      Mnrval;

extern uint16 u16_Delta_DC_bre_[2],u16_Delta_DC_aft_[2];
uint16 PD_WIN_AVG[CHAN_NUM][PD_WINDOW];

uint8 FSM_Timer_Cn; /**����״̬������ʱ��0**/
uint8 FSM_Timer_Cn1; /**����״̬������ʱ��1**/
uint8 FSM_Timer_Cn2; /**����״̬������ʱ��2**/
uint8  u8_Splash_cnt;/********����״̬���ý�����************/

tRain_Stastegy_Config const  Rain_Stastegy_Parameter =
{
    	8400, //dc_stage1
        8600, //dc_stage2
        8900, //dc_stage3
        9100, //dc_stage4
        
        100,  //stage_intensity1
        120,  //stage_intensity2
        160,  //stage_intensity3
        250,  //stage_intensity4
        300,  //stage_intensity5
        
        8, // meas_avg_cnt
        
        6,//park position  high_speed meas timer
        12,//park position high_speed meas timer
        6,// park position low_speed meas timer
        20,//park position low_speed meas timer

        {100,80,80,100,100}, // park_timer(u8_Rain_Sensitivity = 4)
        3,  // park_enter_low_th;
        4,  // park_enter_high_th;

        60, // int_delay_timer;
        
        {4,4,3,3,3},  // int_enter_period_cnt;
        5, // int_enter_low_cnt; 
         
        
        {{3,3,3,3},/*u8_cnt_choose*/
		{3,3,3,3},
		{3,4,4,4},
		{3,4,4,4},
		{3,4,4,5}},
        
        {{100,120,100,80},/*u8_Int_Time*/
		{100,120,100,80},
		{90,110,90,70},
		{80,100,80,60},
		{80,80,60,40}},
        
        
        {{35,30,25,20},/*period_enter_low_cnt*/
		{35,30,25,20},
		{30,25,20,17},
		{25,15,17,15},
		{20,15,12,10}},
        
        
        
        
        4,  //period_enter_low_th;
       
        {{40,100,120},/**low_delaytimer**/
        {40,100,120},
        {40,100,120},
        {40,100,120},
        {40,100,120}},
        
        {{25,30,25},/*low_enter_high_cnt*/
        {25,30,25},
        {25,30,28},
        {28,32,20},
        {28,35,32}},
          
        
        {{40,80,100},/*high_delaytimer*/
		{40,80,100},
		{40,80,100},
		{40,80,100},
		{40,80,100}},
    	
    	{{5,5,5},/*high_hold_th*/
		{5,5,5},
		{5,5,5},
		{5,5,5},
		{5,5,5}},
} ;

uint8 Period_Mode_Timer[5]= 
		{
		    160,
		    160,
		    140,
		    125,
		    120		
		};

uint8  u8_MeasureSureTime;
RLS_StopMsureFlg_t RLS_StopMsureFlg;
Rls_Error_t       App_Rls_Error;
bool_t Lin_Diag_Enable;
uint8  u8_Lin_Diag_Enable_Cnt;
uint8 u8_Sigle_Wipe_Cnt;

uint8  u8_Int_Time_now;
uint8  u8_cnt_choose_now;
uint8  u8_cnt_choose_pre;


uint8  u8_Cmd_Execution;
uint16 u16_Pd_Measure_Value;

RLS_Wiper_State_FSM_t  Wiper_State_Fsm;
RLS_Wiper_State_FSM_t  Wiper_State_FsmPre;

uint16 DC_WIN_BUFF[CHAN_NUM][DC_WINDOW];
uint8  u8_RainIntensity_Win[Rain_WINDOW];
uint8  u8_PD_State[CHAN_NUM];
uint16 u16_Dt_PD[CHAN_NUM];
uint16 u16_DC_Comp_Value[CHAN_NUM];
uint8  u8_RainIntensity[CHAN_NUM];
uint8  u8_RainIntensity_Max;
uint8  u8_IntSpeedEnterCnt;
uint8  u8_Rain_Value;
uint8 u8_WiperSpeed_Expert;



void Auto_Wiper_Var_Init(void)
{
	Wiper_State_Fsm =  PARK_MODE;
	Wiper_State_FsmPre = PARK_MODE;
	
	u8_MeasureSureTime = 0;
	RLS_StopMsureFlg = RLS_Continue_Msure;
	
	BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV4;

	BCM_APP_Value.Single_Wipe_flag = FALSE;

	u8_IntSpeedEnterCnt = 0;	
	

	
	Lin_Diag_Enable = FALSE;
	u8_Lin_Diag_Enable_Cnt = 0;
	
}

/*******************************************************
 * FUNCTION NAME : RLS_Rain_Module_Fault_Process()
 *   DESCRIPTION : RLS_Rain_Module_Fault_Process function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Rain_Module_Fault_Process(uint8 chan)
{
	uint8 Chan_Temp = CHAN_A;
	
	if(chan == PDB) Chan_Temp = CHAN_B;
	App_Rls_Error.RS_Error = 0;
	
	
	if (u16_Pd_Measure_Value == 0) 
	{
		if(App_Rls_Error.RS_Error_Cnt[Chan_Temp] >= 100)   
		{
			App_Rls_Error.RS_Error = 1 ;
		}
		else
		{
			App_Rls_Error.RS_Error_Cnt[Chan_Temp]++;
		}
	} 
	else 
	{
		App_Rls_Error.RS_Error_Cnt[Chan_Temp] = 0;
	}
}


/*******************************************************
 * FUNCTION NAME : RLS_Get_Rain_State()
 *   DESCRIPTION : RLS_Get_Rain_State function 
 *         INPUT : PD_chan
 *        OUTPUT : Rain_State  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
uint8 RLS_Get_Rain_State(uint8 PD_chan)
{
    uint8 i; 
    uint16 temp;
    uint8 Chan_Temp  = CHAN_A;
    
    u16_Pd_Measure_Value = RLS_Rain_Get_Measure(PD_chan,Rain_Stastegy_Parameter.meas_avg_cnt,600);
    
    RLS_Rain_Module_Fault_Process(PD_chan);
    
    if(u16_Pd_Measure_Value == 0) return 0;
    
    if(PD_chan == PDB) Chan_Temp  = CHAN_B;
    
    
	Mnrval.IR_[Chan_Temp] = u16_Pd_Measure_Value;
	
   
	for(i = 1;i < DC_WINDOW;i++)
	{ 
		DC_WIN_BUFF[Chan_Temp][i - 1] = DC_WIN_BUFF[Chan_Temp][i];
	}
	DC_WIN_BUFF[Chan_Temp][DC_WINDOW - 1] = Mnrval.DC_bre_[Chan_Temp] ;
        
        
	if( RLS_StopMsureFlg == RLS_Continue_Msure )
	{
		for(i = 1;i < PD_WINDOW;i++)
		{
			 PD_WIN_AVG[Chan_Temp][i - 1] = PD_WIN_AVG[Chan_Temp][i];
		}
		PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] = Mnrval.IR_[Chan_Temp] ;
		if(Mnrval.DC_bre_[Chan_Temp] < Rain_Stastegy_Parameter.dc_stage1)
		{
				temp =  Rain_Stastegy_Parameter.stage_intensity1;
		}
		else if(Mnrval.DC_bre_[Chan_Temp] < Rain_Stastegy_Parameter.dc_stage2)
		{
				temp =   Rain_Stastegy_Parameter.stage_intensity2;
		}
		else if(Mnrval.DC_bre_[Chan_Temp] < Rain_Stastegy_Parameter.dc_stage3)
		{
				temp =   Rain_Stastegy_Parameter.stage_intensity3;
		}
		else if(Mnrval.DC_bre_[Chan_Temp] < Rain_Stastegy_Parameter.dc_stage4)
		{
				temp =   Rain_Stastegy_Parameter.stage_intensity4;
		}
		else
		{
				temp =   Rain_Stastegy_Parameter.stage_intensity5;
		}     
		
		if(BCM_APP_Value.BCM_RainSensitivity == APP_RainSensitivityAPP_LV1)  temp = temp ;
		else if (BCM_APP_Value.BCM_RainSensitivity == APP_RainSensitivityAPP_LV3)  temp = temp + 20 ;
		else if (BCM_APP_Value.BCM_RainSensitivity == APP_RainSensitivityAPP_LV2)  temp = temp + 40 ;
		else                                temp = temp + 80 ;
		   
	} 
	else
	{
		temp = 3000;
	}
   
			
	if(PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] >= PD_WIN_AVG[Chan_Temp][0]) 
	{                           //��ǰֵ����ǰPD_WINDOW-1���ɼ�ֵʱ������������
		u8_PD_State[Chan_Temp] = 0;
		if((PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] - PD_WIN_AVG[Chan_Temp][0]) > DtABS_MAX) 
			PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] = PD_WIN_AVG[Chan_Temp][PD_WINDOW - 2];
	}
	else
	{
		u16_Dt_PD[Chan_Temp] = PD_WIN_AVG[Chan_Temp][0] - PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1];
		if((u16_Dt_PD[Chan_Temp] > DtABS_MAX)||(u16_Dt_PD[Chan_Temp] < temp)) 
		{                  
		  PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] = PD_WIN_AVG[Chan_Temp][PD_WINDOW - 2];
		  u8_PD_State[Chan_Temp] = 0;          
		}
		else 
		{
			u8_PD_State[Chan_Temp] = (u16_Dt_PD[Chan_Temp] / RAIN_DELTA);
		}
	}
	
	
	return (u8_PD_State[Chan_Temp]);
}

/*******************************************************
 * FUNCTION NAME : RLS_Get_Rain_ExpectStage()
 *   DESCRIPTION : RLS_Get_Rain_ExpectStage function 
 *         INPUT : PD_chan
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Get_Rain_RainIntensity(uint8 PD_chan)
{
	uint8  Rain_temp = 0;
	uint8 Chan_Temp = CHAN_A;
	
	
	Rain_temp = RLS_Get_Rain_State(PD_chan);
	if(PD_chan == PDB) Chan_Temp = CHAN_B;
			       
	if(Rain_temp == 0)                            u8_RainIntensity[Chan_Temp]  = 0;
	else if((Rain_temp >= 1)&&(Rain_temp <= 3))   u8_RainIntensity[Chan_Temp]  = 1;
	else if((Rain_temp >= 4)&&(Rain_temp <= 5))   u8_RainIntensity[Chan_Temp]  = 2;
	else if((Rain_temp >= 6)&&(Rain_temp <= 7))   u8_RainIntensity[Chan_Temp]  = 3;
	else if((Rain_temp >= 8)&&(Rain_temp <= 9))   u8_RainIntensity[Chan_Temp]  = 4;
	else if((Rain_temp >= 10)&&(Rain_temp <= 10)) u8_RainIntensity[Chan_Temp]  = 5;
	else if((Rain_temp >= 11)&&(Rain_temp <= 14)) u8_RainIntensity[Chan_Temp]  = 6;
	else if((Rain_temp >= 15)&&(Rain_temp <= 17)) u8_RainIntensity[Chan_Temp]  = 7;
	else if((Rain_temp >= 18)&&(Rain_temp <= 18)) u8_RainIntensity[Chan_Temp]  = 8;
	else if((Rain_temp >= 19)&&(Rain_temp <= 19)) u8_RainIntensity[Chan_Temp]  = 9;
	else if((Rain_temp >= 20)&&(Rain_temp <= 35)) u8_RainIntensity[Chan_Temp]  = 10;
	else                                          u8_RainIntensity[Chan_Temp]  = 11;

}

/*******************************************************
 * FUNCTION NAME : RLS_Get_Rain_ExpectStage()
 *   DESCRIPTION : RLS_Get_Rain_ExpectStage function 
 *         INPUT : PD_chan
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Get_Rain_ExpectStage(uint8 PD_chan)
{
    if((PD_chan & PDB) == PDB) RLS_Get_Rain_RainIntensity(PDB);     
    if((PD_chan & PDA) == PDA) RLS_Get_Rain_RainIntensity(PDA);  
} 

/*******************************************************
 * FUNCTION NAME : RLS_Mask_False_Operation()
 *   DESCRIPTION : RLS_Mask_False_Operation function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Mask_False_Operation(void)
{
    uint8 i,j;
    
    for(j = 0;j < CHAN_NUM; j++)
    {      
        if((u16_Delta_DC_bre_[j] > DC_bef_dtTH) || (u16_Delta_DC_aft_[j] > DC_aft_dtTH))
		{
        	RLS_APP_Value.Rain_Valid = APP_Rain_Invalid;
		}
        else
        {
        	RLS_APP_Value.Rain_Valid = APP_Rain_Valid;
        }
        
        for(i = 0;i < DC_WINDOW;i++)  //  CHAN_A
           {
               if(DC_WIN_BUFF[j][0] > DC_WIN_BUFF[j][i])
               {
                   if((DC_WIN_BUFF[j][0] - DC_WIN_BUFF[j][i]) >  DC_CHANGE_TH)
                   {
                	   RLS_APP_Value.Rain_Valid = APP_Rain_Invalid;
                   }
               }
               else
               {
                   if((DC_WIN_BUFF[j][i] - DC_WIN_BUFF[j][0]) >  DC_CHANGE_TH)
                   {
                	   RLS_APP_Value.Rain_Valid = APP_Rain_Invalid;
                   }
               }
           }
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Invalid_DataProcess()
 *   DESCRIPTION : RLS_Invalid_DataProcess function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Invalid_DataProcess(void)
{
    uint8 i;
    if(RLS_APP_Value.Rain_Valid == APP_Rain_Valid)
    {
        u8_Rain_Value = u8_RainIntensity_Win[0];
        
        for(i = 1;i < Rain_WINDOW  ;i ++) 
        {
            u8_RainIntensity_Win[i - 1] = u8_RainIntensity_Win[i];
        }  

        if(u8_RainIntensity[CHAN_B] > u8_RainIntensity[CHAN_A]) 
            u8_RainIntensity_Win[Rain_WINDOW - 1] = u8_RainIntensity[CHAN_B];
        else  
            u8_RainIntensity_Win[Rain_WINDOW - 1] = u8_RainIntensity[CHAN_A];
        
        if(u8_Cmd_Execution == 0)
        {
        	switch(u8_Rain_Value)
			{
				case 0:
				case 1:
				case 2: 
				case 3:
				case 4:
					u8_WiperSpeed_Expert = u8_Rain_Value;
					break;
				case 5:
				case 6: 
				case 7:
					u8_WiperSpeed_Expert   = 5; 
				break;
				default:
				case 8:
				case 9: 
				case 10:
					u8_WiperSpeed_Expert   = 6;
				break;                    
			}        
			u8_RainIntensity_Max = u8_Rain_Value;
			u8_Cmd_Execution = 1;
        }
        else if(u8_Rain_Value > u8_RainIntensity_Max)
        {
        	switch(u8_Rain_Value)
			{
				case 0:
				case 1:
				case 2: 
				case 3:
				case 4:
					u8_WiperSpeed_Expert = u8_Rain_Value;
					break;
				case 5:
				case 6: 
				case 7:
					u8_WiperSpeed_Expert   = 5; 
				break;
				default:
				case 8:
				case 9: 
				case 10:
					u8_WiperSpeed_Expert   = 6;
				break;                    
			}        
			u8_RainIntensity_Max = u8_Rain_Value;
        }
        else
        {
        	
        }
        
    }
    else
    {
        for(i = 0;i < (PD_WINDOW - 1); i++) 
        {                   
            //�������е���ʷ����ȫ��ˢ�ɵ�ǰ�ɼ�ֵ
            PD_WIN_AVG[CHAN_A][i] = PD_WIN_AVG[CHAN_A][PD_WINDOW - 1];
            PD_WIN_AVG[CHAN_B][i] = PD_WIN_AVG[CHAN_B][PD_WINDOW - 1];
        }

        u8_Cmd_Execution = 0;
        u8_RainIntensity_Max = 0;
        
        for(i = 0;i < Rain_WINDOW ;i++) 
        {
            u8_RainIntensity_Win[i] = 0;
        }
        
        if(u8_WiperSpeed_Expert >= 2)
		{
			u8_WiperSpeed_Expert = u8_WiperSpeed_Expert - 2;      
		}
		else if(u8_WiperSpeed_Expert > 0) //������������Чʱ��������ٶȽ���һ����ֱ������0
		{
			u8_WiperSpeed_Expert--;
		}    
		else
		{
			
		}
                   
    }
}

uint8 RLS_Period_Time_Choose()
{
   uint8 Temp_Cn;
   if( BCM_APP_Value.u16_SPD_Vehicle < 10)
	{
	   u8_cnt_choose_now = Rain_Stastegy_Parameter.u8_cnt_choose[BCM_APP_Value.BCM_RainSensitivity][0];
	   u8_Int_Time_now = Rain_Stastegy_Parameter.u8_Int_Time[BCM_APP_Value.BCM_RainSensitivity][0];
	   Temp_Cn = Rain_Stastegy_Parameter.period_enter_low_cnt[BCM_APP_Value.BCM_RainSensitivity][0];
	}
	else if(BCM_APP_Value.u16_SPD_Vehicle < 50)
	{
	   u8_cnt_choose_now = Rain_Stastegy_Parameter.u8_cnt_choose[BCM_APP_Value.BCM_RainSensitivity][1];
	   u8_Int_Time_now = Rain_Stastegy_Parameter.u8_Int_Time[BCM_APP_Value.BCM_RainSensitivity][1];
	   Temp_Cn = Rain_Stastegy_Parameter.period_enter_low_cnt[BCM_APP_Value.BCM_RainSensitivity][1];
	}
	else if(BCM_APP_Value.u16_SPD_Vehicle < 80)
	{
	   u8_cnt_choose_now = Rain_Stastegy_Parameter.u8_cnt_choose[BCM_APP_Value.BCM_RainSensitivity][20];
	   u8_Int_Time_now = Rain_Stastegy_Parameter.u8_Int_Time[BCM_APP_Value.BCM_RainSensitivity][2];
	   Temp_Cn = Rain_Stastegy_Parameter.period_enter_low_cnt[BCM_APP_Value.BCM_RainSensitivity][2];
	}
	else
	{
	   u8_cnt_choose_now =  Rain_Stastegy_Parameter.u8_cnt_choose[BCM_APP_Value.BCM_RainSensitivity][3];
	   u8_Int_Time_now = Rain_Stastegy_Parameter.u8_Int_Time[BCM_APP_Value.BCM_RainSensitivity][3];
	   Temp_Cn = Rain_Stastegy_Parameter.period_enter_low_cnt[BCM_APP_Value.BCM_RainSensitivity][3];
	}
    return Temp_Cn;
}
void RLS_Rain_State_Mchaine(void)
{
    uint8  i;
    uint8  temp_cnt;
    uint16  temp_timer;
    
    
    switch(Wiper_State_Fsm)
    {
        case PARK_MODE:
        {  	
        	/***parkmode������ˢoff****/
            RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Off;
        	        	
        	/****
        	 * park_mode ����
        	 * 1     bool_Wiper_StatePre_flag       ��parkmode�Լ��õı����Լ���ʼ�����Լ�����
        	 * 2     u8_WiperSpeed_Expert      ����ȫ�ֱ����������ȼ���only read
        	 * 5     FSM_Timer_Cn              ����ʱ�����������������������ģʽ�����㣬�������¿�ʼ��ʱ
        	 * 6     u8_Splash_cnt             �ý�ģʽ����parkģʽ�Լ�����
        	 * *****/
        	if(u8_IntSpeedEnterCnt < 2)/**�������ν�������ģʽ���ӳ�park�ȴ�ʱ��**/
        	{
        		temp_timer = Rain_Stastegy_Parameter.park_timer[BCM_APP_Value.BCM_RainSensitivity];
        	}
        	else
        	{
        		temp_timer = 800;
        	}

        	/***************����Ƿ������ж�***********************************/
        	if(FSM_Timer_Cn >= temp_timer) /******��������ʱ�䵽�������־λ**********/
			{
        	   FSM_Timer_Cn = 0;
			   u8_Splash_cnt = 0;
			   u8_IntSpeedEnterCnt = 0;/*��������ʱ�䵽����������δ�������*/
			}
        	else/******************�������ʱ��δ��**************************/
        	{
        		FSM_Timer_Cn++;/**��μ�ʱ*/
		 
				 if(Wiper_State_FsmPre != PARK_MODE)/*�ϴ�״̬��Ϊpark*/
				 {
					 u8_Splash_cnt = 0;
					 for(i = 0;i < (PD_WINDOW - 1); i++) 
					 {                   
						 //�������е���ʷ����ȫ��ˢ�ɵ�ǰ�ɼ�ֵ
						 PD_WIN_AVG[CHAN_A][i] = Mnrval.IR_[CHAN_A] ;//PD_WIN_AVG[CHAN_A][0];
						 PD_WIN_AVG[CHAN_B][i] = Mnrval.IR_[CHAN_B] ;//PD_WIN_AVG[CHAN_B][0];
					 } 
				 }
				 /**��park�ȴ�ʱ�䣬��ʼ�������**/
				 if((Wiper_State_FsmPre == PARK_MODE)&&(FSM_Timer_Cn > 20))
				 {		
					 if(u8_WiperSpeed_Expert != 0)/*��⵽����*/
					 {
						 FSM_Timer_Cn = 0;/**��⵽���꣬���¿�ʼ��������ģʽ*/
						 Wiper_State_Fsm = INT_SPEED_MODE;/*��⵽����ͽ�����*/
					 }
				   }

			}
        	
			/***************
			 * �ý�ģʽ
			 * ����Pre_Park_Mode�ȴ�ʱ��Ӱ�죬ֱ�ӽ��룬
			 * ���ǵ�һ�ε�λ����
			 * Ҳ���Ǵӵ�һ�ε����ɺ�ʼ������
			 * �����������������������Ƴ�����״̬��ֹͣ����
			 * *********************/
			 if((u8_RainIntensity[CHAN_A] >= Rain_Stastegy_Parameter.park_enter_high_th)
			   &&(u8_RainIntensity[CHAN_B]>= Rain_Stastegy_Parameter.park_enter_high_th)) 
			{
				u8_Splash_cnt++;
				if(u8_Splash_cnt >= 20)
				{
					u8_Splash_cnt = 0;
		
					Wiper_State_Fsm = HIGH_SPEED_MODE;
				}										
			}
			else
		    {
				u8_Splash_cnt = 0;	 
		    }

			 Wiper_State_FsmPre =  PARK_MODE;
        } break;  
        case INT_SPEED_MODE:
        {
        	/**
        	 * 1��   FSM_Timer_Cn     ������ڼ���,�ӱ��mode�����ʱ�������������������������˾͵��������ģʽ����������ģʽ
        	 * 2��  u8_IntSpeedEnterCnt    �ñ���ֻ��park �� ���ģʽ��  ���������ڹ�     ��     ����  �͵������  
        	 * **/
        	
        	
        	/********
        	 * ������ģʽ��ֱ�ӷ��͵��ģʽ
        	 * ******/
        	RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Single;
        	
        	 /*������״̬������ģʽ�������μ�����*/
        	 if(Wiper_State_FsmPre != INT_SPEED_MODE) 
        		 FSM_Timer_Cn = 0;
        	
        	/*********
        	 * ������������500ms���
        	 * �����λ�parkmode
        	 * *************/
        	 FSM_Timer_Cn++;/**/
            if(FSM_Timer_Cn >= 10)
            {
            	FSM_Timer_Cn = 0;/*������һ�¼�����������һЩ*/
            	Wiper_State_Fsm = PARK_MODE;
                u8_IntSpeedEnterCnt++;
            } 
            
            /*******************����Ϊ���ѭ��*****************************/

                          
            
            /****************************��������*********************************************************/
        	if(u8_WiperSpeed_Expert > 4)/*��������ң�wiperSpeed����4 ������ٹ�ˢ*/
			{			
				if(u8_IntSpeedEnterCnt > 2)/**/
				{
					u8_IntSpeedEnterCnt = 0;
					Wiper_State_Fsm = LOW_SPEED_MODE; 
				}
			}
        	/****************************�������ڹ�*********************************************************/
        	else                     /*������Σ��������ڹ�*/
        	{
				if(u8_IntSpeedEnterCnt >= Rain_Stastegy_Parameter.int_enter_period_cnt[BCM_APP_Value.BCM_RainSensitivity])
				{
					Wiper_State_Fsm = PERIOD_SPEED_MODE;
					u8_IntSpeedEnterCnt = 0;
				}
        	}
        	Wiper_State_FsmPre =  INT_SPEED_MODE;
        } break;
        case PERIOD_SPEED_MODE:
        {
        	/***********
        	 * 1��FSM_Timer_Cn      ����ʱ����ֻ�ڱ�ģʽ�����жϣ�����ģʽ��ʼ����
        	 * 2��FSM_Timer_Cn1              ����ʱ��1��������ټ�ʱ��ֻ�ڱ�ģʽ�����жϣ�����ģʽ��ʼ����
        	 * 3��FSM_Timer_Cn1             ����ʱ��2��������ټ�ʱ��ά�����ڹ�    ֻ�ڱ�ģʽ�����жϣ�����ģʽ��ʼ����
        	 * 4��u8_cnt_choose_pre        ���ڹεļ������������������ʱ��ḳ��ֵ
        	 */
        	
        	//������ѡ��ʱ����
        	temp_timer = Period_Mode_Timer[BCM_APP_Value.BCM_RainSensitivity];
        	temp_cnt = RLS_Period_Time_Choose();
			/*������״̬�������ڹ�ģʽ��������ڹμ�����*/
		    if(Wiper_State_FsmPre != PERIOD_SPEED_MODE)
		    {
		    	FSM_Timer_Cn = 0;
		    	FSM_Timer_Cn1 = 0;
		    	FSM_Timer_Cn2 = 0;
		    	u8_Splash_cnt = 0;
		    	u8_cnt_choose_pre = u8_cnt_choose_now;
		    }
		    FSM_Timer_Cn++;/********������ʱ����ʼ����***********/
		    
		    /*********************����Ϊ���ڹ�************************************/
		
			if((FSM_Timer_Cn >= 0) && (FSM_Timer_Cn < (u8_Int_Time_now - 10)))
			{
				RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Off;
			}
			else if((FSM_Timer_Cn >= (u8_Int_Time_now - 10)) && (FSM_Timer_Cn <= u8_Int_Time_now))
			{
				 RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Single;
			}
			else
			{
				FSM_Timer_Cn = 0;/***********���ڵ��������***************/
				
				u8_cnt_choose_pre--;
				/*****�����ڹεĽ�β�ж����ڹεĴ����Ƿ�������������˻ص�parkmode********/
				if(u8_cnt_choose_pre == 0)
				{
					Wiper_State_Fsm = PARK_MODE;
				}
			}
			
			/****************���ڹε������������������ӳ����ڹε�ʱ��*****************************/
			if(u8_WiperSpeed_Expert > 3)
			{
				if(BCM_APP_Value.u16_SPD_Vehicle >= 5)
				{
					u8_cnt_choose_pre = u8_cnt_choose_now;
				}
			}

   	
        	/*************************���ڹν����ٹ�*******************************/
        	if(u8_WiperSpeed_Expert >= Rain_Stastegy_Parameter.period_enter_low_th)
            {
        		FSM_Timer_Cn1++;/***********�˴��������������ټ�ʱ********/
        		FSM_Timer_Cn2 = 0;
                if(FSM_Timer_Cn1 >= temp_cnt)
                {
                	FSM_Timer_Cn1 = 0;                    
					Wiper_State_Fsm = LOW_SPEED_MODE;					
                }
            }
        	/***********������ټ�ʱ��ά�����ڹ�****************/
        	else
        	{
        		FSM_Timer_Cn2++;
        		if(FSM_Timer_Cn2 >= temp_timer)
        		{
        			FSM_Timer_Cn2 = 0;
        			FSM_Timer_Cn1 = 0;
        		}
        	}
        	
        	/*****************���ڹ�ˢ�ڵĴ���ģʽ****************************/
        	if((u8_RainIntensity[CHAN_A] >= Rain_Stastegy_Parameter.park_enter_high_th)
        			&&(u8_RainIntensity[CHAN_B]>= Rain_Stastegy_Parameter.park_enter_high_th)) 
			{
				if(u8_Splash_cnt >= 40)
				{
					u8_Splash_cnt = 0;
					Wiper_State_Fsm = HIGH_SPEED_MODE;
				}
				else
				{
					u8_Splash_cnt++;
				}								
			} 
        	Wiper_State_FsmPre =  PERIOD_SPEED_MODE;
        } break;
        
        case LOW_SPEED_MODE:
        {        	
         /***********
    	 * 1��FSM_Timer_Cn              ����ģʽ����ʱ��������ģʽ��ʼ����
    	 * 2��FSM_Timer_Cn1                                    �ڴ���������ģʽ�˳���ʱ����ģʽ��ʼ����
    	 * 3��FSM_Timer_Cn2                                    �ٴ����������hold����������ģʽ��ʼ����
    	 */
        	
        	
        	/**************���Σ���������һֱ��������******************/
        	RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Low;
        	
        	/*������״̬��������ģʽ��������μ�����*/
			if(Wiper_State_FsmPre != LOW_SPEED_MODE)
			{
				FSM_Timer_Cn = 0;
				FSM_Timer_Cn1 = 0;
				FSM_Timer_Cn2 = 0;
			}


			FSM_Timer_Cn++;/*********ģʽ����ʱ��*************/
            if(FSM_Timer_Cn >= 200)
			{
            	FSM_Timer_Cn = 0;/***********ģʽ��ʱ������*******************/
            	FSM_Timer_Cn2 = 0;
			}

            /**************����ֻ����ֵ����*******************************/
            

			if(BCM_APP_Value.u16_SPD_Vehicle < 5)
			{
				temp_timer = Rain_Stastegy_Parameter.low_delaytimer[BCM_APP_Value.BCM_RainSensitivity][0];//40
				 temp_cnt = Rain_Stastegy_Parameter.low_enter_high_cnt[BCM_APP_Value.BCM_RainSensitivity][0];
			}
			else if(BCM_APP_Value.u16_SPD_Vehicle < 80)
			{
				temp_timer = Rain_Stastegy_Parameter.low_delaytimer[BCM_APP_Value.BCM_RainSensitivity][1];
				 temp_cnt = Rain_Stastegy_Parameter.low_enter_high_cnt[BCM_APP_Value.BCM_RainSensitivity][1];
			}
			else 
			{
				temp_timer = Rain_Stastegy_Parameter.low_delaytimer[BCM_APP_Value.BCM_RainSensitivity][2];
				 temp_cnt = Rain_Stastegy_Parameter.low_enter_high_cnt[BCM_APP_Value.BCM_RainSensitivity][2];
			}  
            
            if(u8_WiperSpeed_Expert < 4)/*********������ƫСʱ���ӵ����˳������ڹ�*************/
            {        
            	FSM_Timer_Cn1++;
                if(FSM_Timer_Cn1 >= temp_timer)
                {
                	FSM_Timer_Cn1 = 0;
                    Wiper_State_Fsm =  PERIOD_SPEED_MODE;
                }                                   
            }
            /**************����ƫ�󣬽�����******************/
            else
            {   
            	FSM_Timer_Cn2++;
                if(FSM_Timer_Cn2 >= temp_cnt)   
                {                
                	FSM_Timer_Cn2 = 0;
                    Wiper_State_Fsm =  HIGH_SPEED_MODE;               
                } 
            }
            
            if(u8_WiperSpeed_Expert >= 2)
            {
            	FSM_Timer_Cn1 = 0;/****������ƫ��ʱ������˳����ټ���*******/
            }
            Wiper_State_FsmPre =  LOW_SPEED_MODE;
        } break;
        
        case HIGH_SPEED_MODE:
        {
        	/*********
        	 * 1,  FSM_Timer_Cn ģʽ������ʱ������ģʽ��ʼ����
        	 * ************/
        	/***************���ģʽ�£����뷢�Ϳ��*******************************/
            RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_High;
            
            
            /*������״̬������ģʽ�������μ�����*/
			if(Wiper_State_FsmPre != HIGH_SPEED_MODE)
			{
				FSM_Timer_Cn = 0;

			}
            

			if(BCM_APP_Value.u16_SPD_Vehicle < 5)
			{
				temp_timer = Rain_Stastegy_Parameter.high_delaytimer[BCM_APP_Value.BCM_RainSensitivity][0];
				 temp_cnt = Rain_Stastegy_Parameter.high_hold_th[BCM_APP_Value.BCM_RainSensitivity][0];
			}
			else if(BCM_APP_Value.u16_SPD_Vehicle < 80)
			{
				temp_timer = Rain_Stastegy_Parameter.high_delaytimer[BCM_APP_Value.BCM_RainSensitivity][1];
				 temp_cnt = Rain_Stastegy_Parameter.high_hold_th[BCM_APP_Value.BCM_RainSensitivity][1];
			}
			else 
			{
				temp_timer = Rain_Stastegy_Parameter.high_delaytimer[BCM_APP_Value.BCM_RainSensitivity][2];
				 temp_cnt = Rain_Stastegy_Parameter.high_hold_th[BCM_APP_Value.BCM_RainSensitivity][2];    
			}  
			
            FSM_Timer_Cn++;
            
            if(FSM_Timer_Cn >= temp_timer)
            {             
            	Wiper_State_Fsm = LOW_SPEED_MODE;
            	FSM_Timer_Cn = 0;                     
            }
            else
            {
                if(u8_WiperSpeed_Expert >= temp_cnt) 
                {
                	FSM_Timer_Cn = 0;
                }
            }
            Wiper_State_FsmPre =  HIGH_SPEED_MODE;
        } break;
        
        default:  
        {
        	Wiper_State_Fsm = PARK_MODE;
        	Wiper_State_FsmPre = PARK_MODE;
        }break;
    }
}
/*******************************************************
 * FUNCTION NAME : RLS_Wipe_Park_Process()
 *   DESCRIPTION : RLS_Wipe_Park_Process function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Wipe_Park_Process(void)
{
    if(BCM_APP_Value.BCM_WiperPosition == APP_WiperPosition_Not_Parked)   //0Ϊpark��
    {
        u8_MeasureSureTime++;
        if(Wiper_State_Fsm == HIGH_SPEED_MODE)
        {            
            if((u8_MeasureSureTime > Rain_Stastegy_Parameter.park_high_meas_timer1))//||((u8_MeasureSureTime >= Rain_Stastegy_Parameter[0].park_high_meas_timer2)))//&&(u8_MeasureSureTime <= 20)))
            {
                RLS_StopMsureFlg = RLS_Stop_Msure;
            }
        }
        else
        {
            if((u8_MeasureSureTime > Rain_Stastegy_Parameter.park_low_meas_timer1))//||((u8_MeasureSureTime >= Rain_Stastegy_Parameter[0].park_low_meas_timer2)))//&&(u8_MeasureSureTime <= 30)))
            {
                RLS_StopMsureFlg = RLS_Stop_Msure;
            }
        }
    }
    else
    {
        RLS_StopMsureFlg = RLS_Continue_Msure;
        u8_MeasureSureTime = 0;
    }
}

/*******************************************************
 * FUNCTION NAME : RLS_Auto_Rain_Task()
 *   DESCRIPTION : RLS_Auto_Rain_Task function 
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/                      
void RLS_Auto_Rain_Task(void)
{
    RLS_Get_Rain_ExpectStage(PDB|PDA);
    RLS_Mask_False_Operation();
    RLS_Invalid_DataProcess(); 
    RLS_Rain_State_Mchaine();   
}

/*******************************************************
 * FUNCTION NAME : RLS_Single_Wipe_Function()
 *   DESCRIPTION : RLS_Single_Wipe_Function  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Single_Wipe_Function(void)
{
	uint8 i;
	if((BCM_APP_Value.Single_Wipe_flag == TRUE)&&
			((Wiper_State_Fsm == PARK_MODE)||(Wiper_State_Fsm == INT_SPEED_MODE))
			&&(Lin_Diag_Enable == TRUE)
			&&(BCM_APP_Value.BCM_WiperPosition == APP_WiperPosition_Parked ))
	{
		RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Single;
		u8_IntSpeedEnterCnt = 0;
		u8_Sigle_Wipe_Cnt++;
		
		if(u8_Sigle_Wipe_Cnt > 10)
		{
			BCM_APP_Value.Single_Wipe_flag = FALSE;
			RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Off;
		}
		
		for(i = 0;i < Rain_WINDOW ;i ++) 
		{
			u8_RainIntensity_Win[i] = 0;
		}
		Wiper_State_FsmPre = INT_SPEED_MODE;
		Wiper_State_Fsm = PARK_MODE;
	}
	
	else
	{
		u8_Sigle_Wipe_Cnt = 0; 
	} 

}
/*******************************************************
 * FUNCTION NAME : RLS_Lin_Diag_Fucntion()
 *   DESCRIPTION : RLS_Lin_Diag_Fucntion  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void RLS_Lin_Diag_Fucntion(void)
{
    if(u8_Lin_Diag_Enable_Cnt >= 15) //1500ms
    {
        Lin_Diag_Enable = TRUE;
    }
    else
    {
        Lin_Diag_Enable = FALSE;
        u8_Lin_Diag_Enable_Cnt++;
    }
}

