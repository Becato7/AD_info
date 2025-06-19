#include <AT89C5131.h> 						//Crida de la llibreria AT89C5131.h

#define main_screen 	0						//Definim l'estat main_screen
#define temp_screen 	1						//Definim l'estat temp_screen
#define hum_screen 		2						//Definim l'estat hum_screen
#define motor_screen 	3						//Definim l'estat motor_screen
#define ventilator_screen 	4			//Definim l'estat ventilator_screen
#define pump_screen 	5						//Definim l'estat pump_screen

float fast_log(float x);																//Declarem la funció fast_log(float x)
unsigned int calcular_temperatura(unsigned int adc12);	//Declarem la funció calcular_temperatura(unsigned int adc12)
void state_machine(unsigned int temp, unsigned int hum);								//Declarem la funció state_machine(unsigned int lectura)