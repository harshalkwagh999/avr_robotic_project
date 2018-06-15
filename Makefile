CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

.hex:.elf
	avr-objcopy $(CFLAGS3) .elf .hex
.elf:.o
	avr-gcc $(CFLAGS2) .elf .o
.o:.c
	avr-gcc $(CFLAGS1) .c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:.hex

clean:
	rm *.o *.elf *.hex *~ \#*