
unsigned char KEYPAD_ScanKey()
{
  RowColDirection=0xf0; 
  unsigned char ScanKey = 0xe0,i,key;
 
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
  unsigned char key; 
  Lcd8_Init();
  Lcd8_Cmd(0x0F);
  Lcd8_Set_Cursor(1,1);
  Lcd8_Clear();Lcd8_Write_String("KeypadIntrfacing");

  while(1)
    {  key = KEYPAD_ScanKey();
      
      switch(key)                       // Decode the key
	{
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
	}
    }

}
