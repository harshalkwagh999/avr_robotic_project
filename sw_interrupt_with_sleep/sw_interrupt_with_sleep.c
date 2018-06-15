/* using sleep instead of while in interrupt program */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
//#include<avr/io.h>
#include<avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


ISR(TIMER1_OVF_vect)
{
  
  // XOR PORTA with 0x02 to toggle the LSB                                                             
  // PORTA=PORTA ^ 0x01;
  //  PORTA = 64;
  PORTA = PORTA ^ 32;
  PORTB = 64;
  TIMSK=(1<<TOIE1);//(1<<TOIE0);
  TCNT1=0x00;
  sei();
  //  sleep_cpu();
}

int main()
{
  // Configure PORTA as output                                                                         
  DDRA = 0xFF;
  PORTA = 0x00;
  DDRB = 0xFF;
  PORTB = 0x00;
  int t;
  // enable timer overflow interrupt for both Timer0 and Timer1                                        
  TIMSK=(1<<TOIE1);//(1<<TOIE0);

  // set timer0 counter initial value to 0                                                             
  TCNT1=0x00;

  // start timer0 with /1024 prescaler                                                                 
  //  TCCR0 = (1<<CS02) | (1<<CS00);

  // lets turn on 16 bit timer1 also with /64
  TCCR1B |= (0 << CS12) |(1 << CS11) | (1 << CS10);
  //  cli();
  // enable interrupts                                                                                 
  sei();
  while(1)
    {
      t=500000;
      //      set_sleep_mode(0);
      //  cli();
      // sleep_enable();
      //  PORTA=PORTA ^ 64;
      PORTB=0x00;
      while(t--);
      // sleep_cpu();
      // sleep_disable();
    }
  return 0;
}
