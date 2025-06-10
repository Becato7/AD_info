#include "MCP.h"

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

// Llegeix un canal del MCP3302 (0 a 3)
unsigned int MCP3302_ReadChannel(unsigned char channel) {
    unsigned char start_bit = 0x01;
    unsigned char command, msb, lsb;
    unsigned int result;

    // Construcció de la comanda per MCP3302 (single-ended)
    // Primer byte: start bit (0x01)
    // Segon byte: SGL/DIF (1), D2, D1, D0, x, x, x, x
    // Ex: canal 0 -> 0xA0 (10100000)
		command = 0x80 | ((channel & 0x03) << 4);
    SPI_CS = 0;                  // Activa el xip
    SPI_Transfer(start_bit);     // Start bit
    msb = SPI_Transfer(command); // Comanda
    lsb = SPI_Transfer(0x00);    // Dummy byte per llegir LSB
    SPI_CS = 1;                  // Desactiva el xip

    result = ((msb & 0x1F) << 8) | lsb; // 13 bits útils
    return result;
}

// Converteix valor ADC a volts
float MCP3302_ConvertToVoltage(unsigned int adc_value) {
	float vref = 5.0;
    return (vref * adc_value) / 8192.0; // 13 bits = 2^13 = 8192
}
