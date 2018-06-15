/* Final Robot Movement With Interrupt and Sensor's */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define DEFAULT_DL 10

#include<avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

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

int Wait()
{
  int i=50000;
  
  while(i)
    {
      i--;
    }
}

int main()
{
  DDRD = 0x00;
  PORTD = 0;
  DDRA = 0xFF;
  unsigned char key; 
  int timer,speed_flag=0,finish_flag=0,tmp_delay=0,val=0;
  long int dl=DEFAULT_DL;

  /* cli(); //clear global interrupts                                                                     */
  /* GICR = 1 << INT0; //enable intrupt on INT0                                                */
  /* MCUCR |= 1 << ISC01 | 1 << ISC00; // on rising edge                                                 */
  /* sei(); //enable global interrupts        */
  
  
  while(1)
    {  key = KEYPAD_ScanKey();
      
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
      
      if(speed_flag==1)
	{
	  tmp_delay=0;
	  
	  while(1)
	    {
	      key = KEYPAD_ScanKey();
	      switch(key)                       // Decode the key                             
		{
		case 0xeb: key='0';val=0;tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0x77: key='1';val=1; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0x7b: key='2';val=2; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0x7d: key='3';val=3; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0xb7: key='4';val=4; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0xbb: key='5';val=5; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0xbd: key='6';val=6; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0xd7: key='7';val=7; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0xdb: key='8';val=8; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0xdd: key='9';val=9; tmp_delay=tmp_delay*10+val; Wait(); break;
		case 0xed: key='#';tmp_delay=0; Wait(); break;
		case 0xee: key='D';finish_flag=1; Wait(); break;
		}
	      
	      if(finish_flag==1)
		{
		  if(tmp_delay >= 1 && tmp_delay <= 5000)
		    {
		      dl=tmp_delay; finish_flag=0; speed_flag=0; break;
		    }
		  else
		    {
		      dl=DEFAULT_DL; finish_flag=0; speed_flag=0; break;
		    }
		  break;
		}
	    }
	  
	}
    }  
  return 0;
}

int rev_move(int pin_val)
{
  int tmp=20000;
  if(pin_val!= 0)
    {
      PORTA=pin_val;
      while(tmp)
	{  tmp--; }
      return -1;
    }
  return 0;
}

int delay(long int timer)
{
  timer=timer*100;
  
  while(timer)
    {
      if(rev_move(PIND) == -1)
      	{  break;  }
      PORTD=0;
      timer--;
    }
  return 0;
}



/*
      if(PIND & (1 << PIND0) ) // M5 Right
	{
	  PORTA=1;
	  while(tmp)
	    {  tmp=tmp-2;  }
	  return 1;
	}
      else if(PIND & (1 << PIND1)) // M5 Left
	{
	  PORTA=2;
	  while(tmp)
	    {  tmp--;  }
	  return 1;
	}      
      else if(PIND & (1 << PIND2)) // M4 F/W
	{
	  PORTA=4;
	  while(tmp)
	    {  tmp--;  }
	  return 1;
	}
      else if(PIND & (1 << PIND3)) // M4 B/W
	{
	  PORTA=8;
	  while(tmp)
	    {  tmp--;  }
	  return 1;

	}
      else if(PIND & (1 << PIND4)) // M3 F/W
	{
	  PORTA=16;
	  while(tmp)
	    {  tmp--;  }
	  return 1;
	}
      else if(PIND & (1 << PIND5)) // M3 B/W
	{
	  PORTA=32;
	  while(tmp)
	    {  tmp--;  }
	  return 1;
	}
      else if(PIND & (1 << PIND6))  // M1 B/W
	{
	  PORTA=64;
	  while(tmp)
	    {  tmp=tmp-1; }
	  return 1;
	}
      else if(PIND & (1 << PIND7))  // M1 B/W
	{
	  PORTA=128;
	  while(tmp)
	    {  tmp=tmp-1; }
	  return 1;
	}


*/
