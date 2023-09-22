#include "control_mcu_rtos.h"

void setup() {
  Serial.begin(9600);
  RTOS_init();
}

void loop() {
}
