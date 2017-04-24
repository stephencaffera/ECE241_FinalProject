#ifndef Clock_H
#define Clock_H

#define CLOCK_INTERVAL 1000

#define CONCAT(A, B) A ## B

unsigned int hours, minutes, seconds, clockTimer = 0;

void ClockSetup()
{
	SetTime();
	clockTimer = millis();
}

void Console_PrintTime()
{
	if (hours < 10) 
	{
		Serial.print("0");
	} 
	
	Serial.print(hours); 
	Serial.print(":");

	
	if (minutes < 10) 
	{
		Serial.print("0");
	} 
	
	Serial.print(minutes);
	Serial.print(":");

	if (seconds < 10) 
	{
		Serial.print("0");
	} 
	
	Serial.println(seconds);
} 

void LCD_PrintTime()
{
	LcdDriver.print("                ");
	if (hours < 10) {
		LcdDriver.print("0");
	}
	LcdDriver.print(hours);
	LcdDriver.print(":");

	if (minutes < 10) {
		LcdDriver.print("0");
	}
	LcdDriver.print(minutes);
	LcdDriver.print(":");

	if (seconds < 10) {
		LcdDriver.print("0");
	}
	LcdDriver.print(seconds);
}

boolean OneSecondPassed()
{
	if (millis() - clockTimer >= CLOCK_INTERVAL) return true;
	else return false;
}

void Console_SetTime()
{
	do
	{
		Serial.write("Enter the current time (hh:mm:ss): ")
			string userTime = Serial.read();

		if (userTime == 'Q' || userTime == 'q') break;
	} while (strlen(userTime) == 8);

	hours = CONCAT(userTime[0], userTime[1]);
	minutes = CONCAT(userTime[3], userTime[4]);
	seconds = CONCAT(userTime[6], userTime[7]);
}

void UpdateClockTimer()
{
	clockTimer += CLOCK_INTERVAL;
}

void UpdateTime()
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

enum ClockStates {CLOCK_RUNNING, SET_HOURS, SET_MINUTES, SET_SECONDS};

ClockStates clockState = CLOCK_RUNNING;

void LCD_SetTime(char input)
{
	switch (clockState)
	{ 
		case CLOCK_RUNNING:
			if (input == 'S')
			{
				
				Hours = 0; 
				Minutes = 0;
				Seconds = 0;
				clockState = SET_HOURS;
			} 
			break;
		case SET_HOURS: 
			if (input >= '0' && input <= '9')
			{
				Hours = 10 * (Hours % 10) + input - '0';
			}
			else if (input == ':')
			{
				clockState = SET_MINUTES;
			}
			else if (input == 'R')
			{
				clockState = CLOCK_RUNNING;
			}
			break;
		case SET_MINUTES: 
			if (input >= '0' && input <= '9')
			{
				Minutes = 10 * (Minutes % 10) + input - '0';
			}
			else if (input == ':')
			{
				clockState = SET_SECONDS;
			}
			else if (input == 'R')
			{
				clockState = CLOCK_RUNNING;
			}
			break;
		case SET_SECONDS: 
			if (input >= '0' && input <= '9')
			{
				Seconds = 10 * (Seconds % 10) + input - '0';
			}
			else if (input == 'R')
			{
				clockState = CLOCK_RUNNING;
			}
			break;
	}
} #endif
