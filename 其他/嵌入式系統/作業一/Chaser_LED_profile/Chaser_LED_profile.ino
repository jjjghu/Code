// #include <stdint.h>
// #include <avr/pgmspace.h> // PROGMEM 需要的標頭，有時預設已經 include
#include "profile.h"
void setup() {
  for(uint8_t i = 0; i < MX; i++) {
    pinMode(i, OUTPUT);
  }
}
const uint8_t ledPatterns[] PROGMEM = {LED_PATTERN0, LED_PATTERN1, LED_PATTERN2, LED_PATTERN3, LED_PATTERN4, LED_PATTERN5, LED_PATTERN6, LED_PATTERN7};
void displayLED(uint8_t x) {
  for(uint8_t j = 0; j < 8; j++) {
    digitalWrite(j, (x >> j) & 0x01);
  }
}
void loop() {
  for(uint8_t i = 0; i < ARRSIZE; i++) {
    displayLED(pgm_read_byte(&ledPatterns[i]));
    delay(TIME_INTERVAL);
  }
}
//使用 962 bytes
// 9 bytes