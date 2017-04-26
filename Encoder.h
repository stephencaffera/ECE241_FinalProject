#ifndef ENCODER_H
#define ENCODER_H

enum ButtonState {Idle, Wait, Low};

ButtonState State = Idle;
int encoderPosition = 0;
unsigned long timer, buttonTime;

boolean ButtonNextState(int Input)
{
  switch(State)
  {
    case Idle:
      if(Input == LOW)
      {
        buttonTime = millis();
        State = Wait;
      }
      break;
    case Wait:
      if(Input == HIGH)
      {
        State = Idle;
      }
      else if(millis() - buttonTime >= 5)
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
