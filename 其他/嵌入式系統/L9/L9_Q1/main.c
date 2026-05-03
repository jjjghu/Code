#include <stdint.h>
#include <ioavr.h>
#include "delay.h"
#include "button.h"
#include "ws8212b.h"
#include <stdbool.h>
int main(void)
{
  bool state = false;
  INIT_ALL_BTN();
  Init_RGBLED();
  Delay_10ms(10);
  for(;;){
    if(isS1Pressed)  {
      state = !state;
      while(isS1Pressed) {};
    }
    Delay_10ms(10);
    if(state) {
        setPurple();
        setOrange();
    }
    else {
      setCyan();
      setDarkGreen();
    }
    updateRGBLED();
  }
}