#include "digital_sensor.h"
#include <Arduino.h>

#define PROXIMITY_READS_METAL        1
#define PROXIMITY_READS_NOT_METAL    0

class Proximity: public DigitalSensor{
private:

  uint8_t signalPin;
  uint8_t metalOnLogicOne;

public:

  Proximity(uint8_t signalPin, uint8_t metalOnLogicOne=true);
  virtual void init(void) const override;
  virtual uint8_t detect(void) const override;

};