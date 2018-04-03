#include "button.h"

// initialize pull up resistor to the pin 
void ButtonInit()
{
	BUTTON_PORT |= BUTTON_MASK;	
}

// solve push button debounce issue
uint8_t ButtonDebounce()
{
	// counter for number of equal states
	static uint8_t count = 0;
	// keep track of current (debounced) state
	static uint8_t button_state = 0;
	// set 1 if check button is debounced and changed 
	uint8_t button_down = 0;
	// check if button is high or low 
	uint8_t current_state = (~BUTTON_PIN & BUTTON_MASK) != 0;
	// if state is changed
	if(current_state != button_state)
	{
		count++;
		if(count >= 4)
		{
			// assign current_state into button_state
			button_state = current_state;
			if(current_state != 0)
			{
				// set button debounce flag 
				button_down = 1;
			}
			count = 0;
		}
	}
	// if state is not changed
	else
	{
		button_down = 0;
		count = 0;
	}
	return button_down;
}

