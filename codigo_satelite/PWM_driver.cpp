#include "Arduino.h"
#include "PWM_driver.hpp"

#define PWM_DEBUG	1 // apagar si no se va a debuggear

	volatile unsigned char _temporal_estado_laser = 0;
	bool _new_packet = false; // modo read
	bool _send_ready = false; // modo write
	
void _driver_init()
{
	#if PWM_DEBUG == 1 		// esto no llegará a compilarse, se lo come el preprocesador
		Serial.begin(9600);
		Serial.println("PWM_driver.cpp. Modo debug TLE activo!"); 
	#endif
	
	LASER_OUTPUT();
	
	// Modo, comparamos OCR0B con TCNT0.
	// Cuando valgan igual, entra en la IRQ.
	// Entra 2 veces en la IRQ (mirar el código del ISR()):
	// Primera: cuando el timer y el valor del usuario son iguales
	// Segunda: cuando el timer vale 255 ( terminó el duty cycle)
	
	PRESCALING_1024(); 		// Menor división, más velocidad.
	DISABLE_TIMER_IRQ(); 	// de momento no queremos disparar el contador

	sei();				// activamos interrupciones
	_send_ready = true; // podemos enviar;
}

void _driver_write( char *_text, int text_size )
{
	for(int i = 0; i < text_size; )
	{
		if( _driver_can_send() )
		{
			_driver_send_byte( _text[i] );
			_driver_can_send(false);	// hasta que no termine, no se envía uno nuevo
			i++;
		}
	}
	_driver_can_send(true); // para nuevo paquete
}

void _driver_read( char *_text, int text_size ) // No devolver el string con un return, suele dar problemas con el stack
{

}

ISR(TIMER0_COMPB_vect) // cuando TCNT0 y OCR0B valgan igual, entra
{
	cli();					// para evitar saltar a otras interrup. las apagamos temporalmente

	#if PWM_DEBUG == 1
		Serial.print(_temporal_estado_laser);
	#endif

	if( TIMER == USER_COUNTER)
	{
		LASER_LOW();		// apagamos el láser
		USER_COUNTER = 255;	// Queremos que entre de nuevo cuando valga 255 para apagar
	}
	
	if( TIMER == 255) // cuando terminemos el duty cycle, podemos enviar nuevo paquete
	{
		#if PWM_DEBUG == 1
			Serial.println("");
		#endif
		
		RESET_TIMER();		// De momento no usaremos más el timer
		DISABLE_TIMER_IRQ();
				
		_driver_can_send(true);	// se envió el dato, podemos enviar uno nuevo
	}
 
	sei();					// IRQs activas de nuevo
}















