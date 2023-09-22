#include "proximity.h"

Proximity::Proximity(uint8_t signalPin, uint8_t metalOnLogicOne): signalPin(signalPin), metalOnLogicOne(metalOnLogicOne){}

void Proximity::init() const 
{
  pinMode(signalPin, INPUT);
}

uint8_t Proximity::detect() const
{
  return !(digitalRead(signalPin) ^ metalOnLogicOne);
}
