#define MX 13
#define ARRSIZE 6
#define TIME_INTERVAL 1000
void setup() {
  DDRD = 0xff;
  DDRB = 0xff;
}

const uint8_t ledPatterns[] PROGMEM = {
  0xC1, // 1100 0001
  0x22, // 0010 0010
  0x14, // 0001 0100
  0x08, // 0000 1000
  0x14, // 0001 0100
  0x22, // 0010 0010
};

void displayLED(uint8_t x) {
  PORTD = x; // 控制 D0 ~ D7
  PORTB = x>>1;// 控制 D8 ~ D13
}

void loop() {
  for(uint8_t i = 0; i < ARRSIZE; i++) {
    displayLED(pgm_read_byte(&(ledPatterns[i])));
    delay(TIME_INTERVAL);
  }
}
// 使用 984 bytes