/* Transmitter. While transmitting using USART it works as a transmitter*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "usart_avr.h"


void main()
{
	//Initialize the USART with Baud rate = 2400bps
	USARTInit(416);	
	uint8_t data;
	while(1)
	{
	  /* Now we will start the data sending */
		UWriteData('J');
		UWriteData('A');
		UWriteData('B');
		UWriteData('C');
		UWriteData('Z');
		_delay_loop_2(0);
		_delay_loop_2(0);
		_delay_loop_2(0);
		_delay_loop_2(0);
	}
}
