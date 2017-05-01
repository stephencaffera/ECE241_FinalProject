/**
* < Written by Stephen Caffera & Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker>
*
* < IO.h: header file for input/output control >
*/

#ifndef IO_H
#define IO_H

#include <LiquidCrystal.h>

#define BAUD_RATE 9600
#define TOP_ROW 0
#define BOTTOM_ROW 1
#define FIRST_COL 0
#define CLEAR "                "
#define ARRAY_LENGTH 6
#define ENCODER_PIN 4

enum ClockStates {CLOCK_RUNNING, CLOCK_SET_HOURS, CLOCK_SET_MINUTES, CLOCK_SET_SECONDS}; //Enumerator for the clock state

//Global variable and object declarations:
  LiquidCrystal LCD(11, 9, 5, 6, 7, 8);
  
  ClockStates clockState = CLOCK_SET_HOURS;
  int currentClock[ARRAY_LENGTH], newTime[3], CurrentClockIndex;

  extern int hours, minutes, seconds;
  extern boolean clockSet;
//

//Function prototypes and external function declarations:
  void ClockSetNextState(void);
  void Console_PrintTime(void);
  void Console_PrintAngle(int);
  void Console_SetTime();
  boolean Console_TimeChangeRequested(void);
  void EditCurrentClockPosition(int);
  void IO_Setup(void);
  void LCD_ClearTopRow(void);
  void LCD_ClearTopRow(void);
  void LCD_PrintAngle(int);
  void LCD_PrintTime(void);
  void Universal_PrintTime(void);
  void Universal_PrintAngle(int);

  extern boolean ButtonNextState(int);
//

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
} // End of Console_PrintTime()

void Console_PrintAngle(int angle)
{
  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.println(" deg.\n");
} //End of Console_PrintAngle()

void Console_SetTime()
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

  if (Serial.read() == 'Y' || Serial.read() == 'y')
  {
    hours = newTime[0];
    minutes = newTime[1];
    seconds = newTime[2];
  }
} // End of Console_SetTime()

boolean Console_TimeChangeRequested()
{
  (Serial.read() == 'S' || Serial.read() == 's') ? return true : return false;
} // End of Console_TimeChangeRequested()

void IO_Setup()
{
  Serial.begin(BAUD_RATE);
  LCD.clear();
} // End of IO_Setup

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
} // End of LCD_PrintTime()

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
} // End of ClockSetNextState()

void EditCurrentClockPosition(int n)
{
  encoderPosition = 0;
  do{
    do
    {
      LCD.setCursor(n, 0);
      LCD.print(encoderPosition);
    } while(!ButtonNextState(digitalRead(ENCODER_PIN)));

    if (ButtonNextState(digitalRead(ENCODER_PIN)))
    {
      currentClock[n] = encoderPosition;
      LCD.setCursor(n, 0);
      LCD.print(encoderPosition);
    }
  } while (currentClock[n] == 0);
} // End of EditCurrentClockPosition()

void LCD_ClearBottomRow()
{
  LCD.setCursor(FIRST_COL, BOTTOM_ROW);
  LCD.print(CLEAR);
} // End of LCD_ClearBottomRow()

void LCD_ClearTopRow()
{
  LCD.setCursor(FIRST_COL, TOP_ROW);
  LCD.print(CLEAR);
} // End of LCD_ClearTopRow()

void LCD_PrintAngle(int angle)
{
  LCD_ClearBottomRow();
  LCD.setCursor(FIRST_COL, BOTTOM_ROW);
  LCD.print("Angle: ");
  LCD.print(angle);
  LCD.print(" deg.");
} // End of LCD_PrintAngle()

void Universal_PrintTime()
{
  Console_PrintTime();
  LCD_PrintTime();
} // End of Universal_PrintTime()

void Universal_PrintAngle(int angle)
{
  Console_PrintAngle(angle);
  LCD_PrintAngle(angle);
} // End of Universal_PrintAngle()

#endif
