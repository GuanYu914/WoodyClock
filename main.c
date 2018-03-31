#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <display.h>
#include <clock.h>

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

void TimerInit()
{
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
}

int main(void)
{
	uint8_t Temp_min = 0, Temp_hour = 0, Temp_temp = 0;

	// SetHour(23);
	// SetMinute(7);
	// SetSecond(10);
	HC595Init();	
	TimerInit();
	ClockInit();
	
	while(1)
	{			
		Temp_min = GetMinute();
		Temp_hour = GetHour();
		digit[0] = Temp_min%10;
		digit[1] = Temp_min/10;
		digit[2] = Temp_hour%10;
		digit[3] = Temp_hour/10;
		_delay_ms(5000);
		Temp_temp = GetTemp();
		digit[0] = Temp_temp%10;
		digit[1] = Temp_temp/10;
		digit[2] = 0;
		digit[3] = 0;	
		_delay_ms(5000);
	}
	return 0;
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t i = 0;
	
	if(i == 3)
	{
		i = 0;
	}else
	{
		i++;
	}
	
	// turn off all digit switch
	DISPLAY_PORT&=(~(1<<BUT_DIGIT3));
	DISPLAY_PORT&=(~(1<<BUT_DIGIT2));
	DISPLAY_PORT&=(~(1<<BUT_DIGIT1));
	DISPLAY_PORT&=(~(1<<BUT_DIGIT0));

	if(i == 3)
	{
		DISPLAY_PORT|=(1<<BUT_DIGIT3);
	}
	if(i == 2)
	{
		DISPLAY_PORT|=(1<<BUT_DIGIT2);
	}
	if(i == 1)
	{
		DISPLAY_PORT|=(1<<BUT_DIGIT1);
	}
	if(i == 0)
	{
		DISPLAY_PORT|=(1<<BUT_DIGIT0);
	}
	SevenSegDisplay(digit[i]);
}

