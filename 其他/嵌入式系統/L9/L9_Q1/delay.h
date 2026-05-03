#ifndef _DELAY_H
#define _DELAY_H
#include <intrinsics.h>
#define F_CPU 16e6
#define Delay_1us(us) __delay_cycles((F_CPU / 1e6) * (us))
#define Delay_1ms(ms) __delay_cycles((F_CPU / 1e3) * (ms))
#define Delay_10ms(count) Delay_1ms(count * 10)
#endif