int test_lcd()
{
  Lcd8_Init();
  Lcd8_Cmd(0x0F);
  Lcd8_Set_Cursor(1,1);
  Lcd8_Write_String("LCD INTERFACING");
  return 0;
}
