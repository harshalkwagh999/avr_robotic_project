CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

software_interrupt.hex:software_interrupt.elf
	avr-objcopy $(CFLAGS3) software_interrupt.elf software_interrupt.hex
software_interrupt.elf:software_interrupt.o
	avr-gcc $(CFLAGS2) software_interrupt.elf software_interrupt.o
software_interrupt.o:software_interrupt.c
	avr-gcc $(CFLAGS1) software_interrupt.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:software_interrupt.hex

clean:
	rm *.o *.elf *.hex