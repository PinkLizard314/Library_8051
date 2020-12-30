//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|

#ifndef SPIH
  #define SPIH
  
#define MISO      	P1_1	
#define MOSI		P1_2                   // RX1
#define SCK			P1_3                   // TX1
 	
#ifndef HIGH
	#define HIGH 	1
#endif
#ifndef LOW
	#define LOW 	0
#endif

void SPIStart(unsigned char target);
void SPIStop(unsigned char target);
void SPIWrite(unsigned char data);
unsigned char SPIRead(void);                
unsigned char RVRSByte(unsigned char data);
	

struct STByte
{
  unsigned char bit0: 1;
  unsigned char bit1: 1;
  unsigned char bit2: 1;
  unsigned char bit3: 1;
  unsigned char bit4: 1;
  unsigned char bit5: 1;
  unsigned char bit6: 1;
  unsigned char bit7: 1;
};

union UNByte
{
  unsigned char whole;
  struct STByte split;
};
#endif