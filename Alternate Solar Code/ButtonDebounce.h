#ifndef ButtonDebounce_H
#define ButtonDebounce_H
// Set up pin and button state.
int ButtonPin = 4, buttonState = 0;
unsigned long buttonTimer;
// Initialization code, setting up pin.
void ButtonInitialize()
{
pinMode(ButtonPin, INPUT);
} // End of ButtonInitialize
// Function called in loop to check for button release.
// Returns a 1 on the buttons release.
int ButtonRead()
{
// Read in the buttons current value.
int Press = digitalRead(ButtonPin);
int ReturnValue = 0;
switch (buttonState)
{
case 0: // if we are waiting for a press,
if (Press == LOW)
{
// Once press occurs
buttonTimer = millis(); // record time
buttonState = 1; // and move to next state
}
break;
case 1: // button just went low
if (Press == HIGH) // and now goes high
{
buttonState = 0; // return to 0 state.
}
else // if still low
{
// and sufficient time has passed.
if (millis() - buttonTimer >= 10)
{
buttonState = 2; // move on to state two
}
}
break;
case 2:
if (Press == HIGH)
{
ReturnValue = 1; // Return 1 indicating release.
buttonState = 0;
} // End of high test.
break;
} // End of switch on buttonState
return ReturnValue;
} // End of ButtonRead
#endif