#include "Arduino.h"
#include "PWM_driver.hpp"

#define PWM_DEBUG	1 // apagar si no se va a debuggear


void PWM_driver::init()
{
	#if PWM_DEBUG == 1 		// esto no llegará a compilarse, se lo come el preprocesador
		Serial.begin(9600);
		Serial.println("PWM_driver.cpp. Modo debug TLE activo!"); 
	#endif
	
	LASER_OUTPUT();
	PRESCALING_1024(); 	// prescaler -> F_CPU / 1024. Menor división, más velocidad
	RESET_TIMER();
	DISABLE_TIMER_IRQ(); // de momento no queremos disparar el contador
	sei();				// activamos interrupciones
	_send_ready = true; // podemos enviar;
}

void PWM_driver::write( char *_text, int text_size )
{
	for(int i = 0; i < text_size; )
	{
		if(_send_ready)
		{
			send_byte( _text[i] );
			_send_ready = false;	// hasta que no termine, no se envía uno nuevo
			i++;
		}
	}
	_packet_sent = true;
}

void PWM_driver::read( char *_text, int text_size ) // No devolver el string con un return, suele dar problemas con el stack
{

}

bool PWM_driver::is_sent()
{
	return _packet_sent;
}

bool PWM_driver::new_packet()
{
	return _new_packet;
}


ISR(TIMER0_COMPB_vect) // cuando el timer y el valor dado valgan igual, entra
{
	#if PWM_DEBUG == 1 		// esto no llegará a compilarse, se lo come el preprocesador
		Serial.println("T0"); 
	#endif
	
	cli();					// para evitar saltar a otras interrup. las apagamos temporalmente
	RESET_TIMER();
	LASER_LOW();			// apagamos el láser
	DISABLE_TIMER_IRQ();	// De momento no lo usaremos más
	sei();					// IRQs activas de nuevo
	_send_ready = true;		// se envió el dato, podemos enviar uno nuevo
}















