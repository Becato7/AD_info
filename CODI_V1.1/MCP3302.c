#include "MCP3302.h"					//Cridem la llibreria MCP3302.h
#include <intrins.h>					//Cridem la llibreria intrins.h

static void spi_delay(void) {	//Declarem la funció spi_delay
	_nop_();										//Permet estar 1 cicle de màquina sense fer res
	_nop_();										//Permet estar 1 cicle de màquina sense fer res
}

void spi_write_bit(unsigned char b) {	//Declarem la funció spi_write_bit(unsigned char b) que permet escriure un bit en SPI
    SPI_MOSI = b;											//Posem el pin de MOSI al valor 0/1 que hagi entrat per la funció
    SPI_CLK = 1; 											//Posem el pin de CLK a 1 
		spi_delay();											//Delay de 2 cicles de màquina, és a dir 2us
    SPI_CLK = 0; 											//Posem el pin de CLK a 0 
		spi_delay();											//Delay de 2 cicles de màquina, és a dir 2us
}

unsigned char spi_transfer_byte(unsigned char out) {	//Declarem la funció spi_transfer_byte(unsigned char out)
    unsigned char in = 0;															//Declarem la variable in
    signed char i;																		//Declarem la variable i
    for (i = 7; i >= 0; i--) {												//Bucle que va de 7 a 0 per enviar de msb a lsb
        spi_write_bit((out >> i) & 1);								//Cridem la funció spi_write_bit i li entrem el bit corresponent del byte que volem enviar
        in <<= 1;																			//Ens guardem el bit que llegim pel pin MISO
        in |= SPI_MISO;																//Ens guardem el bit que llegim pel pin MISO
    }
    return in;																				//Retornem el valor llegir
}

unsigned int MCP3302_ReadChannel(unsigned char ch) {
																											//Configuració del canal (single-ended):
																											//Start=1, SGL/DIFF=1, D2=0, D1/D0 = ch
    unsigned char command = 0x18 | (ch & 0x03); 			//Declarem la variable command amb el valor del canal que volem llegir després command serà la comanda a enviar0x18 = b00011000
    unsigned char rx_buf[3];													//Declarem l'array de rebuda de dades
    unsigned int result;															//Declarem la variable on es guardaran els resultats
    
    SPI_CS = 0; 																			//Posem el CS de l'SPI a 0
    rx_buf[0] = spi_transfer_byte(command);  					//Enviem el byte del comanda i ens guardem els valors
    rx_buf[1] = spi_transfer_byte(0x00);   						//Enviem un byte buit i ens guardem els valors
    rx_buf[2] = spi_transfer_byte(0x00);   						//Enviem un byte buit i ens guardem els valors
    SPI_CS = 1;  																			//Posem el CS de l'SPI a 1

    result = (rx_buf[1] & 0x3F);     									//Agafem els 6 bits útils (màscara 00111111)
    result = result << 6;             								//Desplaçem 6 posicions a l'esquerra
    result |= (rx_buf[2] >> 2);       								//Agafem els 6 bits alts del byte 3 i els unim amb els del byte 2

    return result;																		//Retornem el resultat
}

unsigned int MCP3302_ReadChannel12(unsigned char ch) {//Declarem la funció MCP3302_ReadChannel12(unsigned char ch)
    return MCP3302_ReadChannel(ch) & 0x0FFF;					//Guardem unicament un byte i mig, elidint el primer que indica el signe del valor
}

float MCP3302_ToVoltage(unsigned int adc12, float vref) {	//Declarem la funció MCP3302_ToVoltage(unsigned int adc12, float vref) on se li entra el valor del adc i el voltatje de referència
    return (vref * adc12) / 4096.0f;											//Retornem el valor de voltatje fent la conversió amb el voltatje de referència i la resolució de l'ADC que es de 4096 bits
}
