CFLAGS1=-g -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

robot_demo.hex:robot_demo.elf
	avr-objcopy $(CFLAGS3) robot_demo.elf robot_demo.hex
robot_demo.elf:robot_demo.o
	avr-gcc $(CFLAGS2) robot_demo.elf robot_demo.o
robot_demo.o:robot_demo.c
	avr-gcc $(CFLAGS1) robot_demo.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:robot_demo.hex

clean:
	rm *.o *.elf *.hex *~
