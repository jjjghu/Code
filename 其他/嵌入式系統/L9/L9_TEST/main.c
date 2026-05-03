#include <stdint.h>
#include "ws8212b.h"
#include "delay.h"
void setPixelColor(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t val = ((uint32_t)g << 24) + ((uint32_t)r << 16) + ((uint32_t)b << 8);
    for (uint8_t i = 0; i < 24; i++)
    {
        if (val & 0x80000000UL)
        {
            wrOneToDIN();
        }
        else
        {
            wrZeroToDin();
        }
        val <<= 0x01;
    }
}

int main(void)
{
    Init_RGBLED();
    for (;;)
    {
        setPixelColor(60, 0, 0); // 第一個燈珠為紅
        setPixelColor(0, 0, 0);  // 第二個燈珠為無
        updateRGBLED();          // 實際顯示
        Delay_10ms(50);

        setPixelColor(0, 0, 0);  // 第一個燈珠為無
        setPixelColor(0, 60, 0); // 第二個燈珠為綠
        updateRGBLED();          // 實際顯示
        Delay_10ms(50);
    }
    return 0;
}