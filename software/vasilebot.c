#define F_CPU 16000000
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
/* Debug LED conectat pe portul PB0 */
#define DEBUG_LED_DDR	DDRB
#define DEBUG_LED_PIN	PINB
#define DEBUG_LED_PORT	PORTB
#define DEBUG_LED		PB0
 
/* Buton on/off(BTN1) conectat pe portul PD4 */
#define BTN1_DDR		DDRD
#define BTN1_PIN		PIND
#define BTN1_PORT		PORTD
#define BTN1			PD4
#define BTN1_PCINT		PCINT20
#define BTN1_PCINT_IE	PCIE2
#define BTN1_PCMSK 		PCMSK2

/* Buton lower frequency(BTN2) conectat pe portul PC5 */
#define BTN2_DDR		DDRC
#define BTN2_PIN		PINC
#define BTN2_PORT		PORTC
#define BTN2			PC5
#define BTN2_PCINT		PCINT13
#define BTN2_PCINT_IE	PCIE1
#define BTN2_PCMSK 		PCMSK1

/* Buton higher frequency(BTN3) conectat pe portul PC4 */
#define BTN3_DDR		DDRC
#define BTN3_PIN		PINC
#define BTN3_PORT		PORTC
#define BTN3			PC4
#define BTN3_PCINT		PCINT12
#define BTN3_PCINT_IE	PCIE1
#define BTN3_PCMSK 		PCMSK1

/* senzorul S1 conectat pe pinul PD0 */
#define S1 			PD0
#define S1_DDR 		DDRD
#define S1_PIN 		PIND
#define S1_PORT 		PORTD

/* senzorul S2 conectat pe pinul PD1 */
#define S2 			PD1
#define S2_DDR 		DDRD
#define S2_PIN 		PIND
#define S2_PORT 		PORTD

/* senzorul S3 conectat pe pinul PD2 */
#define S3 			PD2
#define S3_DDR 		DDRD
#define S3_PIN 		PIND
#define S3_PORT 		PORTD

/* senzorul S4 conectat pe pinul PD3 */
#define S4 			PD3
#define S4_DDR 		DDRD
#define S4_PIN 		PIND
#define S4_PORT 		PORTD

/* senzorul S5 conectat pe pinul PD5 */
#define S5 			PD5
#define S5_DDR 		DDRD
#define S5_PIN 		PIND
#define S5_PORT 		PORTD

/* senzorul S6 conectat pe pinul PC0 */
#define S6 			PC0
#define S6_DDR 		DDRC
#define S6_PIN 		PINC
#define S6_PORT 		PORTC

/* senzorul S7 conectat pe pinul PC1 */
#define S7 			PC1
#define S7_DDR 		DDRC
#define S7_PIN 		PINC
#define S7_PORT 		PORTC
 
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

void sensors_init(void)
{
	/* se seteaza porturile de intrare pentru S1..7 */
	S1_DDR &= ~(1 << S1);
	S2_DDR &= ~(1 << S2);
	S3_DDR &= ~(1 << S3);
	S4_DDR &= ~(1 << S4);
	S5_DDR &= ~(1 << S5);
	S6_DDR &= ~(1 << S6);
	S7_DDR &= ~(1 << S7);
}

int sens[7] = {0};

void sensors_read(void)
{
	sens[0] = (S1_PIN & (1 << S1)) != 0;
	sens[1] = (S2_PIN & (1 << S2)) != 0;
	sens[2] = (S3_PIN & (1 << S3)) != 0;
	sens[3] = (S4_PIN & (1 << S4)) != 0; 
	sens[4] = (S5_PIN & (1 << S5)) != 0;
	sens[5] = (S6_PIN & (1 << S6)) != 0;
	sens[6] = (S7_PIN & (1 << S7)) != 0;
}

void motor_init(void)
{
	// TODO
}

int freq = 1000, freq_max = 4999, freq_min = 9;

ISR(PCINT1_vect)
{
	if( ( BTN3_PIN & ( 1 << BTN3)) == 0 )
		if( freq < freq_max )
			freq++;
	
	if( ( BTN2_PIN & ( 1 << BTN2)) == 0 )
		if( freq > freq_min )
			freq--;
}

int dbg_led_go = 0;

ISR(PCINT2_vect)
{
	if( ( BTN1_PIN & ( 1 << BTN1 ) ) == 0 )
		dbg_led_go^= 1;
}


int main() 
{
	int i = 0;
	IO_init();
	sensors_init();
	
	sei();
	
	while(1) 
	{
		DEBUG_LED_PORT ^= (1 << DEBUG_LED);
		for( i =0; i < freq ; i++)
			_delay_ms(1);
	}
 
	return 0;
}
