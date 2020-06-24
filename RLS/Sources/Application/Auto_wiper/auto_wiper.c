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
#include "config_parameter.h"

extern Main_Fsm_t             RLS_RunMode;
//this frame is for APP 
extern RLS_APP_Value_t     RLS_APP_Value;
extern BCM_APP_Value_t     BCM_APP_Value;

extern RLS_APP_Value_t     RLS_APP_Value;
extern MLX75308_Frame_t       MLX75308_RxFrame;
extern MLX75308_Mnrval_t      Mnrval;

extern uint16 u16_Delta_DC_bre_[2],u16_Delta_DC_aft_[2];
uint16 PD_WIN_AVG[CHAN_NUM][PD_WINDOW];

uint16 FSM_Timer_Cn; /**雨量状态机主计时器0**/
uint8 FSM_Timer_Cn1; /**雨量状态机主计时器1**/
uint8 FSM_Timer_Cn2; /**雨量状态机主计时器2**/

uint8 u8_Dt_Rain_Cnt[2];

tRain_Stastegy_Config const  Rain_Stastegy_Parameter =
{
    	8400, //dc_stage1
        8600, //dc_stage2
        8900, //dc_stage3
        9100, //dc_stage4
        
        40,  //stage_intensity1
        80,  //stage_intensity2
        120,  //stage_intensity3
        200,  //stage_intensity4
        300,  //stage_intensity5
        
        8, // meas_avg_cnt
        
        20,//park position  high_speed meas timer
        20,//park position high_speed meas timer
        30,// park position low_speed meas timer
        30,//park position low_speed meas timer

        {100,80,100,100,100}, // park_timer(u8_Rain_Sensitivity = 4)
        4,  // park_enter_low_th;
        4,  // park_enter_high_th;

        60, // int_delay_timer;
        
        {4,
		4,
		3,
		3,
		3},  // int_enter_period_cnt;
        5, // int_enter_low_cnt; 
         
        
        {{3,3,3,3},/*u8_cnt_choose*/
		{3,3,3,3},
		{3,4,4,4},
		{3,4,4,4},
		{3,4,4,5}},
        
        {{80,120,100,80},/*u8_Int_Time*/
		{80,120,100,80},
		{80,100,90,70},
		{60,80,80,60},
		{60,60,60,40}},
        
        
        {{30,28,26,24},/*period_enter_low_cnt*/
		{35,32,30,28},
		{32,30,28,26},
		{30,28,26,24},
		{26,24,22,20}},
        
        4,  //period_enter_low_th;
       
        {{40,100,140},/**low_delaytimer**/
        {40,100,140},
        {40,100,140},
        {40,100,140},
        {40,100,140}},
        
        {{58,63,58},/*low_enter_high_cnt*/
        {65,70,65},
        {60,65,60},
        {58,63,58},
        {55,60,55}},
          
        
        {{40,80,100},/*high_delaytimer*/
		{40,80,100},
		{40,80,100},
		{40,80,100},
		{40,80,100}},
    	
    	{{5,4,3},/*high_hold_th*/
		{5,4,3},
		{5,4,3},
		{5,4,3},
		{5,4,3}},
} ;

uint8 Period_Mode_Timer[5]= 
		{
		    160,
		    160,
		    140,
		    125,
		    120		
		};

RLS_PARK_MODE_FSM_t PARK_MODE_FSM;
uint8  u8_MeasureSureTime;
RLS_StopMsureFlg_t RLS_StopMsureFlg;
Rls_Error_t       App_Rls_Error;
bool_t Lin_Diag_Enable;
uint8  u8_Lin_Diag_Enable_Cnt;

uint8  u8_Int_Time_now;
uint8  u8_cnt_choose_now;
uint8  u8_cnt_choose_pre;


uint8  u8_Cmd_Execution;

RLS_Wiper_State_FSM_t  Wiper_State_Fsm;
RLS_Wiper_State_FSM_t  Wiper_State_FsmPre;

uint16 DC_WIN_BUFF[CHAN_NUM][DC_WINDOW];
uint8  u8_RainIntensity_Win[Rain_WINDOW];
uint16 u16_DC_Comp_Value[CHAN_NUM];
uint8  u8_RainIntensity[CHAN_NUM];
uint8  u8_RainIntensity_Max;
uint8  u8_IntSpeedEnterCnt;
uint8  u8_Rain_Value;
uint8 u8_WiperSpeed_Expert;



void Auto_Wiper_Var_Init(void)
{
	PARK_MODE_FSM = PARK_MODE_No_Rain;
	Wiper_State_Fsm =  PARK_MODE;
	Wiper_State_FsmPre = PARK_MODE;
	u8_MeasureSureTime = 0;
	RLS_StopMsureFlg = RLS_Continue_Msure;
	BCM_APP_Value.BCM_RainSensitivity = APP_RainSensitivityAPP_LV4;
    u8_IntSpeedEnterCnt = 0;	
	Lin_Diag_Enable = FALSE;
	u8_Lin_Diag_Enable_Cnt = 0;
	BCM_APP_Value.Single_Wipe_flag = FALSE;
	
}

/*******************************************************
 * FUNCTION NAME : RLS_Rain_Module_Fault_Process()
 *   DESCRIPTION : RLS_Rain_Module_Fault_Process function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
bool_t RLS_Rain_Module_Fault_Process(uint8 chan, uint8 PD_Temp)
{	
	App_Rls_Error.RS_Error = 0;	
	
	if (PD_Temp == 0) 
	{
		if(App_Rls_Error.RS_Error_Cnt[chan] >= 100)   
		{
			App_Rls_Error.RS_Error = 1 ;
		}
		else
		{
			App_Rls_Error.RS_Error_Cnt[chan]++;
		}
		return TRUE;
	} 
	else 
	{
		App_Rls_Error.RS_Error_Cnt[chan] = 0;
	}
	
	return FALSE;
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
    uint16 u16_Dt_PD;
    uint8  u8_PD_State = 0;
    uint8 Chan_Temp  = CHAN_A;
    uint16 Pd_Temp;

    
    Pd_Temp = RLS_Rain_Get_Measure(PD_chan,Rain_Stastegy_Parameter.meas_avg_cnt,600);
    
    if(PD_chan == PDB) Chan_Temp  = CHAN_B;
    if(TRUE == RLS_Rain_Module_Fault_Process(Chan_Temp,Pd_Temp))  return 0;

	Mnrval.IR_[Chan_Temp] = Pd_Temp;
	
   
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
	{                           //当前值大于前PD_WINDOW-1个采集值时，返回无雨量
		if((PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] - PD_WIN_AVG[Chan_Temp][0]) > DtABS_MAX) 
			PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] = PD_WIN_AVG[Chan_Temp][PD_WINDOW - 2];
	}
	else
	{
		u16_Dt_PD = PD_WIN_AVG[Chan_Temp][0] - PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1];
		if(u16_Dt_PD > DtABS_MAX) 
		{                  
		  PD_WIN_AVG[Chan_Temp][PD_WINDOW - 1] = PD_WIN_AVG[Chan_Temp][PD_WINDOW - 2];         
		}
		else 
		{
			if(Wiper_State_Fsm == PARK_MODE)
			{
				if(u16_Dt_PD >=  temp)
				{
					u8_Dt_Rain_Cnt[Chan_Temp]++;
					if(u8_Dt_Rain_Cnt[Chan_Temp] >= RAIN_ACTIV_CNT)
					{
						u8_Dt_Rain_Cnt[Chan_Temp] = 0;
						u8_PD_State = 1;
					}
				}
				else
				{
					u8_Dt_Rain_Cnt[Chan_Temp] = 0;
				}
			}
			else
			{
				u8_PD_State = (uint8)(u16_Dt_PD / RAIN_DELTA);
			}
		}
	}
	
	
	return (u8_PD_State);
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
void RLS_Get_Rain_ExpectStage()
{
    RLS_Get_Rain_RainIntensity(PDB);     
    RLS_Get_Rain_RainIntensity(PDA); 
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
    uint16 temp_th1,temp_th2,temp_th3;
    
    
    if(u8_IntSpeedEnterCnt > 2)
	{
		temp_th1 =  DC_bef_dtTH_RAIN;
		temp_th2 =  DC_aft_dtTH_RAIN;
		temp_th3 =  DC_CHANGE_TH_RAIN;
	}
	else
	{
		temp_th1 =  DC_bef_dtTH;
		temp_th2 =  DC_aft_dtTH;
		temp_th3 =  DC_CHANGE_TH;
	}
    
    for(j = 0;j < CHAN_NUM; j++)
    {      
        if((u16_Delta_DC_bre_[j] > temp_th1) || (u16_Delta_DC_aft_[j] > temp_th2))
		{
        	RLS_APP_Value.Rain_Valid = APP_Rain_Invalid;
		}
        else
        {
        	RLS_APP_Value.Rain_Valid = APP_Rain_Valid;
        }
        
        for(i = 0;i < DC_WINDOW;i++)  
	   {
		   if(DC_WIN_BUFF[j][0] > DC_WIN_BUFF[j][i])
		   {
			   if((DC_WIN_BUFF[j][0] - DC_WIN_BUFF[j][i]) >  temp_th3)
			   {
				   RLS_APP_Value.Rain_Valid = APP_Rain_Invalid;
			   }
		   }
		   else
		   {
			   if((DC_WIN_BUFF[j][i] - DC_WIN_BUFF[j][0]) >  temp_th3)
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
            //将窗口中的历史数据全部刷成当前采集值
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
		else if(u8_WiperSpeed_Expert > 0) //当雨量数据无效时，将雨刮速度降低一级，直至降到0
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
        	/***parkmode得让雨刷off****/
            RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Off;
        	        	
        	/****
        	 * park_mode 变量
        	 * 1     bool_Wiper_StatePre_flag       在parkmode自己用的变量自己初始化，自己清理
        	 * 2     u8_WiperSpeed_Expert      输入全局变量，雨量等级，only read
        	 * 3     FSM_Timer_Cn              主计时器，点刮连续计数器，有雨模式下清零，非有雨下开始计时
        	 * *****/
        	
        	if(Wiper_State_FsmPre != PARK_MODE)/*上次状态不为park*/
			{
				FSM_Timer_Cn = 0;
				for(i = 0;i < (PD_WINDOW - 1); i++) 
				{                   
					 //将窗口中的历史数据全部刷成当前采集值
					PD_WIN_AVG[CHAN_A][i] = Mnrval.IR_[CHAN_A] ;//PD_WIN_AVG[CHAN_A][0];
					PD_WIN_AVG[CHAN_B][i] = Mnrval.IR_[CHAN_B] ;//PD_WIN_AVG[CHAN_B][0];
				} 
				PARK_MODE_FSM =  PARK_MODE_Rain_Wait;
			}
        	
        	/*
        	 * 按照时间把parkmode分为三个状态机
        	 * 1、正常无雨状态：  正常检测，没有任何计时
        	 * 2、有雨点刮等待、等待1s
        	 * 3、有雨状态是否连续计时
        	 * */
			switch(PARK_MODE_FSM)
			{
			    default:
				case PARK_MODE_No_Rain:/*无雨状态正常检测*/
				{
					if(u8_WiperSpeed_Expert != 0)/*检测到有雨*/
					{
						Wiper_State_Fsm = INT_SPEED_MODE;/*检测到有雨就进入点刮*/
						u8_IntSpeedEnterCnt++;
					}
					else 
					{
						if(BCM_APP_Value.Single_Wipe_flag == TRUE)/*未检测到有雨，但是有升档提醒*/
						{
							Wiper_State_Fsm = INT_SPEED_MODE;
						}	
					}
				}break;
				case PARK_MODE_Rain_Wait:/*有雨点刮park等待1s*/
				{
					FSM_Timer_Cn++;
					if(FSM_Timer_Cn >= 20) 
					{
						for(i = 0;i < Rain_WINDOW ;i++) 
						{
						  u8_RainIntensity_Win[i] = 0;
						}
						PARK_MODE_FSM = PARK_MODE_Raining;
					}
				}break;
				case PARK_MODE_Raining:/*有雨模式检测*/
				{
					/***************点刮是否连续判断***********************************/
					 FSM_Timer_Cn++;/**点刮计时*/
					if(FSM_Timer_Cn >= 800) /******有雨连续时间到，清除标志位**********/
					{
					   u8_IntSpeedEnterCnt = 0;/*有雨连续时间到，清除进入点刮次数计数*/
					   PARK_MODE_FSM = PARK_MODE_No_Rain;/*退出有雨检测模式*/
					   RLS_APP_Value.vehicle_start_Flag = FALSE; //关闭启停标志
					}
					else
					{
						if(u8_WiperSpeed_Expert != 0)/*检测到有雨或者升档提醒*/
						{
						   Wiper_State_Fsm = INT_SPEED_MODE;/*检测到有雨就进入点刮*/
						   u8_IntSpeedEnterCnt++;
						}	
						else
						{
							if(BCM_APP_Value.Single_Wipe_flag == TRUE)/*未检测到有雨，但是有点刮提醒*/
							{
								Wiper_State_Fsm = INT_SPEED_MODE;
							}
						}
					}
				}break;
			}
			
			Wiper_State_FsmPre =  PARK_MODE;
        } break;  
        
        case INT_SPEED_MODE:
        {
        	/**
        	 * 1、   FSM_Timer_Cn     点刮周期计数,从别的mode进入的时候清除计数器，当点刮周期满了就得跳出点刮模式，进入其他模式
        	 * 2、  u8_IntSpeedEnterCnt    该变量只在park 和 点刮模式用  当进入周期刮     或     慢刮  就得清除掉  
        	 * **/
        	
        	
        	/********
        	 * 进入点刮模式就直接发送点刮模式
        	 * ******/
        	RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Single;
        	
        	 /*从其他状态进入点刮模式就清除点刮计数器*/
        	 if(Wiper_State_FsmPre != INT_SPEED_MODE) 
        	 {
        		 FSM_Timer_Cn = 0;
        	 }
        	
        	/*********
        	 * 进入点刮连续发500ms点刮
        	 * 发完点刮回parkmode
        	 * *************/
        	 FSM_Timer_Cn++;/**/
            if(FSM_Timer_Cn >= 10)/*必须点刮完才能进入下一模式*/
            {
            	Wiper_State_Fsm = PARK_MODE;

                /****************************有雨模式进入周期刮*********************************************************/
                if(u8_IntSpeedEnterCnt >= 3)
    			{
    				Wiper_State_Fsm = PERIOD_SPEED_MODE;
    				u8_IntSpeedEnterCnt = 2;
    			}
                else
                {
                	Wiper_State_Fsm = PARK_MODE;
                }
            } 
            
            /*******************以上为点刮循环*****************************/
        	
        	Wiper_State_FsmPre =  INT_SPEED_MODE;
        } break;
        case PERIOD_SPEED_MODE:
        {
        	/***********
        	 * 1、FSM_Timer_Cn      主计时器，只在本模式下做判断，进入模式开始计数
        	 * 2、FSM_Timer_Cn1              主计时器1，进入低速计时，只在本模式下做判断，进入模式开始计数
        	 * 3、FSM_Timer_Cn1             主计时器2，清除低速计时，维持周期刮    只在本模式下做判断，进入模式开始计数
        	 * 4、u8_cnt_choose_pre        周期刮的计数器，在雨量过大的时候会赋初值
        	 */
        	
        	//灵敏度选择时间间隔
        	temp_timer = Period_Mode_Timer[BCM_APP_Value.BCM_RainSensitivity];
        	temp_cnt = RLS_Period_Time_Choose();
			/*从其他状态进入周期刮模式就清除周期刮计数器*/
		    if(Wiper_State_FsmPre != PERIOD_SPEED_MODE)
		    {
		    	FSM_Timer_Cn = 0;
		    	FSM_Timer_Cn1 = 0;
		    	FSM_Timer_Cn2 = 0;
		    	u8_cnt_choose_pre = u8_cnt_choose_now;
		    }
		    
		    
		    FSM_Timer_Cn++;/********主机计时器开始计数***********/
		    
		    /*********************以下为周期刮************************************/
		
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
				FSM_Timer_Cn = 0;/***********周期到清除计数***************/
				
				u8_cnt_choose_pre--;
				/*****在周期刮的结尾判断周期刮的次数是否结束，结束则退回到parkmode********/
				if(u8_cnt_choose_pre == 0)
				{
					Wiper_State_Fsm = PARK_MODE;
					RLS_APP_Value.vehicle_start_Flag = TRUE;//开启启停雨刮标志
				}
			}
			
			/****************周期刮的情况下遇到以下情况延长周期刮的时间*****************************/
			if(u8_WiperSpeed_Expert > 3)
			{
				if(BCM_APP_Value.u16_SPD_Vehicle >= 5)
				{
					u8_cnt_choose_pre = u8_cnt_choose_now;
				}
			}

   	
        	/*************************周期刮进低速刮*******************************/
        	if(u8_WiperSpeed_Expert >= Rain_Stastegy_Parameter.period_enter_low_th)
            {
        		FSM_Timer_Cn1++;/***********此处用来计数来低速计时********/
        		FSM_Timer_Cn2 = 0;
                if(FSM_Timer_Cn1 >= temp_cnt)
                {                   
					Wiper_State_Fsm = LOW_SPEED_MODE;					
                }
            }
        	/***********清除低速计时，维持周期刮****************/
        	else
        	{
        		FSM_Timer_Cn2++;
        		if(FSM_Timer_Cn2 >= temp_timer)
        		{
        			FSM_Timer_Cn2 = 0;
        			FSM_Timer_Cn1 = 0;
        		}
        	}
        	
        	Wiper_State_FsmPre =  PERIOD_SPEED_MODE;
        } break;
        
        case LOW_SPEED_MODE:
        {        	
         /***********
    	 * 1、FSM_Timer_Cn              低速模式主计时器，进入模式开始计数
    	 * 2、FSM_Timer_Cn1                                    在此用作低速模式退出计时进入模式开始计数
    	 * 3、FSM_Timer_Cn2                                    再次用作进快刮hold计数，进入模式开始计数
    	 */
        	
        	
        	/**************慢刮，进入慢刮一直发送慢刮******************/
        	RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Low;
        	
        	/*从其他状态进入慢刮模式就清除慢刮计数器*/
			if(Wiper_State_FsmPre != LOW_SPEED_MODE)
			{
				FSM_Timer_Cn = 0;
				FSM_Timer_Cn1 = 0;
				FSM_Timer_Cn2 = 0;
			}


			if(BCM_APP_Value.u16_SPD_Vehicle == 0)
			{
				i = 140;
			}
			else if(BCM_APP_Value.u16_SPD_Vehicle < 30)
			{
				i = 100;
			}
			else if(BCM_APP_Value.u16_SPD_Vehicle < 60)
			{
				i = 140;
			}
			else if(BCM_APP_Value.u16_SPD_Vehicle < 80)
			{
				i = 160;
			}
			else
			{
				i = 200;
			}
			
			FSM_Timer_Cn++;/*********模式主计时器*************/
            if(FSM_Timer_Cn >= i)
			{
            	FSM_Timer_Cn = 0;/***********模式计时器清零*******************/
            	FSM_Timer_Cn2 = 0;
			}

            /**************本处只做赋值处理*******************************/
            

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
            
            if(u8_WiperSpeed_Expert < 2)/*********当雨量偏小时，从低速退出到周期刮*************/
            {        
            	FSM_Timer_Cn1++;
                if(FSM_Timer_Cn1 >= temp_timer)
                {
                    Wiper_State_Fsm =  PERIOD_SPEED_MODE;
                }                                   
            }
            else
            {
            	FSM_Timer_Cn1 = 0;/****当雨量偏大时，清除退出低速计数*******/
            	if((u8_WiperSpeed_Expert >= 4))/**************雨量偏大，进入快刮******************/
            	{
            		FSM_Timer_Cn2++;
					if(FSM_Timer_Cn2 >= temp_cnt)   
					{        
						Wiper_State_Fsm =  HIGH_SPEED_MODE;               
					} 
            	}
            }
            Wiper_State_FsmPre =  LOW_SPEED_MODE;
        } break;
        
        case HIGH_SPEED_MODE:
        {
        	/*********
        	 * 1,  FSM_Timer_Cn 模式下主计时器，进模式开始计数
        	 * ************/
        	/***************快刮模式下，必须发送快刮*******************************/
            RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_High;
            
            
            /*从其他状态进入快刮模式就清除快刮计数器*/
			if(Wiper_State_FsmPre != HIGH_SPEED_MODE)
			{
				FSM_Timer_Cn = 0;

			}
            
            /*赋值部分*/
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
			
			/*
			 * 逻辑处理部分
			 * */
			
			if(u8_WiperSpeed_Expert >= temp_cnt) /*雨量偏大就停止退出快刮计时*/
			{
				FSM_Timer_Cn = 0;
			}
			else
			{
				/*退出快刮计时*/
				FSM_Timer_Cn++;
	            if(FSM_Timer_Cn >= temp_timer)
	            {             
	            	Wiper_State_Fsm = LOW_SPEED_MODE;                  
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
    if(BCM_APP_Value.BCM_WiperPosition == APP_WiperPosition_Not_Parked)   //0为park点
    {
        u8_MeasureSureTime++;
        if(Wiper_State_Fsm == HIGH_SPEED_MODE)
        {            
            if(u8_MeasureSureTime > Rain_Stastegy_Parameter.park_high_meas_timer1)
            {
                RLS_StopMsureFlg = RLS_Stop_Msure;
            }
        }
        else
        {
            if(u8_MeasureSureTime > Rain_Stastegy_Parameter.park_low_meas_timer1)
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
    RLS_Get_Rain_ExpectStage();
    RLS_Mask_False_Operation();
    RLS_Invalid_DataProcess(); 
    RLS_Rain_State_Mchaine();   
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

