#ifndef DIGITAL_SENSOR_H
#define DIGITAL_SENSOR_H

#include <Arduino.h>

class DigitalSensor{
public:

  virtual void init(void) const = 0;
  virtual uint8_t detect(void) const = 0;
  
};

#endif
