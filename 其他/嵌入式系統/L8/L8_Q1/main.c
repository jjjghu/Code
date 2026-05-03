#include <stdint.h>
#include <intrinsics.h>
#include <ioavr.h>
#include "delay.h"
#include "button.h"
#define GLED 7
#define GLED_DIR DDRD
#define GLED_PORT PORTD
#define GLED_ON() GLED_PORT &= ~(1 << GLED)
#define GLED_OFF() GLED_PORT |= (1 << GLED)
#define Init_GLED() \
    GLED_OFF();     \
    GLED_DIR |= (1 << GLED)
int main(void)
{
    Init_GLED();
    PORTD = (1 << S1) | (1 << S2) | (1 << S3); // 0b00001110;
    for (;;)
    {
        // if press S1, make LED light until release it
        while (!(PIND & (1 << S1)))
        {
            GLED_ON();
        }
        GLED_OFF();
        if (!(PIND & (1 << S2))) // // if press S2, green light for 5 times, timeinterval = 100ms
        {
            for (uint8_t i = 0; i < 5; i++)
            {
                GLED_ON();
                Delay_1ms(100);
                GLED_OFF();
                Delay_1ms(100);
            }
        }
        else if (!(PIND & (1 << S3))) // eles if press S3, green light for 5 times, lightTimeInterval = 400ms, closeTimeInterval = 100ms
        {
            for (uint8_t i = 0; i < 5; i++)
            {
                GLED_ON();
                Delay_1ms(400);
                GLED_OFF();
                Delay_1ms(100);
            }
        }
    }
    return 0;
}