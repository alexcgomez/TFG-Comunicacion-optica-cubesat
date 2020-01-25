#include "Arduino.h"
#include "PWM_driver.hpp"

// Variables
	volatile unsigned char ticks_usuario = 0;
	volatile unsigned char _ticks = 0;
	volatile bool _new_packet = false; // modo read
	volatile bool _send_ready = false; // modo write

// Funciones
	void _driver_init()
	{
		#if PWM_DEBUG == 1 		// esto no llegará a compilarse, se lo come el preprocesador
			Serial.begin(9600);
			Serial.println("PWM_driver.cpp. Modo debug TLE activo!"); 
		#endif
		
		LASER_OUTPUT();

		cli();						// apagamos interrupciones
			PRESCALING_1024(); 		// Menor división, más velocidad. Ahora --> super slow
			DISABLE_TIMER_IRQ(); 	// de momento no queremos disparar el contador
		sei();						// activamos interrupciones
	}

	void _driver_write( char *_text, int text_size )
	{
		for(int i = 0; i < text_size; i++)
		{
			#if PWM_DEBUG == 1
				Serial.print("Sending: ");
				Serial.println(_text[i]);
			#endif
			
			_driver_send_byte( _text[i] );
		}
	}

	// to-do. No devolver el string con un return, suele dar problemas con el stack
	void _driver_read( char *_text, int text_size )
	{

	}

	void _driver_send_byte( unsigned char dato )
	{
		LASER_HIGH();
		ticks_usuario = dato;
		ENABLE_TIMER_IRQ();
		_ticks = 0;
		
		_send_ready = 0;
		while( _send_ready == 0 ); // arreglar, chapuza
	}

	ISR(TIMER2_COMPB_vect)
	{
		cli();
				
		if(_ticks == ticks_usuario )
		{
			LASER_LOW();
		}
		
		if(_ticks == 255)
		{
			DISABLE_TIMER_IRQ();	// De momento no usaremos más el timer	
			_send_ready = true;		// se envió el dato, podemos enviar uno nuevo
		}

		_ticks++;	
	
		sei();
	}









