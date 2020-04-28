/*
  Notas importantes:
  
  Arduino Uno, al ir a 16MHz, los micros no los lleva muy bien,
  así que la resolución de arduino es de múltiplos de 4
  ( vamos, que salta de 4 en 4 ), hay que tenerlo en cuenta para ajustar
  el TIM4 del STM32
*/

// ARM, PB12 (PPM)      => Arduino, 3 (PPM)
// ARM, PB13 (Trigger)  => Arduino, 2 (IRQ In)

#define PIN_IRQ 2
#define PIN_PPM 3

volatile unsigned long tiempo = 0;

#define SIZE_BUFFER 4 // relacionado con el nº de paquetes que envía el ARM
byte puntero = 0;
unsigned long paquetes[SIZE_BUFFER];

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_IRQ, INPUT_PULLUP);
  pinMode(PIN_PPM, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_IRQ), ISR_pin_IRQ, FALLING); // high=>low = ISR IRQ
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, RISING); // low=>high = ISR PPM
}

void loop()
{
  if(puntero == SIZE_BUFFER )
  {
    Serial.println("Datos captados");
    
    for(int i = 0; i < SIZE_BUFFER; i++)
    {
      Serial.print((char)paquetes[i]);
    }
    puntero = (SIZE_BUFFER + 1); // para evitar que se imprima todo el rato
  }
}

void ISR_pin_IRQ()
{
  tiempo = micros();
}


void ISR_pin_PPM()
{
  paquetes[puntero] = ((micros() - tiempo) / 132 );
  puntero++;
}
