#include "STATE_MACHINE.h"
#include "lcd.h"
#include "BOTONS_RELES.h"

unsigned char PANTALLA = 0;
unsigned char desenes = 0;
unsigned char unitats = 0;
unsigned char decimal = 0;
//MENU
//unsigned char code linea1[16] = {'M','E','N','U',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
//unsigned char code linea2[16] = {'<','-',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','-','>'};

//TEMPERATURE SCREEN
unsigned int temperatura_actual = 245;
unsigned int temperatura_max = 320;
unsigned char code linea3[16] = {'T','E','M','P',':',' ',' ',' ','M','A','X','.','T',':',' ',' '};
unsigned char linea4[16] = 			{' ',' ','.',' ','C',' ',' ',' ',' ',' ','.',' ','C',' ',' ',' '};

//HUMIDITY SCREEN
unsigned int humitat_actual = 245;
unsigned int humitat_min = 320;
unsigned char code linea5[16] = {'H','U','M',':',' ',' ',' ',' ','M','I','N','.','H',':',' ',' '};
unsigned char linea6[16] = 			{' ',' ','.',' ','%',' ',' ',' ',' ',' ','.',' ','%',' ',' ',' '};

//MOTOR SCREEN
unsigned char motor_mode = 0;
unsigned char code linea7[16] = {'M','O','T','O','R',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
unsigned char linea8[16] = 			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

//VENTILATOR SCREEN
unsigned char ventilator_mode = 0;
unsigned char code linea9[16] = {'V','E','N','T','I','L','A','D','O','R',' ',' ',' ',' ',' ',' '};
unsigned char linea10[16] = 		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

void dividir_valor(unsigned int valor){
		desenes = valor/100;
		unitats = (valor/10)%10;
		decimal = valor%10;
}

void control_temp(void){
	if(B_UP == 0){
		temperatura_max++;
	}else if(B_DOWN == 0){
		temperatura_max--;
	}
}

void control_hum(void){
	if(B_UP == 0){
		humitat_min++;
	}else if(B_DOWN == 0){
		humitat_min--;
	}
}

void control_vent(void){
	if(B_OK == 0){
		ventilator_mode++;
	}
	if(ventilator_mode == 4){
		ventilator_mode = 0;
	}
}

void control_motor(void){
	if(B_OK == 0){
		motor_mode++;
	}
	if(motor_mode == 4){
		motor_mode = 0;
	}
}

void state_machine(void){
		if(B_LEFT == 0){
			PANTALLA++;
			if(PANTALLA == 5){
				PANTALLA = main_screen;
			}
			delay(200);
		}else if(B_RIGHT == 0){
			PANTALLA--;
			if(PANTALLA == 255){
				PANTALLA = ventilator_screen;
			}
			delay(200);
		}
		
		if(PANTALLA == main_screen){
			//LCD_BEGIN(linea1, linea2);
		}
		else if(PANTALLA == temp_screen){
			control_temp();
			dividir_valor(temperatura_actual);
			linea4[0] = desenes+0x30;
			linea4[1] = unitats+0x30;
			linea4[3] = decimal+0x30;
			dividir_valor(temperatura_max);
			linea4[8] = desenes+0x30;
			linea4[9] = unitats+0x30;
			linea4[11] = decimal+0x30;
			LCD_BEGIN(linea3, linea4);
		}
		else if(PANTALLA == hum_screen){
			control_hum();
			dividir_valor(humitat_actual);
			linea6[0] = desenes+0x30;
			linea6[1] = unitats+0x30;
			linea6[3] = decimal+0x30;
			dividir_valor(humitat_min);
			linea6[8] = desenes+0x30;
			linea6[9] = unitats+0x30;
			linea6[11] = decimal+0x30;
			LCD_BEGIN(linea5, linea6);
		}
		else if(PANTALLA == motor_screen){
			control_motor();
			if(motor_mode == 0){
				linea8[0] = 'O';
				linea8[1] = 'F';
				linea8[2] = 'F';
				linea8[3] = ' ';
				LCD_BEGIN(linea7, linea8);
				control_porta(0);
			}else if(motor_mode == 1){
				linea8[0] = 'U';
				linea8[1] = 'P';
				linea8[2] = ' ';
				linea8[3] = ' ';
				LCD_BEGIN(linea7, linea8);
				control_porta(1);
				motor_mode = 0;
			}else if(motor_mode == 2){
				linea8[0] = 'D';
				linea8[1] = 'O';
				linea8[2] = 'W';
				linea8[3] = 'N';
				LCD_BEGIN(linea7, linea8);
				control_porta(2);
				motor_mode = 0;
			}
			else if(motor_mode == 3){
				linea8[0] = 'A';
				linea8[1] = 'U';
				linea8[2] = 'T';
				linea8[3] = 'O';
				LCD_BEGIN(linea7, linea8);
			}
		}
		else if(PANTALLA == ventilator_screen){
			control_vent();
			if(ventilator_mode == 0){
				linea10[1] = 'O';
				linea10[2] = 'F';
				linea10[3] = 'F';
			}else if(ventilator_mode == 1){
				linea10[1] = 'O';
				linea10[2] = 'N';
				linea10[3] = ' ';
			}else if(ventilator_mode == 2){
				linea10[1] = 'A';
				linea10[2] = 'U';
				linea10[3] = 'T';
			}
			LCD_BEGIN(linea9, linea10);
		}
		delay(100);
}