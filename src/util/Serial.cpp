/*
    Stuff in here is mostly for prettier
    serial console logging output
*/

#include <Arduino.h>
#include "Serial.h"
#include "settings/serialSet.h"

// for delays
unsigned long gyroPrevMillis = 0;
unsigned long baroPrevMillis = 0;
unsigned long powerPrevMillis = 0;

void srlError(String errorMsg) {
    Serial.println("> Error Report:");
    Serial.println("> " + errorMsg);
    Serial.println(END_SEPERATOR);
}

void srlInfo(String infoMsg) {
    Serial.println("> Info:");
    Serial.println("> " + infoMsg);
    Serial.println(END_SEPERATOR);
}
