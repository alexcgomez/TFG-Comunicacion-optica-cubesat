// Notas importantes:
// Arduino Uno, al ir a 16MHz, los micros no los lleva muy bien,
// así que la resolución de arduino es de múltiplos de 4
// ( vamos, que salta de 4 en 4 ), hay que tenerlo en cuenta para ajustar
// el TIM4 del STM32
// ARM, PB12 (PPM)      => Arduino, 3 (PPM)
// ARM, PB13 (Trigger)  => Arduino, 2 (IRQ In)

#define BIT_START 0
#define BIT_DATA 1
#define BIT_STOP 2

#define PIN_PPM 3
#define SIZE_BUFFER 4 // relacionado con el nº de paquetes que envía el ARM

// Volatile para dejar la variable en RAM y no en stack
volatile unsigned long tiempo = 0;
byte tick = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Listo para recibir!");

  //pinMode(PIN_IRQ, INPUT_PULLUP);
  pinMode(PIN_PPM, INPUT);
  //attachInterrupt(digitalPinToInterrupt(PIN_IRQ), ISR_pin_IRQ, FALLING); // high=>low = ISR IRQ
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, FALLING); // cambio estado pin = ISR PPM
}

void loop()
{
  /*
  if (EOT == true)
  {
    // Serial.print("tamaño puntero: ");
    //Serial.println(puntero);
    //puntero = 0;
    
    Serial.println("Datos captados");

    for (int i = 0; i < SIZE_BUFFER; i++)
    {
      Serial.print((char)paquetes[i]);
    }
    Serial.println("");
    //puntero = (SIZE_BUFFER + 1); // para evitar que se imprima todo el rato
    
    EOT = false;
  }
  */
}

void ISR_pin_PPM()
{

  if (tick == BIT_START)
  {
    tick++;
    tiempo = micros();
  }
  else
  {
    Serial.print("Tick: ");
    Serial.print(tick++, DEC);
    Serial.print(" D: ");
    Serial.println((micros() - tiempo));
    tiempo = micros();
  }
}