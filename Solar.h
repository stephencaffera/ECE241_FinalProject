/**
* < Written by Stephen Caffera & Iris LoCoco >
* < ECE 241, Spring 2017 >
* < Final Project: Solar Tracker>
*
* < Solar.h: header file control and operation of the Servo motor >
*/

#ifndef SOLAR_H
#define SOLAR_H

#include <Servo.h>
#include <float.h>

// Global declaration of constants used in this header file
#define ANGLE_TO_MINUTE_RATIO 0.25
#define DIVIDE_IN_HALF(X) (X / 2)
#define FLT_DIG 1
#define INSUFFICIENT_VOLTAGE 4.0
#define MAX_ANGLE 180
#define MIN_ANGLE 0
#define MINUTES_IN_AN_HOUR 60
#define PIN_PART 1
#define PIN_TOTAL 0
#define SOLAR_PIN 10
#define START_ANGLE 0
#define VOLT_CONVERSION_RATIO (5.0 / 1024.0)
#define VOLT_THRESHOLD 0

// Global variable and object declarations:
  Servo Solar;

  unsigned long solarTimer;
  int solarAngle;
  float voltsTotal;

  extern int hours, minutes, seconds;

// Function prototypes and external function declarations:
  void AdjustSolar(float);
  float ReadSolar(void);
  void SetSolarAngleFromTime(void);
  void SolarSetup(void);

  extern void Universal_PrintAngle(int angle);

/**
* AdjustSolar:
* A function that determines the balance between the two
* photoreactors, and adjust's the angle of the disc attached to the Servo
* motor based on the voltages.
* 
* @params: float diff. Represents the different in voltage between the two
  photoreactors as a floating point. No return value; adjusts global variables.
  @return: void
*/
void AdjustSolar(float diff)
{
  if (voltsTotal < INSUFFICIENT_VOLTAGE)
  {
    solarAngle = Solar.read();

    if (diff < VOLT_THRESHOLD) if (solarAngle > MIN_ANGLE) Solar.write(--solarAngle);
    else if (diff > VOLT_THRESHOLD) if (solarAngle < MAX_ANGLE) Solar.write(++solarAngle);

    Universal_PrintAngle(solarAngle);
  }
  else SetSolarAngleFromTime();
} // End of AdjustSolar()

/**
* ReadSolar:
* A function that reads in the voltages from the two photoreactors connected to
* two of the Arduino's pins, represented by globally-defined constants. The function
* also uses constants to calculate the partial and total voltages and store them as
* floating point values.
* 
* @params: void
* @return: voltsDiff. A float representing the difference in voltage between the two photoreactors.
*/
float ReadSolar()
{
  float lightTotal = digitalRead(PIN_TOTAL);
  float lightPart = digitalRead(PIN_PART);

  voltsTotal = lightTotal * VOLT_CONVERSION_RATIO;
  float voltsPart = lightPart * VOLT_CONVERSION_RATIO;

  float voltsDiff = (DIVIDE_IN_HALF(voltsTotal) - voltsPart);

  return voltsDiff;
} // End of ReadSolar()

/**
* SetSolarAngleFromTime:
* A function that determines the angle the disc needs to rotate to based upon
* the time of day according to the clock. If the time is before 06:00 or after
* 18:00, then the solar angle will be set to 0 in anticipation of the "sunrise".
* If not, then the solar disc angle will be determined by the time of day
* 
* @params: void
* @return: void
*/
void SetSolarAngleFromTime()
{
  (hours < 6 || (hours >= 18 && minutes > 0)) ? solarAngle = START_ANGLE : solarAngle = ((ANGLE_TO_MINUTE_RATIO * minutes) + (ANGLE_TO_MINUTE_RATIO * MINUTES_IN_AN_HOUR * hours));
} // End of SetSolarAngleFromTime()

/**
* SolarSetup:
* A setup function that attaches the servo motor to it's associted pin, represented
* as a global, SOLAR_PIN. It also attached the pins on the Arduino needed to receive
* inputs from the two photoreactors on the solar disc, attached to the pins
* represented by PIN_TOTAL and PIN_PART. It also initializes the solarTimer.
* 
* @params: void
* @return: void
*/
void SolarSetup()
{
  Solar.attach(SOLAR_PIN);
  pinMode(PIN_TOTAL, INPUT);
  pinMode(PIN_PART, INPUT);
  solarTimer = millis();
} // End of SolarSetup()

#endif
