#ifndef PWM_DRIVER_H_	// Evitamos que se añada dos veces el mismo código
#define PWM_DRIVER_H_

	#include "Arduino.h"
	
	//#define PIN_RECEPTOR_LASER	x // usar pin con IRQ por HW (pin 2?)
	#define PIN_EMISOR_LASER 		6
		#define LASER_OUTPUT()		pinMode( PIN_EMISOR_LASER, OUTPUT )
		#define LASER_HIGH()		digitalWrite( PIN_EMISOR_LASER, HIGH)
		#define LASER_LOW()			digitalWrite( PIN_EMISOR_LASER, LOW)

// Macros timing
	#define NO_PRESCALING()		TCCR0B &= ~((1 << CS02) | (1 << CS01));	TCCR0B |= (1 << CS00)
	#define PRESCALING_8()		TCCR0B &= ~((1 << CS02) | (1 << CS00));	TCCR0B |= (1 << CS01)
	#define PRESCALING_64()		TCCR0B &= ~( 1 << CS02);				TCCR0B |= ((1 << CS01) | (1 << CS00))
	#define PRESCALING_256()	TCCR0B &= ~((1 << CS01) | (1 << CS00));	TCCR0B |= (1 << CS02)
	#define PRESCALING_1024()	TCCR0B &= ~( 1 << CS01);				TCCR0B |= ((1 << CS02) | (1 << CS00))

	#define ENABLE_TIMER_IRQ()	TIMSK0 |=  (1 << OCIE0B)
	#define DISABLE_TIMER_IRQ()	TIMSK0 &= ~(1 << OCIE0B)

	#define RESET_TIMER()		TCNT0 = 0


	class PWM_driver
	{
		public:
			void init();
			void write( char *_text, int text_size );
			void read( char *_text, int text_size ); // No devolver el string con un return, suele dar problemas con el stack
			bool is_sent();
			bool new_packet();
			
			inline void send_byte( unsigned char dato ) // función inline, para ganar un poco de velocidad
			{
				ENABLE_TIMER_IRQ();
				OCR0B = dato;
				LASER_HIGH();
			}

		private:
			bool _new_packet = false; // modo read
			bool _send_ready = false; // modo write
			
			
	};

#endif
