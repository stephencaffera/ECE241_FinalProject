/**
* < Written by Stephen Caffera & Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker >
* 
* < SolarTrackerProject.ino: Main file for program; control flow between header files >
* 
* This program is designed using the Model-View-Controller (MVC) architecture.
* Clock.h, Encoder.h, and Solar.h are header files containing the code serving as the Model for the program.
* IO.h is a header file containing the code serving as the View for the program. 
* SolarTrackerProject.ino is an Arduino source file containing the code serving as the Controller for the program.
*/

#include "Clock.h"
#include "Encoder.h"
#include "IO.h"
#include "Solar.h"

//Function prototypes:
  void setup(void);
  void loop(void);
//

/**
* Setup calls functions necessary for initializing the clock, the encoder functionality, the input/output stream, and the light sennsors.
* The setup functions in each header file prepare all the necessary variables and functions to start the program.
*/
void setup()
{
  IO_Setup();
	EncoderSetup();
  SolarSetup();
	ClockSetup();
} // End of setup()

/**
* In the main loop of the program, the clock is set based on user input to the
* serial monitor; then, a function is called to move the solar tracker into position
* based on the time the user entered. Then, then solar trakcer moves by 0.25
* degrees every 1 minute that passes, controlled by a function in the Solar.h
* header file.
*/
void loop()
{
  while (!clockSet) // Prompts user to set clock while control variable is false
  {
    Console_SetTime(); // Allows user to set the clock via serial input monitor
	  ClockSetNextState(); // ...OR, allows the user to set the clock via LCD input; see IO.h
  }
  
  if (millis() > solarTimer) AdjustSolar(ReadSolar()); // Continually adjusts the Servo to respond to changes in the direction of its light source
  
	if (OneSecondPassed()) // Determines if clock face needs to be updated and reprinted
	{
    UpdateClockTimer(); // Resets the clock timer and adjusts for time error
    UpdateClock(); // Updates the time by one second
		if (clockSet) Universal_PrintTime(); // Prints the clock face on the top line of the LCD and on the serial monitor; only prints if the clock is running
    Universal_PrintAngle(solarAngle); // Prints solar angle on the line below the clock on the LCD and on the serial monitor
	}

  if (Serial.available()) if (Console_TimeChangeRequested()) Console_SetTime();
  if (clockSet) if (ButtonNextState(digitalRead(PRESS_READ))) ClockSetNextState;
} // End of loop()
