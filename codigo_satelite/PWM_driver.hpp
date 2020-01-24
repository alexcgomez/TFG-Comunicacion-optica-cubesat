#ifndef PWM_DRIVER_H_	// Evitamos que se añada dos veces el mismo código
#define PWM_DRIVER_H_

	#include "Arduino.h"
	
	//#define PIN_RECEPTOR_LASER	x // usar pin con IRQ por HW (pin 2?)
	#define PIN_EMISOR_LASER 		6
		#define LASER_OUTPUT()		pinMode( PIN_EMISOR_LASER, OUTPUT )
		//define LASER_HIGH()		digitalWrite( PIN_EMISOR_LASER, HIGH)
		#define LASER_HIGH()		_temporal_estado_laser = HIGH; digitalWrite( PIN_EMISOR_LASER, _temporal_estado_laser)
		//#define LASER_LOW()		digitalWrite( PIN_EMISOR_LASER, LOW)
		#define LASER_LOW()			_temporal_estado_laser = LOW; digitalWrite( PIN_EMISOR_LASER, _temporal_estado_laser)

// Macros timing
	#define NO_PRESCALING()		TCCR0B &= ~((1 << CS02) | (1 << CS01));	TCCR0B |= (1 << CS00)
	#define PRESCALING_8()		TCCR0B &= ~((1 << CS02) | (1 << CS00));	TCCR0B |= (1 << CS01)
	#define PRESCALING_64()		TCCR0B &= ~( 1 << CS02);				TCCR0B |= ((1 << CS01) | (1 << CS00))
	#define PRESCALING_256()	TCCR0B &= ~((1 << CS01) | (1 << CS00));	TCCR0B |= (1 << CS02)
	#define PRESCALING_1024()	TCCR0B &= ~( 1 << CS01);				TCCR0B |= ((1 << CS02) | (1 << CS00))

	#define ENABLE_TIMER_IRQ()	TIMSK0 |=  (1 << OCIE0B)
	#define DISABLE_TIMER_IRQ()	TIMSK0 &= ~(1 << OCIE0B)

	#define RESET_TIMER()		TCNT0 = 0
	#define TIMER				TCNT0
	#define USER_COUNTER		OCR0B
	

//Variables
	extern volatile unsigned char _temporal_estado_laser;
	extern bool _new_packet;
	extern bool _send_ready;
	
// Funciones
	void _driver_init();
	void _driver_write( char *_text, int text_size );
	void _driver_read( char *_text, int text_size ); // No devolver el string con un return, suele dar problemas con el stack
	
	inline void _driver_send_byte( unsigned char dato ) // función inline, para ganar un poco de velocidad
	{
		RESET_TIMER();
		ENABLE_TIMER_IRQ();
		USER_COUNTER = dato;
		LASER_HIGH();
	}
	
	inline bool _driver_can_send()
	{
		return _send_ready;
	}
	inline bool _driver_can_send(bool t)
	{
		_send_ready = t;
	}
	

	inline bool new_packet()
	{
		return _new_packet;
	}


			

#endif
