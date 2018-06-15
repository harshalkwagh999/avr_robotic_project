ISR(INT0_vect){
  int i;
  for(i=0;i<3;i++)
    {
      DATA_PORT = 0xFF;
      _delay_ms(50);
      DATA_PORT = 0x00;
      _delay_ms(50);
    }
}




