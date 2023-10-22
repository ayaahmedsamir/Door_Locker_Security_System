 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Aya Ahmed Samir
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "common_header.h"


typedef enum
{
	BITS_5,BIT_6,BITS_7,BITS_8
}UART_Bitdata;

typedef enum
{
	disabled_parity,enable_even=2,enable_odd
}UART_Parity;

typedef enum
{
	BIT_1,BIT_2
}UART_Stopbit;

typedef struct
{
	UART_Bitdata bit_data;
	UART_Parity parity;
	UART_Stopbit stop_bit;
	uint32 baud_rate;

}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *config_ptr);
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
