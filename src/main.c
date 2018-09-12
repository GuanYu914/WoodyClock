#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <display.h>
#include <clock.h>
#include <button.h>

// force to initialize this array as volatile type
volatile uint8_t digit[5];
volatile uint8_t mode = 0;
volatile uint8_t scanFreq = 0;
volatile uint8_t butFreq = 0;
volatile uint16_t timeFreq = 0; 

// process seperate digit number value
// uncomment this function uintil using for special situation 
/*
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
*/

void Timer2Init()
{
	scanFreq = 0;
	// prescaler = FCPU / 32
	TCCR2B|=(1<<CS20) | (1<<CS21);
	
	// enable overflow interrupt enable
	TIMSK2|=(1<<TOIE2);

	// initialize counter
	TCNT2 = 0;
	
	// assigh all digit switch as output
	DISPLAY_DDR|=(1<<BUT_DIGIT0) | (1<<BUT_DIGIT1) | (1<<BUT_DIGIT2) | (1<<BUT_DIGIT3)| (1<<BUT_DIGIT4);
	
	// enable global interrupt
	sei();
}

void ClockGlobalSet(uint16_t year, uint8_t month, uint8_t date, uint8_t hr, uint8_t min, uint8_t sec)
{
	SetYear(year);
	SetMonth(month);
	SetDate(date);
	SetHour(hr);
	SetMinute(min);
	SetSecond(sec);
}


int main(void)
{
	uint8_t Temp_min = 0, Temp_hour = 0, Temp_temp = 0, Temp_month = 0, Temp_date = 0;
	uint16_t Temp_year = 0;

	HC595Init();	
	Timer2Init();
	ClockInit();
	ButtonInit();

	//Print initial logo before start to work
	digit[0] = 's';
	digit[1] = 's';
	digit[2] = 's';
	digit[3] = 's';	
	_delay_ms(2000);
	
	//ClockGlobalSet(2018, 6, 26, 14, 33, 0);
	
	while(1)
	{
		if(mode == 0)
		{	
			Temp_min = GetMinute();
			Temp_hour = GetHour();
			digit[0] = Temp_min%10;
			digit[1] = Temp_min/10;
			digit[2] = Temp_hour%10;
			digit[3] = Temp_hour/10;
			digit[4] = ':';
		}
		
		if(mode == 1)
		{
			Temp_year = GetYear();
			digit[3] = Temp_year /1000;
			Temp_year %= 1000;
			digit[2] = Temp_year / 100;
			Temp_year %= 100;
			digit[1] = Temp_year / 10;
			Temp_year %= 10;
			digit[0] = Temp_year;
			_delay_ms(1000);
			Temp_date = GetDate();
			digit[0] = Temp_date % 10;
			digit[1] = Temp_date / 10;
			Temp_month = GetMonth();
			digit[2] = Temp_month % 10;
			digit[3] = Temp_month / 10;
			_delay_ms(1000);
		}
		
		if(mode == 2)
		{
			Temp_temp = GetTemp();
			digit[3] = Temp_temp/10;
			digit[2] = Temp_temp%10;
			digit[1] = 'o';
			digit[0] = 'c';	
		}
	}
	return 0;
}

ISR(TIMER2_OVF_vect)
{
	static uint8_t i = 0;
		
	butFreq++;
	if(butFreq > 5)
	{
		butFreq = 0;
		if(ButtonDebounce())
		{
			if(mode == 2)
			{
				mode = 0;
			}else
			{
				mode++;
			}
		}
	}
	scanFreq++;
	if(scanFreq >= 6)
	{
		scanFreq = 0;	
		
		if(i == 4)
		{
			i = 0;
		}else
		{
			i++;
		}
	
		DISPLAY_PORT&=(~(1<<BUT_DIGIT3));
		DISPLAY_PORT&=(~(1<<BUT_DIGIT2));	
		DISPLAY_PORT&=(~(1<<BUT_DIGIT0));
		DISPLAY_PORT&=(~(1<<BUT_DIGIT1));		

		if(i == 4)
		{
			if(mode == 0)
			{
				timeFreq++;
				if(timeFreq >= 67)
				{
					DISPLAY_PORT^=(1<<BUT_DIGIT4);
					timeFreq = 0;
				}			
			}else
			{
					DISPLAY_PORT&=(~(1<<BUT_DIGIT4));
			}
		}	
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
}
