#receive_and_send_without_encoding=example
avrora-build:
	avr-gcc -o receive_and_send_without_encoding.elf -mmcu=atmega32 receive_and_send_without_encoding.c -O1
	avr-objdump -zhD receive_and_send_without_encoding.elf > receive_and_send_without_encoding.od
avrora-run:
	java -jar /home/supriya/tinyos/avrora/jars/avrora-rel.jar  -seconds=3 -monitors=ioregs -mcu=atmega32 -intrrupt-schedule=int.txt receive_and_send_without_encoding.od
build: receive_and_send_without_encoding.elf
	avr-objcopy -j .text -j .data -O ihex receive_and_send_without_encoding.elf receive_and_send_without_encoding.hex 
receive_and_send_without_encoding.elf:receive_and_send_without_encoding.o usart_avr.o
	avr-gcc -g -mmcu=atmega32 -o receive_and_send_without_encoding.elf receive_and_send_without_encoding.o usart_avr.o
receive_and_send_without_encoding.o:receive_and_send_without_encoding.c
	avr-gcc -g -Os -mmcu=atmega32 -c receive_and_send_without_encoding.c 
usart_avr.o:usart_avr.c
	avr-gcc -g -Os -mmcu=atmega32 -c usart_avr.c

#avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex on_off.elf on_off_eeprom.hex
#avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:on_off.hex
burn:
	sudo /home/vishal/project_root_dir/avrdude/install/bin/avrdude -p atmega32 -P /dev/bus/usb/002/004 -c usbasp -u -U flash:w:receive_and_send_without_encoding.hex 