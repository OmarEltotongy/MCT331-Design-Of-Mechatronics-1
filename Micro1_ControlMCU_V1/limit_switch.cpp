#include "limit_switch.h"

LimitSwitch::LimitSwitch(uint8_t signalPin, uint8_t pullUpEnabled): signalPin(signalPin), pullUpEnabled(pullUpEnabled){}

void LimitSwitch::init(void) const
{
  if(pullUpEnabled)
  {
    pinMode(signalPin, INPUT_PULLUP);
  } 
  else
  {
    pinMode(signalPin, INPUT);
  }
}

uint8_t LimitSwitch::detect(void) const
{
  return digitalRead(signalPin) ^ pullUpEnabled;
}
