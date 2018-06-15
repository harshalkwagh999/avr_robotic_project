CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

keypad_demo.hex:keypad_demo.elf
	avr-objcopy $(CFLAGS3) keypad_demo.elf keypad_demo.hex
keypad_demo.elf:keypad_demo.o
	avr-gcc $(CFLAGS2) keypad_demo.elf keypad_demo.o
keypad_demo.o:keypad_demo.c
	avr-gcc $(CFLAGS1) keypad_demo.c -lm

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:keypad_demo.hex