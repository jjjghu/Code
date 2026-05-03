#ifndef _WS2812B_H
#define _WS2812B_H
#include <ioavr.h>
#include <stdint.h>
#include <intrinsics.h>
#define NOP() __no_operation()
#define Delay_100us() __delay_cycles((16000000UL / 1000000UL) * (100))
#define DIN 5
#define DIN_DIR DDRB
#define DIN_PORT PORTB
#define Set_DIN_High() DIN_PORT |= (1 << DIN)
#define Set_DIN_Low() DIN_PORT &= ~(1 << DIN)
#define wrZeroToDin()                    \
    Set_DIN_High();                      \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    Set_DIN_Low();                       \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               
#define wrOneToDIN() Set_DIN_High(); \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    Set_DIN_Low();                       \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();                               \
    NOP();
#define updateRGBLED() \
    Set_DIN_Low();     \
    Delay_100us()
#define Init_RGBLED()        \
    DIN_PORT &= ~(1 << DIN); \
    DIN_DIR |= (1 << DIN)

#define setDarkGreen() setPixelColor(1, 20, 1); // Dark Green 
#define setOrange() setPixelColor(20, 5, 0); // orange
#define setPurple() setPixelColor(20, 0, 20); // purple 
#define setCyan() setPixelColor(0, 20, 20); // cyan 
      
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
#endif