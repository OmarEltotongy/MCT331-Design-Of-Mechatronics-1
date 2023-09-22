#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

typedef enum{
  STEPPER_CW, STEPPER_CCW
}StepperDirection;

class StepperMotor{
private:

  uint8_t directionPin;
  uint8_t stepPin;
  
public:

  StepperMotor(uint8_t directionPin, uint8_t stepPin);
  void init(void) const;
  void step(uint16_t usDelay, StepperDirection direction) const;
  void makeSteps(int32_t steps, uint16_t usDelay, StepperDirection direction) const;
  
};

#endif
