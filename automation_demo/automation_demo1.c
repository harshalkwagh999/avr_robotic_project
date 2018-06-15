/* Test For Software interrupt */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define DEFAULT_DL 1000

int Move_flag=1,i=0;
unsigned char key,cmdArr[]={0xbe,0x7e,0xbe,0x7e,0x00};

int robot_move(unsigned char key)
{
  static int speed_flag=0,finish_flag=0,tmp_delay=0,val=0;
  static long int dl=DEFAULT_DL;
  
  if(speed_flag==0)
    {
      switch(key)                       // Decode the key                                             
	{
	case 0x77:  // key='1' Forward M1;
	  PORTA=1;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0x7b: // key='2' Forward M3;
	  PORTA=8;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0x7d: // key='3' Forward M4;
	  PORTA=16;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0xb7:  // key='4' Backward M1;
	  PORTA=2;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0xbb: // key='5' Backward M3;
	  PORTA=4;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0xbd: // key='6' Backward M4;
	  PORTA=32;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0x7e: // key='A' Forward M5;
	  PORTA=64;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0xbe: // key='B' Backward M5;
	  PORTA=128;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0xeb: // key 0 to stop all motors
	  PORTA=0;
	  delay(dl);
	  PORTA=0;
	  break;
	case 0xde:  //key='C' Change the Delay ; 
	  speed_flag=1;                                                                               
	  break;
	}
    }
  else if(speed_flag==1)
    {
      switch(key)                       // Decode the key                             
	{
	case 0xeb: key='0';val=0; tmp_delay=tmp_delay*10+val;  break;
	case 0x77: key='1';val=1; tmp_delay=tmp_delay*10+val;  break;
	case 0x7b: key='2';val=2; tmp_delay=tmp_delay*10+val;  break;
	case 0x7d: key='3';val=3; tmp_delay=tmp_delay*10+val;  break;
	case 0xb7: key='4';val=4; tmp_delay=tmp_delay*10+val;  break;
	case 0xbb: key='5';val=5; tmp_delay=tmp_delay*10+val;  break;
	case 0xbd: key='6';val=6; tmp_delay=tmp_delay*10+val;  break;
	case 0xd7: key='7';val=7; tmp_delay=tmp_delay*10+val;  break;
	case 0xdb: key='8';val=8; tmp_delay=tmp_delay*10+val;  break;
	case 0xdd: key='9';val=9; tmp_delay=tmp_delay*10+val;  break;
	case 0xed: key='#';tmp_delay=0;  break;
	case 0xee: key='D';finish_flag=1;  break;
	}
	  
      if(finish_flag==1)
	{
	  if(tmp_delay >= 1 && tmp_delay <= 5000)
	    {
	      dl=tmp_delay; finish_flag=0; speed_flag=0; tmp_delay=0;
	    }
	  else
	    {
	      dl=DEFAULT_DL; finish_flag=0; speed_flag=0; tmp_delay=0;
	    }
	}
    }
  
  return 0;
}

ISR(TIMER0_OVF_vect)
{
 
  if(key == 0x00)
    {  exit(0); }
  if(Move_flag == 1)
    {
      key=cmdArr[i++];
      robot_move(key);
      Move_flag=0;
    }

  TIMSK |=(1<<TOIE0);
  TCNT0=0x00;
  sei();
}

ISR(TIMER1_OVF_vect)
{
  Move_flag=1;
  
  TIMSK |=(1<<TOIE1);
  TCNT1=0x00;
  sei();
}

int main()
{
  // Configure port A B as output and D as input
  DDRD = 0x00;
  DDRA = 0xFF;
  DDRB = 0xFF;
  PORTB = 0x00;
  key=cmdArr[0];

  // enable timer overflow interrupt for both Timer0 and Timer1
  TIMSK=(1<<TOIE0) | (1<<TOIE1);

  // set timer0 counter initial value to 0
  TCNT0=0x00;
  TCNT1=0x00;

  // start timer0 with /1024 prescaler
  TCCR0 = (1<<CS02) | (1<<CS00);
 
  // lets turn on 16 bit timer1 with /64
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // enable interrupts
  sei();
  while(true) {
  }
  
  return 0;
}

int delay(long int timer)
{
  timer=timer*200;
  
  while(timer)
    {
      if(PIND!= 0)
	{
	  PORTA=0;
	  PORTA=PIND;
	  _delay_ms(30);
	  break;
	}
      PORTD=0x00;
      timer--;
    }      

  return 0;
}
