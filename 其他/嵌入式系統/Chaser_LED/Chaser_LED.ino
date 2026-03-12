#define MX 13
#define TIME_INTERVAL 1000
void setup() {
  for(uint8_t i = 0; i <= MX; i++) {
    pinMode(i, OUTPUT);
  }
}

const uint8_t ledPatterns[] PROGMEM = {
  0x41, // 0b1000001
  0x22, // 0b0100010
  0x14, // 0b0010100
  0x08, // 0b0001000
  0x14, // 0b0010100
  0x22, // 0b0100010
};

void displayLED(uint8_t x) {
  for(uint8_t j = 0; j < 7; j++) {
    digitalWrite(j, (x >> j) & 0x01);
    digitalWrite(7 + j, (x >> j) & 0x01);
  }
}

void loop() {
  for(uint8_t i = 0; i < 6; i++) {
    uint8_t pattern = pgm_read_byte(&(ledPatterns[i]));
    displayLED(pattern);
    delay(TIME_INTERVAL);
  }
}
// 使用 984 bytes