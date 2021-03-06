/* To check input output to AVR pins */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include<avr/io.h>

int mydelay(long int timer);

int main()
{
  DDRB = 0x00;   //configure portB as input
  DDRA = 0xFF;   //configure portC as output
  PORTA=0;

  if(PIB && (1<<PB0))
    {
      PORTA=1;
    }
  /* while(1) */
  /*   { */
  /*     PORTA = 5; */
  /*     //  mydelay(100); */
  /*     //      PORTA=0; */
  /*     // break; */
  /*   } */
  return 0;
}

int mydelay(long int timer)
{
  timer=timer*1000;
  while(timer)
    {
      //      PORTA=1;
      timer--;
    }
  return 1;
}
