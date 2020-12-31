//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|


#ifndef BSPH
  #define BSPH
#define BUSY       0x80 
#define REG_CTRL  0x8000                       
#define REG_BUSY  0x8001                       
#define REG_DATAW 0x8002
#define REG_DATAR 0x8003

enum EISRSelect {TMR0,TMR1,TMR2,SP0,SP1,INT0,INT1,INT2,INT3,INT4,INT5,INTWD,ETINT0,ETINT1};

void LEDDallas (bool state);

bool SWDallas1 (void);
bool SWDallas2 (void);
bool SWDallas3 (void);

void InitPS0(unsigned int reload_value,bool state_ISR);
void InitPS1(unsigned int reload_value,bool state_ISR);
void SendSP0 (unsigned char data);
void SendSP1 (unsigned char data);
unsigned char ReadSP0 (void);
unsigned char ReadSP1 (void);

bool SCL_DLS_IN (void);
void SCL_DLS_OUT (bool state);
bool SDA_DLS_IN (void);
void SDA_DLS_OUT (bool state);

void SCK_DLS (bool state);
void MOSI_DLS (bool state);
bool MISO_DLS(void);

void CS_MCP (bool state);
void CS_TLV (bool state);
bool EOC_TLV (void);

void LCDCtrl_DLS(unsigned char data);
bool LCDBusy_DLS (void);
void LCDDataW_DLS (unsigned char data);
unsigned char  LCDDataR_DLS (void);

void ISRSlct(enum EISRSelect eSelect, bool state);

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
  unsigned char IndiceOut;
};

extern struct STBuffer Buf0;
extern struct STBuffer Buf1;

#define BUFFER0   &Buf0.Case0
#define BUFFER1   &Buf1.Case0
	 
#endif