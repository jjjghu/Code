void setup() {
  for(uint8_t i = 0; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
}
void loop() {
  for(uint8_t i = 0; i < 8; i++) {
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
  }
}
// 920 bytes
// 9 bytes