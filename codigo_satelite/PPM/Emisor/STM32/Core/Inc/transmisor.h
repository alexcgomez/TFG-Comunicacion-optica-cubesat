#ifndef _transmisor_h_
#define _transmisor_h_

#include "stdint.h"
#include "stdbool.h"

extern volatile unsigned char dato;
extern volatile bool can_send;

void PPM_send(unsigned char data);

#endif