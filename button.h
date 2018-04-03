#ifndef _BUTTON_H
#define _BUTTON_H
#include <avr/io.h>

#define BUTTON_MASK (1<<PD2)
#define BUTTON_PIN  PIND
#define BUTTON_PORT PORTD

void ButtonInit();
uint8_t ButtonDebounce();

#endif
