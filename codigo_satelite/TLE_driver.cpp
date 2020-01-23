#include "Arduino.h"
#include "TLE_driver.hpp"


void TLE_DRIVER::init()
{
	#if TLE_DEBUG == 1 		// esto no llegará a compilarse, se lo come el preprocesador
		Serial.begin(9600);
		Serial.println("TLE_driver.cpp. Modo debug TLE activo!"); 
	#endif
	
	pinMode( PIN_EMISOR_LASER, OUTPUT ); // Emisor -> salida
	// inicializar timer
}

void TLE_DRIVER::write( char *texto_write, int num_linea )
{

}

void TLE_DRIVER::read( char *texto_read, int num_linea ) // No devolver el string con un return, suele dar problemas con el stack
{

}


// IRQ timer 1
