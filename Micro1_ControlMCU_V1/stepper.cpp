#include "stepper.h"

StepperMotor::StepperMotor(uint8_t directionPin, uint8_t stepPin) : directionPin(directionPin), stepPin(stepPin){}

void StepperMotor::init(void) const
{
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void StepperMotor::step(uint16_t usDelay, StepperDirection direction) const
{
  digitalWrite(directionPin, direction);

  digitalWrite(stepPin, HIGH);
  delayMicroseconds(usDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(usDelay);
  
}

void StepperMotor::makeSteps(int32_t steps, uint16_t usDelay, StepperDirection direction) const
{
  if(steps < 0)
  {
    if(STEPPER_CCW == direction)
    {
      direction = STEPPER_CW;
    }
    else
    {
      direction = STEPPER_CCW;
    }
    steps = abs(steps);
  }  
  for(uint32_t stepNum = 0; stepNum < steps; stepNum++)
  {
    step(usDelay, direction);        
  }    
}
