//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|

#include "I2C.h"

void Wait (unsigned int len);

bit Flag_ACK;

void InitI2C(void)
{
  SCL = LOW;
  SDA = LOW;
  Wait(2);
}

void I2CStart(void)
{	
  SDA = HIGH;
  SCL = HIGH;
  Wait(1);
  SDA = LOW;
  Wait(1);	
  SCL = LOW;
  Wait(2);
}

void I2CStop(void)
{
  SDA = LOW;
  Wait(1);
  SCL = HIGH;
  Wait(1);
  SDA = HIGH;
  Wait(1);
}

void vI2C_ClkPulse (void)
{
  SCL = HIGH;
  Wait(1);
  SCL = LOW;
}

void I2CWrite (unsigned char data)
{
  for(unsigned char i = 0; i<8; i++)
  {
	SDA = data>>7;
	Wait(1);
	I2C_ClkPulse();
	data = data<<1;
	Wait(1);
  }	
  SDA = HIGH;
  Wait(3);
  SCL = HIGH;
  Flag_ACK = SDA;
  Wait(1);
  SCL = LOW;	
}

/* This function may be called in a FOR loop
to receive several data. The same count must
be apply to the loop and n_data. To receive only
one byte, n_data = 1.*/

unsigned char I2CRead(unsigned char n_data)
{
  unsigned char data = 0;
  static unsigned char count = 0;

  SDA = HIGH;
  for(unsigned char i = 0; i<8; i++)
  {
	SCL = HIGH;
	data = data<<1;
	data |= SDA;
	SCL = LOW;
  }
	
  count++;
	
  if (count == n_data)             // NOACK
  {
	count = 0;
	SDA = HIGH;
	I2C_ClkPulse();
  }
  else                               // ACK
  {
	SDA = LOW;
	I2C_ClkPulse();
  }
	
  return (data);
}

void Wait (unsigned int len)
{
  for (unsigned int i = 0; i < len; i++);
}