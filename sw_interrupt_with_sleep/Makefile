CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

sw_interrupt_with_sleep.hex:sw_interrupt_with_sleep.elf
	avr-objcopy $(CFLAGS3) sw_interrupt_with_sleep.elf sw_interrupt_with_sleep.hex
sw_interrupt_with_sleep.elf:sw_interrupt_with_sleep.o
	avr-gcc $(CFLAGS2) sw_interrupt_with_sleep.elf sw_interrupt_with_sleep.o
sw_interrupt_with_sleep.o:sw_interrupt_with_sleep.c
	avr-gcc $(CFLAGS1) sw_interrupt_with_sleep.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:sw_interrupt_with_sleep.hex

clean:
	rm *~ *.o *.hex *.elf \#*