/* === MCP3302.c =================================== */
#include "MCP3302.h"
#include <intrins.h>


void MCP3302_InitPins(void) {
    SPI_CS = 1;
    SPI_CLK = 0;
    SPI_MOSI = 0;
		SPI_MISO = 1;
}

static void spi_delay(void) {
	/*	unsigned int i,j;
		for (i=0;i<1;i++)
		for (j=0;j<24;j++);*/
	_nop_();
	_nop_();
}

void spi_write_bit(unsigned char b) {
    SPI_MOSI = b;
    SPI_CLK = 1; 
		spi_delay();
    SPI_CLK = 0; 
		spi_delay();
}

unsigned char spi_transfer_byte(unsigned char out) {
    unsigned char in = 0;
    signed char i;
    for (i = 7; i >= 0; i--) {
        spi_write_bit((out >> i) & 1);
        in <<= 1;
        in |= SPI_MISO;
    }
    return in;
}

unsigned int MCP3302_ReadChannel(unsigned char ch) {
    // Configuració del canal (single-ended):
    // Start=1, SGL/DIFF=1, D2=0, D1/D0 = ch
    unsigned char command = 0x18 | (ch & 0x03); // 0x18 = b00011000
    
    unsigned char rx_buf[3];
    unsigned int result;
    
    SPI_CS = 0; // Activa CS (baix)

    // Transfereix 3 bytes
    rx_buf[0] = spi_transfer_byte(command);  // Byte 1
    rx_buf[1] = spi_transfer_byte(0x00);     // Byte 2
    rx_buf[2] = spi_transfer_byte(0x00);     // Byte 3

    SPI_CS = 1; // Desactiva CS (alt)

    // Processa les dades rebudes
    result = (rx_buf[1] & 0x3F);     // Agafa els 6 bits útils (màscara 00111111)
    result = result << 6;             // Desplaça 6 posicions a l'esquerra
    result |= (rx_buf[2] >> 2);       // Agafa els 6 bits alts del byte 3

    return result;
}

unsigned int MCP3302_ReadChannel12(unsigned char ch) {
    return MCP3302_ReadChannel(ch) & 0x0FFF;
}

float MCP3302_ToVoltage(unsigned int adc12, float vref) {
    return (vref * adc12) / 4096.0f;
}
