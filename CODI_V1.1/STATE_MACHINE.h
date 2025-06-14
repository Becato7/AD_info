#include <AT89C5131.h> 

#define main_screen 	0
#define temp_screen 	1
#define hum_screen 		2
#define motor_screen 	3
#define ventilator_screen 	4

float fast_log(float x);
unsigned int calcular_temperatura(unsigned int adc12);
void dividir_valor(unsigned int valor);
void control_temp(void);
void control_hum(void);
void control_vent(void);
void control_motor(void);
void state_machine(unsigned int lectura);