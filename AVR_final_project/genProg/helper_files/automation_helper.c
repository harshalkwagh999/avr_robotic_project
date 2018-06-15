
int Move_flag=1,i=0;
unsigned char key=0xff;
unsigned char cmdArr[]={};

int robot_move(unsigned char key)
{
  static int speed_flag=0,finish_flag=0,tmp_delay=0,val=0;
  static long int dl=DEFAULT_DL;
  
  if(speed_flag==0)
    {
      switch(key)                       // Decode the key                                      
       	{
       	case 0x77:  // key='1' Forward M1;
	  DATA_PORT=1;
      	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0x7b: // key='2' Forward M3;
	  DATA_PORT=8;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0x7d: // key='3' Forward M4;
	  DATA_PORT=16;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0xb7:  // key='4' Backward M1;
	  DATA_PORT=2;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0xbb: // key='5' Backward M3;
	  DATA_PORT=4;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0xbd: // key='6' Backward M4;
	  DATA_PORT=32;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0x7e: // key='A' Forward M5;
	  DATA_PORT=64;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0xbe: // key='B' Backward M5;
	  DATA_PORT=128;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0xeb: // key 0 to stop all motors
	  DATA_PORT=0;
	  delay(dl);
	  DATA_PORT=0;
	  break;
	case 0xde:  //key='C' Change the Delay ; 
	  speed_flag=1;                                                                               
	  break;
	}
    }
  else if(speed_flag==1)
    {
      switch(key)                       // Decode the key                             
	{
	case 0xeb: key='0';val=0; tmp_delay=tmp_delay*10+val;  break;
	case 0x77: key='1';val=1; tmp_delay=tmp_delay*10+val;  break;
	case 0x7b: key='2';val=2; tmp_delay=tmp_delay*10+val;  break;
	case 0x7d: key='3';val=3; tmp_delay=tmp_delay*10+val;  break;
	case 0xb7: key='4';val=4; tmp_delay=tmp_delay*10+val;  break;
	case 0xbb: key='5';val=5; tmp_delay=tmp_delay*10+val;  break;
	case 0xbd: key='6';val=6; tmp_delay=tmp_delay*10+val;  break;
	case 0xd7: key='7';val=7; tmp_delay=tmp_delay*10+val;  break;
	case 0xdb: key='8';val=8; tmp_delay=tmp_delay*10+val;  break;
	case 0xdd: key='9';val=9; tmp_delay=tmp_delay*10+val;  break;
	case 0xed: key='#';tmp_delay=0;  break;
	case 0xee: key='D';finish_flag=1;  break;
	}
      
      if(finish_flag==1)
	{
	  if(tmp_delay >= 1 && tmp_delay <= 5000)
	    {
	      dl=tmp_delay; finish_flag=0; speed_flag=0; tmp_delay=0;
	    }
	  else
	    {
	      dl=DEFAULT_DL; finish_flag=0; speed_flag=0; tmp_delay=0;
	    }
	}
    }
  
  return 0;
}

ISR(TIMER0_OVF_vect)
{ 
  if(key == 0x00)
    {  exit(0); }
  if(Move_flag == 1)
    {
      key=cmdArr[i++];
      robot_move(key);
      Move_flag=0;
    }

  TIMSK |=(1<<TOIE0);
  TCNT0=0x00;
  sei();
}

ISR(TIMER1_OVF_vect)
{
  Move_flag=1;
  
  TIMSK |=(1<<TOIE1);
  TCNT1=0x00;
  sei();
}

int delay(long int timer)
{
  timer=timer*200;
  
  while(timer)
    {
      if(SENS_PORT!= 0)
	{
	  DATA_PORT=0;
	  DATA_PORT=SENS_PORT;
	  _delay_ms(30);
	  break;
	}
      timer--;
    }      

  return 0;
}


//key=cmdArr[0];
