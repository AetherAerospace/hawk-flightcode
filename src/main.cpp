/*
  main file
  folder structure explained below

  src/
  ├─ main.cpp
  ├─ settings/
  │  ├─ header files with settings for other code modules
  ├─ proc/
  │  ├─ contains the more code heavy processing stuff and modules
  ├─ util/
  │  ├─ general use modules and code
*/

#include <Arduino.h>
#include "util/LoRa.h"
#include "util/Serial.h"
#include "proc/Power.h"
#include "proc/Servo.h"
#include "proc/lTRX.h"
#include "proc/pidKal.h"

void setup() {
  // force fastest speed
  setCpuFrequencyMhz(240);
  // start serial
  Serial.begin(115200);
  // start LoRa Link
  initLoRa();
  // speed controllers
  initESC();
  // axis servos
  initServo();
}

void loop() {
  // power handling
  powerctl(getButtons(0));
  // servo handling
  servoctl(getControls(0), getControls(1), getControls(2));
  // LoRa control loop
  lTRXctl();
}
