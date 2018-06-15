/* Interfacing Keypad with AVR */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* #define D0 eS_PORTA0 */
/* #define D1 eS_PORTA1 */
/* #define D2 eS_PORTA2 */
/* #define D3 eS_PORTA3 */
/* #define D4 eS_PORTA4 */
/* #define D5 eS_PORTA5 */
/* #define D6 eS_PORTA6 */
/* #define D7 eS_PORTA7 */
/* #define RS eS_PORTC6 */
/* #define EN eS_PORTC7 */

#define DEFAULT_DL 10

#include<avr/io.h>
#include <stdio.h>
//#include <lcd.h>
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

ISR(INT0_vect){
  int i=50000;

  /* Lcd8_Init(); */
  /* Lcd8_Cmd(0x0F); */
  /* Lcd8_Set_Cursor(1,1); */

  while(i)
    {
      i--;  //      Lcd8_Clear(); Lcd8_Write_String("INTERPT");
    }
  // delay(500);
  // PIND=0x00;
  }

int main()
{
  DDRD = 0x00;
  //  DDRA = 0xFF;
  DDRC = 0xFF;
  unsigned char key; 
  char str[10];
  int timer,speed_flag=0,finish_flag=0,tmp_delay=0,val=0;
  long int dl=DEFAULT_DL;
  /* Lcd8_Init(); */
  /* Lcd8_Cmd(0x0F); */
  /* Lcd8_Set_Cursor(1,1); */
  /* Lcd8_Clear();Lcd8_Write_Char('H'); */

   cli(); //clear global interrupts                                                                     
   GICR = 1 << INT0; //enable intrupt on INT0                                               
   //  SREG = 1 << 7;                                                                                  
   //  MCUCR |= 0 << ISC11 | 1 << ISC10;// on any logical change                                            
   MCUCR |= 1 << ISC01 | 1 << ISC00; // on rising edge                                                   
   sei(); //enable global interrupts       
 

  while(1)
    {  key = KEYPAD_ScanKey();

      switch(key)                       // Decode the key                                              
        {
	case 0x77:  //key 1: Forward M1
	  PORTC=1;
	  delay(dl);
	  PORTC=0;
	  break;
	case 0x7b:  //key 2: Backward M1
	  PORTC=2;
	  delay(dl);
	  PORTC=0;
	  break;
	case 0x7e: // key A goto modify delay of motor
	  speed_flag=1;
	  break;
	}

      if(speed_flag==1)
	{ // Lcd8_Clear();Lcd8_Write_String("Enter Value:");
	  tmp_delay=0;
	  /* cli(); //clear global interrupts	\ */
	  /* GICR = 1 << INT0; //enable intrupt on INT0 */
	  /* MCUCR |= 1 << ISC01 | 1 << ISC00; // on rising edge	\	   */
	  /* sei(); //enable global interrupts */
      //PORTD=0x00;
	  
	  while(1)
      {
	key = KEYPAD_ScanKey();
	switch(key)                       // Decode the key                             
	{
	case 0xeb: key='0';val=0;tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0x77: key='1';val=1; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0x7b: key='2';val=2; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0x7d: key='3';val=3; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0xb7: key='4';val=4; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0xbb: key='5';val=5; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0xbd: key='6';val=6; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0xd7: key='7';val=7; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0xdb: key='8';val=8; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0xdd: key='9';val=9; tmp_delay=tmp_delay*10+val; PORTD=0x04; PORTD= 0x00; break;
	case 0xed: key='#';tmp_delay=0; PORTD= 0x04;PORTD= 0x00; break;
	case 0xee: key='D';finish_flag=1; PORTD=0x04; PORTD= 0x00; break;
	  //	case 0xde: key='C'; Lcd8_Clear();Lcd8_Write_Char(key); PORTD=0x04; PORTD= 0x00; break;
	  //default:Lcd8_Clear();Lcd8_Write_String("hiii"); break;
	}
      
	if(finish_flag==1)
		{
		  if(tmp_delay >= 1 && tmp_delay <= 250)
		    {
		      dl=tmp_delay; finish_flag=0; speed_flag=0; break;
		    }
		  else
		    {
		      dl=DEFAULT_DL; finish_flag=0; speed_flag=0; break;
		    }
		  // sprintf(str,"%d",dl);Lcd8_Clear();Lcd8_Write_String(str); break;
		  break;
		}
      /* if(finish_flag==1) */
      /* 	{ */
      /* 	  if(tmp_delay >= 1 && tmp_delay <= 500) */
      /* 	    { */
      /* 	      dl=tmp_delay; finish_flag=0; speed_flag=0; break; */
      /* 	    } */
      /* 	  else */
      /* 	    { */
      /* 	      dl=DEFAULT_DL; finish_flag=0; speed_flag=0; break; */
      /* 	    } */
      /* 	  sprintf(str,"%d",dl);Lcd8_Clear();Lcd8_Write_String(str); break; */
      /* 	  break; */
      /* 	} */
    }
    
	}
    }

  /* while(1) */
  /*   {  key = KEYPAD_ScanKey(); */
  /*     //         Lcd8_Clear(); */
  /*     timer=50000; */
  /* switch(key)                       // Decode the key */
  /*   { */
  /*     /\*    case 0xdb: key='0'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xe7: key='1'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xeb: key='2'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xed: key='3'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0x77: key='4'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0x7b: key='5'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0x7d: key='6'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xb7: key='7'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xbb: key='8'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xbd: key='9'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xee: key='A'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xde: key='D'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xbe: key='C'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0x7e: key='B'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xd7: key='*'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   case 0xdd: key='#'; Lcd8_Clear();Lcd8_Write_Char(key); break; */
  /*   default: key='z'; //Lcd8_Clear();Lcd8_Write_Char(key); */
  /*     *\/ */
  /*   case 0xeb: key='0'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0x77: key='1'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0x7b: key='2'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0x7d: key='3'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xb7: key='4'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xbb: key='5'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xbd: key='6'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xd7: key='7'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xdb: key='8'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xdd: key='9'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0x7e: key='A'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xbe: key='B'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xde: key='C'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xee: key='D'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xe7: key='*'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   case 0xed: key='#'; Lcd8_Clear();Lcd8_Write_Char(key); while(timer--); break; */
  /*   default: key='z'; //Lcd8_Clear();Lcd8_Write_Char(key); */
  /*   } */

  /* //  while(timer--); */

  /*   } */

  return 0;
	}

int delay(long int timer)
{
  timer=timer*100;
  //  int tmp=20000;
  while(timer)
    { 
     timer--;
    }
  return 1;
}

