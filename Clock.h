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
  extern int currentClock[];

  int hours, minutes, seconds, timerError;
  unsigned long clockTimer;
  boolean clockSet;
//

//Function prototypes and external functions:
  void ClockSetup(void);
  void ConcatenateArrays(void);
  boolean OneSecondPassed(void);
  void UpdateClockTimer(void);
  void UpdateClock(void);

  extern boolean ButtonNextState(int input);
//

void ClockSetup()
{
  clockSet = false;
	clockTimer = millis();
} // End of ClockSetup()

void ConcatenateArrays()
{
	hours = (currentClock[0] * MULTIPLIER) + currentClock[1];
	minutes = (currentClock[2] * MULTIPLIER) + currentClock[3];
	seconds = (currentClock[4] * MULTIPLIER) + currentClock[5];
} // End of ConcatenateArrays()

boolean OneSecondPassed()
{
	if (millis() - clockTimer >= CLOCK_INTERVAL)
	{
	  timerError = (millis() - clockTimer - CLOCK_INTERVAL);
	  return true;
	}
	else return false;
} // End of OneSecondPassed()

void UpdateClockTimer()
{
	clockTimer += (CLOCK_INTERVAL - timerError);
} // End of UpdateClockTimer()

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
			else
			{
				hours = 0;
			}
		}
	}
} // End of UpdateClock()

#endif
