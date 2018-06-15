CFLAGS1=-g -Os -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data -O ihex

arm_demo.hex:arm_demo.elf
	avr-objcopy $(CFLAGS3) arm_demo.elf arm_demo.hex
arm_demo.elf:arm_demo.o
	avr-gcc $(CFLAGS2) arm_demo.elf arm_demo.o
arm_demo.o:arm_demo.c
	avr-gcc $(CFLAGS1) arm_demo.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:arm_demo.hex