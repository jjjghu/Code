#include <ioavr.h>
#include <stdint.h>
#include <intrinsics.h>
#include "delay.h"
#include "button.h"
#include "seven_segment_display.h"
#include "ws8212b.h"

void displayDigit(uint8_t val)
{
  uint8_t temp = DECODER_PORT;
  temp &= 0xF0;
  temp |= val;
  DECODER_PORT = temp;
}

void display7SEG(int val)
{
  for (uint8_t i = 0; i < 4; i++)
  {
    PORTC |= (1 << DIG1) | (1 << DIG2) | (1 << DIG3) | (1 << DIG4);
    switch (i)
    {
    case 0:
      displayDigit(val % 10000 / 1000);
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

void Init_Routine(void)
{
  Init_RGBLED();
  Init_7SEG();
  INIT_ALL_BTN();
}
int main(void)
{
  Init_Routine();
  // display 0123 on the 7-segment display
  int val = 9990;
  int totalDelay = 0;
  display7SEG(val);
  Delay_10ms(1);
  for (;;)
  {
    if (S1_Pressed())
    {
      if(++val == 9999) val = 0;
      display7SEG(val);
      totalDelay = 4;
      setBlue();
      while(S1_Pressed()) { // ×ÔÐý£¬ÒÀÅfÐèÒªÓ‹Ëã delay
        display7SEG(val);
        totalDelay += 4;
        if(++totalDelay >= 100) {
          clearPixelColor();
        }
      }
    }
    else if(S2_Pressed()) {
      if(val == 0) val = 9999;
      else val--;
      display7SEG(val);
      totalDelay = 4;
      setOrange();
      while(S2_Pressed()) {
        display7SEG(val);
        totalDelay += 4;
        if(totalDelay >= 100) {
          clearPixelColor();
        }
      }
    }
    display7SEG(val);
    totalDelay += 4;
    if(totalDelay >= 100) {
      clearPixelColor();
    }
  }
  return 0;
}
