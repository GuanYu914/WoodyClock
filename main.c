#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "display.h"
#define delay_time 10

// force to initialize this array as volatile type
volatile uint8_t digit[4];

// process seperate digit number value
void FourSevenSegDisplay(uint16_t num)
{
	uint8_t i = 0, j = 0;
	while(num)
	{
		digit[i] = num % 10;
		num /= 10;
		i++;
	}
	for(j = i; j < 4; j++)
	{
		digit[j] = 0;
	}
}

int main(void)
{	
	uint16_t i;

	// prescaler = FCPU / 256
	TCCR0B|=(1<<CS02);
	
	// enable overflow interrupt enable
	TIMSK0|=(1<<TOIE0);

	// initialize counter
	TCNT0 = 0;
	
	// assigh all digit switch as output
	DISPLAY_DDR|=(1<<BUT_DIGIT0) | (1<<BUT_DIGIT1) | (1<<BUT_DIGIT2) | (1<<BUT_DIGIT3);
	
	// enable global interrupt
	sei();

	//FourSevenSegDisplay(9243);
	while(1)
	{
		FourSevenSegDisplay(9487);
		//Wait();
		/*
		for(i = 0; i < 10000; i++)
		{
			FourSevenSegDisplay(i);
			_delay_ms(10);
		}
		*/			
	}
	return 0;
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t i = 0;
	
	// turn off all digit switch
	DISPLAY_PORT&=(~(1<<BUT_DIGIT0));
	DISPLAY_PORT&=(~(1<<BUT_DIGIT1));
	DISPLAY_PORT&=(~(1<<BUT_DIGIT2));
	DISPLAY_PORT&=(~(1<<BUT_DIGIT3));
	
	// display separate digit number alternately
	SevenSegDisplay(digit[i]);
	if(i == 3)
	{
		DISPLAY_PORT|=(1<<BUT_DIGIT3);
		i = 0;
	}else 
	{
		if(i == 0)
		{	
			DISPLAY_PORT|=(1<<BUT_DIGIT0);
		}
		if(i == 1)
		{
			DISPLAY_PORT|=(1<<BUT_DIGIT1);
		}
		if(i == 2)
		{
			DISPLAY_PORT|=(1<<BUT_DIGIT2);
		}
		i++;
	}
}

