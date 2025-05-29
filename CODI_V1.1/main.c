
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
  unsigned int adc_val;
  float volts;

	//SPI_Init();
	//MCP3302_Init();
	
	while(1)
	{ 	
	state_machine();
		//adc_val = LTC_ReadChannel(0);
    //volts = convert_to_voltage(adc_val);
		//adc_val = MCP3302_ReadChannel(0);
		//volts = MCP3302_ConvertToVoltage(adc_val);
  }
}

