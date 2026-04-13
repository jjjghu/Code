// #include <stdint.h>
#define MX 8
#define TIME_INTERVAL 250
void setup() {
  for(uint8_t i = 0; i < MX; i++) {
    pinMode(i, OUTPUT);
  }
}
void displayLED(uint8_t x) {
  for(uint8_t j = 0; j < MX; j++) {
    digitalWrite(j, (x >> j) & 0x01);
  }
}
void loop() {
  for(uint8_t i = 0;; i++) { // 注意，程式會在這個 for 迴圈自旋
    displayLED(i);
    delay(TIME_INTERVAL);
    // for(int i = 0; i < (1<<MX); i++) { 避免自旋的寫法, 950 bytes
    //   displayLED(i);
    //   delay(TIME_INTERVAL);
    // }
  }
}
// 使用 926 bytes