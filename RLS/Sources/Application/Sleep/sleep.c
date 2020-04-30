#include "sleep.h"
#include "lin_app.h"
#include "spi.h"
#include "RTC.h"
#include "gpio.h"
#include "ftm.h"
#include "lin_common_api.h"
#include "auto_light.h"


extern uint8  Timer_4s;
extern uint8  Timer_600ms;
extern uint32  Timer_6h;

extern uint8  u8_RLS_WindowCloseReq;
extern uint16 u16_RainWindow_Cnt;

extern uint8  Light_on_cnt[LIGHT_TYPE];
extern uint8  Light_off_cnt[LIGHT_TYPE];
extern uint8 u8_light_on_req;
extern uint8  u8_twilight_on_req;
extern uint8 u8_enter_period_cnt;
extern uint8 u8_enter_period_flg;
extern uint8  u8_Rain_Flg;
extern uint16 u16_IntWindow_Cnt;
extern uint8  u8_Int_Cnt;
extern bool_t  Lin_Diag_Enable;
extern uint8  u8_Lin_Diag_Enable_Cnt;

extern Main_Fsm_t  RLS_RunMode;

//this frame is for APP 
extern RLS_APP_Value_t     RLS_APP_Value;
extern BCM_APP_Value_t     BCM_APP_Value;

/*********
 * cmd for sleep
 * *********/
bool_t bool_lin_cmd_sleep;
bool_t bool_auto_roof_rain_measure_sleep_flg;
bool_t bool_wakeup_bcm_cnt_sleep_flg;

bool_t bool_Mcu_wakeup_state;

uint8 u8_wakeup_bcm_1500ms_timer;
uint8 u8_wakeup_bcm_1min_timer;

Auto_Roof_FSM_t  Auto_Roof_FSM;

void Sleep_Var_Init(void)
{
	bool_lin_cmd_sleep = FALSE;
	bool_auto_roof_rain_measure_sleep_flg = FALSE;
	bool_wakeup_bcm_cnt_sleep_flg = FALSE;
	bool_Mcu_wakeup_state = FALSE;
	
	u8_wakeup_bcm_1500ms_timer = 0;
	u8_wakeup_bcm_1min_timer = 0;
	Auto_Roof_FSM = Roof_RAIN_CHECK;
	
}


void Sleep_check(void)
{
	if((Timer_4s >= 8) //no lin data for 4s
		||(bool_lin_cmd_sleep == TRUE)  //recive the signal of sleep from BCM
		||(bool_auto_roof_rain_measure_sleep_flg == TRUE)
		||(bool_wakeup_bcm_cnt_sleep_flg == TRUE))
	{
		bool_lin_cmd_sleep = FALSE;
		bool_auto_roof_rain_measure_sleep_flg = FALSE;
		bool_wakeup_bcm_cnt_sleep_flg = FALSE;
		Timer_4s = 0;
			
		Sleep_Process();
		Recover_Process();
	}
	
}



/*******************************************************
 * FUNCTION NAME : Auto_Roof_Process()
 *   DESCRIPTION : Auto_Roof_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Auto_Roof_Process(void)
{   
	Timer_6h++;
	
	switch(Auto_Roof_FSM)
	{
		case Roof_RAIN_CHECK:
		{
            RLS_Auto_Rain_Task();
			if(RLS_APP_Value.RLS_APP_WiperSpeed != WiperSpeed_High)
			{			
				Auto_Roof_FSM = Roof_Wake_Up;	
				u8_wakeup_bcm_1500ms_timer = 0;
				RTC_DisableInt();
			}
			else
			{
				if(Timer_6h >=(6*60*60*20)) //time out deep sleep
				{
					Auto_Roof_FSM = Roof_Wake_Up;
					u8_wakeup_bcm_1500ms_timer = 0;
				}
			}	
			if(bool_Mcu_wakeup_state == TRUE)  //if BCM wake up RLS,  go to normal mode
			{
				bool_auto_roof_rain_measure_sleep_flg = FALSE;
				RLS_RunMode =  MAIN_NORMAL;
			}
		}break;
		
		case Roof_Wake_Up:
		{
			Timer_600ms = 0;	
			if(bool_Mcu_wakeup_state == TRUE)
			{
				u8_wakeup_bcm_1min_timer = 0;
				Auto_Roof_FSM = Roof_CLOSED_WINDOWS;
			}
			else
			{
				u8_wakeup_bcm_1500ms_timer++;
							
				if((u8_wakeup_bcm_1500ms_timer <= 9)&&
					((u8_wakeup_bcm_1500ms_timer%3) == 0))//150ms一包三帧唤醒信号
				{
					Lin_RLS_Wakeup_BCM();							
				}
				
				if(u8_wakeup_bcm_1500ms_timer >= 30)//间隔1500ms发送唤醒包
				{	
					u8_wakeup_bcm_1500ms_timer = 0;
					u8_wakeup_bcm_1min_timer++;
					
					if(u8_wakeup_bcm_1min_timer >= 40)//1min
					{
						u8_wakeup_bcm_1min_timer = 0;
						bool_wakeup_bcm_cnt_sleep_flg = TRUE;
						BCM_APP_Value.BCM_WindowStatus = BCM_Window_All_closed;
					}
				}		
			}
					
		}break;
		case Roof_CLOSED_WINDOWS:
		{
			Timer_600ms = 0;
			u8_wakeup_bcm_1min_timer++;
			u8_RLS_WindowCloseReq = 1 ; //send closed window
			Lin_RLS_data();
			if(u8_wakeup_bcm_1min_timer >= 1200) //120*50ms
			{
				u8_wakeup_bcm_1min_timer = 0;
				u8_RLS_WindowCloseReq = 0 ;
				BCM_APP_Value.BCM_WindowStatus = BCM_Window_All_closed;
				RLS_RunMode =  MAIN_NORMAL;
			}
			
			if(BCM_APP_Value.BCM_WindowStatus == BCM_Window_All_closed)
			{
				u8_RLS_WindowCloseReq = 0;
				RLS_RunMode =  MAIN_NORMAL;
			}	
		}break;
		default:
		{
			Auto_Roof_FSM = Roof_RAIN_CHECK;
		}break;
		
	}
}
/*******************************************************
 * FUNCTION NAME : Sleep_Process()
 *   DESCRIPTION : Sleep_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Sleep_Process(void)
{
	uint8 i;
	RLS_Disable_Light();
	DISABLE_INTERRUPT;
	
	/******MLX75308进入休眠***********/
	(void)SPI_Wr_Cmd(RSLP);    
	(void)SPI_Wr_Cmd(CSLP);
	SPI_Disable();
	
#ifdef ENABLE_AUTO_ROOF	
	if(BCM_APP_Value.BCM_WindowStatus != BCM_Window_All_closed)
	{
		RTC_EnableInt();
		RLS_RunMode =  MAIN_SLEEP_Mode;
		Auto_Roof_FSM = Roof_RAIN_CHECK;
	}
	else
	{
		RTC_DisableInt();
	}
#endif
	
	UART0_S2 |=  UART_S2_RXEDGIF_MASK;   //去掉会产生错误帧
	UART0_BDH  |=  UART_BDH_RXEDGIE_MASK; //去掉会产生错误帧
	/******关闭LIN发送***********/ 
	LIN_DISABLE ;//GPIOA_PCOR |= 0x00008000 ; //PTB7  LIN_EN
	
	for (i = 0;i < LIGHT_TYPE ; i++)
	{
		Light_on_cnt[i] = 0; 
		Light_off_cnt[i] = 0;  
	}
			
	RLS_APP_Value.light_on_req = Light_Off;  
	RLS_APP_Value.twilight_on_req = Light_Off;
	
	bool_Mcu_wakeup_state = FALSE;
	u16_RainWindow_Cnt = 0;
	u8_enter_period_cnt = 0;
	u8_enter_period_flg = 0;
	u8_Rain_Flg = 0;
	u16_IntWindow_Cnt = 0;
	u8_Int_Cnt = 0;
	Lin_RLS_data();
	
	/* disable LVD in stop mode */
	PMC_SPMSC1 &= ~(PMC_SPMSC1_LVDE_MASK | PMC_SPMSC1_LVDRE_MASK | PMC_SPMSC1_LVDSE_MASK);
	/* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
	SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK;
	/* Not using KEIL's uVision, so use the standard assembly command */
	ENABLE_INTERRUPT;	
	asm("WFI");
	
	RTC_DisableInt();
}

/*******************************************************
 * FUNCTION NAME : Recover_Process()
 *   DESCRIPTION : Recover_Process  
 *         INPUT : NONE
 *        OUTPUT : void  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/ 
void Recover_Process(void)
{
	LIN_ENABLE ;// LIN_EN
	Timer_6h = Timer_6h + (5 * 20);//every 5s wake up
#ifdef ENABLE_SOLAR
	RLS_Enable_Light();
#endif
	Lin_Diag_Enable = FALSE;
	u8_Lin_Diag_Enable_Cnt = 0;
	l_sys_init();
	l_ifc_init(LI0);
	SPI_Enable();
	FTM0_Init();
	
    (void)SPI_Wr_Cmd(NRM); 
}
