/*********************************************************************************************************
 *                                               <Module name>
 *						<Module description>
 *
 *						<Copyright>
 *
 *						<Copyright or distribution terms>
 *
 *
 *********************************************************************************************************/

/*********************************************************************************************************
 *                                               <File description>
 *
 * Filename	: Filename
 * Version	: Module version
 * Programmer(s) : Programmer initial(s)
 **********************************************************************************************************
 *  Note(s):
 *
 *
 *
 *********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		${file_name}
 * \brief		Descripcion del modulo
 * \date		${date}
 * \author		Nicolas Ferragamo nferragamo@frba.utn.edu.ar
 * \version
 *********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
 *********************************************************************************************************/

#include <Arduino.h>
#include <util/delay.h>

/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 *********************************************************************************************************/
#define SET_PIN(PORT, PIN) (PORT |= 1 << PIN)
#define CLEAR_PIN(PORT, PIN) (PORT &= ~(1 << PIN))

#define bot1 ((PINC>>PC0)&0x01)
#define bot2 ((PINC>>PC1)&0X01)

/*********************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 *********************************************************************************************************/
/**





Tabla de conversion bcd a 7 segmentos ánodo común.

	Codigo bcd		a	b	c	d	e	f	g   dp
	0				0	0	0	0	0	0	1   1
	1				1	0	0	1	1	1	1   1
	2				0	0	1	0	0	1	0   1
	3				0	0	0	0	1	1	0   1
	4				1	0	0	1	1	0	0   1
	5				1	0	1	1	0	1	1   1
	6				1	1	0	0	0	0	0   1
	7				0	0	0	1	1	1	1   1
	8				0	0	0	0	0	0	0   1
	9				0	0	0	1	1	0	0   1
*/
// uint8_t Tabla_Digitos_7seg[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0xED, 0x83, 0xF8, 0x80, 0x98};

/**
Tabla de conversion bcd a 7 segmentos cátodo común
	Codigo bcd		a	b	c	d	e	f	g   dp
	0				1	1	1	1	1	1	0   0
	1				0	1	1	0	0	0	0
	2				1	1	0	1	1	0	1
	3				1	1	1	1	0	0	1
	4				0	1	1	0	0	1	1
	5				1	0	1	1	0	1	1
	6				0	0	1	1	1	1	1
	7				1	1	1	0	0	0	0
	8				1	1	1	1	1	1	1
	9				1	1	1	0	0	1	1
*/

//                                FEDCBA G
uint8_t Tabla_Digitos_7seg[] = {0b01111110,//0	
								0b00110000,//1	
								0b01101101,//2	
								0b01111001,//3	
								0b00110011,//4	
								0b01011011,//5	
								0b00011111,//6	
								0b01110000,//7	
								0b01111111,//8	
								0b01110011 //9	
								};

// static uint8_t Tabla_Digitos_BCD_7seg[ ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

/*********************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 *   se escriben en CamelCase y están precedidas por la identificación del
 *   módulo seguida de un _
 *   ej: MEM_POOL  Mem_PoolHeap;
 *********************************************************************************************************/
uint16_t cont = 0;
uint32_t i = 0;
/*********************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 *   se declaran con static y se escriben en CamelCase y están precedidas por la
 *   identificación del módulo seguida de un _ y usan _ para separar las palabras
 *   cuando tienen nombres compuestos
 *   ej: static MEM_POOL  Mem_Pool_Heap;
 *********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 * se declaran como estaticas y se escriben en CamelCase, están precedidas por la
 * identificación del módulo seguida de un _. No se decaran en el .h
 * ej static void Clk_DateTimer(parametros)
 *********************************************************************************************************/

/*********************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 *********************************************************************************************************/

/**
	\fn  		Nombre de la Funcion
	\brief 		Descripcion
	\author 	Nombre
	\date 		${date}
	\param [in] 	parametros de entrada
	\param [out] 	parametros de salida
	\return tipo 	y descripcion de retorno
*/

/*

Respetar este pin out.

PC0 -> BOTON 1
PC1 -> BOTON 2

PD2 -> SEGMENTO A
PD3 -> SEGMENTO B
PD4 -> SEGMENTO C
PD5 -> SEGMENTO D
PD6 -> SEGMENTO E
PD7 -> SEGMENTO F
PB0 -> SEGMENTO G
PB1 -> SEGMENTO DP

*/

/*
** The main function. Application starts here.
*/
int main(void)
{
	DDRC &=~(1<<PC0);
	DDRC &=~(1<<PC1);

	PORTC |=(1<<PC0);
	PORTC |=(1<<PC1);

	DDRD |=(1<<PD2);
	DDRD |=(1<<PD3);
	DDRD |=(1<<PD4);
	DDRD |=(1<<PD5);
	DDRD |=(1<<PD6);
	DDRD |=(1<<PD7);
	DDRB |=(1<<PB0);
	DDRB |=(1<<PB1);

	while (1)
	{
		
		if (bot1 == 0)
		{
			_delay_ms(100);
			if (bot1 == 0)
			{
				cont++;
				cont %=10;
			}
		}

		if (bot2 == 0)
		{
			_delay_ms(100);
			if (bot2 == 0)
			{
				cont--;
				if (cont < 0)
				{
					cont = 9;
				}
			}
		}
		

		PORTD= (PORTD & 0b00000011)|(Tabla_Digitos_7seg[cont]&0b11111100);
		PORTB= (PORTB & 0b11111100)|(Tabla_Digitos_7seg[cont]&0b00000011);
	}

}
/*********************************************************************************************************
** end of file
*********************************************************************************************************/