void setup() {
  for(uint8_t i = 0; i < 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}
void loop() {
  uint8_t cur = 0;
  while(++cur < 8) {
    digitalWrite(cur, HIGH);
    delay(100);
    digitalWrite(cur, LOW);
  }
}
//使用 flash 928 bytes