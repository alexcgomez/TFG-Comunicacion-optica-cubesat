#include "transmisor.h"
#include "tim.h"

volatile unsigned char _dato_a_enviar = 0;
unsigned char can_send = 0;

void send_byte(unsigned char dada)
{
	contador = 0; // reset contador
	_dato_a_enviar = dada; // cargamos dato para la IRQ
	can_send = SENDING; // a partir de aqui, estamos enviando un paquete
						// y no podremos enviar el siguiente hasta que
						// no esté listo el primero
}
