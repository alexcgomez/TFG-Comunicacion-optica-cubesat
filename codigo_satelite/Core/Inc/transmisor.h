#ifndef _transmisor_h_
#define _transmisor_h_

// Macros
	#define FREE	0
	#define SENDING	1

// variables
	extern volatile unsigned char _dato_a_enviar;
	extern unsigned char can_send;
	
	void send(unsigned char* texto);
	void send_byte(unsigned char dada);

#endif
