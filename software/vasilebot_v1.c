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


/*
ISR(PCINT0_vect)
{
	if( ( BTN3_PIN & ( 1 << BTN3)) == 0 )
		if( freq < freq_max )
			freq++;

	if( ( BTN2_PIN & ( 1 << BTN2)) == 0 )
		if( freq > freq_min )
			freq--;

	if( ( BTN1_PIN & ( 1 << BTN1 ) ) == 0 )
	{
		//dbg_led_go^= 1;
		DEBUG_LED_PORT |= (1 << DEBUG_LED);
	}
}*/


int main()
{
	int i = 0;
	IO_init();
	//sensors_init();

//	sei();

	int freq = 1000, freq_max = 4900, freq_min = 101;

	while(1)
	{

		if( ( BTN3_PIN & ( 1 << BTN3)) == 0 )
			if( freq < freq_max )
				freq = freq + 100; 

		if( ( BTN2_PIN & ( 1 << BTN2)) == 0 )
			if( freq > freq_min )
				
				freq = freq - 100;

		if( ( BTN1_PIN & ( 1 << BTN1 ) ) == 0 )
		{
		//dbg_led_go^= 1;
			DEBUG_LED_PORT |= (1 << DEBUG_LED);
			_delay_ms(2000);
		}
		/*if( ( BTN1_PIN & ( 1 << BTN1 ) ) == 0 )
		{
			//dbg_led_go^= 1;
			DEBUG_LED_PORT ^= (1 << DEBUG_LED);
		}*/


		DEBUG_LED_PORT ^= (1 << DEBUG_LED);
		for( i =0; i < freq ; i++)
			_delay_ms(1);
		
		
	}

	return 0;
}
