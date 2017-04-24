#include <Servo.h>

#define PIN_TOTAL 0
#define PIN_PART 1
#define RATIO (5.5 / 1024.0)

unsigned int solarTimer;
float lightTotal, lightPart, voltsTotal, voltsPart, voltsDiff;

void AdjustSolar()
{
  if (voltsDiff > 0.5)
  {
    /*Move Servo CCW*/
  }
  else if (voltsDiff < 0.5)
  {
    /*Move Servo CW*/
  }
  else break;
}

void ReadSolar()
{
  lightTotal = digitalRead(PIN_TOTAL);
  lightPart = digitalRead(PIN_PART);

  voltsTotal = lightTotal * RATIO;
  voltsPart = lightPart * RATIO;

  voltsDiff = (voltsTotal - voltsPart);
}

void SolarSetup()
{
  pinMode(PIN_TOTAL, INPUT);
  pinMode(PIN_PART, INPUT};
  solarTimer = millis();
}
