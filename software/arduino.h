
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

/* Motor 1 output A conectat la PB1 */
#define M1A		PB1
#define M1A_PIN	PINB
#define M1A_DDR	DDRB
#define M1A_PORT	PORTB

/* Motor 2 output A conectat la PB2 */
#define M2A		PB2
#define M2A_PIN	PINB
#define M2A_DDR	DDRB
#define M2A_PORT	PORTB

/* Motor 1 output B conectat la PD5 */
#define M1B		PD5
#define M1B_PIN	PIND
#define M1B_DDR	DDRD
#define M1B_PORT	PORTD

/* Motor 2 output B conectat la PD6 */
#define M2B		PD6
#define M2B_PIN	PIND
#define M2B_DDR	DDRD
#define M2B_PORT	PORTD