#include "transmisor.h"
#include "tim.h"

volatile unsigned char _dato_a_enviar = 0;
unsigned char can_send = 0;

void send(unsigned char* texto)
{
	//uart_print("sizeof texto: ");
	//uart_println_int(sizeof(texto));
	int i = 0;


	while (i < (sizeof(texto)))
	{
		if(can_send == FREE)
		{
			// if(texto[i] != 0 )
			//{
				send_byte(texto[i]);
			//}
				i++;
		}
	}
}

void send_byte(unsigned char dada)
{
	contador = 0; // reset contador
	_dato_a_enviar = dada; // cargamos dato para la IRQ
	can_send = SENDING; // a partir de aqui, estamos enviando un paquete
						// y no podremos enviar el siguiente hasta que
						// no esté listo el primero
}
