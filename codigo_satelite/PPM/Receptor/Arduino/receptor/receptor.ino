#define BIT_START 0
#define BIT_DATA 1
#define BIT_STOP 2
#define PIN_PPM 3
#define SIZE_BUFFER 4 // relacionado con el nº de paquetes que envía el ARM

volatile unsigned long tiempo = 0;
byte tick = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Listo para recibir!");
  pinMode(PIN_PPM, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, FALLING); // cambio estado pin = ISR PPM
}

void loop() {}

void ISR_pin_PPM() {}