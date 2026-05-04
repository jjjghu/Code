#include <ioavr.h>
#include <stdint.h>
#include <stdbool.h>
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

void display7SEG(uint8_t val)
{
  for (uint8_t i = 0; i < 2; i++)
  {
    PORTC |= (1 << DIG3) | (1 << DIG4);
    switch (i)
    {
    case 0:
      displayDigit(val / 10);
      break;
    case 1:
      displayDigit(val % 10);
      break;
    }
    PORTC &= ~(1 << (i + 2));
    Delay_1ms(2);
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
  uint8_t mode = 0;
  uint8_t val = 0;
  int totalDelay = 0;
  display7SEG(val);
  Delay_10ms(1);
  for (;;)
  {
    if (S1_Pressed())
    {
      mode = 1;
    }
    else if (S2_Pressed())
    {
      mode = 2;
    }
    else if (S3_Pressed())
    {
      val = 0;
    }
    Delay_1ms(1);
    totalDelay++;
    if (mode == 1)
    {
      if (totalDelay >= 250)
      {
        if (val == 99)
          val = 0;
        else
          val++;
        totalDelay = 0;
        setGreen();
        setGreen();
        updateRGBLED();
      }
    }
    else if (mode == 2)
    {
      if (totalDelay >= 100)
      {
        if (val == 0)
          val = 99;
        else
          val--;
        totalDelay = 0;
        setRed();
        setRed();
        updateRGBLED();
      }
    }
    display7SEG(val);
    totalDelay += 4;
    if (totalDelay >= 50)
    {
      clearPixelColor();
      clearPixelColor();
      updateRGBLED();
    }
  }
}
