/**
* < Written by Stephen Caffera and Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker >
*/

/**
* This program is designed using Model-View-Controller (MVC) architecture.
* Clock.h, Encoder.h, and Solar.h are header files containing the code for the model portion of the project.
* IO.h is a header file containing the code for the view portion, and this main file,
* SolarTrackerProject.ino acts as the controller that calls all other header files and functions.
*/
#include "Clock.h"
#include "Encoder.h"
#include "IO.h"
#include "Solar.h"

extern unsigned long solarTimer;
extern int solarAngle;

/**
* Setup calls functions necessary for initializing the clock,
* the encoder functionality, and the photoreactors.
*/
void setup()
{
  IO_Setup();
	EncoderSetup();
  SolarSetup();
	ClockSetup();
} // End setup

/**
* In the main loop of the program, the clock is set based on user input to the
* serial monitor; then, a function is called to move the solar tracker into position
* based on the time the user entered. Then, then solar trakcer moves by 0.25
* degrees every 1 minute that passes, controlled by a function in the Solar.h
* header file.
*/
void loop()
{ 
  while (!clockSet) // Prompts user to set clock while control variable is false (i.e. clock has not been set)
  {
    SetTime(Serial.read()); // Allows user to set the clock via serial input monitor
  }

  AdjustSolar(ReadSolar()); // Calls AdjustSolar() continuously within the loop; timing of moving solar panel is controlled in Solar.h
  if (Serial.available()) Console_SetTime(Serial.read());
  

	if (OneSecondPassed()) // Calls OneSecondPassed() in Clock.h to determine if clock face needs to be updated on LCD
	{
    UpdateClockTimer();
		if (clockSet) // Only updates and prints clock if it is running
		{
		  UpdateClock(); // Updates the time by one second
		  Universal_PrintTime(); // Prints the clock face on the top line of the LCD and on the serial monitor
		}
    Universal_PrintAngle(solarAngle); // Prints solar angle on the line below the clock on the LCD and on the serial monitor
	}
} // End main loop
