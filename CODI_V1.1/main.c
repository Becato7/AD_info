/*****************************************************************************/
/* Fichero     - main.c                                                      */
/* Descripcion - programaci?n del LCD: programa de ejemplo                   */
/* Autor       - STS														                             */
/* Fecha       - 25/05/2025													                         */
/*****************************************************************************/


#include <AT89C5131.h> 
#include "lcd.h"
#include "STATE_MACHINE.h"
#include "MCP.h"


void main(void)
{
	unsigned char lectura = 0;
	LCD_inicializar();
	LCD_borrar();
	SPI_Init();
	P0 = 0xFF;
	P2 = 0x00;

	while(1){
		state_machine(lectura);
	}
}

