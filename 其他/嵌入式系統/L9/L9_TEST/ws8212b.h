#ifndef _WS2812B_H
#define _WS2812B_H
#include <ioavr.h>
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
#endif