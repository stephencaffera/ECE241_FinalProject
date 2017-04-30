#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_INTERVAL 1000

extern boolean ButtonNextState(int input);

ClockStates clockState;
int hours, minutes, seconds, timerError;
unsigned long clockTimer;

void ClockSetup()
{
	clockTimer = millis();
  clockState = CLOCK_SET_HOURS;
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
