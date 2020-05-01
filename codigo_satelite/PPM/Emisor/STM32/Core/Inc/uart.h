#ifndef uart_h_
#define uart_h_

#include "usart.h"
#include "stm32f1xx_hal.h"

#define UART huart1

UART_HandleTypeDef UART;

void uart_Init();
void uart_put_char(char caracter);
void uart_put_char16(uint16_t caracter);
void uart_print(char* text);
void uart_println(char* text);
void uart_print_int(size_t dada);
void uart_println_int(size_t dada);

#endif
