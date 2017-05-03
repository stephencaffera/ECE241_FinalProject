/**
* < Written by Stephen Caffera & Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker>
*
* < Encoder.h: header file for encoder control >
*/

// Global constant definitions
#ifndef ENCODER_H
#define ENCODER_H

#define INTERRUPT_A 2
#define INTERRUPT_B 3
#define PRESS_ERROR_INTERVAL 5
#define PRESS_READ 4

enum ButtonState {Idle, Wait, Low}; //Enumerator for the button state

//Global variable declarations:
  ButtonState state = Idle;
  int encoderPosition = 0;
  unsigned long timer, buttonTime;

//Function prototypes:
  boolean ButtonNextState(int);
  void MonitorA(void);
  void MonitorB(void);
  void EncoderSetup(void);

/**
* ButtonNextState:
* This function determines whether or not the encoder button has been pressed,
* and debounces the switch so that actual button presses are properly registered.
*
* @params: int input. This represents the input, either high or low, from the switch
* @return: boolean. Will return true is the button has been pressed, and false
*          if it has not actually been pressed.
*/
boolean ButtonNextState(int input) // Passes the input (high or low) as an int
{
  switch(state)
  {
    case Idle:
      if(input == LOW)
      {
        buttonTime = millis(), 
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
} // End of ButtonNextState()

/**
* EncoderSetup:
* This function sets up the interrupts attached the encoder toggle, and the encoder button,
* as well as defining the input pins for each of these functions on the Arduino. It also
* initializes the timer. This is a setup function only, to be called once.
*
* @params: void
* @return: void
*/
void EncoderSetup()
{
  pinMode(INTERRUPT_A, INPUT);
  pinMode(INTERRUPT_B, INPUT);
  pinMode(PRESS_READ, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_A), MonitorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_B), MonitorB, CHANGE);
  timer = millis();
} // End of EncoderSetup()

/**
* MonitorA:
* MonitorA is a function that controls the incrementation of the encoder position
* when the knob is turned in one direction (opposite of MonitorB function below).
* To determine the value of encoderPosition, we check the interrupts defined in the
* encoder setup function and see if the inputs are the same.
*
* @params: void
* @return: void
*/
void MonitorA()
{
  if(digitalRead(INTERRUPT_A) == digitalRead(INTERRUPT_B)) encoderPosition++;
  else encoderPosition--;
} // End of MonitorA()

/**
* MonitorB:
* MonitorB is a function that controls the incrementation of the encoder position
* when the knob is turned in one direction (opposite of MonitorA function above).
* To determine the value of encoderPosition, we check the interrupts defined in the
* encoder setup function and see if the inputs are the same.
*
* @params: void
* @return: void
*/
void MonitorB()
{
  if(digitalRead(INTERRUPT_A) == digitalRead(INTERRUPT_B)) encoderPosition--;
  else encoderPosition++;
} // End of MonitorB()

#endif
