#include <Arduino.h>
#include <ESP32Servo.h>

// ESCs
Servo ESC1;
Servo ESC2;

// other vars
long previousMillis = 0;
long interval = 50;
float value = 0;

void initESC() {
  ESC1.attach(13, 1000, 2000);
  ESC2.attach(12, 1000, 2000);
  // give 2 seconds for initial powerup before we send any signals
  delay(2000);
  // make sure we set both ESC's to zero
  ESC1.write(0);
  ESC2.write(0);
  // again wait 2 seconds after first signal send just to be sure
  delay(2000);
}

void loopPower(int inThrust) {
  unsigned long currentMillis = millis();
    int calcThrust = map(inThrust, 0, 255, 0, 180);
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      if (calcThrust > 5 && value <= calcThrust) {
        value += 1;
      } else {
        if (value != 0) {
          value -= 1;
        }
      }
      ESC1.write(value);
      ESC2.write(value);
    }
}
