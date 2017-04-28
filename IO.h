#ifndef IO_H
#define IO_H

#include <LiquidCrystal.h>
#include <stdio.h> //Add formatted printing using sprintf()

#define BAUD_RATE 9600
#define TOP_ROW 0
#define BOTTOM_ROW 1
#define FIRST_COL 0
#define CLEAR "                "

extern int hours, minutes, seconds;

LiquidCrystal LCD(11, 9, 5, 6, 7, 8);

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
