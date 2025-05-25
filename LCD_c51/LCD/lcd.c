
/*****************************************************************************/
/* Fichero     - lcd.c                                                       */
/* Descripcion - programaci�n del LCD: funciones			             	         */
/* Autor       - STS														                             */
/* Fecha       - 29/09/2023													                         */
/*****************************************************************************/
// Version modificada para poder escribir sin modificar los bits de menor peso del puerto del LCD


#include "lcd.h"


/*----------------------------------*/
/* declaraci�n de funciones ocultas	*/
/*----------------------------------*/

void LCD_enviar_comando(char comando, char instr_dato, char cuatro_ocho);
void LCD_retardo_ms(unsigned int ms);
void LCD_esperar_BF(void);


/*-------------------------------------------------*/
/* Nombre: LCD_inicializar                         */
/* Descripcion: rutina para inicializaci�n del LCD */
/* Parametros:                                     */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_inicializar(void)
{

	// inicialmente se trabaja como si la interfaz fuera de 8 bits 
	// (lo sea realmente o no) y con tiempo fijo entre instrucciones 
	LCD_retardo_ms(15);									// retardo inicial de 15 ms
	LCD_enviar_comando(0x30,0,8);				// Function Set
	LCD_retardo_ms(5);									// retardo de 5 ms (>4.1 ms)
	LCD_enviar_comando(0x30,0,8);				// Function Set
	LCD_retardo_ms(1);									// retardo de 1 ms (>100 us)
	LCD_enviar_comando(0x30,0,8);				// Function Set

	// a partir de ahora hay espera del BF
	// si la interfaz es de 4 bits se le indica al LCD
	if (TAM_INTERFAZ==4)
	{
		LCD_enviar_comando(0x20,0,8);			// Function Set	-> interfaz 4 bits
		LCD_esperar_BF();
	}

	// a partir de aqui el funcionamiento a bajo nivel
	// es diferente en funci�n del tama�o del interfaz
	// (lo gestiona LCD_enviar_comando), pero los
	// comandos enviados son los mismos
	LCD_enviar_comando(0x28,0,TAM_INTERFAZ);	// Function set: N=1, F=0 -> 2 lineas, caracteres de 7*5 pixels
	LCD_esperar_BF();
	LCD_enviar_comando(0x08,0,TAM_INTERFAZ);	// Display Off
	LCD_esperar_BF();
	LCD_enviar_comando(0x01,0,TAM_INTERFAZ);	// Clear Display
	LCD_esperar_BF();	
	LCD_enviar_comando(0x06,0,TAM_INTERFAZ);	// Entry Mode Set: I/D=1 -> cursor a derecha, S=0 -> contenido "quieto"
	LCD_esperar_BF();	
	LCD_enviar_comando(0x02,0,TAM_INTERFAZ);	// Return Home
	LCD_esperar_BF();	
	LCD_enviar_comando(0x0C,0,TAM_INTERFAZ);	// Display Control: D=1 -> LCD on, C=0 -> cursor invisible, B=0 -> caracter no parpadea
}


/*-------------------------------------------------*/
/* Nombre: LCD_borrar                              */
/* Descripcion: borra el contenido del LCD 		     */
/* Parametros:                                     */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_borrar(void)
{
	LCD_enviar_comando(0x01,0,TAM_INTERFAZ);	// Clear Display
	LCD_esperar_BF();
}


/*-------------------------------------------------*/
/* Nombre: LCD_situar_cursor                       */
/* Descripcion: sit�a el cursor del LCD en una     */
/*              determinada posici�n               */
/* Parametros:                                     */
/*   fila - fila seleccionada 					           */
/*   columna - columna							               */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_situar_cursor(unsigned char fila, unsigned char columna)
{
	unsigned char address;
	address = 40*(fila-1)+columna-1;
	LCD_enviar_comando(address|0x80,0,TAM_INTERFAZ);	// Set DDRAM Address
	LCD_esperar_BF();
}


/*-------------------------------------------------*/
/* Nombre: LCD_escribir_caracter                   */
/* Descripcion: escribe un caracter en el LCD, en  */
/*              la posici�n actual del cursor      */
/* Parametros:                                     */
/*   caracter - caracter visualizado			         */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_escribir_caracter(char caracter)
{
	LCD_enviar_comando(caracter,1,TAM_INTERFAZ);	// Write Data
	LCD_esperar_BF();
}


/*-------------------------------------------------*/
/* Nombre: LCD_retardo                             */
/* Descripcion: rutina de retardo                  */
/* Parametros:                                     */
/*   ms - milisegundos de retardo   			         */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_retardo_ms(unsigned int ms)		
{
	unsigned int i,j;

	for (i=0;i<ms;i++)
		for (j=0;j<240;j++);
}


/*-------------------------------------------------*/
/* Nombre: LCD_enviar_comando                      */
/* Descripcion: envia un comando (instruccion o    */
/*              dato) al controlador del LCD       */
/* Parametros:                                     */
/*   comando - comando enviado (DB7-DB0)   		     */
/*   instr_dato - 0 <-> instruccion, 1 <-> dato    */
/*   cuatro_ocho - 0 <-> 4 bits, 1 <-> 8 bits      */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_enviar_comando(char comando, char instr_dato, char cuatro_ocho)
{
	// RS = 0/1 en funcion de instr_dato
	if (instr_dato==0)
		RS = 0;		// instruccion
	else
		RS = 1;		// dato

	// RW = 0 -> escritura
	RW = 0;

	// si interfaz de 4 bits
	if (cuatro_ocho==4)
	{
		// 4 bits altos
		LCD = (LCD&0x0F)|(comando & 0xF0);
		
		// pulso en EN
		EN = 1;
		EN = 0;
		
		// 4 bits bajos
		LCD = (LCD&0x0F)|(comando<<4);

		// pulso en EN
		EN = 1;
		EN = 0;
	}

	// interfaz de 8 bits
	else
	{
		// byte completo
		LCD = comando;
		
		// pulso en EN
		EN = 1;
		EN = 0;
	}
}


/*-------------------------------------------------*/
/* Nombre: LCD_esperar_BF                          */
/* Descripcion: espera a que el BF sea 0 (fin op.) */
/* Parametros:                                     */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_esperar_BF(void)
{
	BF = 1;
	RS = 0;					// instruccion
	RW = 1; 				// lectura
	EN = 1;					// EN=1 -> el LCD responde con BF
	while (BF==1);	// espera a que BF=0 
	EN = 0;					// EN=0
	RW = 0;					// RW=0
}


void LCD_BEGIN(char *linea1, char *linea2)
{
		unsigned int i;	// indice
		// deseleccion de dispositivos conectado a P1-P2
	P1= 0xEF;

	// inicializacion del LCD
	LCD_inicializar();
	// primera linea de texto
	for (i=0 ; i<16 ; i++)
	{
		LCD_escribir_caracter(linea1[i]);		// escritura caracter a caracter
	}
			
 	// segunda linea de texto
	LCD_situar_cursor(2,1);								// ubica el cursor al inicio de segunda linea
	for (i=0 ; i<16 ; i++)
	{
		LCD_escribir_caracter(linea2[i]); 	// escritura caracter a caracter
	}
}

