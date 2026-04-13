#define TIME_INTERVAL 250
#define ARRSIZE 9
const uint8_t patterns[2][ARRSIZE] PROGMEM = {
  {0x10, 0x18, 0x1C, 0x1E, 0x1F, 0x0F, 0x07, 0x03, 0x01}, 
  {0x0A, 0x15, 0x0A, 0x15, 0x01, 0x03, 0x07, 0x0F, 0x1F}
};
int main(void) {
  DDRD = 0xFF; // 0b11110000
  PORTC = 0x07; // pinMode(btn, INPUT_PULLUP);
  uint8_t curMode = 0; // 當前模式
  uint8_t idxs[2] = {0, 0};
  PORTD = (pgm_read_byte(&patterns[curMode][idxs[curMode]])<<3) & 0xF8; // 0x1111 1000
  for(;;) {
    if(!(PINC & 0x01)) { // 有按下 A0
      idxs[curMode] = (idxs[curMode] + 1);
      PORTD = (pgm_read_byte(&patterns[curMode][idxs[curMode]])<<3) & 0xF8;
      _delay_ms(TIME_INTERVAL);
    }
    else if(!(PINC & (1<<1))) { // 有按下 A1
      if(--idxs[curMode] == 0xFF) {
        idxs[curMode] = ARRSIZE - 1;
      }
      PORTD = (pgm_read_byte(&patterns[curMode][idxs[curMode]])<<3) & 0xF8;
      _delay_ms(TIME_INTERVAL);
    }
    else if(!(PINC & (1<<2))) { // 有按下 A2       
      curMode = (curMode + 1) & 0x02;
    }
  } 
}
// 196 0