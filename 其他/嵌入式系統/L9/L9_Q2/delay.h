#ifndef _DELAY_H
#define _DELAY_H
#include <stdint.h>
#include <intrinsics.h>
#define F_CPU 16e6
#define Delay_1us(us) __delay_cycles((F_CPU / 1e6) * (us))
#define Delay_1ms(ms) __delay_cycles((F_CPU / 1e3) * (ms))
#define Delay_10ms(count) Delay_1ms(count * 10)

void delay_ms(uint16_t ms) {
    while (ms--) {
        Delay_1ms(1);
    }
}

void delay_us(uint16_t us) {
    while (us--) {
        Delay_1us(1);
    }
}
#endif