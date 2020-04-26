#include "auto_light.h"
#include "adc.h"
#include "spi.h"
#include "lin_app.h"


extern uint16 u16_SPD_Vehicle;
extern  Rls_Error_t      App_Rls_Error;
extern  MLX75308_Mnrval_t      Mnrval;

/*******************************
 * globle var
 * 
 * *************************************************/
tLight_Stastegy_Config const  Light_Stastegy_Parameter =
{
        55,  //off_timer
        350, //Lowbean_on_th
        1000, //Lowbean_off_th
        350, //PositionLamp_on_th
        1000  //PositionLamp_off_th
} ;

uint8  u8_LightOnTimer;
uint16 u16_Brightness_FW,u16_Brightness_UP;

uint8  Light_on_cnt[LIGHT_TYPE];
uint8  Light_off_cnt[LIGHT_TYPE];

uint8 u8_light_on_req;

uint8  u8_twilight_on_req;
uint8 u8_twilight_on_invent_req;


void Auto_light_Var_Init(void)
{
	uint8 i;
	
	for (i = 0;i < LIGHT_TYPE ; i++)
	{
		Light_on_cnt[i] = 0; 
		Light_off_cnt[i] = 0;  
	}
	u8_light_on_req = 0;  
	u8_twilight_on_req = 0;
	u8_twilight_on_invent_req = 0;
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
    uint32 temp_light_on_th,temp_light_off_th;
    if(u16_SPD_Vehicle == 0)   
    {
        u8_LightOnTimer  =  4 ;        
    }
    else if(u16_SPD_Vehicle <= 40)
    {
        u8_LightOnTimer  =  10;           
    }    
    else if(u16_SPD_Vehicle <= 80)
    {
        u8_LightOnTimer  =  9;         
    }    
    else 
    {
        u8_LightOnTimer  =  7; 
    }
    
	
	if(u16_Brightness_UP <= 100)
	{
	    temp_light_on_th =  Light_Stastegy_Parameter.Lowbean_on_th;
	    temp_light_off_th =  Light_Stastegy_Parameter.Lowbean_off_th; 
	}
	else if (u16_Brightness_UP <= 150)
	{
            temp_light_on_th =  Light_Stastegy_Parameter.Lowbean_on_th + 25;
	    temp_light_off_th =  Light_Stastegy_Parameter.Lowbean_off_th + 25;
	}
	else 
	{
            temp_light_on_th =  Light_Stastegy_Parameter.Lowbean_on_th + 50;
	    temp_light_off_th =  Light_Stastegy_Parameter.Lowbean_off_th + 50;
	}
	
	if(App_Rls_Error.IR_Error == 0)
        {
                    if((u16_Brightness_FW <= temp_light_on_th )&&(u16_Brightness_UP <= 150))
                    {
                             Light_off_cnt[LIGHT] = 0;
                             if(Light_on_cnt[LIGHT] >= u8_LightOnTimer)
                             {
                                     u8_light_on_req = 1;     
                             }
                             else
                             {
                                    Light_on_cnt[LIGHT]++ ;
                             }
                    } 		
                    else if(((u16_Brightness_FW > temp_light_off_th )&&(u16_Brightness_UP > 250))||(u16_Brightness_FW > 1500))
                    {	
                             Light_on_cnt[LIGHT] = 0;
                             if(Light_off_cnt[LIGHT] >= Light_Stastegy_Parameter.off_timer)
                             {
                                     u8_light_on_req = 0;     
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
		if(u16_Brightness_FW <= temp_light_on_th )
		{
			 Light_off_cnt[LIGHT] = 0;
			 if(Light_on_cnt[LIGHT] >= u8_LightOnTimer)
			 {
				 u8_light_on_req = 1;     
			 }
			 else
			 {
				Light_on_cnt[LIGHT]++ ;
			 }
		} 
		else if(u16_Brightness_FW > temp_light_off_th )
		{	
			 Light_on_cnt[LIGHT] = 0;
			 if(Light_off_cnt[LIGHT] >= Light_Stastegy_Parameter.off_timer)
			 {
				 u8_light_on_req = 0;     
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

void RLS_Light_Module_Fault_Process(void)
{
	if(Mnrval.Amb_C == 0xFFFF)    //light
	{
		App_Rls_Error.LS_Error_Cnt++;
		if(App_Rls_Error.LS_Error_Cnt >= 50)
		{
			App_Rls_Error.LS_Error = 1;
		}
	}
	else
	{
		App_Rls_Error.LS_Error_Cnt = 0;
	}
	
	if(App_Rls_Error.LS_Error_Cnt < 50)
	{
		App_Rls_Error.LS_Error = 0;
	}
				
	if(Mnrval.Amb_D == 0)  //IR
	{
		App_Rls_Error.IR_Error_Cnt[0]++;
		if(App_Rls_Error.IR_Error_Cnt[0] >= 50)
		{
			App_Rls_Error.IR_Error = 1;
		}
	}
	else
	{
		App_Rls_Error.IR_Error_Cnt[0] = 0;
	}
	
	/*if(Mnrval.Amb_E < 2000)  //IR
	{
		App_Rls_Error.IR_Error_Cnt[1]++;
		if(App_Rls_Error.IR_Error_Cnt[1] >= 20)
		{
			App_Rls_Error.IR_Error = 1;
		}
	}
	else
	{
		App_Rls_Error.IR_Error_Cnt[1] = 0;
	}*/
	
	if(App_Rls_Error.IR_Error_Cnt[0] < 50)
	{
		App_Rls_Error.IR_Error = 0;
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
    if(avg_ir > 0xFFE)         u16_Brightness_UP = 0xFFE;
    else                       u16_Brightness_UP = avg_ir;
        
    if(avg_fw > 0xFFE)     
    {
    	u16_Brightness_FW = 0xFFE;
    }
    else                 
    {
    	u16_Brightness_FW = avg_fw;
    }
     
    RLS_Light_Module_Fault_Process();
    RLS_AutoLightControl();                
}

 

