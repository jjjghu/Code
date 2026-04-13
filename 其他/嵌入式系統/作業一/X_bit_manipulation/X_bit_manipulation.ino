#define MX 13
#define TIME_INTERVAL 1000
void setup() {
  for(uint8_t i = 0; i <= MX; i++) {
    pinMode(i, OUTPUT);
  }
}
void displayLED(uint8_t x) {
  for(uint8_t j = 0; j < 8; j++) {
    digitalWrite(j, (x >> j) & 0x01);
    digitalWrite(j + 7, (x >> j) & 0x01);
  }
}
uint8_t rev(uint8_t x) {
  // 將二進位的數字反轉。如 1010 -> 0101
  x = ((x & 0xaa) >> 1) | ((x & 0x55) << 1);
  x = ((x & 0xcc) >> 2) | ((x & 0x33) << 2);
  x = ((x & 0xf0) >> 4) | ((x & 0x0f) << 4);
  x >>= 1; // 只需要有效的七位數
  return x;
}
void loop() {
  uint8_t left = (1<<6);
  for(uint8_t i = 0; i < 6; i++) {
    displayLED(left | rev(left));
    left >>= 1;
    delay(TIME_INTERVAL);
  }
}
// 使用 1032 bytes