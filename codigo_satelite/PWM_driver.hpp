#ifndef PWM_DRIVER_H_	// Evitamos que se añada dos veces el mismo código
#define PWM_DRIVER_H_

#define PWM_DEBUG	1 // apagar si no se va a debuggear

	#include "Arduino.h"
	
// Macros laser
	#define PIN_RECEPTOR_LASER		2	// no se usa todavía
	#define PIN_EMISOR_LASER 		6
	#define LASER_OUTPUT()			pinMode( PIN_EMISOR_LASER, OUTPUT )
	#define LASER_HIGH()			digitalWrite( PIN_EMISOR_LASER, HIGH)
	#define LASER_LOW()				digitalWrite( PIN_EMISOR_LASER, LOW)

// Macros timing
	#define NO_PRESCALING()		TCCR2B |= ( 1 << CS20);								TCCR2B &= ~((1 << CS22) | (1 << CS21))
	#define PRESCALING_8()		TCCR2B |= ( 1 << CS21);								TCCR2B &= ~((1 << CS22) | (1 << CS20))
	#define PRESCALING_32()		TCCR2B |= ((1 << CS21) | (1 << CS20));				TCCR2B &= ~( 1 << CS22)
	#define PRESCALING_64()		TCCR2B |= ( 1 << CS22);								TCCR2B &= ~((1 << CS21) | (1 << CS20))
	#define PRESCALING_128()	TCCR2B |= ((1 << CS22) | (1 << CS20) );				TCCR2B &= ~( 1 << CS21)
	#define PRESCALING_256()	TCCR2B |= ((1 << CS22) | (1 << CS21) );				TCCR2B &= ~( 1 << CS20)
	#define PRESCALING_1024()	TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20))

	#define RESET_TIMER()		TCNT2 = 0
	#define RELOAD_COUNTER()	OCR2B = 1

	#define ENABLE_TIMER_IRQ()	TIMSK2 |=  (1 << OCIE2B); RESET_TIMER(); RELOAD_COUNTER()
	#define DISABLE_TIMER_IRQ()	TIMSK2 &= ~(1 << OCIE2B)

//Variables
	extern volatile unsigned char ticks_usuario;
	extern volatile unsigned char _ticks;
	extern volatile bool _new_packet;
	extern volatile bool _send_ready;

// Funciones
	void _driver_init();
	void _driver_write( char *_text, int text_size );
	void _driver_read( char *_text, int text_size ); // No devolver el string con un return, suele dar problemas con el stack
	void _driver_send_byte( unsigned char dato );

#endif
