#include "TLE_protocol.hpp"
#include "PWM_driver.hpp"

/*
 To do:
 - Los datos constantes, moverlos en la EEPROM ( nombre del módulo ). ¿Qué cosas mover?. Habrá que implementarlo
 - Comando para poder cambiar los tiempos desde comandos ( lo deje en la EEPROM )
 - 
 - 
 */

//TLE tle; // temporal


void setup()
{
	Serial.begin(9600);
	
	_driver_init(); // Init TLE driver ( parte hardware, IRQs, pines, etc )
	Serial.println("Sending, super slow speed...");
	_driver_write("Hola\n", 5);
	Serial.println("done!");
}

void loop()
{
}
