#include <SoftwareSerial.h>

// ARM PA9,  TX => Arduino 2, Rx
// ARM PA10, RX => Arduino 3, Tx

SoftwareSerial mySerial(2, 3); // RX, TX
String text;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop()
{
  if(mySerial.available())
  {
    text = mySerial.readStringUntil('\n');
    Serial.println(text);
  }
}
