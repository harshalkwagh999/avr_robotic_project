/* Checking External Interrupts i.e Hardware interrupt  */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT1_vect){
  int i;
  for(i=0;i<3;i++)
    {
      PORTB = 0xFF;
      _delay_ms(50);
      PORTB = 0x00;
      _delay_ms(50);
    } //debouce so that ISR is not called many times in a single button press
}

ISR(INT0_vect){
  int i;
  for(i=0;i<3;i++)
    {
      PORTA = 0xFF;
      _delay_ms(50);
      PORTA = 0x00;
      _delay_ms(50);
    } //debouce so that ISR is not called many times in a single button press
}

int main()
{ 
  DDRA = 0xFF;
  DDRB = 0xFF;//set pin0 as output
  PORTB = 0x00;
  PORTA = 0x00;
  DDRD=0x00; //interrupt pins inputs, rest outputs
  
  cli(); //clear global interrupts
  GICR = 1 << INT1 | 1 << INT0; //enable intrupt on INT0
  //  SREG = 1 << 7;
  MCUCR |= 0 << ISC11 | 1 << ISC10;// on any logical change
  MCUCR |= 0 << ISC01 | 1 << ISC00; // on rising edge
  sei(); //enable global interrupts
  while(1){ }
  
  return 0;
}


