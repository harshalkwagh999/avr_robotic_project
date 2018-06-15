CFLAGS1=-g -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

keypad_interfacing_with_int.hex:keypad_interfacing_with_int.elf
	avr-objcopy $(CFLAGS3) keypad_interfacing_with_int.elf keypad_interfacing_with_int.hex
keypad_interfacing_with_int.elf:keypad_interfacing_with_int.o
	avr-gcc $(CFLAGS2) keypad_interfacing_with_int.elf keypad_interfacing_with_int.o
keypad_interfacing_with_int.o:keypad_interfacing_with_int.c
	avr-gcc $(CFLAGS1) keypad_interfacing_with_int.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:keypad_interfacing_with_int.hex

clean:
	rm *.o *.elf *.hex *~ \#*
