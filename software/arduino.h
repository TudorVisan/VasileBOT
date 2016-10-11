
/* Debug LED conectat pe portul PB0 */
#define DEBUG_LED_DDR	DDRB
#define DEBUG_LED_PIN	PINB
#define DEBUG_LED_PORT	PORTB
#define DEBUG_LED		PB0

/* Buton on/off(BTN1) conectat pe portul PD4/PB4 - pin 8 */
#define BTN1_DDR		DDRB
#define BTN1_PIN		PINB
#define BTN1_PORT		PORTB
#define BTN1			PB4
#define BTN1_PCINT		PCINT4
#define BTN1_PCINT_IE	PCIE0
#define BTN1_PCMSK 		PCMSK0

/* Buton lower frequency(BTN2) conectat pe portul PC5/PB5 - pin 9 */
#define BTN2_DDR		DDRB
#define BTN2_PIN		PINB
#define BTN2_PORT		PORTB
#define BTN2			PB5
#define BTN2_PCINT		PCINT5
#define BTN2_PCINT_IE	PCIE0
#define BTN2_PCMSK 		PCMSK0

/* Buton higher frequency(BTN3) conectat pe portul PC4/PB6 - pin 10 */
#define BTN3_DDR		DDRB
#define BTN3_PIN		PINB
#define BTN3_PORT		PORTB
#define BTN3			PB6
#define BTN3_PCINT		PCINT6
#define BTN3_PCINT_IE	PCIE0
#define BTN3_PCMSK 		PCMSK0

/* senzorul S1 conectat pe pinul PD0/PF7 - pin A0 */
#define S1 			PF7
#define S1_DDR 		DDRF
#define S1_PIN 		PINF
#define S1_PORT 	PORTF

/* senzorul S2 conectat pe pinul PD1/PF6 - pin A1 */
#define S2 			PF6
#define S2_DDR 		DDRF
#define S2_PIN 		PINF
#define S2_PORT 	PORTF

/* senzorul S3 conectat pe pinul PD2/PF5 - pin A2 */
#define S3 			PF5
#define S3_DDR 		DDRF
#define S3_PIN 		PINF
#define S3_PORT 	PORTF

/* senzorul S4 conectat pe pinul PD3/PF4 - pin A3 */
#define S4 			PF4
#define S4_DDR 		DDRF
#define S4_PIN 		PINF
#define S4_PORT 	PORTF

/* senzorul S5 conectat pe pinul PD5/PF1 - pin A4 */
#define S5 			PF1
#define S5_DDR 		DDRF
#define S5_PIN 		PINF
#define S5_PORT 	PORTF

/* senzorul S6 conectat pe pinul PC0/PF0 - pin A5 */
#define S6 			PF0
#define S6_DDR 		DDRF
#define S6_PIN 		PINF
#define S6_PORT 	PORTF

/* senzorul S7 conectat pe pinul PC1/PD4 - pin 4 */
#define S7 			PD4
#define S7_DDR 		DDRD
#define S7_PIN 		PIND
#define S7_PORT 	PORTD

/* Motor 1 output A conectat la PB1/PC6 - pin 5 */
#define M1A			PC6
#define M1A_PIN		PINC
#define M1A_DDR		DDRC
#define M1A_PORT	PORTC

/* Motor 2 output A conectat la PB2/PC7 - pin 13 */
#define M2A			PC7
#define M2A_PIN		PINC
#define M2A_DDR		DDRC
#define M2A_PORT	PORTC

/* Motor 1 output B conectat la PD5/PD7 - pin 6 */
#define M1B			PD7
#define M1B_PIN		PIND
#define M1B_DDR		DDRD
#define M1B_PORT	PORTD

/* Motor 2 output B conectat la PD6/PD0 - pin 3 */
#define M2B			PD0
#define M2B_PIN		PIND
#define M2B_DDR		DDRD
#define M2B_PORT	PORTD