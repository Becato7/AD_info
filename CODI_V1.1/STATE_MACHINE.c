#include "STATE_MACHINE.h"  	//Crida de la llibreria STATE_MACHINE.h
#include "lcd.h"					  	//Crida de la llibreria lcd.h
#include "BOTONS_RELES.h"  		//Crida de la llibreria BOTONS_RELES.h
#include "MCP3302.h"  				//Crida de la llibreria MCP3302.h

unsigned char PANTALLA = 0;						//Declaraci� de la variable PANTALLA on es guarda en quina pantalla es troba en temps real
unsigned char desenes = 0;						//Declaraci� de la variable desenes
unsigned char unitats = 0;						//Declaraci� de la variable unitats
unsigned char decimal = 0;						//Declaraci� de la variable decimal
unsigned int temperature_C = 0;				//Declaraci� de la variable temperature_C
unsigned int temperatura_actual = 0;	//Declaraci� de la variable temperatura_actual
unsigned int temperatura_max = 320;		//Declaraci� de la variable temperatura_max
unsigned int humitat_actual = 0;			//Declaraci� de la variable humitat_actual
unsigned int humitat_min = 320;				//Declaraci� de la variable humitat_min
unsigned char motor_mode = 0;					//Declaraci� de la variable motor_mode
unsigned char ventilator_mode = 0;		//Declaraci� de la variable ventilator_mode
unsigned char pump_mode = 0;					//Declaraci� de la variable pump_mode
bit estat_porta = 0;									//Declaraci� de la variable estat_porta
unsigned char xdata linea4[16] = 			{' ',' ','.',' ','C',' ',' ',' ',' ',' ','.',' ','C',' ',' ',' '}; //Declaraci� de l'array linea4[16]
unsigned char xdata linea6[16] = 			{' ',' ','.',' ','%',' ',' ',' ',' ',' ','.',' ','%',' ',' ',' '}; //Declaraci� de l'array linea4[16]


float fast_log(float x) {							//Deficinici� de la funci� fast_log que permet calcular logaritmes aproximadament
		float y;													//Declaraci� de la variable y
		float y2;													//Declaraci� de la variable y2
    if (x <= 0.01) return -5.0;  			//Tornar un valor -5 si el numero a evaluar �s molt petit per evitar problemes
    y = (x - 1) / (x + 1);						//Interpolar
    y2 = y * y;												//Elevar al quadrat
    return 2 * y * (1 + y2 / 3);			//Calcular el logaritme
}

unsigned int calcular_temperatura(unsigned int adc12) {								//Deficinici� de la funci� calcular_temperatura que permet calcular la temperatura en funci� del valor de l'ADC que se li entri
    float voltatge = MCP3302_ToVoltage(adc12, 5.1);										//Passar del valor de l'adc al voltatje corresponent amb la funci� MCP3302_ToVoltage i el voltatje de refer�ncia a 5.1V
    float r_ntc = (voltatge * 10000.0) / (5.1 - voltatge);						//Obtenci� del valor de la resit�ncia a partir del voltatje del divisor de tenci� sabent que l'altre resist�ncia �s de 10k i el voltatje de refer�ncia �s de 5.1V
    float ln_ratio = fast_log(r_ntc / 10000.0);												//C�lcul del logaritme respecte el valor de laresist�ncia a 25�C
    float temp_K = 1.0 / ((1.0 / 298.15) + (1.0 / 3984.0) * ln_ratio);//C�lcul de la temperatura en graus kelvin
    return (unsigned int)((temp_K - 273.15) * 10);										//C�lcul de la temperatura en graus celsius
}

unsigned int calcular_humitat(unsigned int adc12) {
	float humitat;
	float voltatge_llegit;
    voltatge_llegit = MCP3302_ToVoltage(adc12, 5.0);  
    if (voltatge_llegit > 4.3f) voltatge_llegit = 4.3f; //4.4 �s el valor en sec i 2.1 �s el valor quan est�r submergit
    if (voltatge_llegit < 2.1f) voltatge_llegit = 2.1f;
    humitat = (4.3f - voltatge_llegit) / (4.3f - 2.1f) * 100.0f;
    return (unsigned int)(humitat*10);
}

void dividir_valor(unsigned int valor){		//Definici� de la funci� dividir_valor
		desenes = valor/100;									//Asignaci� de les desenes
		unitats = (valor/10)%10;							//Asignaci� de les unitats
		decimal = valor%10;										//Asignaci� de les decimal
}

void control_temp(void){									//Definici� de la funci� control_temp
	if(B_RIGHT == 0){												//Si s'apreta el boto right
		temperatura_max++;										//Augmenta la temperatura de llindar en 1 decima
	}else if(B_LEFT == 0){									//Si s'apreta el boto left
		temperatura_max--;										//Disminueix la temperatura llindar en 1 decima
	}
}

void control_hum(void){										//Definici� de la funci� control_hum
	if(B_RIGHT == 0){												//Si s'apreta el boto right
		humitat_min++;												//Augmenta la humitat de llindar en 1 decima
	}else if(B_LEFT == 0){									//Si s'apreta el boto left
		humitat_min--;												//Disminueix la humitat llindar en 1 decima
	}
}

void control_vent(void){									//Definici� de la funci� control_vent
	if(B_OK == 0){													//Si s'apreta el boto ok
		ventilator_mode++;										//Augmenta el mode del ventilador, entre OFF/ON/AUT
	}
	if(ventilator_mode == 3){								//Si passa del mode 2 (AUT)
		ventilator_mode = 0;									//Torna al mode 0 (OFF)	
	}
}

/*void control_motor(void){									//Definici� de la funci� control_motor
	if(B_RIGHT == 0){												//Si s'apreta el boto right
		motor_mode = 1;												//Es va al mode 1 que fa obrir la finestra
	}
	if(B_LEFT == 0){												//Si s'apreta el boto left
		motor_mode = 2;												//Es va al mode 2 que fa tancar la finestra
	}
	if(B_OK == 0){													//Si s'apreta el boto ok
		if(motor_mode == 0){									//Si s'est� en el mode OFF
			motor_mode = 3;											//Es va al mode AUT
		}
		if(motor_mode == 3){									//Si s'est� en el mode AUT
			motor_mode = 0;											//Es va al mode OFF
		}
	}
}*/

/*void control_pump(void){									//Definici� de la funci� control_pump
	if(B_OK == 0){													//Si s'apreta el boto ok
		pump_mode++;													//Augmenta el mode de la bomba, entre OFF/ON/AUT
	}
	if(pump_mode == 3){											//Si passa del mode 2 (AUT)										
		pump_mode = 0;												//Torna al mode 0 (OFF)	
	}
}*/

void control_reles(void){									//Definici� de la funci� control_reles
	switch(ventilator_mode){								//Evalua el mode de ventilator_mode
		case 0:																//Si �s 0 (OFF)
			RELE3 = 0;													//Agapa el ventilador
			break;
		case 1:																//Si �s 1 (ON)
			RELE3 = 1;													//Engega el ventilador
			break;
		case 2:																//Si �s 2 (AUT)
			if(temperature_C >= temperatura_max){//Si la temperatura actual �s m�s gran o igual a la llindar
				RELE3 = 1;												//Engega el ventilador
			if(estat_porta != 1){								//Si l'estat_porta �s 0 (avall)
				control_porta(1);									//Obrir la porta
				estat_porta = 1;									//Posem l'estat_porta a 1 per indicar quie la porta est� amunt
			}
			}else{															//En cas contrari
				RELE3 = 0;												//Apaga el ventilador
			if(estat_porta != 0){								//Si l'estat_porta �s 1 (amunt)
				control_porta(2);									//Tancar la porta
				estat_porta = 0;									//Posem l'estat_porta a 1 per indicar quie la porta est� avall
			}
			}
			break;
	}
	control_porta(0);												//Quan acaba deixa el ventialor desconectat
}

void state_machine(unsigned int temp, unsigned int hum){	//Declaraci� funci� state_machine
	//MENU
unsigned char code linea1[16] = "MENU            ";		//Deficini� array linea1
unsigned char code linea2[16] = "<-            ->";		//Deficini� array linea2
unsigned char code linea3[16] = "TEMP:   MAX.T:  ";		//Deficini� array linea3
unsigned char code linea5[16] = "HUM:    MIN.H:  ";		//Deficini� array linea5
//unsigned char code linea7[16] = "MOTOR           ";		//Deficini� array linea7
unsigned char code linea9[16] = "VENTILADOR      ";		//Deficini� array linea9
//unsigned char code linea10[16] = "BOMBA           ";	//Deficini� array linea10
unsigned char code txt_OFF[16]  = "OFF             ";	//Deficini� array txt_OFF
unsigned char code txt_ON[16]   = "ON              ";	//Deficini� array txt_ON
unsigned char code txt_AUT[16]  = "AUT             ";	//Deficini� array txt_AUT
//unsigned char code txt_DOWN[16]  = "DOWN            ";//Deficini� array txt_DOWN
//unsigned char code txt_UP[16]  = "UP              ";	//Deficini� array txt_UP
	humitat_actual = calcular_humitat(hum);				//Evaluem el valor actual de la temperatura amb el valor de l'ADC que s'ha entrat a la funci�
	temperature_C = calcular_temperatura(temp);				//Evaluem el valor actual de la temperatura amb el valor de l'ADC que s'ha entrat a la funci�
		if(B_DOWN == 0){																	//Si es prem el boto down
			PANTALLA++;																			//Augmenta l'estat de la pantalla
			if(PANTALLA == 6){															//Si el valor de la pantalla supera el valor m�xim de pantalles
				PANTALLA = main_screen;												//Torna a la pantalla principal
			}
			delay(200);																			//Delay de 200 ms per tenir temps de treure el dit del bot�
		}else if(B_UP == 0){															//Si es prem el boto up
			PANTALLA--;																			//Decrementa l'estat de la pantalla
			if(PANTALLA == 255){														//Si el valor de la pantalla supera el valor m�xim de pantalles
				PANTALLA = pump_screen;												//Torna a la pantalla pump_screen
			}
			delay(200);																			//Delay de 200 ms per tenir temps de treure el dit del bot�
		}
		if(PANTALLA == main_screen){											//Si est�s a la pantalla main_screen
			LCD_BEGIN(linea1, linea2);
		}
		else if(PANTALLA == temp_screen){									//Si est�s a la pantalla temp_screen
			control_temp();																	//Cridem la funci� de control_temp
			dividir_valor(temperature_C);										//Apliquem la funci� dividir valor a temperature_C
			linea4[0] = desenes+0x30;												//Escrivim a linea4 les desenes
			linea4[1] = unitats+0x30;												//Escrivim a linea4 les unitats
			linea4[3] = decimal+0x30;												//Escrivim a linea4 el decimal
			dividir_valor(temperatura_max);									//Apliquem la funci� dividir valor a temperatura_max
			linea4[8] = desenes+0x30;												//Escrivim a linea4 les desenes
			linea4[9] = unitats+0x30;												//Escrivim a linea4 les unitats
			linea4[11] = decimal+0x30;											//Escrivim a linea4 el decimal
			LCD_BEGIN(linea3, linea4);											//Escrivim les linies linea3 i linea4
		}
		else if(PANTALLA == hum_screen){									//Si est�s a la pantalla hum_screen
			control_hum();																	//Cridem la funci� de control_hum
			dividir_valor(humitat_actual);									//Apliquem la funci� dividir valor a humitat_actual
			linea6[0] = desenes+0x30;												//Escrivim a linea6 les desenes
			linea6[1] = unitats+0x30;												//Escrivim a linea6 les unitats
			linea6[3] = decimal+0x30;												//Escrivim a linea6 el decimal
			dividir_valor(humitat_min);											//Apliquem la funci� dividir valor a humitat_min
			linea6[8] = desenes+0x30;												//Escrivim a linea6 les desenes
			linea6[9] = unitats+0x30;												//Escrivim a linea6 les unitats
			linea6[11] = decimal+0x30;											//Escrivim a linea6 el decimal
			LCD_BEGIN(linea5, linea6);											//Escrivim les linies linea5 i linea6
		}
		else if(PANTALLA == motor_screen){								//Si est�s a la pantalla motor_screen
			/*control_motor();																//Cridem la funci� de control_motor
			if(motor_mode == 0){														//Si el motor_mode es 0
				LCD_BEGIN(linea7, txt_OFF);										//Escrivim les linies linea7 i txt_OFF
				control_porta(0);
			}else if(motor_mode == 1){											//Si el motor_mode es 1
				LCD_BEGIN(linea7, txt_UP);										//Escrivim les linies linea7 i txt_UP
				control_porta(1);															//Obrim la porta
				estat_porta = 1;															//Delcarem la porta com amunt
				motor_mode = 0;																//Tornem al motor_mode 0
			}else if(motor_mode == 2){											//Si el motor_mode es 2
				LCD_BEGIN(linea7, txt_DOWN);									//Escrivim les linies linea7 i txt_DOWN
				control_porta(2);															//Tanquem la porta
				estat_porta = 0;															//Delcarem la porta com avall
				motor_mode = 0;																//Tornem al motor_mode 0
			}
			else if(motor_mode == 3){												//Si el motor_mode es 3
				LCD_BEGIN(linea7, txt_AUT);										//Escrivim les linies linea7 i txt_AUT
			}*/
		}
		else if(PANTALLA == ventilator_screen){						//Si est�s a la pantalla ventilator_screen
			control_vent();																	//Cridem la funci� de control_vent
			if(ventilator_mode == 0){												//Si el ventilator_mode es 0
				LCD_BEGIN(linea9, txt_OFF);										//Escrivim les linies linea9 i txt_OFF
			}else if(ventilator_mode == 1){									//Si el ventilator_mode es 1
				LCD_BEGIN(linea9, txt_ON);										//Escrivim les linies linea9 i txt_ON
			}else if(ventilator_mode == 2){									//Si el ventilator_mode es 2
				LCD_BEGIN(linea9, txt_AUT);										//Escrivim les linies linea9 i txt_AUT
			}
		}else if(PANTALLA == pump_screen){								//Si est�s a la pantalla pump_screen
			/*control_pump();																	//Cridem la funci� de control_pump
			if(pump_mode == 0){															//Si el pump_mode es 0
				LCD_BEGIN(linea10, txt_OFF);									//Escrivim les linies linea10 i txt_OFF
			}else if(pump_mode == 1){												//Si el pump_mode es 1
				LCD_BEGIN(linea10, txt_ON);										//Escrivim les linies linea10 i txt_ON
			}else if(pump_mode == 2){												//Si el pump_mode es 2
				LCD_BEGIN(linea10, txt_AUT);									//Escrivim les linies linea10 i txt_AUT
			}*/
		}
		control_reles();																	//Apliquem el control dels reles
}