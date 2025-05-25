
/*****************************************************************************/
/* Fichero     - main_lcd.c                                                  */
/* Descripcion - Codi principal de la AD									                   */
/* Autor       - Bernat Carnota									                             */
/* Fecha       - 29/04/2025													                         */
/*****************************************************************************/

#include <AT89C5131.h>  // substitueix per el correcte
#include "lcd.h"

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

//PORT 1
sbit SPI_CS   = P1^1;

void SPI_Init(void);
unsigned char SPI_Transfer(unsigned char value);
unsigned int LTC_ReadChannel(unsigned char command);
float convert_to_voltage(unsigned int adc_value);
/*--------------------*/
/* programa principal */
/*--------------------*/

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

// --------------------
// Inicialització SPI hardware
// --------------------
/*
| Bit | Nom          | Valor | Significat                                  |
| --- | ------------ | ----- | ------------------------------------------- |
| 7   | WCOL         | 0     | No col·lisió d’escriptura                   |
| 6   | SPEN         | 1     | SPI **habilitat** (es fa també a sota)      |
| 5   | MSTR         | 1     | SPI en **mode master**                      |
| 4   | CPOL         | 1     | Clock Polarity: **idle = alt**              |
| 3   | CPHA         | 0     | Clock Phase: mostra dades a primer flanc    |
| 2   | SPR1         | 0     | Velocitat: (SPR1\:SPR0) = `00` ? **Fosc/4** |
| 1   | SPR0         | 0     | idem                                        |
| 0   | bit reservat | 0     | No s’utilitza                               |
*/
void SPI_Init(void) {
	SPCON = 0x50;     // Master mode, CPOL=0, CPHA=0, Fosc/4
	SPCON |= 0x10;    // SPI Enable
}

// --------------------
// Envia i rep 1 byte SPI
// --------------------
unsigned char SPI_Transfer(unsigned char value) {
	SPDAT = value;
	while (!(SPSTA & 0x80));  // Espera a que SPIF = 1
	return SPDAT;
}

// --------------------
// Llegeix un canal del LTC1296
// --------------------
/*
| Canal | Codi binari | Hex    |
| ----- | ----------- | ------ |
| CH0   | `11000111`  | `0xC7` |
| CH1   | `11100111`  | `0xE7` |
| CH2   | `11001111`  | `0xCF` |
| CH3   | `11101111`  | `0xEF` |
| CH4   | `11010111`  | `0xD7` |
| CH5   | `11110111`  | `0xF7` |
| CH6   | `11011111`  | `0xDF` |
| CH7   | `11111111`  | `0xFF` |*/
unsigned int LTC_ReadChannel(unsigned char command) {
	unsigned char msb, lsb;
	unsigned int result;

	SPI_CS = 0;                // Activa el xip
	SPI_Transfer(command);     // Envia la comanda (ex: 0xC7 per canal 0)
	msb = SPI_Transfer(0x00);  // Llegeix primer byte
	lsb = SPI_Transfer(0x00);  // Llegeix segon byte
	SPI_CS = 1;                // Desactiva el xip

	result = ((msb << 8) | lsb) >> 3;  // Només els 12 bits útils
	return result;
}

float convert_to_voltage(unsigned int adc_value) {
    return (5.0 * adc_value) / 4096.0;
}