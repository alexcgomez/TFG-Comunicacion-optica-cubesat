// ARM, PB12 (PPM)      => Arduino, 3 (PPM)
// ARM, PB13 (Trigger)  => Arduino, 2 (IRQ In)

#define PIN_IRQ 2
#define PIN_PPM 3

volatile unsigned long tiempo = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_IRQ, INPUT_PULLUP);
  pinMode(PIN_PPM, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_IRQ), ISR_pin_IRQ, FALLING); // high=>low = ISR IRQ
  attachInterrupt(digitalPinToInterrupt(PIN_PPM), ISR_pin_PPM, RISING); // low=>high = ISR PPM
}

void loop(){}

void ISR_pin_IRQ()
{
  tiempo = millis();
}


void ISR_pin_PPM()
{
  Serial.print("PPM: ");
  Serial.println(  ((millis() - tiempo) / 90 ) );
}
