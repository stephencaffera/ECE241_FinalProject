#ifndef SOLAR_H
#define SOLAR_H

#include <Servo.h>
#include <float.h>

#define FLT_DIG 1
#define SOLAR_PIN 3
#define PIN_TOTAL 0
#define PIN_PART 1
#define START_ANGLE 0
#define VOLTAGE_MIDPOINT 0.5
#define VOLT_CONVERSION_RATIO (5.0 / 1024.0)
#define ANGLE_TO_MINUTE_RATIO 0.25
#define MINUTES_IN_AN_HOUR 60

extern void Universal_PrintAngle(int angle);

Servo Solar;
unsigned long solarTimer;
int solarAngle;

void AdjustSolar(float diff)
{
  solarAngle = Solar.read();
  Universal_PrintAngle(solarAngle);
  
  if (diff > VOLTAGE_MIDPOINT) Solar.write(--solarAngle);
  else if (diff < VOLTAGE_MIDPOINT) Solar.write(++solarAngle);
}

float ReadSolar()
{
  float lightTotal = digitalRead(PIN_TOTAL);
  float lightPart = digitalRead(PIN_PART);

  float voltsTotal = lightTotal * VOLT_CONVERSION_RATIO;
  float voltsPart = lightPart * VOLT_CONVERSION_RATIO;

  float voltsDiff = (voltsTotal - voltsPart);

  return voltsDiff;
}

void SolarSetup()
{
  Solar.attach(SOLAR_PIN);
  pinMode(PIN_TOTAL, INPUT);
  pinMode(PIN_PART, INPUT);
  solarTimer = millis();
}

void SetSolarAngleFromTime(int hours, int minutes, int seconds)
{
  if (hours < 6 || (hours > 18 && minutes > 0)) ? solarAngle = START_ANGLE : solarAngle = ((ANGLE_TO_MINUTE_RATIO * minutes) + (ANGLE_TO_MINUTE_RATIO * MINUTES_IN_AN_HOUR * hours));
}

#endif
