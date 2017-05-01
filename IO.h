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
#define ARRAY_LENGTH 6

extern int hours, minutes, seconds;
extern boolean clockSet;

enum ClockStates {CLOCK_RUNNING, CLOCK_SET_HOURS, CLOCK_SET_MINUTES, CLOCK_SET_SECONDS};
ClockStates clockState = CLOCK_SET_HOURS;

LiquidCrystal LCD(11, 9, 5, 6, 7, 8);

int currentClock[ARRAY_LENGTH], newTime[3], CurrentClockIndex;

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

void ClockSetNextState()
{
 switch (clockState)
  {
    case CLOCK_SET_HOURS:
      CurrentClockIndex = 0; // local variable
      EditCurrentClockPosition(CurrentClockIndex);
      
	    CurrentClockIndex = 1; // local variable
      EditCurrentClockPosition(CurrentClockIndex);
      
      clockState = CLOCK_SET_MINUTES;
      break;
      
    case CLOCK_SET_MINUTES:
      CurrentClockIndex = 2;
      EditCurrentClockPosition(CurrentClockIndex);
      
	    CurrentClockIndex = 3;
      EditCurrentClockPosition(CurrentClockIndex);
      
      clockState = CLOCK_SET_SECONDS;
      break;
      
    case CLOCK_SET_SECONDS:
      CurrentClockIndex = 4;
      EditCurrentClockPosition(CurrentClockIndex);
      
	    CurrentClockIndex = 5;
      EditCurrentClockPosition(CurrentClockIndex);
    
      clockSet = false;
      ConcatenateArrays(); // Calls the ConcatenateArrays function to parse arrays indices into proper formats
      clockSet = true;
      break;
    }
} // End of ClockSetNextState function

void EditCurrentClockPosition(int n)
{
  encoderPosition = 0;
  do{
    do
    {
      LCD.setCursor(n, 0);
      LCD.print(encoderPosition);
      buttonpress = ButtonNextState(digitalRead(4)); // import button press function from lab5
    } while(buttonpress == 0);

    if (buttonpress == 1)
    {
      currentClock[n] = encoderPosition;
      LCD.setCursor(n, 0);
      LCD.print(encoderPosition);
    }
  } while (currentClock[n] == 0);
} // EditCurrentClockPosition

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
