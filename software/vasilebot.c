//aprinderea LED-ului de debug
#define F_CPU 16000000
 
#include <avr/io.h>
#include <util/delay.h>
 
 
int main() {
	/* se setează pinul 0 al portului B ca pin de ieșire */
	DDRB |= (1 << PB0);
	
	/* se seteaza porturile de intrare de pe PD4 (BTN1), PC4(BTN3) si PC5(BTN2) */
	DDRC &= ~(1 << PC4);
	DDRC &= ~(1 << PC5);
	DDRD &= ~(1 << PD4);
	
	/* activarea rezistentei de pull-up pentru BTN1,2,3 */
	PORTC |= (1 << PC4);
	PORTC |= (1 << PC5);
	PORTD |= (1 << PD4);
	
	/* turn off the lights! (PB0) */
	PORTB &= ~(1 << PB0);
	
	int freq = 1000, fmax = 4999, fmin 9;
	
	while(1) 
	{
		if( ( PIND & ( 1 << PD4 ) ) == 0 )
				PORTB |= ( 1 << PB0);
		
		else
				PORTB &= ~( 1 << PB0);
		if( ( PINC & ( 1 << PC4) == 0 )
			if(freq < fmax)
				freq++;
		if( ( PINC & ( 1 << PC5) == 0 )
			if(freq > fmin)
				freq--;
		
		PORTB ^= (1 << PB0);
		_delay_ms(freq);
	}
 
	return 0;
}