#ifndef _BUTTON_H
#define _BUTTON_H
#define BTN_PIN PIND
#define S1_PIN 2
#define S2_PIN 3
#define S3_PIN 4
#define S1_Pressed() !(BTN_PIN & (1 << S1_PIN))
#define S2_Pressed() !(BTN_PIN & (1 << S2_PIN))
#define S3_Pressed() !(BTN_PIN & (1 << S3_PIN))
#define INIT_ALL_BTN() BTN_PIN |= (1 << S1_PIN) | (1 << S2_PIN) | (1 << S3_PIN)
#endif