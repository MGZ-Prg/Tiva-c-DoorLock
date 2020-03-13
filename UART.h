#ifndef UART_H
#define UART_H
#include "common_macros.h"
#include "stdint.h"
#include "inc/tm4c123gh6pm.h"
#include "std_types.h"
#include "TM4C123.h"
#define SYS_CLK		16000000


void UART_Init(uint8 UARTX,uint8 length,uint16 baud_rate);
void UART_Send_Char(uint8 character,uint8 UARTX);
uint8 UART_Receive_Char(uint8 UARTX);
void UART_Send_String(const uint8 *Str , uint8 UARTX);
void UART_Receive_String(uint8 *Str,uint8 UARTX);


#endif