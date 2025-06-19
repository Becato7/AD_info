/*****************************************************************************/
/* Fichero     - main.c                                                      */
/* Descripcion - programaci?n del LCD: programa de ejemplo                   */
/* Autor       - STS														                             */
/* Fecha       - 25/05/2025													                         */
/*****************************************************************************/


#include <AT89C5131.h> 			//Crida de la llibreria AT89C5131.h
#include "lcd.h"						//Crida de la llibreria lcd.h
#include "STATE_MACHINE.h"	//Crida de la llibreria STATE_MACHINE.h
#include "BOTONS_RELES.h"		//Crida de la llibreria BOTONS_RELES.h
#include "MCP3302.h"				//Crida de la llibreria MCP3302.h
#define FOSC 12000000UL   	//Defineix la freq��ncia del sistema (12 MHz)

void main(void)
{
	unsigned int temp; 		//Declaraci� del valor llegit per l'ADC
	unsigned int hum; 		//Declaraci� del valor llegit per l'ADC
	LCD_inicializar();				//Crida de la funci� d'inicialitzaci� de la LCD
	LCD_borrar();							//Crida de la funci� per netejar la LCD en cas que hi hagu�s algun caracter
	P0 = 0xFF;								//Incicialitzem el port P0 a FF perqu� son lectures de botons
	P2 = 0x00;								//Inicialitzem el port P2 a 00
	SPI_CS = 1;								//Inicialitzem el pin del CS de l'SPI a 1
  SPI_CLK = 0;							//Inicialitzem el pin del clock de l'SPI a 0
  SPI_MOSI = 0;							//Inicialitzem el pin de MOSI de l'SPI a 0, ja que ser� la sortida d'informaci�
	SPI_MISO = 1;							//Inicialitzem el pin de MISO de l'SPI a 1, ja que hem de preparar el pin per fer lectures

	while(1){
	temp = MCP3302_ReadChannel12(1);			//Cridem la funci� que llegeix els el valor de l'ADC, en aquest cas volem el valor del canal 1 i guardem la informaci� a temp
	hum = MCP3302_ReadChannel12(2);				//Cridem la funci� que llegeix els el valor de l'ADC, en aquest cas volem el valor del canal 2 i guardem la informaci� a hum
		state_machine(temp, hum);							//Cridem la funci� state machine i li entrem el valor de l'ADC
	}
}

