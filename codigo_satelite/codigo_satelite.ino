#define TLE_DEBUG		1	// Si no se va a debuggear, poner a 0
#include "TLE_protocol.hpp"

/*
 To do:
 - Los datos constantes, moverlos en la EEPROM ( nombre del módulo ). ¿Qué cosas mover?
 - 
 - 
 - 
 */

TLE asd; // temporal

void setup()
{
  asd.init();	// temporal, mirar que todo tira
  //Serial.print( sizeof(asd.TLE_buffer[0]) );


}

void loop()
{


}
