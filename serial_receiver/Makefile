CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

serial_receiver.hex:serial_receiver.elf
	avr-objcopy $(CFLAGS3) serial_receiver.elf serial_receiver.hex
serial_receiver.elf:serial_receiver.o
	avr-gcc $(CFLAGS2) serial_receiver.elf serial_receiver.o
serial_receiver.o:serial_receiver.c
	avr-gcc $(CFLAGS1) serial_receiver.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:serial_receiver.hex