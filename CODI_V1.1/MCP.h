#include <AT89C5131.h>

sbit SPI_CS   = P1^4;

void SPI_Init(void);
unsigned char SPI_Transfer(unsigned char value);
unsigned int MCP3302_ReadChannel(unsigned char channel);
float MCP3302_ConvertToVoltage(unsigned int adc_value);
