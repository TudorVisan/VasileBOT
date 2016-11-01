#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "board.h"


/* Debug LED conectat pe portul PB0 */
#define DEBUG_LED_DDR	DDRB
#define DEBUG_LED_PIN	PINB
#define DEBUG_LED_PORT	PORTB
#define DEBUG_LED		PB0

/* Buton 1 conectat pe portul PD4 */
#define BTN1_DDR		DDRD
#define BTN1_PIN		PIND
#define BTN1_PORT		PORTD
#define BTN1			PD4
#define BTN1_PCINT		PCINT20
#define BTN1_PCINT_IE	PCIE2
#define BTN1_PCMSK 		PCMSK2

/* Buton 2 conectat pe portul PC5 */
#define BTN2_DDR		DDRC
#define BTN2_PIN		PINC
#define BTN2_PORT		PORTC
#define BTN2			PC5
#define BTN2_PCINT		PCINT13
#define BTN2_PCINT_IE	PCIE1
#define BTN2_PCMSK 		PCMSK1

/* Buton 3 conectat pe portul PC4 */
#define BTN3_DDR		DDRC
#define BTN3_PIN		PINC
#define BTN3_PORT		PORTC
#define BTN3			PC4
#define BTN3_PCINT		PCINT12
#define BTN3_PCINT_IE	PCIE1
#define BTN3_PCMSK 		PCMSK1

/* Senzorul S1 conectat pe pinul PD0 */
#define S1 				PD0
#define S1_DDR 			DDRD
#define S1_PIN 			PIND
#define S1_PORT 		PORTD

/* Senzorul S2 conectat pe pinul PD1 */
#define S2 				PD1
#define S2_DDR 			DDRD
#define S2_PIN 			PIND
#define S2_PORT 		PORTD

/* Senzorul S3 conectat pe pinul PD2 */
#define S3 				PD2
#define S3_DDR 			DDRD
#define S3_PIN 			PIND
#define S3_PORT 		PORTD

/* Senzorul S4 conectat pe pinul PD3 */
#define S4 				PD3
#define S4_DDR 			DDRD
#define S4_PIN 			PIND
#define S4_PORT 		PORTD

/* Senzorul S5 conectat pe pinul PD5 */
#define S5 				PD5
#define S5_DDR 			DDRD
#define S5_PIN 			PIND
#define S5_PORT 		PORTD

/* Senzorul S6 conectat pe pinul PC0 */
#define S6 				PC0
#define S6_DDR 			DDRC
#define S6_PIN 			PINC
#define S6_PORT 		PORTC

/* Senzorul S7 conectat pe pinul PC1 */
#define S7 				PC1
#define S7_DDR 			DDRC
#define S7_PIN 			PINC
#define S7_PORT 		PORTC

/* Motor 1 output A conectat la PB1 */
#define M1A			PB1
#define M1A_PIN			PINB
#define M1A_DDR		DDRB
#define M1A_PORT		PORTB

/* Motor 2 output A conectat la PB2 */
#define M2A			PB2
#define M2A_PIN			PINB
#define M2A_DDR		DDRB
#define M2A_PORT		PORTB

/* Motor 1 output B conectat la PD5 */
#define M1B			PD5
#define M1B_PIN			PIND
#define M1B_DDR		DDRD
#define M1B_PORT		PORTD

/* Motor 2 output B conectat la PD6 */
#define M2B			PD6
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

	/* Se seteaza porturile de intrare de pe BTN1, 2, 3 */
	BTN1_DDR &= ~(1 << BTN1);
	BTN2_DDR &= ~(1 << BTN2);
	BTN3_DDR &= ~(1 << BTN3);

	/* Activarea rezistentei de pull-up pentru BTN1, 2, 3 */
	BTN1_PORT |= (1 << BTN1);
	BTN2_PORT |= (1 << BTN2);
	BTN3_PORT |= (1 << BTN3);

	/* Stingerea DEBUG_LED */
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

	/* Initializare timer 0 */
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
	TCCR0B = (1 << CS02);

	/* Setarea registrilor pentru 0 de compare cu 0 */
	OCR0A = 0;
	OCR0B = 0;

	/* Initializare timer 1 */
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B = (1 << CS12) | (1 << WGM12);

	/* Setarea registrilor pentru 1 de compare cu 0 */
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

ISR(PCINT1_vect)
{
	if ((BTN3_PIN & (1 << BTN3)) == 0)
		button3_callback();

	if ((BTN2_PIN & (1 << BTN2)) == 0)
		button2_callback();
}

ISR(PCINT2_vect)
{
	if ((BTN1_PIN & (1 << BTN1)) == 0)
		button1_callback();
}