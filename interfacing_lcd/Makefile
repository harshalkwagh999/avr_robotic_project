CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

interfacing_lcd.hex:interfacing_lcd.elf
	avr-objcopy $(CFLAGS3) interfacing_lcd.elf interfacing_lcd.hex
interfacing_lcd.elf:interfacing_lcd.o
	avr-gcc $(CFLAGS2) interfacing_lcd.elf interfacing_lcd.o
interfacing_lcd.o:interfacing_lcd.c
	avr-gcc $(CFLAGS1) interfacing_lcd.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:interfacing_lcd.hex