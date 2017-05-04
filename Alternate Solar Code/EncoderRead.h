#ifndef EncoderRead_H
#define EncoderRead_H
// Variable for keeping track of encoder change.
volatile int EncoderValue = 0;
int EncAPin = 2, EncBPin = 3;
int EncA, EncB;
// Service Routine for Encoder channel A,
// active on channel A changing.
void PinA(void)
{
// Check the two inputs and then if not equal
if (digitalRead(EncBPin) != digitalRead(EncAPin))
{
EncoderValue++; // Increment the encoder.
}
else
{
EncoderValue--; // otherwise decrement
}
} // End of PinA
// Service Routine for Encoder channel B,
// active on channel B changing.
void PinB(void)
{
// Check the two inputs and then if equal
if (digitalRead(EncBPin) == digitalRead(EncAPin))
{
EncoderValue++; // Increment the encoder.
}
else
{
EncoderValue--;// otherwise decrement
}
} // End of PinB
// Setup interrupt services and pinModes for the Encoder lines.
void EncoderInitialize()
{
attachInterrupt(0, PinA, CHANGE); // ISR's
attachInterrupt(1, PinB, CHANGE);
pinMode(EncAPin, INPUT); // Pin Modes.
pinMode(EncBPin, INPUT);
}// End of EncoderInitialize
#endif