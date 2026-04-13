// #include <stdint.h>
#define MX 8
#define ARRSIZE 7
#define TIME_INTERVAL 1000
void setup() {
  for(uint8_t i = 0; i < MX; i++) {
    pinMode(i, OUTPUT);
  }
}
const uint8_t ledPatterns[] PROGMEM = {0x18, 0x3C, 0x66, 0xC3, 0x66, 0x3C, 0x18};
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
//使用 964 bytes