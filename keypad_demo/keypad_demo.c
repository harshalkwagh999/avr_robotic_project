/* Interfacing Keypad with AVR */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC0
#define EN eS_PORTC1

#include<avr/io.h>
#include <util/delay.h>
#include <lcd.h>
#include <math.h>

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

int activate_motor(int mot_no,int dir)
{
  int pin,count;
  
  if(mot_no==5)
    {
      if(dir==0)
	{
	  PORTC = 35;
	  _delay_ms(100);
	  PORTC = 3;
	  return 0;
	}
      else
	{
	  PORTC = 19;
	  _delay_ms(100);
	  PORTC = 3;
	  return 0;
	}
    }
  else
    { pin=1;
       count=((mot_no-1)*2) + dir;
       while(count!=0)
	 {
	   pin = pin*2;
	   count--;
	 }
       // pin=(int)pow(2,pin);
       //       pin=pow(2,3);
       /* Lcd8_Init(); */
       /* Lcd8_Cmd(0x0F); */
       /* Lcd8_Set_Cursor(1,1); */
       /* Lcd8_Clear();Lcd8_Write_Char((char)pin); */
       /* _delay_ms(200); */

      PORTA= pin;
      _delay_ms(200);
      PORTA=0;
      return 0;
    }
  
}

int main()
{
  DDRD = 0xFF;
  DDRC = 0xFF;
  DDRA = 0xFF;
  unsigned char key; 
  int mot_no=0,dir=(-1),Activate=0,out=0,ret=(-1);

  Lcd8_Init();
  Lcd8_Cmd(0x0F);
  Lcd8_Set_Cursor(1,1);
  Lcd8_Clear();Lcd8_Write_Char('H');
  while(1)
    {  key = KEYPAD_ScanKey();

      switch(key)                       // Decode the key
	{

	case 0xe7: mot_no=1; Lcd8_Clear();Lcd8_Write_String("Motor 1 selected"); break;
	case 0xeb: mot_no=2; Lcd8_Clear();Lcd8_Write_String("Motor 2 selected"); break;
	case 0xed: mot_no=3; Lcd8_Clear();Lcd8_Write_String("Motor 3 selected"); break;
	case 0x77: mot_no=4; Lcd8_Clear();Lcd8_Write_String("Motor 4 selected"); break;
	case 0x7b: mot_no=5; Lcd8_Clear();Lcd8_Write_String("Motor 5 selected"); break;
	default: Lcd8_Clear();Lcd8_Write_String("Plz select motor");break;
	}
      if(mot_no !=0)
	{
	  
	  while(1)
	    {  key = KEYPAD_ScanKey();

	      switch(key)                       // Decode the key
		{
		case 0xdb: dir=0; Lcd8_Clear();Lcd8_Write_String("Backward Dir"); break;
		case 0xe7: dir=1; Lcd8_Clear();Lcd8_Write_String("Forward Dir"); break;
		case 0xd7: out=1; break;  // '*' to out
		default: Lcd8_Clear();Lcd8_Write_String("Plz select Direction");  Lcd8_Set_Cursor(2,1);Lcd8_Write_String("Press * to exit"); Lcd8_Set_Cursor(1,1); break;
		}
	      if(out==1)
		{
		  out=0; dir=(-1); mot_no=0; break;
		}
	      else if(dir!=(-1))
		{ 
		  while(1)
		    {  key = KEYPAD_ScanKey();

		      switch(key)                       // Decode the key
			{
			case 0xdd: Activate=1; Lcd8_Clear();Lcd8_Write_String("Activate Motor"); break;
			default: Lcd8_Clear();Lcd8_Write_String("Press # to Activate");
			}
		      if(Activate==1)
			{ret=(-1);
			  ret=activate_motor(mot_no,dir);
			  if(ret==0)
			    {
			      Lcd8_Clear();Lcd8_Write_String("Motor Run SUccessfull..."); 
			      _delay_ms(100);
			    }
			  else
			    {  Lcd8_Clear();Lcd8_Write_String("error in Running ..."); 
			      _delay_ms(100);    }
			  mot_no=0;
			  dir=(-1);			  
			  break;
			}
		    } // while(  for motor activate      )
		}
	    } // while(   for select direction           ) 
	}
      
    } // while(  for motor select     )
  
  return 0;
}
