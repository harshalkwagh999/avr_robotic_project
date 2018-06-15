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
#define RS eS_PORTC6
#define EN eS_PORTC7

#define RowColDirection DDRB //Data Direction Configuration for keypad
#define ROW PORTB            //Lower four bits of PORTC are used as ROWs
#define COL PINB            //Higher four bits of PORTC are used as COLs

#include<avr/io.h>
#include <util/delay.h>
#include <lcd.h>

int main()
{
  DDRD = 0xFF;
  DDRC = 0xFF;

  check_keypad();
  return 0;
}

unsigned char key; 
unsigned char KEYPAD_ScanKey()
{
  RowColDirection=0xf0; 
  unsigned char ScanKey = 0xe0,i;
 
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

int check_keypad()
{
  Lcd8_Init();
  Lcd8_Cmd(0x0F);
  Lcd8_Set_Cursor(1,1);
  Lcd8_Clear();Lcd8_Write_String("KeypadIntrfacing");

  while(1)
    {  key = KEYPAD_ScanKey();
      //         Lcd8_Clear();
  switch(key)                       // Decode the key
    {
      /*    case 0xdb: key='0'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xe7: key='1'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xeb: key='2'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xed: key='3'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x77: key='4'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x7b: key='5'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x7d: key='6'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xb7: key='7'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xbb: key='8'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xbd: key='9'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xee: key='A'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xde: key='D'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xbe: key='C'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x7e: key='B'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xd7: key='*'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xdd: key='#'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    default: key='z'; //Lcd8_Clear();Lcd8_Write_Char(key);
      */

    case 0xeb: key='0'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x77: key='1'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x7b: key='2'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x7d: key='3'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xb7: key='4'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xbb: key='5'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xbd: key='6'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xd7: key='7'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xdb: key='8'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xdd: key='9'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0x7e: key='A'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xbe: key='B'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xde: key='C'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xee: key='D'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xe7: key='*'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    case 0xed: key='#'; Lcd8_Clear();Lcd8_Write_Char(key); break;
    default: key='z'; //Lcd8_Clear();Lcd8_Write_Char(key);
    }
    }

}
