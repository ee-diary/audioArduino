#include "soundtest.h"

short i = 0;

void setup() {
  // put your setup code here, to run once:
  DDRC = 255;
}

void loop() {
  // put your main code here, to run repeatedly:
   PORTC = pgm_read_byte(&(data[i++]));
  if(i >= sizeof(data))
      i = 0;
    delayMicroseconds(62);
}
