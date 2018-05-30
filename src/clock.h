#ifndef _CLOCK_H
#define _CLOCK_H

#include "ds3231.h"
#include "clock.h"

// define current century year
#define CURRENT_YEAR 2000

//Initialization Function
uint8_t ClockInit();

//Get Function
uint8_t GetDate();
uint8_t GetMonth();
uint16_t GetYear();
uint8_t GetSecond();
uint8_t GetMinute();
uint8_t GetHour();
uint8_t GetTemp();

//Set Function
uint8_t SetDate(uint8_t date);
uint8_t SetMonth(uint8_t month);
uint8_t SetYear(uint16_t year);
uint8_t SetSecond(uint8_t sec);
uint8_t SetMinute(uint8_t min);
uint8_t SetHour(uint8_t hr);

#endif
