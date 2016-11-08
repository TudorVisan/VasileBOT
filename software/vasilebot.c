#include "board.h"

int freq = 1000, freq_max = 4999, freq_min = 9;
int dbg_led_go = 0;
int sens[7] = {0};

void button1_callback(void)
{
	if (freq < freq_max)
		freq++;
}

void button2_callback(void)
{
	if (freq > freq_min)
		freq--;
}

void button3_callback(void)
{
	dbg_led_go ^= 1;
}

int main()
{
	init_board(button1_callback, button2_callback, button3_callback);

	while(1)
	{
                debug_led_set_state(1);
                delay(freq);

                debug_led_set_state(0);
                delay(freq);
	}

	return 0;
}
