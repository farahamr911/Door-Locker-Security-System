/*
 * uart.h
 *
 *  Created on: Oct 24, 2024
 *      Author: farah
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"


typedef enum
{
	BitDataType_5,BitDataType_6,BitDataType_7,BitDataType_8,Reserved_mode,Reserved_mode1,Reserved_mode2,BitDataType_9
}UART_BitDataType;

typedef enum
{
	Disable_Parity,Reserved,Enabled_EvenParity,Enabled_OddParity
}UART_ParityType;

typedef enum
{
	StopBite_1bite,StopBite_2bite
}UART_StopBitType;

typedef uint32 UART_BaudRateType;



typedef struct {
UART_BitDataType bit_data;
UART_ParityType parity;
UART_StopBitType  stop_bit;
UART_BaudRateType baud_rate;
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
void UART_init(const UART_ConfigType * Config_Ptr);

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
