
/*****************************************************************************/
/* Fichero     - main_lcd.c                                                  */
/* Descripcion - Codi principal de la AD									                   */
/* Autor       - Bernat Carnota									                             */
/* Fecha       - 29/04/2025													                         */
/*****************************************************************************/

#include <AT89C5131.h> 
#include "lcd.h"
#include "LTC.h"

//PORT 0
sbit fc_inf = P0^6;
sbit fc_sup = P0^5;
sbit sw_right = P0^4;
sbit sw_left = P0^3;
sbit sw_down = P0^2;
sbit sw_ok = P0^1;
sbit sw_up = P0^0;

//PORT 2
sbit ECHO = P2^7;
sbit TRIG = P2^6;
sbit RELE4 = P2^5;
sbit RELE3 = P2^4;
sbit RELE2 = P2^3;
sbit RELE1 = P2^2;
sbit LED_AIGUA = P2^1;
sbit LED_REG = P2^0;


void main(void)
{
  unsigned int adc_val;
  float volts;
	unsigned char code linea1[16] = {' ','H','E','L','L','O',' ','B','A','R','C','E','L','O','N','A'};
	unsigned char code linea2[16] = {' ','I','I','E','I','A',' ','2','0','2','4',' ',' ',' ',' ',' '};
	
	SPI_Init();
	LCD_BEGIN(linea1, linea2);

	while(1)
	{ 	
		    adc_val = LTC_ReadChannel(0xC7);  // canal 0
        volts = convert_to_voltage(adc_val);
  }
}

