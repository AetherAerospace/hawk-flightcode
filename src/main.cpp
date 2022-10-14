#include <Arduino.h>
#include "util/Comms.h"
#include "util/Serial.h"

void setup() {
  // force fastest speed
  setCpuFrequencyMhz(240);
  Serial.begin(115200);
  initLoRa();
}

void loop() {}
