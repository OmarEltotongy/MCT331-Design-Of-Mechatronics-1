#include "suction_cup.h"

SuctionCup::SuctionCup(uint8_t signalPin, uint8_t suckOnOne): signalPin(signalPin), suckOnOne(suckOnOne){}

void SuctionCup::init() const
{
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, !suckOnOne);
}

void SuctionCup::suck() const
{
  digitalWrite(signalPin, suckOnOne);
}

void SuctionCup::unSuck() const
{
  digitalWrite(signalPin, !suckOnOne);
}