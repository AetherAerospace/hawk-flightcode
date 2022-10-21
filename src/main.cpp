/*
  main file
  folder structure explained below

  src/
  ├─ main.cpp
  ├─ settings/
  │  ├─ header files with settings for other code modules
  ├─ pin/
  │  ├─ contains header files with pin definitions
  ├─ proc/
  │  ├─ contains the more code heavy processing stuff and modules
  ├─ util/
  │  ├─ general use modules and code
*/

#include <Arduino.h>
#include "util/Comms.h"
#include "util/Serial.h"

void setup() {
  // force fastest speed
  setCpuFrequencyMhz(240);
  // start serial
  Serial.begin(115200);
  // start LoRa Link
  initLoRa();
}

void loop() {
  delay(5000);
  handleLoRa();
  sendLoRa("Hello World");
}
