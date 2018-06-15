CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

motor_activate_demo.hex:motor_activate_demo.elf
	avr-objcopy $(CFLAGS3) motor_activate_demo.elf motor_activate_demo.hex
motor_activate_demo.elf:motor_activate_demo.o
	avr-gcc $(CFLAGS2) motor_activate_demo.elf motor_activate_demo.o
motor_activate_demo.o:motor_activate_demo.c
	avr-gcc $(CFLAGS1) motor_activate_demo.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:motor_activate_demo.hex