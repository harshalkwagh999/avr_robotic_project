CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

car_demo.hex:car_demo.elf
	avr-objcopy $(CFLAGS3) car_demo.elf car_demo.hex
car_demo.elf:car_demo.o
	avr-gcc $(CFLAGS2) car_demo.elf car_demo.o
car_demo.o:car_demo.c
	avr-gcc $(CFLAGS1) car_demo.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:car_demo.hex