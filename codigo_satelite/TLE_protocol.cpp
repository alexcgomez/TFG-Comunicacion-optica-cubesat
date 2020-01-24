#include "TLE_protocol.hpp"
#include "PWM_driver.hpp"

#define TLE_DEBUG	1 // apagar si no se va a debuggear

//PWM_driver driver;

void TLE::init()
{
	#if TLE_DEBUG == 1 		// esto no llegará a compilarse, se lo come el preprocesador
		Serial.begin(9600);
		Serial.println("TLE_Protocol.cpp. Modo debug TLE activo!"); 
	#endif
	
	//driver.init(); // Init TLE driver ( parte hardware, IRQs, pines, etc )	
}

// Title
void TLE::set_title( char* _title)
{
	#if TLE_DEBUG == 1 
		Serial.print("Debug: TLE.cpp. set_title: ");
		Serial.println( _title );
	#endif
	
	// añadir aquí el código

}

void TLE::get_title( char* _title) // No devolver el string con un return, suele dar problemas con el stack
{
	#if TLE_DEBUG == 1 
		Serial.print("Debug: TLE.cpp. get_title: ");
		Serial.println( _title );
	#endif
	
	// añadir aquí el código
}

// Line 1 & Line 2

// Line 1

// Line 2
















