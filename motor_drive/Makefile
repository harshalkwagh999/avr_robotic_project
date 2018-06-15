CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

motor_drive.hex:motor_drive.elf
	avr-objcopy $(CFLAGS3) motor_drive.elf motor_drive.hex
motor_drive.elf:motor_drive.o
	avr-gcc $(CFLAGS2) motor_drive.elf motor_drive.o
motor_drive.o:motor_drive.c
	avr-gcc $(CFLAGS1) motor_drive.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:motor_drive.hex