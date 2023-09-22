#include "ir.h"

Infrared::Infrared(uint8_t signalPin, uint8_t negativeLogic): signalPin(signalPin), negativeLogic(negativeLogic){}

void Infrared::init(void) const
{
  pinMode(signalPin, INPUT); 
}

uint8_t Infrared::detect(void) const
{
  return digitalRead(signalPin) ^ negativeLogic;
}
