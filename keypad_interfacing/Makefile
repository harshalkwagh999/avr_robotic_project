CFLAGS1=-g -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

keypad_interfacing.hex:keypad_interfacing.elf
	avr-objcopy $(CFLAGS3) keypad_interfacing.elf keypad_interfacing.hex
keypad_interfacing.elf:keypad_interfacing.o
	avr-gcc $(CFLAGS2) keypad_interfacing.elf keypad_interfacing.o
keypad_interfacing.o:keypad_interfacing.c
	avr-gcc $(CFLAGS1) keypad_interfacing.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:keypad_interfacing.hex

clean:
	rm *.o *.elf *.hex *~
