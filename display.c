#include <avr/io.h>
#include <util/delay.h>
#include "display.h"

void HC595Init()
{
   //make the SER, SRCLK, RCLK lines as output
   DISPLAY_DDR|=((1<<HC595_SRCLK)|(1<<HC595_RCLK)|(1<<HC595_SER));
}

void HC595Pulse()
{
   DISPLAY_PORT|=(1<<HC595_SRCLK);    // set SRCLK line as high
   DISPLAY_PORT&=(~(1<<HC595_SRCLK)); // set SRCLK line as low
}

void HC595Latch()
{
   DISPLAY_PORT|=(1<<HC595_RCLK);    // set RCLK line as high
   DISPLAY_PORT&=(~(1<<HC595_RCLK)); // set RCLK line as low
}

void HC595Write(uint8_t data)
{
   // send each 8 bits serially
	HC595DataHigh();
   //order is MSB first
   for(uint8_t i=0;i<8;i++)
   {
      //Output the data on DS line according to the
      if(data & 0b10000000)
      {
         HC595DataHigh();
      }
      else
      {
         HC595DataLow();
      }

      HC595Pulse();  // pulse the SRCLK line
      data=data<<1;  // now bring next bit at MSB position
   }
   HC595Latch();
}

void SevenSegDisplay(uint8_t num)
{
	HC595Init();
	if(num == 9)
	{
		HC595Write(SEG_9);
	}
	if(num == 8)
	{
		HC595Write(SEG_8);
	}
	if(num == 7)
	{
		HC595Write(SEG_7);
	}
	if(num == 6)
	{
		HC595Write(SEG_6);
	}
	if(num == 5)
	{
		HC595Write(SEG_5);
	}
	if(num == 4)
	{
		HC595Write(SEG_4);
	}
	if(num == 3)
	{
		HC595Write(SEG_3);
	}
	if(num == 2)
	{
		HC595Write(SEG_2);
	}
	if(num == 1)
	{
		HC595Write(SEG_1);
	}
	if(num == 0)
	{
		HC595Write(SEG_0);
	}
}

