/**
* < Written by Stephen Caffera & Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker >
* 
* < SolarTrackerProject.ino: Main file for program; control flow between header files >
* 
* This program is designed using the Model-View-Controller (MVC) architecture. The code is divided as follows:
*   Model: Clock.h, Encoder.h, Solar.h
*   View: IO.h
*   Controller: SolarTrackerProject.ino
* All .h files are included in SolarTrackerProject.ino with the '#include' preprocessor command.
* Interconnectivity between the .h files is achieved by using the 'extern' keyword on the necessary variables and functions
*/

#include "Clock.h"
#include "Encoder.h"
#include "IO.h"
#include "Solar.h"

//Function prototypes:
  void setup(void);
  void loop(void);

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
* In the main loop of the program, the clock is set based on user input via the
* serial monitor or via the LCD and encoder; then, a function is called to move the solar tracker 
* into position based on the time the user entered. Then, then solar trakcer moves by 0.25
* degrees every 1 minute that passes, controlled by a function in the Solar.h header file.
*/
void loop()
{
  while (!clockSet) // Prompts user to set clock while control variable is false
  {
    if (Console_TimeChangeRequested()) Console_SetTime(); // Allows user to set the clock via serial input monitor
    if (clockSet) break;
	  if (ButtonNextState(digitalRead(PRESS_READ))) ClockSetNextState(); // ...OR, allows the user to set the clock via LCD input; see IO.h
  }

  if (OneSecondPassed()) // Determines if clock face needs to be updated and reprinted
  {
    UpdateClockTimer(); // Resets the clock timer and adjusts for time error
    UpdateClock(); // Updates the time by one second
    if (clockSet) Universal_PrintTime(); // Prints the clock face on the top line of the LCD and on the serial monitor; only prints if the clock is running
    Universal_PrintAngle(solarAngle); // Prints solar angle on the line below the clock on the LCD and on the serial monitor
  }
  
  if (millis() > solarTimer) AdjustSolar(ReadSolar()); // Continually adjusts the Servo to respond to changes in the direction of its light source

  if (Serial.available()) if (Console_TimeChangeRequested()) Console_SetTime();
  if (clockSet) if (ButtonNextState(digitalRead(PRESS_READ))) ClockSetNextState();
} // End of loop()
