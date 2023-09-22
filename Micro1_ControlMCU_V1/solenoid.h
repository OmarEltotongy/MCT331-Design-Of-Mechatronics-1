#ifndef SOLENOID_H
#define SOLENOID_H

#include <Arduino.h>

#define SOLENOID_PULSE_DELAY  100

class Solenoid{
private:

  uint8_t signalPin;

public:

  Solenoid(uint8_t signalPin);
  void init(void) const;
  void sendPulse(uint16_t msDelay) const;   

};

#endif