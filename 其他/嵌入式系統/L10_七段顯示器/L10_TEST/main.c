#include <ioavr.h>
#include <stdint.h>
#include <intrinsics.h>
#include "delay.h"
#include "gled.h"
#include "seven_segment_display.h"
#include "ws8212b.h"
void displayDigit(uint8_t val)
{
  uint8_t temp = DECODER_PORT;
  temp &= 0xF0;
  temp |= val;
  DECODER_PORT = temp;
}

void Init_Routine(void)
{
  Init_GLED();
  Init_RGBLED();
  Init_7SEG();
}
int main(void)
{
  Init_Routine();
  // display 0123 on the 7-segment display
  uint8_t val = 123;
  for (;;)
  {
    for (uint8_t i = 0; i < 4; i++)
    {
      PORTC |= (1 << DIG4) | (1 << DIG3) | (1 << DIG2) | (1 << DIG1);
      switch (i)
      {
      case 0:
        displayDigit(val / 1000);
        break;
      case 1:
        displayDigit(val % 1000 / 100);
        break;
      case 2:
        displayDigit(val % 100 / 10);
        break;
      case 3:
        displayDigit(val % 10);
        break;
      }
      PORTC &= ~(1 << i);
      Delay_1ms(1);
    }
  }
  return 0;
}
