#include <avr/io.h>
#include <util/delay.h>
#include "display.h"

void HC595Init()
{
   //make the SER, SRCLK, RCLK lines as output
   HC595_DDR|=((1<<HC595_SRCLK)|(1<<HC595_RCLK)|(1<<HC595_SER));
}

void HC595Pulse()
{
   HC595_PORT|=(1<<HC595_SRCLK);    // set SRCLK line as high
   HC595_PORT&=(~(1<<HC595_SRCLK)); // set SRCLK line as low
}

void HC595Latch()
{
   HC595_PORT|=(1<<HC595_RCLK);    // set RCLK line as high
   HC595_PORT&=(~(1<<HC595_RCLK)); // set RCLK line as low
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

void SevenSegment(uint8_t num)
{
	HC595Init();
	HC595Write(num);
}

