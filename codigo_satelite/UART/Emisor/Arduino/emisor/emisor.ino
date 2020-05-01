// Envia hola por la terminal

void setup() {
Serial.begin(9600);

}

void loop() {
  Serial.print("hola");
  Serial.print('\n');
  delay(500);
}
