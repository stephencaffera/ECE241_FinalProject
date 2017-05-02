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

// Definition of global file constants
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

  ClockStates clockState;
  int currentClock[ARRAY_LENGTH], newTime[3], CurrentClockIndex;

  extern int hours, minutes, seconds;
  extern boolean clockSet;

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

/**
* Console_PrintTime:
* Console_PrintTime functions prints the current time to the serial monitor. the
* function uses the print statement, and does not pass any time information as a
* variable.
*
* @params: void
* @return: void
*/
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

/**
* Console_PrintAngle:
* Console_PrintAngle prints the current angle of origin/orientation of the
* light source/solar disc. This information is printed directly to the Serial
* monitor, without passing any variables.
*
* @params: int angle, the current angle of the light source/disc
* @return: void
*/
void Console_PrintAngle(int angle)
{
  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.println(" deg.\n");
} //End of Console_PrintAngle()

/**
* Console_SetTime:
* Console_SetTime function is in charge of prompting the user to input the hours,
* minutes, and seconds, and accepting input for each of the associated variables
* through the serial input monitor. Nothing is passed as a variable, and all
* information is printed directly with the print function.
*
* @params: void
* @return: void
*/
void Console_SetTime()
{
  do
  {
    Serial.print("Enter new hours: ");
      newTime[0] = Serial.read(); // stores the hours at index 0 of the newTime array
  } while (newTime[0] < 0 && newTime[0] > 23);

  do
  {
    Serial.print("Enter new minutes: ");
      newTime[1] = Serial.read(); // stores the minutes at index 1 of the newTime array
  } while (newTime[1] < 0 && newTime[1] > 59);

  do
  {
    Serial.print("Enter new seconds: ");
      newTime[2] = Serial.read(); // stores the seconds at index 2 of the newTime array
  } while (newTime[2] < 0 && newTime[2] > 59);

  Serial.print("Changing time to ");
  Console_PrintTime();
  Serial.print("Confirm (Y/N): ");

  do
  {
    if (Serial.read() == 'Y' || Serial.read() == 'y')
    {
      clockSet = false;
      hours = newTime[0];
      minutes = newTime[1];
      seconds = newTime[2];
      clockSet = true;
    }
  } while (Serial.read() != 'Y' && Serial.read() != 'y' && Serial.read() != 'N' && Serial.read() != 'n');
} // End of Console_SetTime()

/**
* Console_TimeChangeRequested:
* Console_TimeChangeRequested is a function that reads in a character from the
* serial input monitor, and determines whether or not the user intended to
* change the set the clock by whether the inputted character is equal to the character
* 'S' or 's'. This characer is not passed as a variable, but rather detected within
* the function itself.
*
* @params: void
* @return: boolean, returns true for setting the clock, and false for not.
*/
boolean Console_TimeChangeRequested()
{
  (Serial.read() == 'S' || Serial.read() == 's') ? true : false;
} // End of Console_TimeChangeRequested()

/**
* IO_Setup:
* IO_Setup is a function that sets the baud rate based on the global file constants
* defined at the top, clears the LCD monitor completely, and initializes the
* clock state machine to set the hours place of the clock.
*
* @params: void
* @return: void
*/
void IO_Setup()
{
  Serial.begin(BAUD_RATE);
  LCD.clear();
  clockState = CLOCK_SET_HOURS;
} // End of IO_Setup

/**
* LCD_PrintTime:
* LCD_PrintTime is a function that first clears the top row of the LCD monitor
* by calling a function, LCD_ClearTopRow, that prints 16 spaces, then uses a
* series of "if" statements to determine if hours, minutes, and seconds require
* preceeding zeroes to be printed. The total output will be the current time.
*
* @params: void
* @return: void
*/
void LCD_PrintTime()
{
  LCD_ClearTopRow(); // prints 16 spaces to clear the top row of the screen

  if (hours < 10) LCD.print("0");

  LCD.print(hours);
  LCD.print(":");

  if (minutes < 10) LCD.print("0");

  LCD.print(minutes);
  LCD.print(":");

  if (seconds < 10) LCD.print("0");

  LCD.print(seconds);
} // End of LCD_PrintTime()

/**
* ClockSetNextState:
* ClockSetNextState is a function that controls a state machine for setting the
* clock via LCD monitor. Inside the IO_Setup function, the enumerated variable clockState
* is initialized to CLOCK_SET_HOURS, which will trigger a switch statement to move through
* the hours, minutes, and second variables until each has been set via the function
* EditCurrentClockPosition. Each digit of the each time variable in stored in a separate
* array index, and converted later with the ConcatenateArrays function. At the end of the
* switch statement, a boolean flag variable, clockSet, is set to true.
*
* @params: void
* @return: void
*/
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

/**
* EditCurrentClockPosition:
* EditCurrentClockPosition is a function that accepts a digit from the encoder,
* and saved it to the currentClock array if the user presses the encoder ButtonNextState
* to confirm the digit selection. This function should only be called internally,
* from the state machine. It accepts a single variable, and integer representing
* the array index, and returns nothing
*
* @params: int n, an integer representing the current array index, passed from state machine
* @return: void
*/
void EditCurrentClockPosition(int n)
{
  encoderPosition = 0;
  do{
    do
    {
      LCD.setCursor(n, 0);
      LCD.print(encoderPosition);
    } while (!ButtonNextState(digitalRead(ENCODER_PIN)));

    if (ButtonNextState(digitalRead(ENCODER_PIN)))
    {
      currentClock[n] = encoderPosition;
      LCD.setCursor(n, 0);
      LCD.print(encoderPosition);
    }
  } while (currentClock[n] == 0);
} // End of EditCurrentClockPosition()

/**
* LCD_ClearBottomRow:
* LCD_ClearBottomRow sets the cursor to the starting position, and clears the
* bottom row of text.
*
* @params: void
* @return: void
*/
void LCD_ClearBottomRow()
{
  LCD.setCursor(FIRST_COL, BOTTOM_ROW);
  LCD.print(CLEAR);
} // End of LCD_ClearBottomRow()

/**
* LCD_ClearTopRow:
* LCD_ClearTopRow sets the cursor to the starting position, and clears the
* top row of text.
*
* @params: void
* @return: void
*/
void LCD_ClearTopRow()
{
  LCD.setCursor(FIRST_COL, TOP_ROW);
  LCD.print(CLEAR);
} // End of LCD_ClearTopRow()

/**
* LCD_PrintAngle:
* LCD_PrintAngle is a function that outputs the current angle of the solar disc/
* light source to the LCD monitor. First, the LCD_ClearBottomRow function is called,
* and then the cursor is set in position to print the angle degree, which is passed in as an int.
*
* @params: int angle, the angle of the light source/solar disc as an integer value
* @return: void
*/
void LCD_PrintAngle(int angle)
{
  LCD_ClearBottomRow();
  LCD.setCursor(FIRST_COL, BOTTOM_ROW);
  LCD.print("Angle: ");
  LCD.print(angle);
  LCD.print(" deg.");
} // End of LCD_PrintAngle()

/**
* Universal_PrintTime:
* Universal_PrintTime is a function that calls two other functions from IO,
* Console_PrintTime and LCD_PrintTime, enabling the current time to be output
* to both screens at the same time.
*
* @params: void
* @return: void
*/
void Universal_PrintTime()
{
  Console_PrintTime();
  LCD_PrintTime();
} // End of Universal_PrintTime()

/**
* Universal_PrintAngle:
* Universal_PrintAngle is a function that calls two other function from IO,
* Console_PrintAngle and LCD_PrintAngle, enabling the current solar disc/light
* source angle to be output to both screens at the same time.
*
* @params: int angle, the solar disc/light source angle represented as an integer
* @return: void
*/
void Universal_PrintAngle(int angle)
{
  Console_PrintAngle(angle);
  LCD_PrintAngle(angle);
} // End of Universal_PrintAngle()

#endif
