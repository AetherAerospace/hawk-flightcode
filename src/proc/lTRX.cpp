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
unsigned long pastMillTRX = 0;
// keep track of packet count
unsigned int pktCnt = 0;
// main ctl array
int aerMain[3];
// buttons
int btnMain[2];
// packet related data for last
int lastPacketRSSI = 0;
float lastPacketSNR = 0.0;
// true when we need to send ACK
bool isACKLoop = false;

// parse actual packet based on ID
void handleStream(int t, String d) {
    if ( t != 100 ) {
        /*
            Data Packet ( 
                A[val] - Stick Aileron
                E[val] - Stick Elevator
                R[val] - Stick Rudder
                SR[val] - Button Shoulder Left
                SL[val] - Button Shoulder Right
                Q - EOF
            )
        */
        /*
            @TODO:
            !This needs a little bit of error checking!
            Even though we verify packet integrity by size in the
            receive process, we cann't trust data blindly
        */
        // parse main control values
        aerMain[0] = d.substring( 1, d.indexOf("E") ).toInt();
        aerMain[1] = d.substring( (d.indexOf("E") + 1), d.indexOf("R") ).toInt();
        aerMain[2] = d.substring( (d.indexOf("R") + 1), d.indexOf("SR") ).toInt();
        // parse button values
        btnMain[0] = d.substring( (d.indexOf("SR") + 2), d.indexOf("SL") ).toInt();
        btnMain[1] = d.substring( (d.indexOf("SL") + 2), d.indexOf("Q") ).toInt();
        ++pktCnt;
    } else {
        // we need to send ACK
        isACKLoop = true; 
        // reset packet counter
        // so next packets will be ACK
        pktCnt = 0;
    }
}

// decoder function for lTRX packets
void declTRX(int msgType, String data, int pktRS, float pktSNR) {
    lastPacketRSSI = pktRS;
    lastPacketSNR = pktSNR;
    handleStream(msgType, data);
}

// craft and send return packets
void lTRXTransmit() {
    /*
        Telemetry Packet ( 
            RS[val] - Last Packet RSSI value
            Q - EOF

            @TODO: add GPS and other stuff here

        )
    */
    sendLoRa(200,
        "RS" +
        String(lastPacketRSSI) +
        "Q"
    );
    ++pktCnt;
}

// lTRX main control loop
void lTRXctl() {
    if (millis() - pastMillTRX > LTRX_DELAY) {
        if ( 
            !isACKLoop  ||
            pktCnt > LTRX_ACK_PACKETS
        ) {
            // assume ack loop done
            isACKLoop = false;
            // recieving
            LoRaRXM();
        } else {
            // set transmit
            LoRaTXM();
            // send ACK packet with telemetry
            lTRXTransmit();
        }
        pastMillTRX = millis();
    } else return;
}

// expose controls
int getControls(int id) {
    return aerMain[id];
}

// expose buttons
int getButtons(int id) {
    return btnMain[id];
}
