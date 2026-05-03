#include <stdint.h>
#include <stdbool.h>
#include "button.h"
#include "delay.h"
#include "ws8212b.h"
#define MX_FACTOR 50
void breathingLight(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
  for (int i = 0; i < 5; i++)
  {
    for (uint8_t factor = 0; factor <= MX_FACTOR; factor++)
    {
      setPixelColor((r1 * factor) / 100, (g1 * factor) / 100, (b1 * factor) / 100);
      setPixelColor((r2 * factor) / 100, (g2 * factor) / 100, (b2 * factor) / 100);
      updateRGBLED();
      delay_ms(10);
    }
    for (uint8_t factor = MX_FACTOR; factor > 0; factor--)
    {
      setPixelColor((r1 * factor) / 100, (g1 * factor) / 100, (b1 * factor) / 100);
      setPixelColor((r2 * factor) / 100, (g2 * factor) / 100, (b2 * factor) / 100);
      updateRGBLED();
      delay_ms(10);
    }
  }
}

int main(void)
{
  Init_RGBLED();
  INIT_ALL_BTN();
  Delay_10ms(50); // wait for pull up resistor stable
  for (;;)
  {
    if (isS1Pressed)
    {
      breathingLight(0, 20, 0, 0, 0, 0);
    }
    else if (isS2Pressed)
    {
      breathingLight(0, 0, 0, 20, 0, 0);
    }
    else if (isS3Pressed)
    {
      breathingLight(60, 15, 0, 60, 15, 0);
    }
  }
}