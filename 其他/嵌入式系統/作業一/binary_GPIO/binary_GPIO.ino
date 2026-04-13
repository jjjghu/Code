// #include <stdint.h>
#define MX 8
#define TIME_INTERVAL 250
void setup() {
  DDRD = 0xff;
}
void loop() {
  for(uint8_t i = 0;; i++) { // 注意，程式會在這個 for 迴圈自旋
    PORTD = i;
    delay(TIME_INTERVAL);
  }
  // for(uint16_t i = 0; i < (1<<MX); i++) { // 避免自旋的寫法, 612 bytes
  //   PORTD = i;
  //   delay(TIME_INTERVAL);
  // }
}
// 使用 588 bytes