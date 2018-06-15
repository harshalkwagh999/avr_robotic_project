CFLAGS1=-g -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

progname.hex:progname.elf
	avr-objcopy $(CFLAGS3) progname.elf progname.hex
progname.elf:progname.o
	avr-gcc $(CFLAGS2) progname.elf progname.o
progname.o:progname.c
	avr-gcc $(CFLAGS1) progname.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:progname.hex

clean:
	rm *.o *.elf *.hex *~
