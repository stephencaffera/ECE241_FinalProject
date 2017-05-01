/**
* < Written by Stephen Caffera & Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker>
*
* < Encoder.h: header file for encoder control >
*/

#ifndef ENCODER_H
#define ENCODER_H

// Macros to define pin numbers and the error time for the encoder presses
#define INTERRUPT_A 2
#define INTERRUPT_B 3
#define PRESS_READ 4
#define PRESS_ERROR_INTERVAL 5

enum ButtonState {Idle, Wait, Low}; //Enumerator for the button state

ButtonState state = Idle; // initialize the state to idle
int encoderPosition = 0;
unsigned long timer, buttonTime;

pinMode(INTERRUPT_A, INPUT);
pinMode(INTERRUPT_B, INPUT);
pinMode(PRESS_READ, INPUT);
attachInterrupt(digitalPinToInterrupt(INTERRUPT_A), MonitorA, CHANGE);
attachInterrupt(digitalPinToInterrupt(INTERRUPT_B), MonitorB, CHANGE);
Serial.begin(9600);

boolean ButtonNextState(int input) // passes the input (high or low) as an int
{
  switch(state)
  {
    case Idle:
      if(input == LOW)
      {
        buttonTime = millis();
        state = Wait;
      }
      break;
      
    case Wait:
      if(input == HIGH) state = Idle;
      else if(millis() - buttonTime >= PRESS_ERROR_INTERVAL)
      {
        state = Low;
        return true;
      }
      break;
      
    case Low:
      if(input == HIGH) state = Idle;
      break;
  }
  return false;
}

void EncoderSetup()
{
  timer = millis();
}

int GetPress()
{
  return digitalRead(PRESS_READ);
}

void MonitorA()
{
  if(digitalRead(INTERRUPT_A) == digitalRead(INTERRUPT_B))
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
  if(digitalRead(INTERRUPT_A) == digitalRead(INTERRUPT_B))
  {
    encoderPosition--;
  }
  else
  {
    encoderPosition++;
  }
}

#endif
