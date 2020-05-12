#include "auto_air.h"
#include "spi.h"
#include "lin_app.h"

/****************************************
 * var
 *
 * **************************************/
static uint32 Tab_AWG_FW[Tab_FW_NUM]        = {5018,11019, 12317, 13687, 15252, 16290, 16500, 16750,17000,17500,18000,18500,19000,19250,19500,19750};
static uint16 Tab_Brightness_FW[Tab_FW_NUM] = {0,    40,    150,   220,   300,  350,    400,   500,  550, 600, 659 , 700,  750,  800,  866,  1021};



static uint32 Tab_AWG_IR[Tab_IR_NUM]        = {21062,26277 ,29680,30642,31246,32353,33035,33673,34084,34296,34780,35000,35220,  35420,   35700,  36000};
static uint16 Tab_Brightness_IR[Tab_IR_NUM] = { 0   ,  9,     21,    29,   35,  51,   60,   75  , 80,  85,  90,   95,    100,    150,    200,    253}; 


static uint32 Tab_AWG_Solar[Tab_IR_NUM]        = {21062,24500 ,25000,25245,25500,26010,26300,27000,27250,27550,28300,30300,32130,  33200,   33500,  33700};
static uint16 Tab_Brightness_Solar[Tab_IR_NUM] = { 0   , 10,    25,    40,    55,  70,   85,  100 , 115,  130,  145,  160,   180,   200,    220,    250}; 


uint16 u16_solar_buffer[SOLAR_CHAN_NUM][SOLAR_WINDOW];

bool_t Frist_on_flag;

extern  MLX75308_Frame_t       MLX75308_RxFrame;
extern  MLX75308_Mnrval_t      Mnrval;

//this frame is for APP 
extern RLS_APP_Value_t     RLS_APP_Value;
extern BCM_APP_Value_t     BCM_APP_Value;

void Auto_Air_Var_Init(void)
{
	RLS_APP_Value.u8_Solar_l_value = 0;
	RLS_APP_Value.u8_Solar_r_value = 0;
	Frist_on_flag = FALSE ;
}


/*******************************************************
 * FUNCTION NAME : Search_Table()
 *   DESCRIPTION : line table 
 *         INPUT : in_x ,*Tabx ,*Taby, Tab_NUM
 *        OUTPUT : NONE  
 *        RETURN : calc value              
 *        OTHERS : NONE
 *******************************************************/
uint16 Search_Table(uint32 in_x,uint32 *Tabx,uint16 *Taby,uint8 Tab_NUM)
{
    uint8 Search_Inx;
    uint8 Lit_Inx,Big_Inx;
    uint16 Result;
    
    Search_Inx = Tab_NUM/2;
    
    if(in_x < *(Tabx)) 
    {   
        return *(Taby);
    }
    else
    {
        if(in_x == *(Tabx + Search_Inx)) 
        {
            return *(Taby + Search_Inx);
        } 
    
        else if(in_x > *(Tabx + Search_Inx))
        {

            for(Search_Inx ++; Search_Inx <= (Tab_NUM - 1); Search_Inx ++)
            {
                if((Search_Inx == (Tab_NUM - 1)) || (in_x <= *(Tabx + Search_Inx))) 
                {
                    
                    Lit_Inx = Search_Inx - 1;
                    Big_Inx = Search_Inx;
                    Result = (uint16) ((*(Taby + Big_Inx) - *(Taby + Lit_Inx)) * (in_x - *(Tabx + Lit_Inx))/(*(Tabx + Big_Inx) - *(Tabx + Lit_Inx)) + *(Taby + Lit_Inx));
                    return Result;
                }
            }
        } 
        else 
        {
            for(Search_Inx --; Search_Inx >= 0; Search_Inx --)
            {
                if((Search_Inx == 0) || (in_x >= *(Tabx + Search_Inx))) 
                {
                    Lit_Inx = Search_Inx;
                    Big_Inx = Search_Inx + 1;
                    Result = (uint16) ((*(Taby + Big_Inx) - *(Taby + Lit_Inx)) * (in_x - *(Tabx + Lit_Inx))/(*(Tabx + Big_Inx) - *(Tabx + Lit_Inx)) + *(Taby + Lit_Inx));
                    return Result;
                }
            }        
        }
    }
}


/*******************************************************
 * FUNCTION NAME : RLS_Auto_Solar_Task()
 *   DESCRIPTION : RLS_Auto_Solar_Task function 
 *         INPUT : 
 *        OUTPUT : NONE  
 *        RETURN : NONE              
 *        OTHERS : NONE
 *******************************************************/
void RLS_Auto_Solar_Task(void)
{
        uint32  avg_Solar_l_value = 0;
        uint32  avg_Solar_r_value = 0;
        uint32  sum_left = 0;
        uint32  sum_right = 0;
        uint16  avg_hud = 0;
        uint8 i;
        for(i = 0; i < SOLAR_AVG_N; i++)
        {
            MLX75308_Meansure(PDC | PDD |PDE);
            avg_hud +=  MLX75308_RxFrame.data_field[0];
            avg_Solar_l_value +=  MLX75308_RxFrame.data_field[1];
            avg_Solar_r_value +=  MLX75308_RxFrame.data_field[2];
        }
        
        avg_hud = avg_hud / SOLAR_AVG_N;
        avg_Solar_l_value = avg_Solar_l_value / SOLAR_AVG_N;
        avg_Solar_r_value = avg_Solar_r_value / SOLAR_AVG_N;
        
        Mnrval.Amb_[0] = (uint16)(avg_hud);
        Mnrval.Amb_[1] = (uint16)(avg_Solar_l_value);
        Mnrval.Amb_[2] = (uint16)(avg_Solar_r_value);
	
	for(i = 1;i < SOLAR_WINDOW;i++)
	{	
		if(Frist_on_flag == FALSE)
		{
			u16_solar_buffer[SOLAR_CHAN_A][i - 1] = (uint16)(avg_Solar_l_value);
		    u16_solar_buffer[SOLAR_CHAN_B][i - 1] = (uint16)(avg_Solar_r_value);
		    if(i >= 7)
		    {
		    	Frist_on_flag = TRUE;	
		    }
		}
		else
		{
			u16_solar_buffer[SOLAR_CHAN_A][i - 1] = u16_solar_buffer[SOLAR_CHAN_A][i];	
			u16_solar_buffer[SOLAR_CHAN_B][i - 1] = u16_solar_buffer[SOLAR_CHAN_B][i];
		}
	}
	u16_solar_buffer[SOLAR_CHAN_A][SOLAR_WINDOW - 1] = (uint16)(avg_Solar_l_value) ;
	u16_solar_buffer[SOLAR_CHAN_B][SOLAR_WINDOW - 1] = (uint16)(avg_Solar_r_value) ;
	
	for(i = 0; i < SOLAR_WINDOW;i++)
	{
		sum_left += u16_solar_buffer[SOLAR_CHAN_A][i];
		sum_right += u16_solar_buffer[SOLAR_CHAN_B][i];
	}
	
	avg_Solar_l_value =  sum_left/SOLAR_WINDOW ;
	avg_Solar_r_value =  sum_right/SOLAR_WINDOW;
	
	avg_Solar_l_value = Search_Table(avg_Solar_l_value,Tab_AWG_Solar, Tab_Brightness_Solar, 16);
	avg_Solar_r_value = Search_Table(avg_Solar_r_value,Tab_AWG_Solar, Tab_Brightness_Solar, 16);
	
	
	if(avg_Solar_l_value >= 250) RLS_APP_Value.u8_Solar_l_value =  250;
	else                         RLS_APP_Value.u8_Solar_l_value =  avg_Solar_l_value;
	
	if(avg_Solar_r_value >= 250) RLS_APP_Value.u8_Solar_r_value =  250;
	else                         RLS_APP_Value.u8_Solar_r_value =  avg_Solar_r_value;
}
