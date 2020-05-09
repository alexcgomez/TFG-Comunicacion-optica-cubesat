// Notas importantes:
// Arduino Uno, al ir a 16MHz, los micros no los lleva muy bien,
// así que la resolución de arduino es de múltiplos de 4
// ( vamos, que salta de 4 en 4 ), hay que tenerlo en cuenta para ajustar
// el TIM4 del STM32
// ARM, PB12 (PPM)      => Arduino, 3 (PPM)
// ARM, PB13 (Trigger)  => Arduino, 2 (IRQ In)

#define BIT_STOP 20
#define PIN_PPM 3
#define SIZE_BUFFER 4 // relacionado con el nº de paquetes que envía el ARM

// Volatile para dejar la variable en RAM y no en stack
volatile unsigned long tiempo = 0;
unsigned int puntero = 0;
unsigned long paquetes[SIZE_BUFFER];
bool bit_start = true;
bool EOT = false;
volatile char palabra = 'a';

void setup()
{

  Serial.begin(9600);
  Serial.println("Listo para recibir!");
  //pinMode(PIN_IRQ, INPUT_PULLUP);
  pinMode(PIN_PPM, INPUT);
  //attachInterrupt(digitalPinToInterrupt(PIN_IRQ), ISR_pin_IRQ, FALLING); // high=>low = ISR IRQ
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, CHANGE); // cambio estado pin = ISR PPM
}

void loop()
{
  if (EOT == true)
  {
    Serial.print("tamaño puntero: ");
    Serial.println(puntero);
    puntero = 0;
    /*
    Serial.println("Datos captados");

    for (int i = 0; i < SIZE_BUFFER; i++)
    {
      Serial.print((char)paquetes[i]);
    }
    Serial.println("");
    //puntero = (SIZE_BUFFER + 1); // para evitar que se imprima todo el rato
    */
    EOT = false;
  }
}

void ISR_pin_PPM()
{
  cli();
  // si es la caída del clock ( final del
  // "byte"), nos interesa empezar de nuevo
  // ya que es cuando empieza un nuevo paquete.

  // Cuando esté en la subida, es que ya terminó
  // el antiguo y cronometramos el tiempo pasado

  if (bit_start) // sólo se usa para iniciar la trama
  {
    if (palabra <= BIT_STOP) // señal de stop
    {
    } // no hacemos nada, está cayendo el flanco
    else
    {
      bit_start = false;
      Serial.println("St");
    }
  }
  else
  {
    if (digitalRead(PIN_PPM) == LOW)
    {
      tiempo = micros();
      Serial.println("i");
    }
    else // HIGH
    {
      unsigned long _t_tiempo = micros();
      palabra = ((_t_tiempo - tiempo) / 133);
      Serial.print("w:");
      Serial.println(palabra, DEC);

      if (palabra <= BIT_STOP) // señal de stop
      {
        Serial.println("Sp");
        EOT = true;       // end of transmision
        bit_start = true; // reset start para la próxima irq
        //puntero = 0;
      }
      else // byte normal
      {
        paquetes[puntero] = palabra;
        puntero++;
      }
    }
  }
  sei();
}
