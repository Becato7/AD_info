
/*****************************************************************************/
/* Fichero     - main_lcd.c                                                  */
/* Descripcion - Codi principal de la AD									                   */
/* Autor       - Bernat Carnota									                             */
/* Fecha       - 29/04/2025													                         */
/*****************************************************************************/

#include <AT89C5131.h> 
#include "BOTONS_RELES.h"
#include "STATE_MACHINE.h"
#include "lcd.h"
#include "LTC.h"
#include "MCP.h"


//PORT 2
sbit ECHO = P2^7;
sbit TRIG = P2^6;

void main(void)
{
	unsigned char code linea1[16] = {' ','H','E','L','L','O',' ','B','A','R','C','E','L','O','N','A'};
	unsigned char code linea2[16] = {' ','I','I','E','I','A',' ','2','0','2','4',' ',' ',' ',' ',' '};


	LCD_inicializar();
	LCD_borrar();
	P1 = 0xFF;
	P0 = 0xFF;
	P2 = 0x00;

	while(1)
	{ 				
		LCD_situar_cursor(1,1);	
		LCD_escribir_caracter('1');
		delay(5);
		LCD_situar_cursor(1,10);	
		LCD_escribir_caracter('2');
		delay(5);
  }
}

