#include "Arduino.h"
#include "solenoid.h"

Solenoid::Solenoid(uint8_t signalPin): signalPin(signalPin){}

void Solenoid::init(void) const
{
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, HIGH);
}

void Solenoid::sendPulse(uint16_t msDelay) const
{
  digitalWrite(signalPin, LOW);
  delay(msDelay);
  digitalWrite(signalPin, HIGH);    
}