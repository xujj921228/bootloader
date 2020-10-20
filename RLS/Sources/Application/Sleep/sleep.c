#include "sleep.h"
#include "app_data.h"
#include "spi.h"
#include "RTC.h"
#include "gpio.h"
#include "ftm.h"
#include "lin_common_api.h"
#include "auto_light.h"
#include "lin_app.h"
#include "local_eep_data.h"
#include "lin_diagnostic_service.h"


extern uint8  Timer_4s;
extern uint16 u16_RainWindow_Cnt;

extern uint8  Light_on_cnt[LIGHT_TYPE];
extern uint8  Light_off_cnt[LIGHT_TYPE];
extern uint8 u8_light_on_req;
extern uint8  u8_twilight_on_req;
extern bool_t Rain_Flg;
extern uint16 u16_IntWindow_Cnt;
extern uint8  u8_Int_Cnt;
extern bool_t  Lin_Diag_Enable;
extern uint8  u8_Lin_Diag_Enable_Cnt;

extern Main_Fsm_t  RLS_RunMode;

//this frame is for APP 
extern RLS_APP_Value_t     RLS_APP_Value;
extern BCM_APP_Value_t     BCM_APP_Value;
extern local_info_t local_info;


/*********
 * cmd for sleep
 * *********/
uint8  Timer_600ms;
uint16  Timer_6h;
bool_t bool_lin_cmd_sleep;
bool_t bool_auto_roof_rain_measure_sleep_flg;
bool_t bool_wakeup_bcm_cnt_sleep_flg;

bool_t bool_Mcu_wakeup_state;

uint8 u8_wakeup_bcm_1500ms_timer;
uint16 u16_wakeup_bcm_1min_timer;

Auto_Roof_FSM_t  Auto_Roof_FSM;

void Sleep_Var_Init(void)
{
	Timer_600ms = 0;
	
	bool_lin_cmd_sleep = FALSE;
	bool_auto_roof_rain_measure_sleep_flg = FALSE;
	bool_wakeup_bcm_cnt_sleep_flg = FALSE;
	bool_Mcu_wakeup_state = FALSE;
	
	u8_wakeup_bcm_1500ms_timer = 0;
	u16_wakeup_bcm_1min_timer = 0;
	Auto_Roof_FSM = Roof_RAIN_CHECK;
	RLS_APP_Value.RLS_APP_ClosedWind = RLS_APP_No_Request;	
}

void RLS_Lin_Tx_Control(void)
{   
    UART0_C2 &= ~(UARTCR2_TE_MASK | UARTCR2_RE_MASK | UARTCR2_RIE_MASK);   
    GPIOA_PDDR |= 0x00000200 ; //PTB1-output  tx
    GPIOA_PCOR |= 0x00000200 ; //PTB1-output  tx    
}

void Sleep_check(void)
{
	if((Timer_4s >= 8) //no lin data for 4s
		||(bool_lin_cmd_sleep == TRUE)  //recive the signal of sleep from BCM
		||(bool_auto_roof_rain_measure_sleep_flg == TRUE))
	{
		if(BCM_APP_Value.BCM_APP_ModReq != APP_Polling_Mode)//非pollingmode
		{
			 RLS_Lin_Tx_Control();//深度休眠
		}
		
		bool_lin_cmd_sleep = FALSE;
		Timer_4s = 0;
		bool_auto_roof_rain_measure_sleep_flg = FALSE;
			
		if(RLS_RunMode == MAIN_NORMAL)//第一次进入pollingmode计数器初始化
		{
			Timer_6h = 0;
			RLS_RunMode =  MAIN_SLEEP_Mode;
			Auto_Roof_FSM = Roof_RAIN_CHECK;
			
		}
		else
		{
			Timer_6h++;
		}
		
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
	switch(Auto_Roof_FSM)
	{
		case Roof_RAIN_CHECK:
		{
			RLS_Auto_Rain_Task();
			if(RLS_APP_Value.RLS_APP_WiperSpeed != WiperSpeed_Off)//检测到有雨，雨刷信号不为0
			{			
				Auto_Roof_FSM = Roof_Wake_Up;	
				u8_wakeup_bcm_1500ms_timer = 0;
				u16_wakeup_bcm_1min_timer = 0;
				RTC_DisableInt();
				RLS_APP_Value.RLS_APP_ClosedWind = RLS_APP_Rain_Closed;
			}
			else
			{
				if(Timer_6h >=3857) //5.6秒一次待机，5.6*（x - 1） + 5 = 6*3600
				{
					Timer_6h = 0;
					Auto_Roof_FSM = Roof_Wake_Up;
					u8_wakeup_bcm_1500ms_timer = 0;
					u16_wakeup_bcm_1min_timer = 0;
					RTC_DisableInt();
					RLS_APP_Value.RLS_APP_ClosedWind = RLS_APP_Time_Closed;
				}	
				else
				{
					if(bool_Mcu_wakeup_state == TRUE)
					{
						boot_jump_to_APP((uint16 *)APP_start_address);
					}
					
					Timer_600ms++;
				    if(Timer_600ms >= 12) //   600ms Task
					{
						bool_auto_roof_rain_measure_sleep_flg = TRUE;
					} 
					
				}
			}
		}break;
		
		case Roof_Wake_Up:
		{	
			if(bool_Mcu_wakeup_state == TRUE)
			{
				u16_wakeup_bcm_1min_timer = 0;
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
					u16_wakeup_bcm_1min_timer++;
					
					if(u16_wakeup_bcm_1min_timer >= 40)//1min
					{
						u16_wakeup_bcm_1min_timer = 0;
						RLS_APP_Value.RLS_APP_ClosedWind = RLS_APP_No_Request;
						BCM_APP_Value.BCM_APP_ModReq = APP_Nomal_Mode;
					}
				}		
			}
					
		}break;
		case Roof_CLOSED_WINDOWS:
		{
			/*u16_wakeup_bcm_1min_timer++;
			if(u16_wakeup_bcm_1min_timer >= 1200) //1200*50ms
			{
				u16_wakeup_bcm_1min_timer = 0;
				RLS_APP_Value.RLS_APP_ClosedWind = RLS_APP_No_Request;
			    BCM_APP_Value.BCM_APP_ModReq = APP_Sleep_Mode;
			    bool_wakeup_bcm_cnt_sleep_flg = TRUE;
			}*/
				
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
	
	RTC_EnableInt();
	
	
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
#ifdef ENABLE_SOLAR
	RLS_Enable_Light();
#endif
	Lin_Diag_Enable = FALSE;
	u8_Lin_Diag_Enable_Cnt = 0;
	l_sys_init();
	l_ifc_init(LI0);
	SPI_Enable();
	FTM0_Init();
	Timer_600ms = 0;
	
    (void)SPI_Wr_Cmd(NRM); 
}
