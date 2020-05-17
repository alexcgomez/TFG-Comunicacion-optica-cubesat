<<<<<<< HEAD
#include "constants.h"
=======
/*
  Notas importantes:

  Arduino Uno, al ir a 16MHz, los micros no los lleva muy bien,
  así que la resolución de arduino es de múltiplos de 4
  ( vamos, que salta de 4 en 4 ), hay que tenerlo en cuenta para ajustar
  el TIM4 del STM32
*/

// ARM, PB12 (PPM)      => Arduino, 3 (PPM)
#define PIN_PPM 3

#define BIT_START 0
#define BIT_DATA 1
#define BIT_STOP 4

#define SIZE_BUFFER 5 // relacionado con el nº de paquetes que envía el ARM
>>>>>>> c3355400b1fe64584086f367d8d36098df8d06dd

volatile unsigned char flanco = BIT_START;
volatile unsigned long tiempo = 0;
<<<<<<< HEAD
byte tick = 0;
=======
volatile char paquetes[(SIZE_BUFFER)];
volatile byte puntero = 0;
volatile byte bit_start = BIT_START;
volatile bool EOT = false;
>>>>>>> c3355400b1fe64584086f367d8d36098df8d06dd

void setup()
{
  Serial.begin(9600);
<<<<<<< HEAD
  Serial.println("Listo para recibir!");
=======
  Serial.println("Init!");

>>>>>>> c3355400b1fe64584086f367d8d36098df8d06dd
  pinMode(PIN_PPM, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, CHANGE); // cambio estado pin = ISR PPM
}

void loop() {}

void ISR_pin_PPM()
{
  switch (flanco)
  {
<<<<<<< HEAD
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
=======
    imprimir_datos_recibidos();
    reset_variables_ppm();
    EOT = false;
  }
}

void ISR_pin_PPM()
{
  switch (bit_start)
  {
  case BIT_START: // Sólo se usa para iniciar la trama
    bit_start++;
    break;

  case BIT_DATA: // Data
  default:

    switch (digitalRead(PIN_PPM))
    {
    case LOW:
      tiempo = micros();
      break;

    case HIGH:
      char palabra = ((micros() - tiempo) / 133);

      if (palabra <= BIT_STOP) // if señal de stop => end of transmission
      {
        EOT = true;
      }
      else // byte normal
      {
        paquetes[puntero] = palabra;
        puntero++;
      }
      break;
    }
    break;
  }
}

void reset_variables_ppm()
{
  puntero = 0;
  bit_start = BIT_START; // reset start para la próxima irq
  tiempo = 0;
}

void imprimir_datos_recibidos()
{
  Serial.print("Data: ");

  for (int i = 0; i < sizeof(paquetes); i++)
  {
    Serial.print((char)paquetes[i]);
  }
  Serial.println("");
>>>>>>> c3355400b1fe64584086f367d8d36098df8d06dd
}