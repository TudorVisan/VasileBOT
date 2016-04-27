all: vasilebot.hex
 
vasilebot.hex: vasilebot.elf
	avr-objcopy  -j .text -j .data -O ihex $^ $@
	avr-size $@
 
vasilebot.elf: vasilebot.c	
	avr-gcc -mmcu=atmega328p -Os -Wall -o $@ $^
 
clean:
	rm -rf vasilebot.elf vasilebot.hex