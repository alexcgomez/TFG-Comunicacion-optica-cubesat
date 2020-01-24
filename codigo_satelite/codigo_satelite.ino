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
PWM_driver driver;

void setup()
{
  tle.init();	// temporal, mirar que todo tira
  
  delay(1500);
  driver.init(); // Init TLE driver ( parte hardware, IRQs, pines, etc )
  driver.send_byte('A');
  
  

}

void loop()
{


}
