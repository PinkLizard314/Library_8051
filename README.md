# Library_8051
MCU original : Dallas DS89C450

C documents were written with KEIL IDE.

C++ documents were written with IAR 8051.

Hardware related functions are in BCP.c.
All classes must be declared with those
functions as parameters.
 
Files with identical name in both C and C++
folders have the same functionalities, 
one done with functions, the other with classes
and methods.

The dev board used made use of the parallel
BUS with A0-A7 and D0-D7 on port 0 and
A8-A15 on port 2. 

An IC allows for some CS selection through
the value of A0-A7 (with a latch present to keep 
the values available while displaying D0-D7).

Other characteristics:

Push button active on 0 on P3_2, P3_3, P3_4

LED active on 0 on P3_5

FTDI RS232 on Serial Port 0 (P3_0,P3_1)

8-1-0-no handshake

crystal frequency : 11.092MHz
