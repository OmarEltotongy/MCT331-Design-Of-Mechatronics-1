#ifndef ETHERNET_H
#define ETHERNET_H

#include <Arduino.h>

void ETHERNET_init(void);
void ETHERNET_send(const char* text);

#endif