//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|
	
#include <stdarg.h>
#include "Serial.h"

void DECtoUART (unsigned int value);
	void OneDGTtoUART (unsigned int value);
	void TwoDGTtoUART (unsigned int value);
	void ThreeDGTtoUART (unsigned int value);
	void FourDGTtoUART (unsigned int value);
	void FiveDGTtoUART (unsigned int value);

void HEXtoUART (unsigned int value);
	void BYTEtoUART (unsigned char value);
	void INTtoUART (unsigned int value);

void BINtoUART (unsigned int value);
	void ByteBINtoUART(unsigned char value);
	void IntBINtoUART(unsigned int value);
		
struct STBuffer Buf0 = {0,0,0,0,0,0,0,0,0};
struct STBuffer Buf1 = {0,0,0,0,0,0,0,0,0};
bit Flag_Buf0 = 0;
bit Flag_Buf1 = 0;

/* Baudrate from Timer2 */
void InitSP0(unsigned int reload_value, bit state_ISR)
{
  T2CON |= 0x30;                          
  SCON0 |= 0x50;             
  RCAP2L = reload_value & 0xFF;
  RCAP2H = reload_value>>8;
  TR2 = 1;
  TI_0 = 1;
  if(state_ISR) ES0 = 1;
}

/* Baudrate from Timer1 */
void InitSP1(unsigned char reload_value,bit state_ISR)
{
  SCON1 = 0x50;              
  TMOD  = TMOD | 0x20;              
  TH1   = reload_value;
  SMOD_1 = 1;                        
  TR1   = 1;  
  TI_1 = 1;  
  if(state_ISR) ES1 = 1;
}

void WaitSP0(void)
{
  while (!TI_0);
  TI_0 = 0;
}

void WaitSP1(void)
{
  while (!TI_1);
  TI_1 = 0;
}

void SendSP0(unsigned char data)
{
  WaitSP0();
  SBUF0 = data;
}

void SendSP1(unsigned char data)
{
  WaitSP1();
  SBUF1 = data;	
}

unsigned char ReadSP1 (void)
{
  REN_1 = 1;
  while (!RI_1)
  REN_1 = 0;  
  RI_1 = 0;
  return (SBUF1);
}

/* Getchar, Getkey, Getint and Printf only available on SP0 */
unsigned char Getchar(void)
{
  unsigned char value;

  while (!RI_0);
  RI_0 = DOWN;
  value = SBUF0;
  SendSP0 (value);
  return(value);
}

unsigned char Getkey(void)
{
  while (!RI_0);
  RI_0 = DOWN;
  return(SBUF0);
}

unsigned int Getint(void) // to get a numerical value < 65 536
{
  unsigned int temp = 0;
  unsigned char key = 0x30;

  while (key != ENTER)
  {
    temp *= 10;
    key -= 0x30;
    temp += key;
    key = Getchar();
  }
  return (temp);
}

/* 8 bytes circular buffer available on both SP.
state_ISR (InitSPn()) and EA must be HIGH to enable.
GetBufn() must be called first, then Flag_Bufn checked */
unsigned char Getbuf0(void)                      
{
  static unsigned char IndiceOut = 0;
  unsigned char *PtrBuf = &Buf0.Case0;
  unsigned char value = 0;

  if (IndiceOut != Buf0.IndiceIn)
  {
    value = *(PtrBuf+IndiceOut);
    IndiceOut++;
    IndiceOut &= 0x07;
    Flag_Buf0 = 1;
  }
  return (value);
}

unsigned char Getbuf1(void)                               
{
  static unsigned char IndiceOut = 0;
  unsigned char *PtrBuf = &Buf1.Case0;
  unsigned char value = 0;

  if (IndiceOut != Buf1.IndiceIn)
  {
    value = *(PtrBuf+IndiceOut);
    IndiceOut++;
    IndiceOut &= 0x07;
    Flag_Buf1 = 1;
  }
  return (value);
} 

/* variables can only be char or int.          
%d = decimal                             
%x = hexadecimal                         
%b = binary                              
%% = %                                 
\n = Line Feed                  
\r = Carriage Return             
\t = tab                            */  
void Printf(const char Array[], ...)                                             
{
  unsigned int value;
  unsigned char i = 0;

  va_list args;
  va_start (args, Array);

  while (*(Array+i) != 0x00)
  {
    if (*(Array+i) == '%')
    {
	  i++;
	
	  if (*(Array+i) == '%') SendSP0('%');
	  else value = va_arg(args, int);
	
	  if (*(Array+i) == 'd')DECtoUART(value);
	  else if (*(Array+i) == 'x')HEXtoUART(value);
	  else if (*(Array+i) == 'b') BINtoUART(value);

    }
    else if (*(Array+i) == '\n')
    {
	  SendSP0(0x0A);
	  SendSP0(0x0D);
    }
    else
    {
	  SendSP0(*(Array+i));
    }
    i++;
  }
  va_end(args);
}
 
void ISR_Serial0(void) interrupt 4											 												
{
  unsigned char *PtrBuf = &Buf0.Case0;
  
  if (RI_0)
  {
	*(PtrBuf + Buf0.IndiceIn) =  SBUF0;				
	Buf0.IndiceIn += 1;
	Buf0.IndiceIn &= 0x07;
	RI_0 = 0;
  }
}	
	
void ISR_Serial1(void) interrupt 7																				
{
  unsigned char *PtrBuf = &Buf1.Case0;
  
  if (RI_1)
  {
	*(PtrBuf + Buf1.IndiceIn) =  SBUF1;				
	Buf1.IndiceIn += 1;
	Buf1.IndiceIn &= 0x07;
	RI_1 = 0;
  }	
} 
  
void DECtoUART(unsigned int value)
{
  if (value < 10) OneDGTtoUART (value);        
  else if (value < 100) TwoDGTtoUART (value);
  else if (value < 1000) ThreeDGTtoUART (value);
  else if (value < 10000) FourDGTtoUART (value);
  else if (value >= 10000) FiveDGTtoUART (value);
}

void OneDGTtoUART(unsigned int value)
{
  SendSP0((char)value+0x30);
}

void TwoDGTtoUART(unsigned int value)
{
  SendSP0((char)(value/10)+0x30);
  OneDGTtoUART (value%10);
}

void ThreeDGTtoUART(unsigned int value)
{
  SendSP0((char)(value/100)+0x30);
  TwoDGTtoUART (value%100);
}

void FourDGTtoUART(unsigned int value)
{
  SendSP0((char)(value/1000)+0x30);
  ThreeDGTtoUART (value%1000);
} 

void FiveDGTtoUART(unsigned int value)
{
  SendSP0((char)(value/10000)+0x30);
  FourDGTtoUART (value%10000);
} 

void HEXtoUART(unsigned int value)
{
  if (value < 256) BYTEtoUART((char)value);
  else INTtoUART (value);
}

void BYTEtoUART(unsigned char value)
{
  if((value>>4) < 10) SendSP0((value>>4)+0x30);
  else SendSP0((value>>4)+0x37);
  if((value & 0x0F) < 10) SendSP0((value & 0x0F)+0x30);
  else SendSP0((value & 0x0F)+0x37);
}

void INTtoUART(unsigned int value)
{          
  BYTEtoUART((char)(value>>8));
  BYTEtoUART((char)(value & 0xFF));
}

void BINtoUART(unsigned int value)
{
if (value < 256) vBIN8BITtoUART((char)value);
else vBIN16BITtoUART (value);    
}

void ByteBINtoUART(unsigned char value)
{
  for(unsigned char i = 0; i<4; i++)
  {
    SendSP0((value>>7)+0x30);
    value <<= 1;
  }
  SendSP0(' ');
  for(i = 0; i<4; i++)
  {
    SendSP0((value>>7)+0x30);
    value <<= 1;
  }
}

void IntBINtoUART(unsigned int value)
{
  ByteBINtoUART((char)(value>>8));
  SendSP0(' ');
  ByteBINtoUART((char)(value & 0xFF));    
}
        

