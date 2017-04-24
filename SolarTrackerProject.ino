/*
* Project by Stephen Caffera and Iris LoCoco
* ECE 241, Spring 2017
*/

#include <LiquidCrystal.h>
#include <Servo.h>
#include "Clock.h"
#include "Encoder.h"
#include "Solar.h"

#define BAUD 9600

extern unsigned int solarTimer;

void setup()
{
	Serial.begin(BAUD);
	EncoderSetup();
  SolarSetup();
	ClockSetup();
}

void loop()
{
  if (millis() - solarTimer > 0)
  {
    ReadSolar();
    AdjustSolar();
  }
  
	if (OneSecondPassed())
	{
		UpdateClock();
		Console_PrintTime();
		UpdateClockTimer();
	}

	if (Serial.available())
	{
		Console_SetTime(Serial.read());
	}

}
