#include <AT89C5131.h>


void MCP3302_Init(void);
unsigned int MCP3302_ReadChannel(unsigned char channel);
float MCP3302_ConvertToVoltage(unsigned int adc_value);
