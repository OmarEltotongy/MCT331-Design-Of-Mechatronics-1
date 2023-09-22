#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

#include <Arduino.h>
#include "digital_sensor.h"

#define BTN_PRESSED     1
#define BTN_RELEASED    0

class LimitSwitch: public DigitalSensor{
private:

  uint8_t signalPin;
  uint8_t pullUpEnabled;
  
public:

  LimitSwitch(uint8_t signalPin, uint8_t pullUpEnabled=true);
  virtual void init(void) const override;
  virtual uint8_t detect(void) const override;
  
};

#endif
