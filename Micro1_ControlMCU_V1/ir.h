#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include "digital_sensor.h"

#define IR_DETECTS_OBJECT    1
#define IR_UNDETECTS_OBJECT  0

class Infrared: public DigitalSensor{
private:

  uint8_t signalPin;
  uint8_t negativeLogic;
  
public:

  Infrared(uint8_t signalPin, uint8_t negativeLogic=false);
  virtual void init(void) const override;
  virtual uint8_t detect(void) const override;
  
};

#endif
