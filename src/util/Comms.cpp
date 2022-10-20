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

    int recipient = LoRa.read();
    byte sender = LoRa.read();
    byte incomingMsgId = LoRa.read();
    byte incomingLength = LoRa.read();

    while (LoRa.available()) {
        LoRaData += (char)LoRa.read();
    }

    if (incomingLength != LoRaData.length()) {
        srlInfo("lTRX: Corrupt Packet?");
        return;
    }

    if (recipient != LORA_LOCAL) {
        srlInfo("lTRX: Rogue Address?");
        return;
    }
}

void initLoRa() {
    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO0);
    if (!LoRa.begin(BAND)) {
        srlError("Unable to start lTRX!");
        while (1);
    }
    LoRa.onReceive(onReceive);
    LoRa.receive();
    srlInfo("lTRX: Initialized");
}

void sendLoRa(String outgoing) {
  LoRa.beginPacket();
  LoRa.write(LORA_DEST);
  LoRa.write(LORA_LOCAL);
  LoRa.write(outgoing.length());
  LoRa.print(outgoing);
  LoRa.endPacket();
}
