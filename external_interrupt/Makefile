CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

external_interrupt0.hex:external_interrupt0.elf
	avr-objcopy $(CFLAGS3) external_interrupt0.elf external_interrupt0.hex
external_interrupt0.elf:external_interrupt0.o
	avr-gcc $(CFLAGS2) external_interrupt0.elf external_interrupt0.o
external_interrupt0.o:external_interrupt0.c
	avr-gcc $(CFLAGS1) external_interrupt0.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:external_interrupt0.hex

clean:
	rm *.o *.elf *.hex