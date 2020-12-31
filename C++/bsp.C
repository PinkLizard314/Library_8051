//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|

#include "bsp.h"

struct STBuffer Buf0 ={0,0,0,0,0,0,0,0,0,0};
struct STBuffer Buf1 ={0,0,0,0,0,0,0,0,0,0};
unsigned char __xdata *Ctrl_DLS = (unsigned char __xdata *)REG_CTRL;
unsigned char __xdata *Busy_DLS = (unsigned char __xdata *)REG_BUSY;
unsigned char __xdata *DataW_DLS = (unsigned char __xdata *)REG_DATAW;
unsigned char __xdata *DataR_DLS = (unsigned char __xdata *)REG_DATAR;


void LEDDallas (bool state)
{
  P3_bit.P35_T1 = !state; 	
}


bool SWDallas1 (void)
{
  return (P3_bit.P32_INT0); 	
}


bool SWDallas2 (void)
{
  return (P3_bit.P33_INT1); 	
}
	
	
bool SWDallas3 (void)
{
  return (P3_bit.P34_T0); 	
}


void SendSP0 (unsigned char data)
{ 
  while (!SCON0_bit.TI_0);
  SCON0_bit.TI_0 = 0;
  SBUF0 = data;
}


void SendSP1 (unsigned char data)
{
  while (!SCON1_bit.TI_1);
  SCON1_bit.TI_1 = 0; 
  SBUF1 = data;
}
 

unsigned char ReadSP0 (void)
{
  while (!SCON0_bit.RI_0);
  SCON0_bit.RI_0 = 0;          
  return (SBUF0);
}


unsigned char ReadSP1 (void)
{
  while (!SCON1_bit.RI_1);
  SCON1_bit.RI_1 = 0;          
  return (SBUF1);
}


void InitPS0(unsigned int reload_value,bool state_ISR)
{
  T2CON |= 0x30;                            
  SCON0 |= 0x50;             
  RCAP2L = reload_value & 0x00FF;
  RCAP2H = reload_value>>8;
  T2CON_bit.TR2 = 1;				               
  SCON0_bit.TI_0 = 0;
  if(state_ISR) IE_bit.ES0 = ON;
}


void InitPS1(unsigned int reload_value,bool state_ISR)
{
  SCON1 = 0x50;             
  TMOD  = TMOD | 0x20;              
  TH1   = (unsigned char)reload_value;
  WDCON_bit.SMOD_1 = 1;                        
  TCON_bit.TR1   = 1;                                  
  SCON1_bit.TI_1 = 0;
  if(state_ISR) IE_bit.ES1 = ON;
}


bool SCL_DLS_IN (void)
{
  return (P3_bit.P35_T1);              
}


void SCL_DLS_OUT (bool state)
{
  P3_bit.P35_T1 = state;              
}
 

bool SDA_DLS_IN (void)
{          
  return (P3_bit.P34_T0);
}


void SDA_DLS_OUT (bool state)
{
  P3_bit.P34_T0 = state;
}


void SCK_DLS (bool state)
{
  P1_bit.P13_TXD1 = state;
}


void MOSI_DLS (bool state)
{
  P1_bit.P12_RXD1 = state;
}


bool MISO_DLS(void)
{
  return(P1_bit.P11_T2EX);
}

void CS_MCP (bool state)
{
  P1_bit.P14_INT2 = state;
}


void CS_TLV (bool state)
{
  P1_bit.P15_INT3 = state;
}


bool EOC_TLV (void)
{
  return(P1_bit.P17_INT5);
}


void LCDCtrl_DLS(unsigned char data)
{
  *Ctrl_DLS = data; 
}


bool LCDBusy_DLS (void)
{
  return (*Busy_DLS & BUSY);
}


void LCDDataW_DLS (unsigned char data)
{
  *DataW_DLS = data;
}


unsigned char LCDDataR_DLS (void)
{
  return(*DataR_DLS);
}


void ISRSlct(enum EISRSelect eSelect, bool state)
{
  switch (eSelect)
  {
    case TMR0   : IE_bit.ET0 = state; break;
    case TMR1   : IE_bit.ET1 = state; break;
    case TMR2   : IE_bit.ET2 = state; break;
    case SP0    : IE_bit.ES0 = state; break;
    case SP1    : IE_bit.ES1 = state; break;            
    case INT0   : IE_bit.EX0 = state; break;
    case INT1   : IE_bit.EX1 = state; break; 
    case INT2   : EIE_bit.EX2 = state; break;
    case INT3   : EIE_bit.EX3 = state; break;
    case INT4   : EIE_bit.EX4 = state; break;
    case INT5   : EIE_bit.EX5 = state; break;
    case INTWD  : EIE_bit.EWDI = state; break;
    case ETINT0 :
	  IE_bit.EX0 = state;
	  TCON_bit.IT0 = state;
      break;
    case ETINT1 : 
	  IE_bit.EX1 = state;
	  TCON_bit.IT1 = state;
      break;
  }
}
       

#pragma vector = RI_0_int
__interrupt void ISR_Serial0 (void)											 												
{
  unsigned char *PtrBuf = BUFFER0;
  
  if (SCON0_bit.RI_0)
  {
    *(PtrBuf + Buf0.IndiceIn) =  SBUF0;				
    Buf0.IndiceIn += 1;
    Buf0.IndiceIn &= 0x07;
    SCON0_bit.RI_0 = 0;
  }
}	
	

#pragma vector = RI_1_int
__interrupt void ISR_Serial1 (void)										 												
{
  unsigned char *PtrBuf = BUFFER1;
  
  if (SCON1_bit.RI_1)
  {
    *(PtrBuf + Buf1.IndiceIn) =  SBUF1;				
    Buf1.IndiceIn += 1;
    Buf1.IndiceIn &= 0x07;
    SCON1_bit.RI_1 = 0;
  }	
}