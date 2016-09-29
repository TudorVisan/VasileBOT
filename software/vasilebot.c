#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#if defined BOARD_VASILEBOT_V1
#include "vasilebot.h"
#elif defined BOARD_ARDUINO_UNO
#include "arduino.h"
#else
#error Board not defined!
#endif

void IO_init(void)
{
	/* se setează pinul de iesire al DEBUG_LED */
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
	/* setarea porturilor de iesire */
	M1A_DDR |= (1 << M1A);
	M2A_DDR |= (1 << M2A);
	M1B_DDR |= (1 << M1B);
	M2B_DDR |= (1 << M2B);

	/* initializare timer 0 */
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
	TCCR0B = (1 << CS02);

	/* setarea registrilor pentru 0 de compare cu 0 */
	OCR0A = 0;
	OCR0B = 0;

	/* initializare timer 1 */
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B = (1 << CS12) | (1 << WGM12);

	/* setarea registrilor pentru 1 de compare cu 0 */
	OCR1A = 0;
	OCR1B = 0;
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
