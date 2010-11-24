/*
  Buttons.h - Peggy 2.0 Pushbutton Library for Arduino
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


#ifndef Buttons_h
#define Buttons_h

#include <inttypes.h>
#include <wiring.h>

#define BUTTON_ANY 1			// b1 "any" button
#define BUTTON_LEFT 2			// b2 "left" button
#define BUTTON_DOWN 4			// b3 "down" button
#define BUTTON_UP 8				// b4 "up" button
#define BUTTON_RIGHT 16		// b5 "right" button
#define BUTTON_OFF_SEL 32	// s2 "off/select" button
#define BUTTONS_CURRENT ((PINC & B00011111) | ((PINB & 1)<<5))^B00111111	// Actual hardware state


class Peggy2Buttons
{
	public:
		// Constructor
		// Initialize hardware
		Peggy2Buttons(void);

		// Get the current state of the pushbuttons on the Peggy 2.0 board
		// return - PollState, Pressed, Released
		void Poll(void);

		// The current state of the buttons after calling Poll()
		static uint8_t PollState;

		// Buttons whose state has changed to pressed since the last call to Poll()
		static uint8_t Pressed;

		// Buttons whose state has changed to released since the last call to Poll()
		static uint8_t Released;

	private:
		static uint32_t debounce;
		static uint8_t pollStatePrev;
};

#endif

