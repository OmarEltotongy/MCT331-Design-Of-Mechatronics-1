#include "ethernet.h"
#include <EtherCard.h>

static byte mymac[] = { 0x1A,0x2B,0x3C,0x4D,0x5E,0x6F };
static byte myip[] = { 192, 168, 1, 2 };
static byte gwip[] = { 192, 168, 1, 1 };
static byte mask[] = { 255, 255, 255, 0 };
static byte dstIp[] = { 192, 168, 1, 3 };

const int dstPort PROGMEM = 1234;
const int srcPort PROGMEM = 4321;

byte Ethernet::buffer[700];

void ETHERNET_init(void)
{
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
  {
    Serial.println("ETHERNET FAILED");
    return;
  }
    
  ether.staticSetup(myip, gwip, 0, mask);
}

void ETHERNET_send(const char* text)
{
  for(uint32_t i = 0; i < 2000; i++)
  {
    ether.sendUdp(text, sizeof(text), srcPort, dstIp, dstPort); 
  }
  
  Serial.println(text); 
} 
