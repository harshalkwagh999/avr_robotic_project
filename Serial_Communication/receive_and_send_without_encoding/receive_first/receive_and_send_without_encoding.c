/* Sender first */
#define F_CPU 16000000UL

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

#include<avr/io.h>
#include<util/delay.h>
#include<stdbool.h>
#include "usart_avr.h"
#include <avr/lcd.h>

void send_packet(uint8_t  input_data[])
{
  int i=0;
  for(i=0;i<6;i++)
    {
      UWriteData(input_data[i]);
      _delay_loop_2(0);
      _delay_loop_2(0);
      _delay_loop_2(0);
      _delay_loop_2(0);
    }
}

int main(void)
{
  DDRB = 0xFF;// make PORTD as output for lcd data pins
  DDRC = 0xFF;// make PORTC as output
  DDRD = 0xFF;
  DDRA = 0xFF;
  char c;
  uint8_t input_data[]="SABCDE";
  Lcd8_Init();
  Lcd8_Set_Cursor(1,1);
  DDRC|=0xFF;   //All Output
  PORTA = 0x08;
  int i,j;
  int flag=0;
  while(1)
    {
      flag=0;
      USARTInitReceive(416);
      while(1)
	{
	  while(!UDataAvailable());
	  c = UReadData();
	  if(c=='S')
	    flag=1;
	  if(flag==1)
	    {
	      input_data[j]=c;
	      j++;
	    }
	  if(c=='E')
	    {
	      Lcd8_Write_String(input_data);
	      break;
	    }
	}
      USARTInitSend(416);
      flag=0;
      for(i=0;i<1;i++)
	{
	  send_packet(input_data);
	}
    }
}
