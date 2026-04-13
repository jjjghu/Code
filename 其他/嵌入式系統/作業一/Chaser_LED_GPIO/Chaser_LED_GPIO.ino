// #include <stdint.h>
// #include <avr/pgmspace.h> // PROGMEM 需要的標頭，有時預設已經 include
#define MX 8
#define ARRSIZE 8
#define TIME_INTERVAL 100
void setup() {
  DDRD = 0xFF;
}
void loop() {
  uint8_t pattern = 1;
  for(uint8_t i = 0; i < ARRSIZE; i++) {
    PORTD = pattern;
    delay(TIME_INTERVAL);
    pattern <<= 1;
  }
}
//使用 608 bytes
// 9 bytes