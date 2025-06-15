#include <AT89C5131.h>  	//Crida de la llibreria AT89C5131.h

sbit LED_AIGUA = P2^1;		//Declarem el pin P2^1 com a LED_AIGUA
sbit LED_REG = P2^0;			//Declarem el pin P2^0 com a LED_AIGUA
sbit RELE4 = P2^5;				//Declarem el pin P2^5 com a RELE4 que correspon a la bomba
sbit RELE3 = P2^4;				//Declarem el pin P2^4 com a RELE3 que correspon al ventilador
sbit RELE2 = P2^3;				//Declarem el pin P2^3 com a RELE2 que correspon al motor
sbit RELE1 = P2^2;				//Declarem el pin P2^2 com a RELE1 que correspon al motor

sbit B_LEFT  = P0^3;			//Declarem el pin P0^1 com a B_LEFT
sbit B_RIGHT = P0^4;			//Declarem el pin P0^4 com a B_RIGHT
sbit B_UP    = P0^0;			//Declarem el pin P0^0 com a B_UP
sbit B_DOWN  = P0^2;			//Declarem el pin P0^2 com a B_DOWN
sbit B_OK    = P0^1;			//Declarem el pin P0^1 com a B_OK

void delay(unsigned int ms);								//Declarem la funció delay(void)
void control_porta(unsigned char control);	//Declarem la funció control_porta(unsigned char control)
