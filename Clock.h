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

extern boolean ButtonNextState(int input);
extern int currentClock[];

int hours, minutes, seconds, timerError;
unsigned long clockTimer;
boolean clockSet;

//Function prototypes:
  void ClockSetup(void);
  void ConcatenateArrays(void);
  boolean OneSecondPassed(void);
  void UpdateClockTimer(void);
  void UpdateClock(void);
//

void ClockSetup()
{
  clockSet = false;
	clockTimer = millis();
}

void ConcatenateArrays()
{
	hours = (currentClock[0] * MULTIPLIER) + currentClock[1];
	minutes = (currentClock[2] * MULTIPLIER) + currentClock[3];
	seconds = (currentClock[4] * MULTIPLIER) + currentClock[5];
}

boolean OneSecondPassed()
{
	if (millis() - clockTimer >= CLOCK_INTERVAL)
	{
	  timerError = (millis() - clockTimer - CLOCK_INTERVAL);
	  return true;
	}
	else return false;
}

void UpdateClockTimer()
{
	clockTimer += (CLOCK_INTERVAL - timerError);
}

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
}

#endif
