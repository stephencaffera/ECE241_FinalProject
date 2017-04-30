#ifndef IO_H
#define IO_H

#include <LiquidCrystal.h>
/*
#include <stdio.h> //Add formatted printing using sprintf()
*/

#define BAUD_RATE 9600
#define TOP_ROW 0
#define BOTTOM_ROW 1
#define FIRST_COL 0
#define CLEAR "                "

extern int hours, minutes, seconds;

LiquidCrystal LCD(11, 9, 5, 6, 7, 8);

enum ClockStates = {CLOCK_RUNNING, CLOCK_SET_HOURS, CLOCK_SET_MINUTES, CLOCK_SET_SECONDS};

int[3] newTime;

void Console_PrintTime()
{
  Serial.print("Time: ");
  if (hours < 10) Serial.print("0");

  Serial.print(hours);
  Serial.print(":");

  if (minutes < 10) Serial.print("0");

  Serial.print(minutes);
  Serial.print(":");

  if (seconds < 10) Serial.print("0");

  Serial.println(seconds);
}

void Console_PrintAngle(int angle)
{
  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.println(" deg.\n");
}

void Console_SetTime(char input)
{
  if (input == 'S' || input == 's')
  {
    do
    {
      Serial.print("Enter new hours: ");
        newTime[0] = Serial.read();
    } while (newTime[0] < 0 && newTime[0] > 23);

    do
    {
      Serial.print("Enter new minutes: ");      
        newTime[1] = Serial.read();
    } while (newTime[1] < 0 && newTime[1] > 59);

    do
    {
      Serial.print("Enter new seconds: ");
        newTime[2] = Serial.read();
    } while (newTime[2] < 0 && newTime[2] > 59);

    Serial.print("Changing time to ");
    Console_PrintTime();
    Serial.print("Confirm (Y/N): ");
      char confirm = Serial.read();

    if (confirm == 'Y' || confirm == 'y')
    {
      hours = newTime[0];
      minutes = newTime[1];
      seconds = newTime[2];
    }
  }
}

void IO_Setup()
{
  Serial.begin(BAUD_RATE);
  LCD.clear();
}

void LCD_PrintTime()
{
  LCD_ClearTopRow();

  if (hours < 10) LCD.print("0");

  LCD.print(hours);
  LCD.print(":");

  if (minutes < 10) LCD.print("0");

  LCD.print(minutes);
  LCD.print(":");

  if (seconds < 10) LCD.print("0");

  LCD.print(seconds);
}

/**
* SettingClock is a function that processes incoming
* characters from serial input to set the clock. If the user enters
* the letter "S" or "s", clock-setting mode will execute.
* @params: char Input.
*/
void SettingClock(char Input)
{
	// interpret input based on state
	switch (clockState)
	{
	case CLOCK_RUNNING:
		if (Input == 'S' || Input == 's') // If user inputs 'S' or 's'
		{
			clockState = CLOCK_SET_HOURS;
			hours = 0;   // Resets clock variables to 0 before setting
			minutes = 0;
			seconds = 0;
		}
		break;

	case CLOCK_SET_HOURS: //
		if (Input >= '0' && Input <= '9')
			hours = 10 * (hours % 10) + Input - '0';
		else if (Input == ':')
			clockState = CLOCK_SET_MINUTES;
		else if (Input == 'R')
			clockState = CLOCK_RUNNING;
		break;

	case CLOCK_SET_MINUTES: //
		if (Input >= '0' && Input <= '9')
			minutes = 10 * (minutes % 10) + Input - '0';
		else if (Input == ':')
			clockState = CLOCK_SET_SECONDS;
		else if (Input == 'R')
			clockState = CLOCK_RUNNING;
		break;

	case CLOCK_SET_SECONDS: //
		if (Input >= '0' && Input <= '9')
			seconds = 10 * (seconds % 10) + Input - '0';
      clockSet = true;
		else if (Input == 'R')
			clockState = CLOCK_RUNNING;
		break;
	}// End of clock mode switch statement
} // End of SettingClock function

void LCD_DisplayEncoderPosition(int col, int row, int encoderPosition)
{
    static int encoderCount = encoderPosition / 4;
    LCD.setCursor(col, row);
    LCD.print(encoderCount);
}

void LCD_ClearBottomRow()
{
  LCD.setCursor(FIRST_COL, BOTTOM_ROW);
  LCD.print(CLEAR);
}

void LCD_ClearTopRow()
{
  LCD.setCursor(FIRST_COL, TOP_ROW);
  LCD.print(CLEAR);
}

void LCD_PrintAngle(int angle)
{
  LCD_ClearBottomRow();
  LCD.setCursor(FIRST_COL, BOTTOM_ROW);
  LCD.print("Angle: ");
  LCD.print(angle);
  LCD.print(" deg.");
}

void Universal_PrintTime()
{
  Console_PrintTime();
  LCD_PrintTime();
}

void Universal_PrintAngle(int angle)
{
  Console_PrintAngle(angle);
  LCD_PrintAngle(angle);
}

#endif
