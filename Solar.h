#ifndef SOLAR_H
#define SOLAR_H

#include <Servo.h>
#include <float.h>

#define FLT_DIG 1
#define SOLAR_PIN 3
#define PIN_TOTAL 0
#define PIN_PART 1
#define RATIO (5.0 / 1024.0)

extern void Universal_PrintAngle(int angle);

Servo Solar;
unsigned long solarTimer;
int solarAngle;

void AdjustSolar(float diff)
{
  solarAngle = Solar.read();
  Universal_PrintAngle(solarAngle);
  
  if (diff > 0.5)
  {
    Solar.write(--solarAngle);
  }
  else if (diff < 0.5)
  {
    Solar.write(++solarAngle);
  }
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
  Solar.attach(SOLAR_PIN);
  pinMode(PIN_TOTAL, INPUT);
  pinMode(PIN_PART, INPUT);
  solarTimer = millis();
}

#endif
