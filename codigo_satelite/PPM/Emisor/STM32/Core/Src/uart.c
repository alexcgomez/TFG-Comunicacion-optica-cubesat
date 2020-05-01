#include "uart.h"

void UART_Init()
{
  UART.Instance = USART1;
  UART.Init.BaudRate = 9600;
  UART.Init.WordLength = UART_WORDLENGTH_8B;
  UART.Init.StopBits = UART_STOPBITS_1;
  UART.Init.Parity = UART_PARITY_NONE;
  UART.Init.Mode = UART_MODE_TX_RX;
  UART.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UART.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&UART) != HAL_OK)
  {
    Error_Handler();
  }
}

void uart_put_char(char caracter)
{
	HAL_UART_Transmit(&UART, caracter, 1, 100);
}

void uart_put_char16(uint16_t caracter)
{
	uint8_t dades[2] = 
	{
		(caracter & 0x00FF),
		((caracter & 0xFF00) << 8)
	};
	HAL_UART_Transmit(&UART, dades, 2, 100);
}

void uart_print(char* text)
{
	HAL_UART_Transmit(&UART, text, strlen(text), 100);
}

void uart_println(char* text)
{
	uart_print(text);
	HAL_UART_Transmit(&UART, "\r\n", sizeof("\r\n"), 100);
}

void uart_print_int(size_t dada)
{
	char text_dada[10]={0,0,0,0,0};
	itoa( dada , text_dada, 10);			
	HAL_UART_Transmit(&UART, text_dada , sizeof(text_dada), 100);
}

void uart_println_int(size_t dada)
{
	uart_print_int(dada);			
	uart_println("");
}
