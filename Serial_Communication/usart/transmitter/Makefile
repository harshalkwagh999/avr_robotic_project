#main=main
avrora-build:
	avr-gcc -o main.elf -mmcu=atmega32 main.c -O1
	avr-objdump -zhD main.elf > main.od
avrora-run:
	java -jar /home/supriya/tinyos/avrora/jars/avrora-rel.jar  -seconds=3 -monitors=ioregs -mcu=atmega32 -intrrupt-schedule=int.txt main.od
build: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex 
main.elf:main.o usart_avr.o
	avr-gcc -g -mmcu=atmega32 -o main.elf main.o usart_avr.o
main.o:main.c
	avr-gcc -g -Os -mmcu=atmega32 -c main.c 
usart_avr.o:usart_avr.c
	avr-gcc -g -Os -mmcu=atmega32 -c usart_avr.c

#avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex on_off.elf on_off_eeprom.hex
#avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:on_off.hex
burn:
	sudo /home/harshal/proj_utility/avr_dude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:main.hex 


