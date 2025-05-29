
#include "BOTONS_RELES.h"

void delay(unsigned int ms){
		unsigned int i,j;
	for (i=0;i<ms;i++)
		for (j=0;j<240;j++);
}

void control_leds(bit senyal_riego, bit falta_agua){
  LED_REG = senyal_riego;
	LED_AIGUA = falta_agua;
}

void control_bomba_ventilador(bit ventilador, bit bomba){
	RELE4 = bomba;
	RELE3 = ventilador;
}

void control_porta(unsigned char control){
	if(control == 1){					//Obrir la porta
		control_leds(1, 1);
		RELE1 = 1;
		RELE2 = 0;
		delay(5000);
		RELE1 = 0;
		RELE2 = 0;
	}else if (control == 2){	//Tancar la porta
		control_leds(1, 1);
		RELE1 = 0;
		RELE2 = 1;
		delay(5000);
		RELE1 = 0;
		RELE2 = 0;
	}else{										//Porta en OFF
		control_leds(0, 0);
		RELE1 = 0;
		RELE2 = 0;
	}
}
// código de los botones



/*
sbit MOTOR   P
sbit VENT    P
// DEFINES PRIVADOS
#define LEFT		1
#define RIGHT		2
#define UP			3
#define DOWN		4
#define OK			5
#define NONE		6

#define SCREEN_MAX		5	// puede cambiar, ahora hay 4 pantallas (3+1)
#define SCREEN_MIN		0	// SIEMPRE SERÁ 0

#define HUM_SCREEN		0
#define TEMP_SCREEN		1
#define BLINDS_SCREEN	2
#define VENT_SCREEN		3
#define WATER_SCREEN	4

// VARIABLES GLOBALES

unsigned char B_EVENT;		// nos dice el estado de los botones
unsigned char SCREEN = 0;		// indica en que pantalla estamos
bit temp_celsius = 1;
bit hum_percent = 1;

// FUNCIONES

void button_read (void){

    if (B_LEFT == 0) {
        B_EVENT = LEFT;
    } else if (B_RIGHT == 0) {
        B_EVENT = RIGHT;
    } else if (B_UP == 0) {
        B_EVENT = UP;
    } else if (B_DOWN == 0) {
        B_EVENT = DOWN;
    } else if (B_OK == 0) {
        B_EVENT = OK;
    } else {
        B_EVENT = NONE;
    }
}

void handle_buttons (void){
	switch (B_EVENT){
	
        case LEFT:
            if (SCREEN > SCREEN_MIN){
                SCREEN--;
            } break;

        case RIGHT:
            if (SCREEN < SCREEN_MAX){
                SCREEN++;
            } break;

        case OK:
            if (SCREEN == BLINDS_SCREEN){
                MOTOR = !MOTOR;

            } else if (SCREEN == VENT_SCREEN){
                 if (FC_0 == 1) {	// Persiana completamente cerrada -> Abrirla
                    VENT = 1;  		// Activa el actuador para abrir
                    while (FC_1 == 0){}	// Esperamos a que se abra (final de carrera FC_1)    
                    VENT = 0;  		// Parar el actuador cuando se abre completamente
                } 
                else if (FC_1 == 1) {	 // Persiana completamente abierta -> Cerrar
                    VENT = 1; 		 // Activa el actuador para cerrar
                    while (FC_0 == 0){}  // Esperamos a que se cierre (final de carrera FC_0)
                    VENT = 0;  		 // Parar el actuador cuando se cierra completamente
                }
	    }
            break;

        case UP:
            if (SCREEN == TEMP_SCREEN){
		temp_celsius = !temp_celsius;
	    } else if (SCREEN == HUM_SCREEN){
		hum_percent = !hum_percent;
            } break;

        case DOWN:
            if (SCREEN == TEMP_SCREEN){
		temp_celsius = !temp_celsius;
	    } else if (SCREEN == HUM_SCREEN){
		hum_percent = !hum_percent;
            } break;
    }

   B_EVENT = NONE;

}
*/