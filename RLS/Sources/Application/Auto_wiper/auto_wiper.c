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

uint8 FSM_Timer_Cn; /**雨量状态机主计时器0**/
uint8 FSM_Timer_Cn1; /**雨量状态机主计时器1**/
uint8 FSM_Timer_Cn2; /**雨量状态机主计时器2**/
uint8  u8_Splash_cnt;/********雨量状态机泼溅计数************/

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
	{                           //当前值大于前PD_WINDOW-1个采集值时，返回无雨量
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
        	 * 5     FSM_Timer_Cn              主计时器，点刮连续计数器，有雨模式下清零，非有雨下开始计时
        	 * 6     u8_Splash_cnt             泼溅模式，在park模式自己清理
        	 * *****/
        	if(u8_IntSpeedEnterCnt < 2)/**连续两次进入有雨模式，延长park等待时间**/
        	{
        		temp_timer = Rain_Stastegy_Parameter.park_timer[BCM_APP_Value.BCM_RainSensitivity];
        	}
        	else
        	{
        		temp_timer = 800;
        	}

        	/***************点刮是否连续判断***********************************/
        	if(FSM_Timer_Cn >= temp_timer) /******有雨连续时间到，清除标志位**********/
			{
        	   FSM_Timer_Cn = 0;
			   u8_Splash_cnt = 0;
			   u8_IntSpeedEnterCnt = 0;/*有雨连续时间到，清除进入点刮次数计数*/
			}
        	else/******************点刮连续时间未到**************************/
        	{
        		FSM_Timer_Cn++;/**点刮计时*/
		 
				 if(Wiper_State_FsmPre != PARK_MODE)/*上次状态不为park*/
				 {
					 u8_Splash_cnt = 0;
					 for(i = 0;i < (PD_WINDOW - 1); i++) 
					 {                   
						 //将窗口中的历史数据全部刷成当前采集值
						 PD_WIN_AVG[CHAN_A][i] = Mnrval.IR_[CHAN_A] ;//PD_WIN_AVG[CHAN_A][0];
						 PD_WIN_AVG[CHAN_B][i] = Mnrval.IR_[CHAN_B] ;//PD_WIN_AVG[CHAN_B][0];
					 } 
				 }
				 /**非park等待时间，开始检测雨量**/
				 if((Wiper_State_FsmPre == PARK_MODE)&&(FSM_Timer_Cn > 20))
				 {		
					 if(u8_WiperSpeed_Expert != 0)/*检测到有雨*/
					 {
						 FSM_Timer_Cn = 0;/**检测到有雨，重新开始计数有雨模式*/
						 Wiper_State_Fsm = INT_SPEED_MODE;/*检测到有雨就进入点刮*/
					 }
				   }

			}
        	
			/***************
			 * 泼溅模式
			 * 不受Pre_Park_Mode等待时间影响，直接进入，
			 * 但是第一次点刮会继续
			 * 也就是从第一次点刮完成后开始计数，
			 * 雨量不大就清除计数，或者推出有雨状态就停止计数
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
        	 * 1、   FSM_Timer_Cn     点刮周期计数,从别的mode进入的时候清除计数器，当点刮周期满了就得跳出点刮模式，进入其他模式
        	 * 2、  u8_IntSpeedEnterCnt    该变量只在park 和 点刮模式用  当进入周期刮     或     慢刮  就得清除掉  
        	 * **/
        	
        	
        	/********
        	 * 进入点刮模式就直接发送点刮模式
        	 * ******/
        	RLS_APP_Value.RLS_APP_WiperSpeed = WiperSpeed_Single;
        	
        	 /*从其他状态进入点刮模式就清除点刮计数器*/
        	 if(Wiper_State_FsmPre != INT_SPEED_MODE) 
        		 FSM_Timer_Cn = 0;
        	
        	/*********
        	 * 进入点刮连续发500ms点刮
        	 * 发完点刮回parkmode
        	 * *************/
        	 FSM_Timer_Cn++;/**/
            if(FSM_Timer_Cn >= 10)
            {
            	FSM_Timer_Cn = 0;/*再清理一下计数器，保险一些*/
            	Wiper_State_Fsm = PARK_MODE;
                u8_IntSpeedEnterCnt++;
            } 
            
            /*******************以上为点刮循环*****************************/

                          
            
            /****************************进入慢刮*********************************************************/
        	if(u8_WiperSpeed_Expert > 4)/*连续点刮且，wiperSpeed大于4 进入低速刮刷*/
			{			
				if(u8_IntSpeedEnterCnt > 2)/**/
				{
					u8_IntSpeedEnterCnt = 0;
					Wiper_State_Fsm = LOW_SPEED_MODE; 
				}
			}
        	/****************************进入周期刮*********************************************************/
        	else                     /*连续点刮，进入周期刮*/
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
		    	u8_Splash_cnt = 0;
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
                	FSM_Timer_Cn1 = 0;                    
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
        	
        	/*****************周期刮刷内的大雨模式****************************/
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


			FSM_Timer_Cn++;/*********模式主计时器*************/
            if(FSM_Timer_Cn >= 200)
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
            
            if(u8_WiperSpeed_Expert < 4)/*********当雨量偏小时，从低速退出到周期刮*************/
            {        
            	FSM_Timer_Cn1++;
                if(FSM_Timer_Cn1 >= temp_timer)
                {
                	FSM_Timer_Cn1 = 0;
                    Wiper_State_Fsm =  PERIOD_SPEED_MODE;
                }                                   
            }
            /**************雨量偏大，进入快刮******************/
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
            	FSM_Timer_Cn1 = 0;/****当雨量偏大时，清除退出低速计数*******/
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
    if(BCM_APP_Value.BCM_WiperPosition == APP_WiperPosition_Not_Parked)   //0为park点
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

