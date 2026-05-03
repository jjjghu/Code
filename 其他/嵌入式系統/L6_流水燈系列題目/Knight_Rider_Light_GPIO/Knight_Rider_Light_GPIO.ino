// #include <stdint.h>
#define MX 8
#define TIME_INTERVAL 250
void setup() {
  DDRD = 0xff;
}
void loop() {
  uint8_t pattern = 0x01;
  for(uint8_t i = 0; i < MX; i++) {
      PORTD = pattern;
      delay(TIME_INTERVAL);
      pattern <<= 1;
  }
  pattern = 1<<7;
  for(uint8_t i = MX; i > 0; i--) { // 需要注意 uint8_t 類型只能表示 0 與正整數
      PORTD = pattern;
      delay(TIME_INTERVAL);
      pattern >>= 1;
  }
}
//使用 990 bytes