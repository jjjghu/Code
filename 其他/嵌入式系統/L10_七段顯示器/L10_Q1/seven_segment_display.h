#ifndef _7SEG_DISPLAY_H
#define _7SEG_DISPLAY_H
#include <ioavr.h>
#include <stdint.h>
#define DIG1 0
#define DIG2 1
#define DIG3 2
#define DIG4 3
#define DIG_DIR DDRC
#define DIG_PORT PORTC
#define DECODER_A 0
#define DECODER_B 1
#define DECODER_C 2
#define DECODER_D 3
#define DECODER_DIR DDRB
#define DECODER_PORT PORTB
#define DP 4
#define DP_DIR DDRB
#define DP_PORT PORTB
#define Init_7SEG()                                                                            \
    DP_DIR |= (1 << DP);                                                                       \
    DP_PORT |= (1 << DP);                                                                      \
    DECODER_DIR |= (1 << DECODER_A) | (1 << DECODER_B) | (1 << DECODER_C) | (1 << DECODER_D);  \
    DECODER_PORT |= (1 << DECODER_A) | (1 << DECODER_B) | (1 << DECODER_C) | (1 << DECODER_D); \
    DIG_DIR |= ((1 << DIG1) | (1 << DIG2) | (1 << DIG3) | (1 << DIG4));                        \
    DIG_PORT |= ((1 << DIG1) | (1 << DIG2) | (1 << DIG3) | (1 << DIG4))
#define Set_DIG4_High DIG_PORT |= (1 << DIG4)
#define Set_DIG4_Low DIG_PORT &= ~(1 << DIG4);
#define Set_DIG3_High DIG_PORT |= (1 << DIG3)
#define Set_DIG3_Low DIG_PORT &= ~(1 << DIG3);
#define Set_DIG2_High DIG_PORT |= (1 << DIG2)
#define Set_DIG2_Low DIG_PORT &= ~(1 << DIG2);
#define Set_DIG1_High DIG_PORT |= (1 << DIG1)
#define Set_DIG1_Low DIG_PORT &= ~(1 << DIG1);
void displayDigit(uint8_t);
#endif
