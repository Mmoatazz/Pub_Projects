/*
 ============================================================================
 Name        : Final Project
 Author      : Moataz Mokhtar
 Description : Door-Locking system
 Date        : 25/3/2021
 ============================================================================
 */

/*****************GUARDING *****************/
#ifndef USART_H_
#define USART_H_
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#define _5_bit 0
#define _6_bit 2
#define _7_bit 4
#define _8_bit 6
#define _9_bit sdqwe
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
   _5_bits =_5_bit , _6_bits = _6_bit ,_7_bits = _7_bit, _8_bits=_8_bit
}NO_OF_BIT_DATA;
typedef enum
{
   disabled =0, EVEN = 32 ,ODD = 48
}PARITY_BIT;
typedef enum
{
   _1_bit =0, _2_bit=8
}STOP_BIT;

typedef struct
{
	NO_OF_BIT_DATA         bitdata;
	PARITY_BIT            paritybit;
	STOP_BIT               stopbit;
	uint16             baudrate;
}USART_config_type;

/*****************STATIC CONFIGURATIONS *****************/
#define BAUD_PRESCALE (((F_CPU / ( (baudrate) * 8UL))) - 1) //UBRR 8 for double speed mode U2X=1
/*****************FUNCTIONS PROTOTYPE *****************/
void UART_sendByte(uint8 data);
void UART_sendByte_method_1(uint8 data);
uint8 UART_recieveByte (void);
void UART_sendString(const uint8 *Str);
void UART_receivestring(uint8 *Str);
void UART_init(const USART_config_type * Config_Ptr);
#endif
