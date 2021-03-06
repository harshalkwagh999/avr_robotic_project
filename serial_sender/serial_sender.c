/* Code for sender in serial communication without USART */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
uint8_t input[10],i;

ISR(TIMER0_OVF_vect)
{
  if(input[i]==0)
    {
      PORTB = 0x00;
      _delay_ms(10);
      PORTB = 0x01;
      _delay_ms(10);
      PORTB = 0x00;
      _delay_ms(10);
    }
  else if(input[i]==1)
    {
      PORTB= 0x01;
      _delay_ms(10);
      PORTB= 0x00;
      _delay_ms(10);
      PORTB= 0x01;
      _delay_ms(10);
    }
  if(i==10)
    {
      PORTB= 0x00;
      _delay_ms(10);
      PORTB= 0x00;
      _delay_ms(10);
      PORTB= 0x01;
      _delay_ms(10);
    }
  
  i++;
  
}

int main()
{
  uint8_t j,k;

  DDRB=0x00;

  while(1)
    {
      if(PINB | 1 << PB0)
	{
	  DDRB=0xFF;
	  PORTB=0x01;
	  _delay_ms(10);
	  break;
	}
    }

   for(i=0;i<10;i++)
    {
      input[i]=1;
    }

  /*  for(i=0;i<10;i++)
    {
      for(j=0;j<10;j++)
	{
	  if(i%2==0)
	    {
	      if(j%2==0)
		{
		  input[10*i+j]=0;
		}
	      else
		{
		  input[10*i+j]=1;
		}
	    }
	  else
	    {
	      if(j%2==0)
		{
		  input[10*i+j]=1;
		}
	      else
		{
		  input[10*i+j]=0;
		}
	      
	    }
	}
    }
  */
  i=0;  
  // enable timer overflow interrupt for both Timer0 and Timer1
  TIMSK=(1<<TOIE0);

  // set timer0 counter initial value to 0
  TCNT0=0x00;

  // start timer0 with /1024 prescaler
  TCCR0 = (1<<CS01) | (1<<CS00);

  // enable interrupts
  sei();

  while(1) {
  }



  return 0;
}


