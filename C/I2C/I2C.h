//    ____  ____  ____  ____ _________ ____  ____  ____  ____  ____  ____ 	   
//   ||P ||||i ||||n ||||k |||       |||L ||||i ||||z ||||a ||||r ||||d ||	  
//   ||__||||__||||__||||__|||_______|||__||||__||||__||||__||||__||||__||	  
//   |/__\||/__\||/__\||/__\|/_______\|/__\||/__\||/__\||/__\||/__\||/__\|	  
//   ||D ||||e ||||s ||||i ||||g ||||n ||			                      	   
//   ||__||||__||||__||||__||||__||||__||			                      	    
//   |/__\||/__\||/__\||/__\||/__\||/__\|

#ifndef I2CH
	#define I2CH
	
#define SDA 		P3_4
#define SCL 		P3_5	

#ifndef HIGH
	#define HIGH 	1
#endif
#ifndef LOW
	#define LOW 	0
#endif
 
void InitI2C(void);
void I2CStart(void);
void I2CStop (void);
void I2C_ClkPulse (void);
void I2CWrite(unsigned char data);
unsigned char I2CRead(unsigned char n_data);

extern bool Flag_ACK; 
#endif