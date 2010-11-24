/*
  Buttons.cpp - Peggy 2.0 Pushbutton Library for Arduino
  Version 1.0 - 06/20/2008
  Copyright (c) 2008 Arthur J. Dahm III.  All right reserved.
  Email: art@mindlessdiversions.com
  Web: mindlessdiversions.com/peggy2

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

extern "C" {
#include <inttypes.h>
#include <binary.h>
#include <avr/interrupt.h>
#include <avr/io.h>
}

#include "Buttons.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/

#define BUTTON_DEBOUNCE 20UL	// Time in mS to wait until next poll


/******************************************************************************
 * Initialize Class Variables
 ******************************************************************************/

// The current state of the buttons after calling Poll()
uint8_t Peggy2Buttons::PollState;

// Buttons whose state has changed to pressed since the last call to Poll()
uint8_t Peggy2Buttons::Pressed;

// Buttons whose state has changed to released since the last call to Poll()
uint8_t Peggy2Buttons::Released;

uint32_t Peggy2Buttons::debounce;
uint8_t Peggy2Buttons::pollStatePrev;

/******************************************************************************
 * Constructor
 ******************************************************************************/

Peggy2Buttons::Peggy2Buttons(void)
{
	// Set up input buttons
	PORTB = B00000001;	// Pull up on ("OFF/SELECT" button)
	PORTC = B00011111;	// Pull-ups on C
	DDRB = B11111110;		// B0 is an input ("OFF/SELECT" button)
	DDRC = B11100000;		// All inputs

	pollStatePrev = BUTTONS_CURRENT;
	cli();
	debounce = millis();
	sei();
}

/******************************************************************************
 * User API
 ******************************************************************************/

// Process button input

void Peggy2Buttons::Poll()
{
	uint32_t debouncetime;

	cli();
	debouncetime = millis();
	sei();
	
	if (debouncetime > (debounce + BUTTON_DEBOUNCE))
	{
		debounce = debouncetime;
		
		PollState = BUTTONS_CURRENT;
		pollStatePrev ^= PollState;
	
		Pressed = pollStatePrev & PollState;
		Released = pollStatePrev & ~PollState;
	
		pollStatePrev = PollState;
	}
	else
	{
		Released = 0;
		Pressed = 0;
	}
}
