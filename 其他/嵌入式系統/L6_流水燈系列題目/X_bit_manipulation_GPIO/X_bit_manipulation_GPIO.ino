#define TIME_INTERVAL 100
void setup() {
  DDRD = 0xff;
  DDRB = 0xff;
}
void displayLED(uint8_t pattern) {
  PORTD = pattern; // 控制 D0 ~ D7
  PORTB = pattern >> 1;// 控制 D8 ~ D13
}
void loop() {
  uint8_t left = (1 << 6), right = 1;
  for(uint8_t i = 0; i < 6; i++) {
    uint8_t pattern = left | right;
    if(i == 0) pattern |= 1<<7;
    displayLED(pattern);
    delay(TIME_INTERVAL);
    left >>= 1;
    right <<= 1;
  }
}
// 使用 638 bytes