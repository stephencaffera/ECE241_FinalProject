/**
* < Written by Stephen Caffera & Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker>
*
* < Clock.h: header file for clock control >
*/

#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_INTERVAL 1000
#define MULTIPLIER 10

//Global variable declarations:
  int hours, minutes, seconds, timerError;
  unsigned long clockTimer;
  boolean clockSet;

  extern int currentClock[];

//Function prototypes and external function declarations:
  void ClockSetup(void);
  void ConcatenateArrays(void);
  boolean OneSecondPassed(void);
  void UpdateClockTimer(void);
  void UpdateClock(void);

  extern boolean ButtonNextState(int input);

/**
* ClockSetup:
* A function for initializing the master clockSet boolean variable, and initializing
* the clockTimer.
*
* @params: void
* @return: void
*/
void ClockSetup()
{
  clockSet = false;
	clockTimer = millis();
} // End of ClockSetup()

/**
* ConcatenateArrays:
* A function that takes the input arrays from LCD clock-setting, and converts
* them into usable numbers to be assigned to the hours, minutes, and seconds
* global variables.
*
* @params: void
* @return: void
*/
void ConcatenateArrays()
{
	hours = (currentClock[0] * MULTIPLIER) + currentClock[1];
	minutes = (currentClock[2] * MULTIPLIER) + currentClock[3];
	seconds = (currentClock[4] * MULTIPLIER) + currentClock[5];
} // End of ConcatenateArrays()

/**
* OneSecondPassed:
* A function the checks to see if one second has passed on the timer.
*
* @params: void
* @return: true or false
*/
boolean OneSecondPassed()
{
	if (millis() - clockTimer >= CLOCK_INTERVAL)
	{
	  timerError = (millis() - clockTimer - CLOCK_INTERVAL);
	  return true;
	}
	else return false;
} // End of OneSecondPassed()

/**
* updateClockTimer:
* A function for updating the clock timer every second, and taking into account
* an error margin in the accuracy of the timer.
*
* @params: void
* @return: void
*/
void UpdateClockTimer()
{
	clockTimer += (CLOCK_INTERVAL - timerError);
} // End of UpdateClockTimer()

/**
* UpdateClock:
* A function that updates the minutes, seconds, and hours of the clock; to be
* called every second to change the clock values.
*
* @params: void
* @return: void
*/
void UpdateClock()
{
	if (seconds < 59) seconds++;
	else
	{
		seconds = 0;

		if (minutes < 59) minutes++;
		else
		{
			minutes = 0;

			if (hours < 23) hours++;
			else hours = 0;
		}
	}
} // End of UpdateClock()

#endif
