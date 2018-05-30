#ifndef DS1307_H
#define DS1307_H

#include <avr/io.h>

uint8_t DS3231Read(uint8_t address,uint8_t *data);
uint8_t DS3231Write(uint8_t address,uint8_t data);

#endif
