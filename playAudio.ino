
#include "soundtest.h"

#define  CS  8
#define  WR  9
#define  LDAC  10

short i = 0;

void setup() {
  //SET UP TIMER 1
cli(); //Disable global interrupts
TCCR1A = 0; //Reset Timer 1 Counter Control Register A
TCCR1B = 0; //Reset Timer 1 Counter Control Register B
//Set Timer 1 Output Compare Register A to desired frequency
//(16,000,000 / 16384) - 1 = 975
OCR1A = 975;
TCCR1B |= (1 << WGM12);  //Turn on CTC mode
TCCR1B |= (1 << CS10);   //Prescalar = 1 (no prescalar used)
TIMSK1 |= (1 << OCIE1A); //Enable timer interrupt
sei(); //Enable interrupts
  
  DDRC = 255; //make PORTC output
  pinMode(CS, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(LDAC, OUTPUT);

  digitalWrite(CS, HIGH);  //Set the CS high by default
  digitalWrite(WR, HIGH);  //Set the WR pin high by default
  digitalWrite(LDAC, LOW);
}

void loop() {
  
}


ISR(TIMER1_COMPA_vect)
{
  //Prepare IC for DAC conversion
  digitalWrite(CS, LOW);    //Ready the AD5330 for input
  digitalWrite(WR, LOW);    //Enable Writes on the AD5330
 PORTC = pgm_read_byte(&(data[i++]));
  if(i >= sizeof(data))
      i = 0;
 //Prepare IC for DAC conversion
 digitalWrite(WR, HIGH);    //Enable Writes on the AD5330
  digitalWrite(CS, HIGH);    //Ready the AD5330 for input
  
}
