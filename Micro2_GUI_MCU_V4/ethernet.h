#ifndef ETHERNET_H
#define ETHERNET_H

#include <Arduino.h>
#include <EtherCard.h>
#include <IPAddress.h>

uint8_t ETHERNET_init(void);
void ETHERNET_setRecCallBack(void(*ptr)(void));
void ETHERNET_waitForRec();

#endif