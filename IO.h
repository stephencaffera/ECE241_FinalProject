#ifndef IO_H
#define IO_H

#include <LiquidCrystal.h>

#define BAUD_RATE 9600


LiquidCrystal LCD(11, 9, 5, 6, 7, 8);

void Console_PrintTime(int hours, int minutes, int seconds)
{
  if (hours < 10) Serial.print("0"); 
  
  Serial.print(hours); 
  Serial.print(":");

  if (minutes < 10) Serial.print("0"); 
  
  Serial.print(minutes);
  Serial.print(":");

  if (seconds < 10) Serial.print("0");
  
  Serial.println(seconds);
} 

void IO_Setup()
{
  Serial.begin(BAUD_RATE);
}

void LCD_PrintTime(int hours, int minutes, int seconds)
{
  LCD.print("                ");
  
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

void LCD_ClearRow(int row)
{
  LCD.setCursor(0, row);
  LCD.print("                ");
}

void LCD_DisplayAngle(int row, int angle)
{
  LCD_ClearRow(row);
  LCD.setCursor(0, row);
  LCD.print(angle);
}

void Universal_PrintTime()
{
  Console_PrintTime();
  LCD_PrintTime();
}

void Universal_PrintAngle(int angle)
{
  Console_PrintAngle();
  LCD_PrintTime();
}

#endif
