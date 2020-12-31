//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|

#ifndef SERIALH
  #define SERIALH
    
#define KBHIT  	        RI_0
#define ENTER           0x0D
#define BACKSPACE       0x08
#define ESC             0x1B
#define SPACE           0x20
#define DEL             0x7F
#define TAB             0x09
            
#define SP0_57K    		0xFFFA 
#define SP0_28K    		0xFFF4
#define SP0_19K    		0xFFEE
#define SP0_9K     		0xFFDC

#define SP1_57K   		0xFF
#define SP1_28K   		0xFE
#define SP1_19K   		0xFD             
#define SP1_9K    		0xFA

void InitSP0(unsigned int reload_value, bit state_ISR);
void InitSP1(unsigned char reload_value, bit state_ISR);
void WaitSP0(void);
void WaitSP1(void);
void SendSP0(unsigned char data);
void SendSP1(unsigned char data);
unsigned char ReadSP1(void);
unsigned char Getchar(void);
unsigned char Getkey(void);
unsigned int Getint(void);
unsigned char Getbuf0(void);
unsigned char Getbuf1(void);
void Printf(const char Array[], ...);

struct STBuffer
{
  unsigned char Case0;
  unsigned char Case1;
  unsigned char Case2;
  unsigned char Case3;
  unsigned char Case4;
  unsigned char Case5;
  unsigned char Case6;
  unsigned char Case7;
  unsigned char IndiceIn;
};

extern struct STBuffer Buf0;
extern struct STBuffer Buf1;
extern bit Flag_Buf0;
extern bit Flag_Buf1;
#endif