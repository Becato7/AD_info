#include "MCP.h"
#include "LTC.h"

// Inicialització SPI
void MCP3302_Init(void) {
    SPCON = 0x50;   // Mode master, CPOL = 0, CPHA = 0, Fosc/4
    SPCON |= 0x10;  // SPI enable
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
