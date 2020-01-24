#include "TLE_protocol.hpp"
#include "PWM_driver.hpp"

/*
 To do:
 - Los datos constantes, moverlos en la EEPROM ( nombre del módulo ). ¿Qué cosas mover?. Habrá que implementarlo
 - 
 - 
 - 
 */

TLE tle; // temporal


void setup()
{
  tle.init();	// temporal, mirar que todo tira
  
  delay(1500);
  _driver_init(); // Init TLE driver ( parte hardware, IRQs, pines, etc )
  _driver_send_byte('A');
  
  

}

void loop()
{


}
