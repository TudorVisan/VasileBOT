#include "board.h"

volatile int freq = 1000, freq_max = 4999, freq_min = 99;
volatile int dbg_led_go = 0;
volatile int sens[7] = {0};

void button1_callback(void)
{
	if (freq < freq_max)
		freq+=100;
}

void button2_callback(void)
{
	if (freq > freq_min)
		freq-=100;
}

void button3_callback(void)
{
	dbg_led_go ^= 1;
	power_led_change_state(dbg_led_go);
}

int main()
{
	int i;

	init_board(button1_callback, button2_callback, button3_callback);


	for (i =0; i < 3; ++i)
	{
	          debug_led_set_state(1);
	          delay(250);

	          debug_led_set_state(0);
	          delay(250);
	}

	 

	while(1)
	{
		sensors_read(sens);

		if (sens[0] != 0){
			debug_led_set_state(1);
			delay(3000);
		}
		

                debug_led_set_state(1);
                delay(freq);

                debug_led_set_state(0);
                delay(freq);

                motors_set_speed(130, 0);
                delay(1000);
                motors_set_speed(12, 0);
                delay(1000);

	}

	return 0;
}
