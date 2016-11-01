#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "board.h"

/* Debug LED conectat pe portul PC7 */
#define DEBUG_LED_DDR	DDRC
#define DEBUG_LED_PIN	PINC
#define DEBUG_LED_PORT	PORTC
#define DEBUG_LED		PC7

/* Buton 1 conectat pe portul PB4 - pin 8 */
#define BTN1_DDR		DDRB
#define BTN1_PIN		PINB
#define BTN1_PORT		PORTB
#define BTN1			PB4
#define BTN1_PCINT		PCINT4
#define BTN1_PCINT_IE	PCIE0
#define BTN1_PCMSK 		PCMSK0

/* Buton 2 conectat pe portul PB5 - pin 9 */
#define BTN2_DDR		DDRB
#define BTN2_PIN		PINB
#define BTN2_PORT		PORTB
#define BTN2			PB5
#define BTN2_PCINT		PCINT5
#define BTN2_PCINT_IE	PCIE0
#define BTN2_PCMSK 		PCMSK0

/* Buton 3 conectat pe portul PB6 - pin 10 */
#define BTN3_DDR		DDRB
#define BTN3_PIN		PINB
#define BTN3_PORT		PORTB
#define BTN3			PB6
#define BTN3_PCINT		PCINT6
#define BTN3_PCINT_IE	PCIE0
#define BTN3_PCMSK 		PCMSK0

/* Senzorul S1 conectat pe pinul PF7 - pin A0 */
#define S1 				PF7
#define S1_DDR 			DDRF
#define S1_PIN 			PINF
#define S1_PORT 		PORTF

/* Senzorul S2 conectat pe pinul PF6 - pin A1 */
#define S2 				PF6
#define S2_DDR 			DDRF
#define S2_PIN 			PINF
#define S2_PORT 		PORTF

/* Senzorul S3 conectat pe pinul PF5 - pin A2 */
#define S3 				PF5
#define S3_DDR 			DDRF
#define S3_PIN 			PINF
#define S3_PORT 		PORTF

/* Senzorul S4 conectat pe pinul PF4 - pin A3 */
#define S4 				PF4
#define S4_DDR 			DDRF
#define S4_PIN 			PINF
#define S4_PORT 		PORTF

/* Senzorul S5 conectat pe pinul PF1 - pin A4 */
#define S5 				PF1
#define S5_DDR 			DDRF
#define S5_PIN 			PINF
#define S5_PORT 		PORTF

/* Senzorul S6 conectat pe pinul PF0 - pin A5 */
#define S6 				PF0
#define S6_DDR 			DDRF
#define S6_PIN 			PINF
#define S6_PORT 		PORTF

/* Senzorul S7 conectat pe pinul PD4 - pin 4 */
#define S7 				PD4
#define S7_DDR 			DDRD
#define S7_PIN 			PIND
#define S7_PORT 		PORTD

/* Motor 1 output A conectat la PC6 - pin 5 */
#define M1A			PC6
#define M1A_PIN			PINC
#define M1A_DDR		DDRC
#define M1A_PORT		PORTC

/* Motor 2 output A conectat la PC7 - pin 13 */
#define M2A			PC7
#define M2A_PIN			PINC
#define M2A_DDR		DDRC
#define M2A_PORT		PORTC

/* Motor 1 output B conectat la PD7 - pin 6 */
#define M1B			PD7
#define M1B_PIN			PIND
#define M1B_DDR		DDRD
#define M1B_PORT		PORTD

/* Motor 2 output B conectat la PD0 - pin 3 */
#define M2B			PD0
#define M2B_PIN			PIND
#define M2B_DDR		DDRD
#define M2B_PORT		PORTD

void (*button3_callback)(void) ;
void (*button1_callback)(void) ;
void (*button2_callback)(void) ;

void IO_init(void)
{
	/* Se setează pinul de iesire al DEBUG_LED */
	DEBUG_LED_DDR |= (1 << DEBUG_LED);

	/* Stingerea DEBUG_LED */
	DEBUG_LED_PORT &= ~(1 << DEBUG_LED);

	/* Se seteaza porturile de intrare de pe BTN1, 2, 3 */
	BTN1_DDR &= ~(1 << BTN1);
	BTN2_DDR &= ~(1 << BTN2);
	BTN3_DDR &= ~(1 << BTN3);

	/* Activarea rezistentei de pull-up pentru BTN1, 2, 3 */
	BTN1_PORT |= (1 << BTN1);
	BTN2_PORT |= (1 << BTN2);
	BTN3_PORT |= (1 << BTN3);

	PCICR |= (1 << BTN1_PCINT_IE);
	PCICR |= (1 << BTN2_PCINT_IE);
	PCICR |= (1 << BTN3_PCINT_IE);

	BTN1_PCMSK |= (1 << BTN1_PCINT);
	BTN2_PCMSK |= (1 << BTN2_PCINT);
	BTN3_PCMSK |= (1 << BTN3_PCINT);
}

void sensors_init(void)
{
	/* Se seteaza porturile de intrare pentru S1..7 */
	S1_DDR &= ~(1 << S1);
	S2_DDR &= ~(1 << S2);
	S3_DDR &= ~(1 << S3);
	S4_DDR &= ~(1 << S4);
	S5_DDR &= ~(1 << S5);
	S6_DDR &= ~(1 << S6);
	S7_DDR &= ~(1 << S7);
}

void sensors_read(int *sens)
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
	/* Setarea porturilor de iesire */
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

void motors_set_speed(int motor1_speed, int motor2_speed)
{
	//TODO
}

void debug_led_set_state(int state)
{
	if (state == 0)
		DEBUG_LED_PORT &= ~(1 << DEBUG_LED);
	else
		DEBUG_LED_PORT |= (1 << DEBUG_LED);
}

void delay(int ms)
{
	int i;
	for (i = 0; i < ms; ++i)
		_delay_ms(1);
}

void init_board(void (*button1)(void), void (*button2)(void), void (*button3)(void))
{
	IO_init();
	sensors_init();
	motor_init();

	button1_callback = button1;
	button2_callback = button2;
	button3_callback = button3;

	sei();
}

ISR(PCINT0_vect)
{
	if ((BTN3_PIN & (1 << BTN3)) == 0)
		button3_callback();

	if ((BTN2_PIN & (1 << BTN2)) == 0)
		button2_callback();

	if ((BTN1_PIN & (1 << BTN1)) == 0)
		button1_callback();
}
