#include "transmisor.h"
volatile unsigned char dato = 0;
volatile bool can_send = true;

void PPM_send(unsigned char data)
{
	dato = data;
	can_send = false;
	while (!can_send)
		;
}