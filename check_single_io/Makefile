CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

check_single_io.hex:check_single_io.elf
	avr-objcopy $(CFLAGS3) check_single_io.elf check_single_io.hex
check_single_io.elf:check_single_io.o
	avr-gcc $(CFLAGS2) check_single_io.elf check_single_io.o
check_single_io.o:check_single_io.c
	avr-gcc $(CFLAGS1) check_single_io.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:check_single_io.hex

clean:
	rm *.hex *.elf *.o