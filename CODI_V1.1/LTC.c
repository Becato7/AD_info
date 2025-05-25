


#include "LTC.h"

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