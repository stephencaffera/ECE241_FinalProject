/*
* Written by Stephen Caffera and Iris LoCoco
* Solar Tracker Final Project
* ECE 241, Spring 2017
*/

#include "Clock.h"
#include "Encoder.h"
#include "IO.h"
#include "Solar.h"

extern unsigned int solarTimer;

void setup()
{
  IO_Setup();
	EncoderSetup();
  SolarSetup();
	ClockSetup();
}

void loop()
{
  if (millis() > solarTimer)
  {
    AdjustSolar(ReadSolar());
  }
  
	if (OneSecondPassed())
	{
    UpdateClockTimer();
		UpdateClock();
		Console_PrintTime();
	}

	if (Serial.available()) SetTime(Serial.read());
}
