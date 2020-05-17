#include "transmisor.h"
volatile unsigned char dato = 0;
volatile bool can_send = true;

<<<<<<< HEAD
void PPM_send(unsigned char data)
{
	dato = data;
	can_send = false;
	while (!can_send)
		;
}
=======
volatile unsigned char _dato_a_enviar = 0;
unsigned char can_send = 0;

void send(unsigned char *texto)
{
	for (int i = 0; i < sizeof(texto);)
	{
		send_byte(texto[i]);
		i++;
		while (can_send == SENDING);
	}
}

void send_byte(unsigned char dada)
{
	contador = 0;		   // reset contador
	_dato_a_enviar = dada; // cargamos dato para la IRQ
	can_send = SENDING;	   // a partir de aqui, estamos enviando un paquete
						   // y no podremos enviar el siguiente hasta que
						   // no esté listo el primero
}
>>>>>>> c3355400b1fe64584086f367d8d36098df8d06dd
