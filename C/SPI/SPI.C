//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|

#include "SPI.h"

void SPI_CLK_Pulse(void);
void Wait (unsigned int len);


void SPIStart(unsigned char target)
{  
  switch (target)
  {
    case 0: /*CS_IC_1 = LOW*/; break;
    case 1: /*CS_IC_2 = LOW*/; break;
	/* Etc. */
  }	
  Wait(1);
}

void SPIStop(unsigned char target)            
{
  switch (target)
  {
    case 0: /*CS_IC_1 = HIGH*/; break;
    case 1: /*CS_IC_2 = HIGH*/; break;
	/* Etc. */
  }
}

void SPI_CLK_Pulse(void)
{
  SKL = HIGH;
  Wait(1);
  SKL = LOW;
}

void SPIWrite(unsigned char data)     
{
  for(unsigned char i = 0; i<8; i++)
  {
    MOSI = data>>7;				
    SPI_CLK_Pulse();
    data <<= 1;
  }
}

unsigned char SPIRead(void)
{
  unsigned char data = 0;

  for(unsigned char i=0; i<8; i++)
  {		
	SCK = HIGH;
	data <<= 1;
	data |= MISO;
	Wait(1);		
	SCK = LOW;
  }
  return (data);
}

/* It is possible to use Serial Port 1 (mode 0)
for SPI protocol (only some ICs), but the endian 
is reversed (SPI sends MSB first, Serial LSB). 
This function is used to reverse the data to 
send or received. */

unsigned char RVRSByte(unsigned char data)                             
{
  union UNByte ByteIn;
  union UNByte ByteOut;
  
  ByteIn.whole = data;
  
  ByteOut.split.bit0 = ByteIn.split.bit7;
  ByteOut.split.bit1 = ByteIn.split.bit6;
  ByteOut.split.bit2 = ByteIn.split.bit5;
  ByteOut.split.bit3 = ByteIn.split.bit4;
  ByteOut.split.bit4 = ByteIn.split.bit3;
  ByteOut.split.bit5 = ByteIn.split.bit2;
  ByteOut.split.bit6 = ByteIn.split.bit1;
  ByteOut.split.bit7 = ByteIn.split.bit0;
  
  return (ByteOut.whole);  
}

void Wait (unsigned int len)
{
  for (unsigned int i = 0; i < len; i++);
}