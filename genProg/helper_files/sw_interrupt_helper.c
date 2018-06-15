ISR(TIMER1_OVF_vect)
{
  PORT1 = PORT1 ^ 32;

  TIMSK |=(1<<TOIE1);
  TCNT1=0x00;
  sei();
}

ISR(TIMER0_OVF_vect)
{
  PORT0 = PORT0 ^ 64; 

  TIMSK |=(1<<TOIE0);
  TCNT0=0x00;
  sei();
}
