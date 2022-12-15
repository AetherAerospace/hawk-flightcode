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
#include "util/LoRa.h"
#include "util/Serial.h"
#include "util/Power.h"
#include "proc/lTRX.h"

void setup() {
  // force fastest speed
  setCpuFrequencyMhz(240);
  // start serial
  Serial.begin(115200);
  // start LoRa Link
  initLoRa();
  // speed controllers
  initESC();
}

void loop() {
  // power handling
  loopPower(fetchButtons(0));
  // LoRa control loop
  lTRXctl();
}
