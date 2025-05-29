
/*****************************************************************************/
/* Fichero     - lcd.h                                                       */
/* Descripcion - programación del LCD: cabeceras de funciones				         */
/* Autor       - STS														                             */
/* Fecha       - 29/09/2023                       													 */
/*****************************************************************************/

#include <AT89C5131.h> 

/*-------------------------------------*/
/* definicion de la interfaz del LCD   */
/* debe adaptarse a la conexión entre  */
/* LCD y micro                         */
/*-------------------------------------*/

// conexión micro-LCD en el kit I2Kit
#define TAM_INTERFAZ 4	// interfaz de 4 bits
#define LCD P3					// LCD conectado al puerto P3
sbit EN = P3^0;					// ubicacion pin EN
sbit RW = P3^1;					// ubicacion pin RW
sbit RS = P3^2;					// ubicacion pin RS	
sbit BF = P3^7;					// ubicacion BF

void LCD_retardo_ms(unsigned int ms);
/*-------------------------------------------------*/
/* Nombre: LCD_inicializar                         */
/* Descripcion: rutina para inicialización del LCD */
/* Parametros:                                     */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_inicializar(void);


/*-------------------------------------------------*/
/* Nombre: LCD_borrar                              */
/* Descripcion: borra el contenido del LCD 		     */
/* Parametros:                                     */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_borrar(void);


/*-------------------------------------------------*/
/* Nombre: LCD_situar_cursor                       */
/* Descripcion: sitúa el cursor del LCD en una     */
/*              determinada posición               */
/* Parametros:                                     */
/*   fila - fila seleccionada 					           */
/*   columna - columna							               */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_situar_cursor(unsigned char fila, unsigned char columna);


/*-------------------------------------------------*/
/* Nombre: LCD_escribir_caracter                   */
/* Descripcion: escribe un caracter en el LCD, en  */
/*              la posición actual del cursor      */
/* Parametros:                                     */
/*   caracter - caracter visualizado			         */
/* Resultado:                                      */
/*-------------------------------------------------*/

void LCD_escribir_caracter(char caracter);

void LCD_BEGIN(char *linea1, char *linea2);
