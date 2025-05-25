
#include <AT89C5131.h>

//PORT 1
sbit SPI_CS   = P1^1;


void SPI_Init(void);
unsigned char SPI_Transfer(unsigned char value);
unsigned int LTC_ReadChannel(unsigned char command);
float convert_to_voltage(unsigned int adc_value);