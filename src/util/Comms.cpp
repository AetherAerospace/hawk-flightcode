/*
    This file contains most of the 
    Communication logic via the LoRa
*/

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "Comms.h"
#include "pins/loraPins.h"
#include "util/Serial.h"
#include "settings/loraSet.h"

String LoRaData;

void onReceive(int packetSize) {
    if (packetSize == 0) return;

    LoRaData = "";
    int recipient = LoRa.read();
    byte sender = LoRa.read();
    int incomingLength = LoRa.read();

    while (LoRa.available()) {
        LoRaData += (char)LoRa.read();
    }

    if (recipient != LORA_LOCAL) {
        srlInfo("lTRX: '" + String(recipient) +  "' -> rogue?");
        return;
    }

    if (incomingLength != LoRaData.length()) {
        srlInfo("lTRX: '" + String(incomingLength) +  "' -> corrupt?");
        return;
    }
    srlInfo("lTRX: received '" + String(LoRaData) + "'");
}

void initLoRa() {
    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO0);
    if (!LoRa.begin(BAND)) {
        srlError("Unable to start lTRX!");
        while (1);
    }
    srlInfo("lTRX: Initialized");
}

void handleLoRa() {
    onReceive(LoRa.parsePacket());
}

void sendLoRa(String outgoing) {
  LoRa.beginPacket();
  LoRa.write(LORA_DEST);
  LoRa.write(LORA_LOCAL);
  LoRa.write(outgoing.length());
  LoRa.print(outgoing);
  LoRa.endPacket();
}
