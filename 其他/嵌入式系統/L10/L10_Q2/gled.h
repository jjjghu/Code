#ifndef GLED_H
#define GLED_H
#define GLED 7
#define GLED_DIR DDRD
#define GLED_PORT PORTD
#define GLED_ON() GLED_PORT &= ~(1 << GLED)
#define GLED_OFF() GLED_PORT |= (1 << GLED)
#define Init_GLED() \
    GLED_OFF();     \
    GLED_DIR |= (1 << GLED)
#endif