#include "ethernet.h"

static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192, 168, 1, 3 };
static byte gwip[] = { 192, 168, 1, 1 };
static byte mask[] = { 255, 255, 255, 0 };


byte Ethernet::buffer[50];

uint8_t ETHERNET_init(void)
{
  // Begin Ethernet communication
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
  {
    return 0;
  }
  // Setup static IP address
  ether.staticSetup(myip, gwip, 0, mask);  
  return 1;
}

void ETHERNET_waitForRec()
{
  ether.packetLoop(ether.packetReceive());
}
