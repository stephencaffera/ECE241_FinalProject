#include <Servo.h>

Servo SolarServo;
#include <LiquidCrystal.h>
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8);

//Set up clock.
#define LcdDisplay

#define TOTAL 0 // for pin 0
#define PART 1 // for pin 1

#include "ClockBasics.h"
unsigned long ClockTimer;
int tolerance = 100;

int SolarValue = 90; // variable for the solar angle, set to initial position 90 deg

#include "EncoderRead.h"

#include "ButtonDebounce.h"

void UpdateLCD()
{
  LcdDriver.clear();// Reset display
  LcdDriver.setCursor(0, 1);
  LcdDriver.print("Degree: "); // place Solar on first line
  LcdDriver.print(SolarValue);

  // Place cursor on line that is currently being changed.
  // Be sure cursor is on and blinking.
  LcdDriver.setCursor(1, 0);
  LcdClock();
} // End of UpdateLCD

// put your setup code here, to run once:
void setup() {

  // Set up Encoder
  EncoderInitialize();

  // Set up button
  ButtonInitialize();

  // Set up servos.
  SolarServo.attach(10);
  pinMode(TOTAL, INPUT);
  pinMode(PART, INPUT);
  SolarServo.write(SolarValue);

  // Set up software timers.
  ClockTimer = millis();

  // Set up lcd.
  LcdDriver.begin(16, 2);
  UpdateLCD();
  Serial.begin(9600);
}
// put your main code here, to run repeatedly:
void loop()
{
  int val1 = analogRead(TOTAL);
    Serial.println(val1);
  int val2 = analogRead(PART);
    Serial.println(val2);

  if ((abs(val2 - val1) <= tolerance)) 
  {
      //do nothing if the difference between values is within the tolerance limit
    } else {
      if (val1 > val2)
      {
        SolarValue = --SolarValue;
      }
      if (val1 < val2)
      {
        SolarValue = ++SolarValue;
      }
    }

    if (SolarValue > 180) {
      SolarValue = 180;  // reset to 180 if it goes higher
    }
    if (SolarValue < 0) {
      SolarValue = 0;  // reset to 0 if it goes lower
    }

    SolarServo.write(SolarValue);
    

  // Check for button press
  if (1 == ButtonRead())
  {
    // loop code here to set the clock?
  } // End of Button if

  if (millis() - ClockTimer >= 1000)
  {
    ClockTimer += 1000;

    // if clock is running, update the clock
    if (clockState == CLOCK_RUNNING)
    {
      UpdateClock();
      SendClock();
      UpdateLCD();
    // Then send data out...
    }
  } // End of ClockTimer if
  
  // Check for incoming data
  if (Serial.available())
  {
    // Use character to set clock.
    SettingClock(Serial.read());
  } // End of Serial input handling
  // Check for update from encoder.

  SolarServo.write(SolarValue);
  UpdateLCD(); // update display reflecting change of axes.
}
