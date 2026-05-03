#define MX 13
#define TIME_INTERVAL 100
void setup() {
  for(uint8_t i = 0; i <= MX; i++) {
    pinMode(i, OUTPUT);
  }
}

const uint8_t ledPatterns[] PROGMEM = {
  0x41, // 1000001
  0x22, // 0100010
  0x14, // 0010100
  0x08, // 0001000
  0x14, // 0010100
  0x22, // 0100010
};

void displayLED(uint8_t x) {
  for(uint8_t j = 0; j < 7; j++) {
    digitalWrite(j, (x >> j) & 0x01);
    digitalWrite(7 + j, (x >> j) & 0x01);
  }
}

void loop() {
  for(uint8_t i = 0; i < 6; i++) {
    displayLED(pgm_read_byte(&(ledPatterns[i])));
    delay(TIME_INTERVAL);
  }
}
// 使用 984 bytes