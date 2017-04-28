#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_INTERVAL 1000

enum ClockStates {Running, SetHours, SetMinutes, SetSeconds};

ClockStates clockState;
boolean clockSet;
int hours, minutes, seconds, timerError;
unsigned long clockTimer;

void ClockSetup()
{
	clockTimer = millis();
  clockSet = false;
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

void SetTime(char input)
{
	switch (clockState)
	{ 
		case Running:
			if (input == 'S' || input == 's')
			{
				hours = 0; 
				minutes = 0;
				seconds = 0;
				clockState = SetHours;
        clockSet = false;
			} 
			break;
		case SetHours: 
			if (input >= 0 && <= 24) hours = input;
			else if (input == ':') clockState = SetMinutes;
			else if (input == 'R')
			{
			  clockState = Running;
        clockSet = true;
			}
			break;
		case SetMinutes: 
			if (input >= 0 && <= 59) minutes = input;
      else if (input == ':') clockState = SetSeconds;
      else if (input == 'R')
      {
        clockState = Running;
        clockSet = true;
      }
      break;
		case SetSeconds: 
			if (input >= 0 && <= 59)
			{
			  seconds = input;
        clockSet = true;
			}
      else if (input == 'R') clockState = Running;
      break;
	}
} 

#endif
