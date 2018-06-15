CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

automation_demo.hex:automation_demo.elf
	avr-objcopy $(CFLAGS3) automation_demo.elf automation_demo.hex
automation_demo.elf:automation_demo.o
	avr-gcc $(CFLAGS2) automation_demo.elf automation_demo.o
automation_demo.o:automation_demo.c
	avr-gcc $(CFLAGS1) automation_demo.c

burn:
	sudo ~/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:automation_demo.hex

clean:
	rm *.elf *.o *.hex
