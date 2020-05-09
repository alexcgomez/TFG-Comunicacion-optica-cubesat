// Notas importantes:
// Arduino Uno, al ir a 16MHz, los micros no los lleva muy bien,
// así que la resolución de arduino es de múltiplos de 4
// ( vamos, que salta de 4 en 4 ), hay que tenerlo en cuenta para ajustar
// el TIM4 del STM32
// ARM, PB12 (PPM)      => Arduino, 3 (PPM)
// ARM, PB13 (Trigger)  => Arduino, 2 (IRQ In)

#define BIT_STOP 4
#define PIN_PPM 3
#define SIZE_BUFFER 4 // relacionado con el nº de paquetes que envía el ARM

volatile unsigned long tiempo = 0;
byte puntero = 0;
unsigned long paquetes[SIZE_BUFFER];
bool bit_start = true;
bool EOT = false;

void setup()
{
  Serial.begin(9600);
  //pinMode(PIN_IRQ, INPUT_PULLUP);
  pinMode(PIN_PPM, INPUT);
  //attachInterrupt(digitalPinToInterrupt(PIN_IRQ), ISR_pin_IRQ, FALLING); // high=>low = ISR IRQ
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, CHANGE); // cambio estado pin = ISR PPM
}

void loop()
{
  if (EOT == true)
  {
    Serial.println("Datos captados");

    for (int i = 0; i < SIZE_BUFFER; i++)
    {
      Serial.print((char)paquetes[i]);
    }
    Serial.println("");
    puntero = (SIZE_BUFFER + 1); // para evitar que se imprima todo el rato
    EOT = false;
  }
}

void ISR_pin_IRQ()
{
}

void ISR_pin_PPM()
{
  // si es la caída del clock ( final del
  // "byte"), nos interesa empezar de nuevo
  // ya que es cuando empieza un nuevo paquete.

  // Cuando esté en la subida, es que ya terminó
  // el antiguo y cronometramos el tiempo pasado

  if ( bit_start ) // sólo se usa para iniciar la trama
  {
    bit_start = false;
  }
  else
  {
    if ( digitalRead(PIN_PPM) == LOW )
    {
      tiempo = micros();
    }
    else // HIGH
    {
      char palabra = ((micros() - tiempo) / 133 );

      if (palabra < BIT_STOP ) // señal de stop
      {
        EOT = true; // end of transmision
        bit_start = true; // reset start para la próxima irq
        puntero = 0;
      }
      else // byte normal
      {
        paquetes[puntero] = palabra;
        puntero++;
      }
    }
  }
}



