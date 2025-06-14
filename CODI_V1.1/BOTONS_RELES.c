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