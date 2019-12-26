#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "global_parameter.h"
#include "gpio.h"
#include "clock.h"
#include "spi.h"
#include "rls_app.h"

/********************************************************************************
 * @discription : uint8 SPI_Wr_Cmd(uint16 Cmd) 
 ********************************************************************************/

uint8 SPI_Wr_Cmd(uint16 Cmd) 
{
    uint8 i;
    uint8 p, parity;
    uint16 RDBUF,SPI_RD;
    RDBUF  = 0;
    SPI_RD = 0;
    p = 0;
    parity = (uint8)Cmd;

    if((Cmd & 0xf000) == 0xD000)            //if the command is SM ,add even parity bit
    {
        p = (BIT(Cmd,1)^BIT(Cmd,2)^BIT(Cmd,3)^BIT(Cmd,4)^BIT(Cmd,5)^BIT(Cmd,6)^BIT(Cmd,7));
        Cmd |= p;
    }

    while(!DR); //wait until is DR goes high

    CS = 0;

    for(i = 0;i < 16;i++) 
    {
        SCLK =0;

        MOSI = ((Cmd & (0x8000 >> i)) != 0); //rising clock edge MOSI  

        SCLK = 1;

        RDBUF = MISO;                       //falling clock edge MISO
        SPI_RD |= (RDBUF << (15 - i));
    }

    CS = 1;

    if((SPI_RD & 0x00ff) == ((Cmd >> 8) & 0x00ff))  //verify the right command is uploaded to the device
    return TRUE;                                  //reture State Flag & Ctrl1 Byte
    else
    return FALSE;
}


/********************************************************************************
 * @discription : uint8 SPI_Wr_Reg(uint8 Data, uint8 Addr)
 ********************************************************************************/
uint8 SPI_Wr_Reg(uint8 Data, uint8 Addr) 
{
    uint32 Cmd = 0;
    uint32 RDBUF = 0, SPI_RD = 0;
    uint8  p0 = 0,p1 = 0;
    uint8  i;

    p0 = !(BIT(Data,7)^BIT(Data,6)^BIT(Data,5)^BIT(Data,4)^BIT(Data,3)^BIT(Data,2)^BIT(Data,1)^BIT(Data,0)
       ^BIT(Addr,3)^BIT(Addr,2)^BIT(Addr,1)^BIT(Addr,0));
    p1 = (BIT(Data,0)^BIT(Data,1)^BIT(Data,2)^BIT(Data,3)^BIT(Data,4)^BIT(Data,5)^BIT(Data,6)^BIT(Data,7)
       ^BIT(Addr,3)^BIT(Addr,2)^BIT(Addr,1)^BIT(Addr,0));

    Cmd = (((((((((Cmd | Data)<<4) | Addr) << 1) | p0 ) << 1) | p1) << 2) | 0x870000);

    while(!DR); //wait until is DR goes high

    CS = 0;

    for(i = 0;i < 24;i++) 
    {

        SCLK =0;

        MOSI = ((Cmd & (0x800000 >> i)) != 0); //rising clock edge MOSI  

        SCLK = 1;

        RDBUF = MISO;                       //falling clock edge MISO
        SPI_RD |= (RDBUF << (23 - i));     
         
    }

    CS = 1;

    if((SPI_RD  & 0x800000) == 0)  //verify the right command is uploaded to the device
    return TRUE;                    //reture TRUE State Flag , 0x87, 0x00
    else
    return FALSE;  
}

/********************************************************************************
 * @discription : uint8 SPI_Wr_Reg(uint8 Data, uint8 Addr)
 ********************************************************************************/
uint8 SPI_Rd_Reg(uint8 Addr) 
{
    uint32 Cmd = 0;
    uint32 RDBUF = 0, SPI_RD = 0;
    uint8  Data;               //the content of the register
    uint8  i;

    Cmd = (((((Cmd << 4) | Addr) << 12) | 0x8e0000));

    while(!DR); //wait until is DR goes high

    CS = 0;

    for(i = 0;i < 24;i++) 
    {
        SCLK =0;

        MOSI = ((Cmd & (0x800000 >> i)) != 0); //rising clock edge MOSI  

        SCLK = 1;

        RDBUF = MISO;                       //falling clock edge MISO
        SPI_RD |= (RDBUF << (23 - i));        
    }

    CS = 1;

    Data = (uint8)(SPI_RD);

    if(((SPI_RD >> 8) & 0x0000ff)  == 0x8e)          //verify the right command is uploaded to the device
    return Data;                                  //reture State Flag & Ctrl1 Byte  
    else
    return 0xAA;
}

/********************************************************************************
 * @discription : uint8 MLX75308_SetPara(uint8 Para_Name,uint8 Set_val)
 ********************************************************************************/
//-----------------------------------------------------
//-----------------------------------------------------
//Para_Name		Vector		Max_value
//Tdem          	0x01		  0x0f
//Unity_Gain    	0x02		  0x01		  
//GAIN_ADJ_AA_A 	0x03		  0x07
//GAIN_ADJ_AA_B 	0x04		  0x07
//BW_ADJ_AA_A		  0x05		  0x07
//BW_ADJ_AA_B		  0x06		  0x07
//BW_SEL_LP_A	  	0x07		  0x03
//BW_SEL_LP_B	  	0x08		  0x03
//NP		        	0x09		  0x0f
//RF		        	0x0a		  0x07
//DACA	      		0x0b		  0xff
//DACB		      	0x0c		  0xff
//GAIN_BUF	    	0x0d		  0x01
//DC_ENCOMP       0x0e      0x01
//DC_COMP_IC1     0x0f      0x0f
//DC_COMP_IC2     0x10      0x0f
//DC_COMP_IC3     0x11      0x0f
//DC_COMP_IC4     0x12      0x0f
//DC_COMP_IC5     0x13      0x0f
//-----------------------------------------------------
//-----------------------------------------------------

uint8 MLX75308_SetPara(uint8 Para_Name,uint8 Set_val)
{
  uint8 Wr_Sgn;
  uint8 old_val,addr_AB;

  switch(Para_Name)    
  {
        case Tdem:
        {
    	  old_val = SPI_Rd_Reg(addr_SetAna);
      	  Set_val = (old_val & 0x0f) | ((Set_val << 0x04) & 0xf0);
      	  Wr_Sgn = SPI_Wr_Reg(Set_val,addr_SetAna);
    	}
      	break;
    	
      	case Tdc:
        {
    	  old_val = SPI_Rd_Reg(addr_SetAna);
      	  Set_val = (old_val & 0xF9) | (Set_val << 0x01);
      	  Wr_Sgn = SPI_Wr_Reg(Set_val,addr_SetAna);
    	}
      	break;
    //-----------------------------------------
        case Unity_Gain:
        {
      	    old_val = SPI_Rd_Reg(addr_SetAna);
        	Set_val = (old_val & 0xfe) | ((Set_val) & 0x01);
        	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_SetAna);
      	}
      	break;
    //----------------------------------------
        case GAIN_ADJ_AA_A:
    	case GAIN_ADJ_AA_B:
    	{
        	if(Para_Name == GAIN_ADJ_AA_A)
        	   addr_AB = addr_SetAL;
        	else
         	   addr_AB = addr_SetBL;
               
        	old_val = SPI_Rd_Reg(addr_AB);
          	Set_val = (old_val & 0x1f) | ((Set_val << 0x05) & 0xe0);
          	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_AB);
    	}
    	break;
    //-------------------------------------
    	case BW_ADJ_AA_A:
    	case BW_ADJ_AA_B:
    	{	
        	if(Para_Name == BW_ADJ_AA_A)
        	   addr_AB = addr_SetAL;
        	else
         	   addr_AB = addr_SetBL;
               
        	old_val = SPI_Rd_Reg(addr_AB);
          	Set_val = (old_val & 0xe3) | ((Set_val << 0x02) & 0x1c);
          	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_AB);
    	}
    	break;
    //----------------Set BW_SEL_LP---------------
    	case BW_SEL_LP_A:
    	case BW_SEL_LP_B:
    	{	
        	if(Para_Name == BW_SEL_LP_A)
        	   addr_AB = addr_SetAL;
        	else
         	   addr_AB = addr_SetBL;
               
        	old_val = SPI_Rd_Reg(addr_AB);
          	Set_val = (old_val & 0xfc) | ((Set_val) & 0x3);
          	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_AB);
    	}
    	break;
    //-----------------Set NP----------------------
    	case NP:
    	{
           	old_val = SPI_Rd_Reg(addr_SetPF);
        	Set_val = (old_val & 0x0f) | ((Set_val<<0x04) & 0xf0);
          	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_SetPF);
    	}
    	break;
    //-----------------Set RF----------------------
    	case RF:
    	{
           	old_val = SPI_Rd_Reg(addr_SetPF);
        	Set_val = (old_val & 0xf8) | ((Set_val) & 0x07);
          	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_SetPF);
    	}
    	break;
    //-----------------Set DAC---------------------
    	case DACA:                  
    	case DACB:
    	{
        	if(Para_Name == DACA)
        	   addr_AB = addr_SetAH;
        	else
         	   addr_AB = addr_SetBH;
               
               Wr_Sgn = SPI_Wr_Reg(Set_val,addr_AB);
    	}
    	break;

    	case GAIN_BUF:
    	{

    	}
    	break;
    //---------------------------------------
      case EN_DCCOMP:
      {
        old_val = SPI_Rd_Reg(addr_SetPF);
    	Set_val = (old_val & 0xf7) | ((Set_val << 3) & 0x08);
      	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_SetPF);
      }
      break;
    //---------------------------------------
      case DC_COMP_IC1:
      {
        old_val = SPI_Rd_Reg(addr_Rst);
    	Set_val = (old_val & 0x0f) | ((Set_val << 4) & 0xf0);
      	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_Rst);
      }
      break;
     //---------------------------------------
      case DC_COMP_IC2:
      {
        old_val = SPI_Rd_Reg(addr_DCComp1);
    	Set_val = (old_val & 0xf0) | (Set_val & 0x0f);
      	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_DCComp1);
      }
      break;
      //---------------------------------------
      case DC_COMP_IC3:
      {
        old_val = SPI_Rd_Reg(addr_DCComp2);
    	Set_val = (old_val & 0x0f) | ((Set_val << 4) & 0xf0);
      	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_DCComp2);
      }
      break;
      //---------------------------------------
      case DC_COMP_IC4:
      {
        old_val = SPI_Rd_Reg(addr_DCComp2);
    	Set_val = (old_val & 0xf0) | (Set_val & 0x0f);
      	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_DCComp2);
      }
      break;
      //---------------------------------------
      case DC_COMP_IC5:
      {
        old_val = SPI_Rd_Reg(addr_Tamb);
    	Set_val = (old_val & 0x0f) | ((Set_val << 4) & 0xf0);
      	Wr_Sgn = SPI_Wr_Reg(Set_val,addr_Tamb);
      } 
      break;
    	default:Wr_Sgn = 0;
    	break;
  }

}

/********************************************************************************
 * @discription : uint8 SPI_Rd_Mchan(uint8 Mnsr_chan)
 ********************************************************************************/
 
uint8 SPI_Rd_Mchan(uint8 Mnsr_chan) 
{
  uint8 i,j,ch,RD_NB;
  uint16 temp,RDBUF;
  uint8 Output_Nbr = 0;
  RDBUF  = 0;
  temp = 0;
  ch = 0x0;
  
  MLX75308_RxFrame.data_field[2] = 0;
  
  if((Mnsr_chan & Temp) != 0) Output_Nbr ++;
  if((Mnsr_chan & PDA) != 0)  Output_Nbr = 3 + Output_Nbr;
  if((Mnsr_chan & PDB) != 0)  Output_Nbr = 3 + Output_Nbr;
  if((Mnsr_chan & PDC) != 0)  Output_Nbr ++;
  if((Mnsr_chan & PDD) != 0)  Output_Nbr ++;
  if((Mnsr_chan & PDE) != 0)  Output_Nbr ++;  
  
  while (!DR);     //wait until is DR goes high
  
  CS = 0;
  
  // RO command
  SCLK = 0;
  for(i = 0;i < 16;i++)          
  {
    MOSI = ((RO & (0x8000 >> i)) != 0);  

    SCLK = 1;

    Delay_Nus(1); //
    
    SCLK = 0;
    RDBUF = MISO;
    temp |= (RDBUF << (15 - i));     
  }
  
  MLX75308_RxFrame.StateFlag = (uint8) ((temp >> 8) & 0x00ff);
  MLX75308_RxFrame.CtrlByte1 = (uint8) (temp);
  
  MOSI = 0;     //push down MOSI
  
  // Output Frame 
  temp = 0;
    
  for(j = 0;j < (Output_Nbr);j++)
  {  
    for(i = 0;i < 16;i++) 
    {  
        SCLK =0; 
        Delay_Nus(1); //
        SCLK = 1;

        RDBUF = MISO;
        temp |= (RDBUF << (15 - i));
    }
    MLX75308_RxFrame.data_field[j] = temp;
    temp = 0; 
  }
     
  for (i=0;i<8;i++) 
  {
 
      SCLK =0; 
      Delay_Nus(1);
      SCLK = 1;
     
      RDBUF = MISO;
      ch |= (uint8)(RDBUF << (7 - i));
     
  }
  
  MLX75308_RxFrame.CRC = ch;
  
  CS = 1;
  
  if (MLX75308_RxFrame.CRC == 0)       //check the transmission is error free
  return TRUE;
  else
  return FALSE;
   
}


/********************************************************************************
 * @discription : void MLX75308_Meansure(uint8 Mnsr_chan)
 ********************************************************************************/
//------------------------------------------
//------------------------------------------
//Temp      	0x80	//1000_0000
//PDA       	0x10	//0001_0000
//PDB    	  	0x08	//0000_1000
//PDC    	  	0x04	//0000_0100
//PDD    	  	0x02	//0000_0010
//PDE	      	0x01	//0000_0001
//-------------------------------------------
void MLX75308_Meansure(uint8 Mnsr_chan)
{
    uint8 old_val,set_val;
    uint8 Wr_Sgn;
    uint16 SM_reg = 0;
    uint16 TempCnt;
    
    SM_reg = (Mnsr_chan & 0x80);
    if((Mnsr_chan & 0x07) != 0x0)
    {
       SM_reg = SM_reg | 0x40;
    
    }
    
    if((Mnsr_chan & PDA) == PDA)
       SM_reg = SM_reg | 0x34;    // M4 M3 M1 =1   PDA DC & Brust
    if((Mnsr_chan & PDB) == PDB)
       SM_reg = SM_reg | 0x2a;    // M4 M2 M0 =1   PDB DC & Brust
                                 
    SM_reg = 0xD000 | SM_reg;
    SPI_Wr_Cmd(SM_reg);
    
    Delay_Ms(1);                 //Measure Delay, very important

    SPI_Rd_Mchan(Mnsr_chan);

}

