CFLAGS1=-g -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

check_io.hex:check_io.elf
	avr-objcopy $(CFLAGS3) check_io.elf check_io.hex
check_io.elf:check_io.o
	avr-gcc $(CFLAGS2) check_io.elf check_io.o
check_io.o:check_io.c
	avr-gcc $(CFLAGS1) check_io.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:check_io.hex