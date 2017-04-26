#ifndef SOLAR_H
#define SOLAR_H

#include <Servo.h>

#define PIN_TOTAL 0
#define PIN_PART 1
#define RATIO (5.5 / 1024.0)

Servo Solar;
unsigned int solarTimer;
int solarAngle;

void AdjustSolar(float diff)
{
  if (diff > 0.5)
  {
    solarAngle = --Solar.read();
    Solar.write(solarAngle);
  }
  else if (diff < 0.5)
  {
    solarAngle = ++Solar.read();
    Solar.write(solarAngle);
  }
  else break;
}

float ReadSolar()
{
  float lightTotal = digitalRead(PIN_TOTAL);
  float lightPart = digitalRead(PIN_PART);

  float voltsTotal = lightTotal * RATIO;
  float voltsPart = lightPart * RATIO;

  float voltsDiff = (voltsTotal - voltsPart);

  return voltsDiff;
}

void SolarSetup()
{
  pinMode(PIN_TOTAL, INPUT);
  pinMode(PIN_PART, INPUT};
  solarTimer = millis();
}

#endif
