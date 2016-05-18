
#define F_CPU 16000000
 
#include <avr/io.h>
#include <util/delay.h>
 
/* Debug LED conectat pe portul PB0 */
 #define DEBUG_LED_DDR	DDRB
 #define DEBUG_LED_PIN	PINB
 #define DEBUG_LED_PORT	PORTB
 #define DEBUG_LED		PB0
 
/* Buton on/off(BTN1) conectat pe portul PD4 */
 #define BTN1_DDR	DDRD
 #define BTN1_PIN	PIND
 #define BTN1_PORT	PORTD
 #define BTN1		PD4
 #define BTN1_PCINT	PCINT20
 #define BTN1_PCINT_IE	PCIE2
 #define BTN1_PCMSK PCMSK2
 
/* Buton lower frequency(BTN2) conectat pe portul PC5 */
 #define BTN2_DDR	DDRC
 #define BTN2_PIN	PINC
 #define BTN2_PORT	PORTC
 #define BTN2		PC5
 #define BTN2_PCINT	PCINT13
 #define BTN2_PCINT_IE	PCIE1
 #define BTN2_PCMSK PCMSK1
 
/* Buton higher frequency(BTN3) conectat pe portul PC4 */
 #define BTN3_DDR	DDRC
 #define BTN3_PIN	PINC
 #define BTN3_PORT	PORTC
 #define BTN3		PC4
 #define BTN3_PCINT	PCINT12
 #define BTN3_PCINT_IE	PCIE1
 #define BTN3_PCMSK PCMSK1
 
 
void IO_init(void)
{
	/* se setează pinul de ieșire al DEBUG_LED */
	DEBUG_LED_DDR |= (1 << DEBUG_LED);
	
	/* se seteaza porturile de intrare de pe BTN1,2,3 */
	BTN1_DDR &= ~(1 << BTN1);
	BTN2_DDR &= ~(1 << BTN2);
	BTN3_DDR &= ~(1 << BTN3);
	
	/* activarea rezistentei de pull-up pentru BTN1,2,3 */
	BTN1_PORT |= (1 << BTN1);
	BTN2_PORT |= (1 << BTN2);
	BTN3_PORT |= (1 << BTN3);
	
	/* stingerea DEBUG_LED */
	DEBUG_LED_PORT &= ~(1 << DEBUG_LED);
	
	PCICR |= (1 << BTN1_PCINT_IE);
	PCICR |= (1 << BTN2_PCINT_IE);
	PCICR |= (1 << BTN3_PCINT_IE);
	
	BTN1_PCMSK |= (1 << BTN1_PCINT);
	BTN2_PCMSK |= (1 << BTN2_PCINT);
	BTN3_PCMSK |= (1 << BTN3_PCINT);
}

void motor_init(void)
{
	// TODO
}

ISR(PCINT1_vect)
{
	if( ( BTN3_PIN & ( 1 << BTN3) == 0 )
		if( freq < fmax )
			freq++;
	
	if( ( BTN2_PIN & ( 1 << BTN2) == 0 )
		if( freq > fmin )
			freq--;
}

ISR(PCINT2_vect)
{
	if( ( BTN1_PIN & ( 1 << BTN1 ) ) == 0 )
		DBG_LED_GO ^= 1;
}


int main() 
{
	IO_init();
	
	sei();
	
	int freq = 1000, fmax = 4999, fmin = 9;
	
	while(1) 
	{
		DEBUG_LED_PORT ^= (1 << DEBUG_LED);
		_delay_ms(freq);
	}
 
	return 0;
}