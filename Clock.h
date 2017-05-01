#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_INTERVAL 1000

extern boolean ButtonNextState(int input);
extern enum ClockStates clockState;
extern int currentClock[];

int hours, minutes, seconds, timerError;
unsigned long clockTimer;

enum ClockStates = { CLOCK_RUNNING, CLOCK_SET_HOURS,
                    CLOCK_SET_MINUTES, CLOCK_SET_SECONDS };
ClockStates clockState = CLOCK_RUNNING;

void ClockSetup()
{
	clockTimer = millis();
	clockState = CLOCK_SET_HOURS;
}

void ConcatenateArrays()
{
	hours = (currentClock[0] * 10) + currentClock[1];
	minutes = (currentClock[2] * 10) + currentClock[3];
	seconds = (currentClock[4] * 10) + currentClock[5];
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
