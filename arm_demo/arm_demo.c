/* Demo ARM Movement progm */

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
  int F1=0,F2=0,B1=0,B2=0;
  DDRA=0xFF;
  PORTA=0;
  unsigned char key;
  int dl=15;
  while(1)
    {  key = KEYPAD_ScanKey();

      switch(key)                       // Decode the key                                              
        {
	case 0xe7:  //key 1: Forward M1
	  PORTA=1;
	  _delay_us(dl);
	  PORTA=0;
	  break;
	case 0xeb:  //key 2: Backward M1
	  PORTA=2;
	  _delay_us(dl);
	  PORTA=0;
	  break;
	}
    }
  return 0;
}
