#include "BOTONS_RELES.h"			//Cridem la llibreria BOTONS_RELES.h

void delay(unsigned int ms){	//Definim la funci� delay a la que li entrem quants ms de delay volem
		unsigned int i,j;					//Declarem les variables per comptar i, j
	for (i=0;i<ms;i++)					//Bucle per cada ms
		for (j=0;j<240;j++);			//Bucle per comptar 1 ms
}

void control_porta(unsigned char control){		//Definim la funci� control_porta
	if(control == 1){														//Si l'entrada �s 1 llavors volem obrir la porta
		RELE1 = 1;																//El rel� 1 es tanca per tenir 12V a la borna positiva del motor
		RELE2 = 0;																//El rel� 2 s'obre per tenir 0V a la borna negativa del motor
		delay(500);																//Esperem 500 ms perque el motor giri
		RELE1 = 0;																//El rel� 1 s'obre per tenir 0V a la borna positiva del motor
		RELE2 = 0;																//El rel� 2 s'obre per tenir 0V a la borna negativa del motor
	}else if (control == 2){										//Si l'entrada �s 2 llavors volem tancar la porta
		RELE1 = 0;																//El rel� 1 s'obre per tenir 0V a la borna positiva del motor
		RELE2 = 1;																//El rel� 2 es tanca per tenir 12V a la borna negativa del motor
		delay(500);																//Esperem 500 ms perque el motor giri
		RELE1 = 0;																//El rel� 1 s'obre per tenir 0V a la borna positiva del motor
		RELE2 = 0;																//El rel� 2 s'obre per tenir 0V a la borna negativa del motor
	}else{																			//Si l'entrada �s 0 llavors volem deixar la porta est�tica
		RELE1 = 0;																//El rel� 1 s'obre per tenir 0V a la borna positiva del motor
		RELE2 = 0;																//El rel� 2 s'obre per tenir 0V a la borna negativa del motor
	}
}