/* This Programm demonstrate the movement of car using key board */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include<avr/io.h>
#include <util/delay.h>
#define RowColDirection DDRB //Data Direction Configuration for keypad                                 
#define ROW PORTB            //Lower four bits of PORTC are used as ROWs                               
#define COL PINB            //Higher four bits of PORTC are used as COLs

unsigned char KEYPAD_ScanKey()
{
  RowColDirection=0xf0;
unsigned char ScanKey = 0xe0,i, key;
for(i=0;i<0x04;i++)           // Scan All the 4-Rows for key press                                    
  {
    ROW=ScanKey + 0x0F;         // Select 1-Row at a time for Scanning the Key                        
    key=COL & 0x0F;             // Read the Column, for key press                                     

    if(key!= 0x0F)             // If the KEY press is detected for the selected                       
      break;                   // ROW then stop Scanning,                                             

    ScanKey=(ScanKey<<1)+ 0x10; // Rotate the ScanKey to SCAN the remaining Rows                      
  }

key = key + (ScanKey & 0xf0);  // Return the row and COL status to decode the key                     

return(key);
}



int main()
{
  DDRA=0xFF;
  PORTA=10;
  unsigned char key;
  
  while(1)
    {  key = KEYPAD_ScanKey();
      
      switch(key)                       // Decode the key                                       
	{
	case 0xdb: PORTA=6; break;   //Backward
	case 0xe7: PORTA=9; break;   //Forward
	case 0xd7:if(PORTA==6 )     // stop                                                 
 	    {PORTA=9; _delay_ms(50);PORTA=10; break; }
	  else if(PORTA==9)
	    {PORTA=6; _delay_ms(50);PORTA=10; break; }
	  
	}
    }
      


  return 0;
}
