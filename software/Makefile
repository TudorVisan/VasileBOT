all: basic_0.hex
 
basic_0.hex: basic_0.elf
	avr-objcopy  -j .text -j .data -O ihex $^ $@
	avr-size $@
 
basic_0.elf: basic_0.c	
	avr-gcc -mmcu=atmega328p -Os -Wall -o $@ $^
 
clean:
	rm -rf basic_0.elf basic_0.hex