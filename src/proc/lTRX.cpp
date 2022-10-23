/*
    lTRX
    Protocol for intercommunication and packet parsing
*/

#include <Arduino.h>
#include "lTRX.h"
#include "util/LoRa.h"
#include "util/Serial.h"
#include "settings/ltrxset.h"

unsigned long prCL = 0;
unsigned long crCL = 0;

void handleCTL(int t, String d) {
    switch (t) {
        case 31:
            // Stick Values ( A E R )
            int ail = d.substring(1, d.indexOf("E")).toInt();
            int elv = d.substring((d.indexOf("E") + 1), d.indexOf("R")).toInt();
            int rud = d.substring((d.indexOf("R") + 1), d.indexOf("Q")).toInt();
            srlInfo("lTRX", "Ail: "
                + String(ail) + " Elv: "
                + String(elv) + " Rud: "
                + String(rud)
            );
            break;
        /*
        case 32:
            // Custom Button 1, @TODO, do nothing for now
            break;
        case 33:
            // Custom Button 2, @TODO, do nothing for now
            break;
        case 34:
            // Custom Button 3, @TODO, do nothing for now
            break;
        */
    }
}

void declTRX(int msgType, String data) {
    switch (msgType) {
        /*
        case 10 ... 19:
            // ACK, @TODO, do nothing for now
            break;
        case 20 ... 29:
            // ACK, @TODO, do nothing for now
            break;
        */
        case 30 ... 39:
            handleCTL(msgType, data);
            break;
        /*
        case 40 ... 49:
            // ERR, @TODO, do nothing for now
            break;
        case 50 ... 59:
            // GPS, @TODO, do nothing for now
            break;
        */
    }
}

void lTRXctl() {
    crCL = millis();
    if (crCL - prCL > LTRX_DELAY) {
        prCL = crCL;
    } else return;
}
