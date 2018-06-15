CFLAGS1=-g -mmcu=atmega32 -c
CFLAGS2=-g -mmcu=atmega32 -o
GFLAGS3=-j .text -j .data ihex

robo_arm_demo.hex:robo_arm_demo.elf
	avr-objcopy $(CFLAGS3) robo_arm_demo.elf robo_arm_demo.hex
robo_arm_demo.elf:robo_arm_demo.o
	avr-gcc $(CFLAGS2) robo_arm_demo.elf robo_arm_demo.o
robo_arm_demo.o:robo_arm_demo.c
	avr-gcc $(CFLAGS1) robo_arm_demo.c

burn:
	sudo ~/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:robo_arm_demo.hex

clean:
	rm *.o *.elf *.hex *~