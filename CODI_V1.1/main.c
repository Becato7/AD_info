/*****************************************************************************/
/* Fichero     - main.c                                                      */
/* Descripcion - programaci?n del LCD: programa de ejemplo                   */
/* Autor       - STS														                             */
/* Fecha       - 25/05/2025													                         */
/*****************************************************************************/


#include <AT89C5131.h> 
#include "lcd.h"
#include "STATE_MACHINE.h"
#include "BOTONS_RELES.h"
#include "MCP3302.h"
#define FOSC 12000000UL   // Defineix la freqüència del teu sistema (12 MHz típic)

void main(void)
{
	unsigned int adc_raw; 
	LCD_inicializar();
	LCD_borrar();
	P0 = 0xFF;
	P2 = 0x00;
	P1 = 0x00;
	MCP3302_InitPins(); 

	while(1){
	adc_raw = MCP3302_ReadChannel12(1);
	state_machine(adc_raw);
	}
}

