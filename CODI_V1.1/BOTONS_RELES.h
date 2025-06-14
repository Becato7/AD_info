#include <AT89C5131.h> 

sbit LED_AIGUA = P2^1;
sbit LED_REG = P2^0;
sbit RELE4 = P2^5;
sbit RELE3 = P2^4;
sbit RELE2 = P2^3;
sbit RELE1 = P2^2;

// DEFINICIÓN DE LOS BITS DE LOS PUERTOS
sbit B_LEFT  = P0^3;
sbit B_RIGHT = P0^4;
sbit B_UP    = P0^0;
sbit B_DOWN  = P0^2;
sbit B_OK    = P0^1;

sbit FC_1    = P0^6;		// persiana completamente cerrada
sbit FC_0    = P0^5;		// persiana completamente abierta

void delay(unsigned int ms);
void control_leds(bit senyal_riego, bit falta_agua);
void control_porta(unsigned char control);
