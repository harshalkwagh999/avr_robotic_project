CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

serial_sender.hex:serial_sender.elf
	avr-objcopy $(CFLAGS3) serial_sender.elf serial_sender.hex
serial_sender.elf:serial_sender.o
	avr-gcc $(CFLAGS2) serial_sender.elf serial_sender.o
serial_sender.o:serial_sender.c
	avr-gcc $(CFLAGS1) serial_sender.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:serial_sender.hex