#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#define delay_time 1000

int main(void)
{
	HC595Init();
	while(1)
	{
		SevenSegment(SEG_9);
		_delay_ms(delay_time);
		SevenSegment(SEG_8);
		_delay_ms(delay_time);
		SevenSegment(SEG_7);
		_delay_ms(delay_time);
		SevenSegment(SEG_6);
		_delay_ms(delay_time);
		SevenSegment(SEG_5);
		_delay_ms(delay_time);
		SevenSegment(SEG_4);
		_delay_ms(delay_time);
		SevenSegment(SEG_3);
		_delay_ms(delay_time);
		SevenSegment(SEG_2);
		_delay_ms(delay_time);
		SevenSegment(SEG_1);
		_delay_ms(delay_time);
		SevenSegment(SEG_0);
		_delay_ms(delay_time);
	}
	return 0;
}
