/* Automation Demo of Robotic arm movement */
 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define D0 eS_PORTB0
#define D1 eS_PORTB1
#define D2 eS_PORTB2
#define D3 eS_PORTB3
#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define DEFAULT_DL 350;
#define OL1 10
int Move_flag=1,i=0;
unsigned char key,cmdArr[]={0x7e,0xbe,0x00};
char buff[10];
long int mot1_L=0,mot1_R=0,mot2_U=0,mot2_D=0,mot3_U=0,mot3_D=0,mot4_B=0,mot4_U=0;
long int motors_reading[7][1]={{132},{97},{130},{136},{122},{6},{100}};

int delay(long int timer,unsigned char key)
{
  timer=timer*200;
  mot4_B=0;
  while(timer)
    {
      if(PIND!= 0)
       	{
	  
       	  PORTA=0;
       	  PORTA=PIND;
       	  _delay_ms(30);
       	  break;
       	}
      if(key == 'B')
	{
	  mot1_L--;mot1_R++;
	  if(mot1_R > (motors_reading[4][0]*200))
	    {
	      Lcd8_Clear();
	      Lcd8_Write_String("Sensor 1 Failed");

	      PORTA=0;
	      PORTA=64;
	      mot1_L+=1000;mot1_R-=1000;
	  
	      _delay_ms(30);
	      PORTA=0;
	      break;
	    }	
	}
      else  if(key == 'A')
	{
	  mot1_L++;mot1_R--;
	  if(mot1_L > (motors_reading[0][0]*200))
	    {
	      Lcd8_Clear();
	      Lcd8_Write_String("Sensor 2 Failed");

	      PORTA=0;
	      PORTA=128;
	      mot1_L-=1000;mot1_R+=1000;	  
	      _delay_ms(30); PORTA=0;	      
	      break;
	    }
	  
	}

      else if(key == '3')
	{
	  mot2_D++;mot2_U--;
	  if(mot2_D > (motors_reading[1][0]*200))
	    {
	      
	      Lcd8_Clear();
	      Lcd8_Write_String("Sensor 3 Failed");

	      PORTA=0;
	      PORTA=32;
	      mot2_D-=1000;mot2_U+=1000;
	  
	      _delay_ms(30); PORTA=0;
	      break;
	  

	    }
	}
      else if(key == '6')
	{
	  
	  mot2_D--;mot2_U++;
	  if(mot2_U > (motors_reading[6][0]*200))
	    {
	      Lcd8_Clear();
	      Lcd8_Write_String("Sensor 4 Failed");

	      PORTA=0;
	      PORTA=16;
	      mot2_D+=1000;mot2_U-=1000;
	  
	      _delay_ms(30); PORTA=0;
	      break;

	    }
	
	}
 
      else if(key == '2')
	{
	  mot3_D++;mot3_U--;
	  if(mot3_D > (motors_reading[3][0]*200))
	    {
	      Lcd8_Clear();
	      Lcd8_Write_String("Sensor 5 Failed");

	      PORTA=0;
	      PORTA=4;
	      mot2_D-=1000;mot2_U+=1000;
	      _delay_ms(30); PORTA=0;
	      break;

	    }
	}
      else if(key == '5')
	{
	  
	  mot3_D--;mot3_U++;
	  if(mot3_U > (motors_reading[2][0]*200))
	    {
	      Lcd8_Clear();
	      Lcd8_Write_String("Sensor 6 Failed");

	      PORTA=0;
	      PORTA=8;
	      mot2_D+=1000;mot2_U-=1000;
	      _delay_ms(30); PORTA=0;
	      break;

	    }
	 
	}
      else if(key == '4')
	{
	  mot4_B++;
	  if(mot4_B > (motors_reading[5][0]*200))
	    {
	      Lcd8_Clear();
	      Lcd8_Write_String("Sensor 7 Failed");

	      PORTA=0;
	      PORTA=2;
	      mot4_B-=1000;
	      _delay_ms(30); PORTA=0;
	      break;

	    }
	}
 
      
      PORTD=0x00;
      timer--;
    }      
  return 0;
}


int original_pos()
{
  long int ol=110,temp=0;
  if(mot1_L<0)
    {
      PORTA=64;
      ol=((-1)*mot1_L)/200;
      delay(ol,'D');
      PORTA=0;
    }
  return 0;
}

int robot_move(unsigned char key)
{
  static int speed_flag=0,finish_flag=0,tmp_delay=0,val=0;
  static long int dl = DEFAULT_DL;

  if(speed_flag==0)
    {
      switch(key)                       // Decode the key                                      
       	{
	case 0x77:  // key='1' Forward M1;
	  PORTA=1;
      	  delay(dl,'1');
	  PORTA=0;
	  break;
	case 0x7b: // key='2' Forward M3;
	  PORTA=8;
	  delay(dl,'2');
	  PORTA=0;
	  break;
	case 0x7d: // key='3' Forward M4;
	  PORTA=16;
	  delay(dl,'3');
	  PORTA=0;
	  break;
	case 0xb7:  // key='4' Backward M1;
	  PORTA=2;
	  delay(dl,'4');
	  PORTA=0;
	  break;
	case 0xbb: // key='5' Backward M3;
	  PORTA=4;
	  delay(dl,'5');
	  PORTA=0;
	  break;
	case 0xbd: // key='6' Backward M4;
	  PORTA=32;
	  delay(dl,'6');
	  PORTA=0;
	  break;
	case 0x7e: // key='A' Forward M5;
	  PORTA=64;
	  delay(dl,'A');
	  PORTA=0;
	  break;
	case 0xbe: // key='B' Backward M5;
	  PORTA=128;
	  delay(dl,'B');
	  PORTA=0;
	  break;
	case 0xeb: // key 0 to stop all motors
	  PORTA=0;
	  delay(dl,'0');
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
    {
      exit(0); }
  if(Move_flag == 1)
    {
      key=cmdArr[i++];
      sprintf(buff,"%x",key);
      Lcd8_Write_String(buff);

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
  DDRC = 0xFF;
  PORTB = 0xFF;
  PORTC = 0x00;

  Lcd8_Init();
  Lcd8_Cmd(0x0F);
 
  
 
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

