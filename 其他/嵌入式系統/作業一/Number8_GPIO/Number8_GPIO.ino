// #include <stdint.h>
#define MX 8
#define ARRSIZE 4
#define TIME_INTERVAL 1000
void setup() {
  DDRD = 0xff;
}
const uint8_t ledPatterns[] PROGMEM = {0x18, 0x3C, 0x66, 0xC3, 0x66, 0x3C, 0x18};
void loop() {
  for(int8_t i = 0; i < ARRSIZE; i++) {
    PORTD = pgm_read_byte(&ledPatterns[i]);
    delay(TIME_INTERVAL);
  }
}
// 使用 626 bytes
// 9 bytes