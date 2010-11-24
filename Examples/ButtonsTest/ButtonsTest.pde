// ButtonsTest.pde
//
// Test Peggy2Buttons library

// Include libraries
#include <Display.h>
#include <Buttons.h>

// Create library objects
Peggy2Display Display;
Peggy2Buttons Buttons;

void setup()
{
	// Construct library objects
	Display = Peggy2Display();
	Display.SetRefreshRate(60.0);
	Buttons = Peggy2Buttons();
}

void loop()
{
	// Poll buttons to get latest button status
	Buttons.Poll();
	
	// Display the state of the buttons
	Display.framebuffer[0] = Buttons.PollState;
	Display.framebuffer[4] = Buttons.Pressed;
	Display.framebuffer[8] = Buttons.Released;
	Display.framebuffer[12] = BUTTONS_CURRENT;

	// Insert a delay to make Pressed and Released visible
	delay(100);
}

