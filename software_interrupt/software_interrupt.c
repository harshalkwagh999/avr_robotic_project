/* Test For Software interrupt */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include<avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect)
{
  PORTA = PORTA ^ 32;

  TIMSK |=(1<<TOIE1);
  TCNT1=0x00;
  sei();
}

ISR(TIMER0_OVF_vect)
{
  PORTB = PORTB ^ 64; 

  TIMSK |=(1<<TOIE0);
  TCNT0=0x00;
  sei();
}

int main()
{
  //  int i=10;
  // Configure PORTA as output
  DDRA = 0xFF;
  PORTA = 0x00;
  DDRB = 0xFF;
  PORTB = 0x00;

  // enable timer overflow interrupt for both Timer0 and Timer1
  TIMSK=(1<<TOIE0) | (1<<TOIE1);

  // set timer0 counter initial value to 0
  TCNT0=0x00;
  TCNT1=0x00;
  // start timer0 with /1024 prescaler
  TCCR0 = (1<<CS02) | (1<<CS00);
 
  // lets turn on 16 bit timer1 with /64
  TCCR1B |= (1 << CS11) | (1 << CS10);
    //   TCCR1B |= (1 << CS00);
  // enable interrupts
  sei();
  while(true) {
  }
  
  return 0;
}


