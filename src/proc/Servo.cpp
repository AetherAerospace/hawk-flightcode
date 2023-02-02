#include <Arduino.h>
#include <ESP32Servo.h>
#include "Servo.h"
#include "settings/servoSet.h"

// define for each axis
Servo srvAil;
Servo srvElv;
Servo srvRud;

// initialize all servos
void initServo() {
	// correct pins
	srvAil.attach(SERVO_AIL, 0, 2500);
  	srvElv.attach(SERVO_ELV, 0, 2500);
	srvRud.attach(SERVO_RUD, 0, 2500);
	// give a second for initial
	delay(1000);
	// center all
	srvAil.write(90);
	srvElv.write(90);
	srvRud.write(90);
	// wait a second after
	delay(1000);
}

// keep servos up to date
void servoctl(int aileron, int elevator, int rudder) {
	// convert to correct vals
	int actAilVal = map(aileron, -128, 128, 0, 180);
	int actElvVal = map(elevator, -128, 128, 0, 180);
	int actRudVal = map(rudder, -128, 128, 0, 180);
	// write to servos
	srvAil.write(actAilVal);
	srvElv.write(actElvVal);
	srvRud.write(actRudVal);
}
