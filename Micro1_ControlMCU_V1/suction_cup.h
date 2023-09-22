#ifndef SUCTION_CUP_H
#define SUCTION_CUP_H

#include <Arduino.h>

class SuctionCup
{
private:

  uint8_t signalPin;
  uint8_t suckOnOne;

public:

  SuctionCup(uint8_t signalPin, uint8_t suckOnOne=true);
  void init(void) const;
  void suck(void) const;
  void unSuck(void) const;

};

#endif