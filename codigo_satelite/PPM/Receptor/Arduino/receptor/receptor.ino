#include "constants.h"

volatile unsigned char flanco = BIT_START;
volatile unsigned long tiempo = 0;
byte tick = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Listo para recibir!");
  pinMode(PIN_PPM, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, CHANGE); // cambio estado pin = ISR PPM
}

void loop() {}

void ISR_pin_PPM()
{
  switch (flanco)
  {
  case BIT_START:

    if (digitalRead(PIN_PPM) == LOW)
    {
      Serial.println("x");
      tiempo = micros();
      flanco++;
    }
    break;

  default: // Data
    if (digitalRead(PIN_PPM) == HIGH)
    {
      Serial.println("y");
      Serial.print("D: ");
      uint16_t n = micros() - tiempo;
      Serial.println(n, DEC);
    }
    else // LOW
    {
      Serial.println("z");
      tiempo = micros();
    }

    // cuando el valor de data == stop ==> reiniciar flanco

    break;
  }
}