#define TIME_INTERVAL 1000
#define ARRSIZE 8
int main() {
  DDRD = 0xFF;
  while(true) {
    uint8_t left = 0x18, right = 0x18; // left: 往左, right 往右
    for(uint8_t i = 0; i < ARRSIZE; i++) {
      if(i == 4) {
        // 觸底反彈, right left 數值交換
        right = 0xC0, left = 0x03; // 11000011
      }
      PORTD = left | right;
      _delay_ms(TIME_INTERVAL);
      left <<= 1;
      right >>= 1;
    }
  }
}
// 使用 186 bytes
// 0 bytes