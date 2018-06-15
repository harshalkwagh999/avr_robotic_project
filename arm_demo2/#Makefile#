CFLAGS1=-g -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

ar_demo_with_int.hex:ar_demo_with_int.elf
	avr-objcopy $(CFLAGS3) ar_demo_with_int.elf ar_demo_with_int.hex
ar_demo_with_int.elf:ar_demo_with_int.o
	avr-gcc $(CFLAGS2) ar_demo_with_int.elf ar_demo_with_int.o
ar_demo_with_int.o:ar_demo_with_int.c
	avr-gcc $(CFLAGS1) ar_demo_with_int.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:ar_demo_with_int.hex

clean:
	rm *.o *.elf *.hex *~
