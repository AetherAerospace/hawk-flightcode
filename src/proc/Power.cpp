#include <Arduino.h>
#include <ESP32Servo.h>
#include "Power.h"
#include "settings/escSet.h"

// ESCs
Servo ESC1;
Servo ESC2;

// other vars
long previousMillis = 0;
long interval = 50;
float value = 0;

void initESC() {
	ESC1.attach(ESC_1, 1000, 2000);
	ESC2.attach(ESC_2, 1000, 2000);
	// give a second for initial
	delay(1000);
	// make sure we set both ESC's to zero
	ESC1.write(0);
	ESC2.write(0);
	// wait a second after
	delay(1000);
}

// look at throttle and keep up to date
void powerctl(int inThrust) {
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
