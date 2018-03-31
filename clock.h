#ifndef _CLOCK_H
#define _CLOCK_H

#include "ds3231.h"
#include "clock.h"

//Initialization Function
uint8_t ClockInit();

//Get Function
uint8_t GetSecond();
uint8_t GetMinute();
uint8_t GetHour();
uint8_t GetTemp();

//Set Function
uint8_t SetSecond(uint8_t sec);
uint8_t  SetMinute(uint8_t min);
uint8_t  SetHour(uint8_t hr);

#endif
