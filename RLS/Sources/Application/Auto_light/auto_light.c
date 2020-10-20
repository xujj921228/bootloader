#include "auto_light.h"
#include "adc.h"
#include "spi.h"
#include "app_data.h"


extern  Rls_Error_t      App_Rls_Error;
extern  MLX75308_Mnrval_t      Mnrval;

//this frame is for APP 
extern RLS_APP_Value_t     RLS_APP_Value;
extern BCM_APP_Value_t     BCM_APP_Value;

/*******************************
 * globle var
 * 
 * *************************************************/
tLight_Stastegy_Config const  Light_Stastegy_Parameter =
{
        55,  //off_timer
        100, //Lowbean_on_th
        150, //Lowbean_off_th
        100, //PositionLamp_on_th
        150  //PositionLamp_off_th
} ;

uint8  u8_LightOnTimer[Speed_Gear_Sum] = {5,5,10,9,7} ;

uint8  Light_on_cnt[LIGHT_TYPE];
uint8  Light_off_cnt[LIGHT_TYPE];


void Auto_light_Var_Init(void)
{
	App_Rls_Error.LS_Error_Cnt = 0;
	App_Rls_Error.IR_Error_Cnt = 0;
	
	RLS_APP_Value.u16_Brightness_FW = 0;
	RLS_APP_Value.u16_Brightness_UP = 0;
	
	RLS_APP_Value.light_on_req = Light_Off;  
	RLS_APP_Value.twilight_on_req = Light_Off;
}

/*******************************************************
 * FUNCTION NAME : RLS_AutoLightControl()
 *   DESCRIPTION : RLS_AutoLightControl function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_AutoLightControl(void)
{
    uint16 temp_light_on_th,temp_light_off_th;

    
	
	if(RLS_APP_Value.u16_Brightness_UP <= 50)
	{
	    temp_light_on_th =  Light_Stastegy_Parameter.Lowbean_on_th;
	    temp_light_off_th =  Light_Stastegy_Parameter.Lowbean_off_th; 
	}
	else if (RLS_APP_Value.u16_Brightness_UP <= 80)
	{
        temp_light_on_th =  Light_Stastegy_Parameter.Lowbean_on_th + 10;
	    temp_light_off_th =  Light_Stastegy_Parameter.Lowbean_off_th + 10;
	}
	else 
	{
        temp_light_on_th =  Light_Stastegy_Parameter.Lowbean_on_th + 20;
	    temp_light_off_th =  Light_Stastegy_Parameter.Lowbean_off_th + 20;
	}
	
	if(App_Rls_Error.IR_Error == FALSE)
    {
		if((RLS_APP_Value.u16_Brightness_FW <= temp_light_on_th )&&(RLS_APP_Value.u16_Brightness_UP <= 50))
		{
			 Light_off_cnt[LIGHT] = 0;
			 if(Light_on_cnt[LIGHT] >= u8_LightOnTimer[BCM_APP_Value.SPD_Vehicle_Gear])
			 {
				 RLS_APP_Value.light_on_req = Light_On;     
			 }
			 else
			 {
					Light_on_cnt[LIGHT]++ ;
			 }
		} 		
		else if(((RLS_APP_Value.u16_Brightness_FW > temp_light_off_th )&&(RLS_APP_Value.u16_Brightness_UP > 64))||(RLS_APP_Value.u16_Brightness_FW > 300))
		{	
			 Light_on_cnt[LIGHT] = 0;
			 if(Light_off_cnt[LIGHT] >= Light_Stastegy_Parameter.off_timer)
			 {
				 RLS_APP_Value.light_on_req = Light_Off;     
			 }
			 else
			 {
				 Light_off_cnt[LIGHT]++ ;
			 }
		}	
		else
		{
			Light_on_cnt[LIGHT] = 0;
			Light_off_cnt[LIGHT] = 0;
		}
    }
	else
	{
		if(RLS_APP_Value.u16_Brightness_FW <= temp_light_on_th )
		{
			 Light_off_cnt[LIGHT] = 0;
			 if(Light_on_cnt[LIGHT] >= u8_LightOnTimer[BCM_APP_Value.SPD_Vehicle_Gear])
			 {
				 RLS_APP_Value.light_on_req = Light_On;     
			 }
			 else
			 {
				Light_on_cnt[LIGHT]++ ;
			 }
		} 
		else if(RLS_APP_Value.u16_Brightness_FW > temp_light_off_th )
		{	
			 Light_on_cnt[LIGHT] = 0;
			 if(Light_off_cnt[LIGHT] >= Light_Stastegy_Parameter.off_timer)
			 {
				 RLS_APP_Value.light_on_req = Light_Off;     
			 }
			 else
			 {
				Light_off_cnt[LIGHT]++ ;
			 }
		}		
		else
		{
			Light_on_cnt[LIGHT] = 0;
			Light_off_cnt[LIGHT] = 0;
		}
	}	
}

void RLS_Light_Module_Fault_Process(uint16 Fault_FW,uint16 Fault_UP)
{
	if(Fault_FW >= 0xFFF)    //light
	{
		if(App_Rls_Error.LS_Error_Cnt >= 50)
		{
			App_Rls_Error.LS_Error = TRUE;
		}
		else
		{
			App_Rls_Error.LS_Error_Cnt++;
		}
	}
	else
	{
		App_Rls_Error.LS_Error_Cnt = 0;
		App_Rls_Error.LS_Error = FALSE;
	}
				
	if(Fault_UP >= 0xFFF)  //IR
	{
		
		if(App_Rls_Error.IR_Error_Cnt >= 50)
		{
			App_Rls_Error.IR_Error = TRUE;
		}
		else
		{
			App_Rls_Error.IR_Error_Cnt++;
		}
	}
	else
	{
		App_Rls_Error.IR_Error_Cnt = 0;
		App_Rls_Error.IR_Error = FALSE;
	}
}

/*******************************************************
 * FUNCTION NAME : RLS_Auto_Light_Task()
 *   DESCRIPTION : RLS_Auto_Light_Task function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Auto_Light_Task(void)
{
    uint32 avg_ir = 0 , avg_fw = 0;
    uint8 i;
             
    for(i = 0; i < AVG_N; i++)
    {
            avg_fw +=  get_adc_times(AMB_FW_CH,MEAS_NUM);
            avg_ir +=  get_adc_times(AMB_UP_CH,MEAS_NUM);
    }
    
    avg_ir = avg_ir / AVG_N;
    avg_fw = avg_fw / AVG_N;
    
    RLS_Light_Module_Fault_Process((uint16)avg_fw,(uint16)avg_ir);
    
    if(avg_ir > 0xFFE)     
    {
    	RLS_APP_Value.u16_Brightness_UP = 0xFFE;	
   	}
    else                      
    {
    	RLS_APP_Value.u16_Brightness_UP = (uint16)avg_ir;
   	}
        
    if(avg_fw > 0xFFE)
    {
    	RLS_APP_Value.u16_Brightness_FW = 0xFFE;
   	}
    else
    {
    	RLS_APP_Value.u16_Brightness_FW = (uint16)avg_fw;
    }
    
     
    RLS_AutoLightControl();                
}

 

