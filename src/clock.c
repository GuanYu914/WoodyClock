#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "ds3231.h"
#include "clock.h"

uint8_t ClockInit()
{
	// initialize i2c bus
	I2cInit();
	uint8_t temp = 0;
	if(!DS3231Read(0x00,&temp)){return 0;}
	if(!DS3231Write(0x00,temp)){return 0;}
	// set 24 hour mode
	if(!DS3231Read(0x02,&temp)){return 0;}
	// set 24 Hour bit
	temp|=(0b00000000);
	// write back to ds3231
	if(!DS3231Write(0x02,temp)){return 0;}
	return 1;
}

uint8_t GetDate()
{
	uint8_t date, temp;
	DS3231Read(0x04, &temp);
	date = (((temp & 0b00110000)>>4)*10) + (temp & 0b00001111);	
	return date;
}

uint8_t GetMonth()
{
	uint8_t month, temp;
	DS3231Read(0x05, &temp);
	month = (((temp & 0b00110000)>>4)*10) + (temp & 0b00001111);
	return month;
}

uint16_t GetYear()
{
	uint8_t year;
	uint8_t temp;
	uint16_t u16year;
	DS3231Read(0x06, &temp);
	year = (((temp & 0b11110000)>>4)*10) + (temp & 0b00001111);
	u16year = year + CURRENT_YEAR;
	return  u16year;
}

uint8_t GetSecond()
{
	uint8_t sec,temp;
	// read the second register
	DS3231Read(0x00,&temp);
	sec=(((temp & 0b01110000)>>4)*10)+(temp & 0b00001111);
	return sec;
}

uint8_t GetMinute()
{
	uint8_t min,temp;
	// read the minute register
	DS3231Read(0x01,&temp);
	min=(((temp & 0b01110000)>>4)*10)+(temp & 0b00001111);
	return min;	
}

uint8_t GetHour()
{
	uint8_t hr,temp;
	// read the hour register
	DS3231Read(0x02,&temp);
	if(((temp & 0b00100000)>>5)*20 > 0)
	{
		hr=(((temp & 0b00100000)>>5)*20)+(temp & 0b00001111);	
	}else
	{
		hr=(((temp & 0b00010000)>>4)*10)+(temp & 0b00001111);
	}
	return hr;
}

uint8_t GetTemp()
{
	uint8_t temp_dec = 0;
	uint8_t temp = 0;
	uint8_t mask;
	// read the temp decimal register
	DS3231Read(0x11, &temp_dec);
	//DS3231Read(0x12, &temp_dp);
	for(mask = 0x01; mask != 0; mask <<= 1)
	{
		if(temp_dec & mask)
		{
			// bit is one
			temp += mask;		
		}	
	}
	return temp;
}

uint8_t SetDate(uint8_t date)
{
	uint8_t temp, result;
	temp = ((date / 10)<<4) | (date % 10);
	result = DS3231Write(0x04, temp);
	return result;
}

uint8_t SetMonth(uint8_t month)
{
	uint8_t temp, result;
	temp = ((month / 10)<<4) | (month % 10);
	result = DS3231Write(0x05, temp);
	return result;
}

uint8_t SetYear(uint16_t year)
{
	uint8_t temp, result;
	year -= CURRENT_YEAR;
	uint8_t u8year;
	u8year = (uint8_t)year;
	temp = ((u8year / 10)<<4) | (u8year % 10);
	result = DS3231Write(0x06, temp);
	return result;
}

uint8_t SetSecond(uint8_t sec)
{
	uint8_t temp,result;
	temp=((sec/10)<<4)|(sec%10);
	result=DS3231Write(0x00,temp);
	return result;
}

uint8_t SetMinute(uint8_t min)
{
	uint8_t temp,result;
	temp=((min/10)<<4)|(min%10);
	result=DS3231Write(0x01,temp);
	return result;
}

uint8_t SetHour(uint8_t hr)
{
	uint8_t temp,result;
	
	// set 24 hour
	if(hr < 20)
	{
		temp=((hr/10)<<4)|(hr%10);
	}else 
	{
		temp=((hr/20)<<5)|(hr%10);
	}
	result=DS3231Write(0x02,temp);
	return result;	
}
