#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "lin.h"
#include "lin_app.h"


/********************************************************************************
 * @discription : uint8 LINSendChar(uint8 brk, uint8 ch) 
 ********************************************************************************/
uint8 LinSendChar(uint8 brk, uint8 ch) 
{
    uint8 i,j;
  
    while(!(SCI0SR1&0x80))
    {
        _FEED_COP(); /* feeds the dog */
    }
    i = LIN_DATA;
    j = 0;
    i = 0;
    
    if((SCI0ASR1 & 0x02))
    {
        SCI0ASR1 = SCI0ASR1 | 0x02;
    }
  

    if(brk)    // if break field, transmit one break character (13-14 bits of dominant value)
    {
        SCI0CR2 |= 0x01;
        SCI0CR2 &= ~0x01;     
    } 
    else 
    {
        LIN_DATA = ch;
    }
  
    while(!(SCI0SR1 & 0x40))   // Waits until Transmission Complete Flag is clear(TC = 1)
    {
        _FEED_COP(); /* feeds the dog */
        if(j > 200) 
        {
            j = 0;
            i ++;
            if(i > 200)
            {
                return (FALSE);      //Send timeout
            }
        }         
        else 
        {
            j++;
        }
    }

    if((SCI0ASR1 & 0x02))
    {
        SCI0ASR1 = SCI0ASR1 | 0x02;
        return (FALSE);
    } 

    return(TRUE);
  
} 

/********************************************************************************
 * @discription : uint8 LinCalcParity(uint8 id) 
 ********************************************************************************/
uint8 LinCalcParity(uint8 id) 
{
    uint8 parity, p0, p1;

    parity = id;
    p0 = (BIT(parity,0)^BIT(parity,1)^BIT(parity,2)^BIT(parity,4))<<6;
    p1 = (~(BIT(parity,1)^BIT(parity,3)^BIT(parity,4)^BIT(parity,5)))<<7;
    parity |= (p0|p1);
    return parity;
}


/********************************************************************************
 * @discription : uint8 LINCalcChecksum(uint8 *data) 
 ********************************************************************************/
 
uint8 LinCalcChecksum(uint8 *data) 
{
    uint16 sum = 0;
    uint8 i;
  
    for(i=0; i < MAX_DATA; i++) 
    {
        sum += data[i];
        if(sum&0xFF00)
            sum = (sum&0x00FF) + 1;         //adds carry
    }
    
    sum ^= 0x00FF;                          // complement
    return (uint8)sum;

}

/********************************************************************************
 * @discription : uint8 EnhancedLINCalcChecksum(uint8 *data, uint8 val) 
 ********************************************************************************/
uint8 EnhancedLinCalcChecksum(uint8 *data, uint8 val) 
{
    unsigned int sum = 0;
    uint8 i;
  
    sum += val;
    
    if(sum & 0xFF00)
        sum = (sum&0x00FF) + 1;
  
    for(i=0; i < MAX_DATA; i++) 
    {
        sum += data[i];
        
        if(sum & 0xFF00)
            sum = (sum&0x00FF) + 1;        //adds carry
    }
    
    sum ^= 0x00FF;                         //complement
    return (uint8)sum;  
}

/********************************************************************************
 * @discription : Bool LinSndMsg(struct lin_message msg,uint8 DTC) 
 ********************************************************************************/
 
uint8 LinSndMsg(struct Lin_message msg,uint8 DTC) 
{
    unsigned char check_sum, i;

    for(i=0; i< MAX_DATA; i++) 
    {
        // Send data field
        if(!LinSendChar(FALSE, msg.data_field[i]))
            return(FALSE);
    }

    if(DTC == 0xFF) 
        check_sum = LinCalcChecksum(msg.data_field);                            //DTC CRC
    
    else  
        check_sum = EnhancedLinCalcChecksum(msg.data_field, rx.protected_id);   //Enhanced CRC for LIN 2.0
          
    // Send checksum field
    if(!LinSendChar(FALSE,check_sum))
        return(FALSE);
   
    rx.state = IDLE;    
                 
    return(TRUE);  
}

/********************************************************************************
 * @discription : Bool Lin_chkparity(uint8 parity_id) 
 ********************************************************************************/
 
uint8 Lin_chkparity(uint8 parity_id) 
{
    uint8 id, calc_parity_id;
    
    id = parity_id & 0x3f;
    calc_parity_id = LinCalcParity(id);
    
    if(calc_parity_id == parity_id) 
        return (TRUE);
    else 
        return (FALSE);

}

void Lin_send_break(void) 
{
  SCI0CR2 |= 0x01;
  SCI0CR2 &= ~0x01;
}
