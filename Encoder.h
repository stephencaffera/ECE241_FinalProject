#ifndef ARDUINO_ENCODER_H
#define ARDUINO_ENCODER_H

#include <LiquidCrystal.h>

LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8);

enum ButtonState {Idle, Wait, Low};
ButtonState State = Idle;

int encoderPosition = 0;
int encoderCount = 0;
unsigned long timer;
unsigned long ButtonTime;
int PressCount = 0;

boolean ButtonNextState(int Input)
{
  switch(State)
  {
    case Idle:
      if(Input == LOW)
      {
        ButtonTime = millis();
        State = Wait;
      }
      break;
    case Wait:
      if(Input == HIGH)
      {
        State = Idle;
      }
      else if(millis() - ButtonTime >= 5)
      {
        State = Low;
        return true;
      }
      break;
    case Low:
      if(Input == HIGH)
      {
        State = Idle;
      }
      break;
  }
  return false;
}

void MonitorA()
{
  if(digitalRead(2) == digitalRead(3))
  {
    encoderPosition++;
  }
  else
  {
    encoderPosition--;
  }
}

void MonitorB()
{
  if(digitalRead(2) == digitalRead(3))
  {
    encoderPosition--;
  }
  else
  {
    encoderPosition++;
  }
}

void LCD_DisplayPressCount() 
{
  if(ButtonNextState(digitalRead(4)))
  {
    PressCount++;
    LcdDriver.clear();
    LcdDriver.setCursor(0,0);
    LcdDriver.print(PressCount);
  }
}

void LCD_DisplayEncoderPosition()
{
  if(millis() - timer >= 100)
  {
    encoderCount = encoderPosition / 4;
    LcdDriver.setCursor(0, 0);
    LcdDriver.print(encoderCount);
    timer += 100;
  }
}

void LCD_DisplayEncoderPosition(int col)
{
  if(millis() - timer >= 100)
  {
    LcdDriver.setCursor(col, 0);
    LcdDriver.print(encoderPosition);
    timer += 100;
  }
}

void EncoderSetup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), MonitorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), MonitorB, CHANGE);
  timer = millis();
}

#endif
