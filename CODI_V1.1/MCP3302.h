#ifndef MCP3302_H
#define MCP3302_H

#include <AT89C5131.h>

sbit SPI_CS   = P1^4; // MCP3302 pin 10 - /CS
sbit SPI_MISO = P1^5; // MCP3302 pin 12 - DOUT
sbit SPI_CLK  = P1^6; // MCP3302 pin 11 - CLK
sbit SPI_MOSI = P1^7; // MCP3302 pin 13 - DIN

void MCP3302_InitPins(void);                        // opcional
void spi_write_bit(unsigned char b);
unsigned char spi_transfer_byte(unsigned char out);
unsigned int MCP3302_ReadChannel(unsigned char ch); // 13 bits
unsigned int MCP3302_ReadChannel12(unsigned char ch); // 12 bits
float MCP3302_ToVoltage(unsigned int adc12, float vref);

#endif
