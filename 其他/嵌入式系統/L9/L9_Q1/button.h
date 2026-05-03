#ifndef _BUTTON_H
#define _BUTTON_H
#define S1 2 
#define S2 3
#define S3 4 
#define isS1Pressed !(PIND & (1<<S1))
#define isS2Pressed !(PIND & (1<<S2))
#define isS3Pressed !(PIND & (1<<S3))
#define INIT_ALL_BTN() PORTD |= (1<<S1) | (1<<S2) | (1<<S3)
#endif 