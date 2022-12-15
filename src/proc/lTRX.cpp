/*
    lTRX
    Protocol for intercommunication and packet parsing
*/

#include <Arduino.h>
#include "lTRX.h"
#include "util/LoRa.h"
#include "util/Serial.h"
#include "settings/ltrxset.h"

// timeouts for main loop
unsigned long prCL = 0;
// keep track of packet count
unsigned int pktCnt = 0;
// main ctl array
int aerMain[3];
// buttons
int btnMain[2];
// packet related data for last
int lastPacketRSSI = 0;
float lastPacketSNR = 0.0;
// if this is non-zero, the link has problems
int packetDiff = 0;
// remote pkt counter for LQ
int rmtPktCnt = 0;

// craft control packets to be handled by receiver
void lTRXStream() {
    sendLoRa(2,
        "RS" +
        String(lastPacketRSSI) +
        "Q"
    );
    ++pktCnt;
}

// parse known control packets
void handleStream(int t, String d) {
    // Stick Val ( A[val]E[val]R[val]Q )
    aerMain[0] = d.substring( 1, d.indexOf("E") ).toInt();
    aerMain[1] = d.substring( (d.indexOf("E") + 1), d.indexOf("R") ).toInt();
    aerMain[2] = d.substring( (d.indexOf("R") + 1), d.indexOf("SL") ).toInt();
    btnMain[0] = d.substring( (d.indexOf("SL") + 2), d.indexOf("SR") ).toInt();
    btnMain[1] = d.substring( (d.indexOf("SR") + 2), d.indexOf("Q") ).toInt();
    ++pktCnt;
}

// decoder function for lTRX packets
void declTRX(int msgType, String data, int pktRS, float pktSNR) {
    lastPacketRSSI = pktRS;
    lastPacketSNR = pktSNR;
    handleStream(msgType, data);
}

// expose controls
int fetchControls(int id) {
    return aerMain[id];
}

// expose buttons
int fetchButtons(int id) {
    return btnMain[id];
}

// lTRX main control loop
void lTRXctl() {
    // send response after delay
    if (millis() - prCL > LTRX_DELAY) {
        // set transmit
        LoRaTXM();
        // telemetry response
        lTRXStream();
        prCL = millis();
        // set receive
    } else return;
    // recieving
    LoRaRXM();
}
