/* Receiver while communicating using USART*/
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


#include <avr/io.h>
#include <util/delay.h>
#include "usart_avr.h"
#include <lcd.h>
void main()
{
  DDRB = 0xFF;// make PORTD as output for use of lcd data pins                                                                          
  DDRC = 0xFF;// make PORTC as output         
  Lcd8_Init();
  Lcd8_Set_Cursor(1,1);
  uint8_t i=0; //Classical loop variable
  
  DDRC|=0xFF;	//All Output
  Lcd8_Write_String("hii");
  _delay_ms(50);
  USARTInit(416);
  while(1)
    {
      //Wait for a packet
      i++;
      while(!UDataAvailable());
      
      Lcd8_Write_Char(UReadData());
      if(i%5==0)
	Lcd8_Set_Cursor(1,1);		  
	}
}
