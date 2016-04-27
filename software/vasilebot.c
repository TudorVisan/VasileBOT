//aprinderea LED-ului de debug
#define F_CPU 16000000
 
#include <avr/io.h>
#include <util/delay.h>
 
int main() {
	/* se setează prinul 0 al portului B ca pin de ieșire */
	DDRB |= (1 << PB0);
 
	while(1) {
                /* schimbăm valoarea pinului LOW - HIGH la fiecare 2 secunde ca să aprindă și stingă LED-ul */
		PORTB ^= (1 << PB0);
 
                _delay_ms(2000);
	}
 
	return 0;
}