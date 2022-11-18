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
unsigned long crCL = 0;
// keep track of packet count
unsigned int pktCnt = 0;
// main ctl array
int aerMain[3];
// buttons
int btnMain[6];
// packet related data for last
int lastPacketRSSI = 0;
float lastPacketSNR = 0.0;
// if this is non-zero, the link has problems
int packetDiff = 0;
// remote pkt counter for LQ
int remotePktCnt = 0;

// link quality management
void handleLNK(int t, String d) {
    switch (t) {
        case 11:
            remotePktCnt = d.substring(2, d.indexOf("Q")).toInt();
            ++pktCnt;
            packetDiff = (remotePktCnt - pktCnt);
            /*
            sendLoRa(t,
                "PD" +
                String(packetDiff) +
                "Q"
            );
            srlInfo("lTRX", "pktCnt: "
                + String(lnkMain[0]) + " RSSI: "
                + String(lnkMain[1]) + " SNR: "
                + String(lnkMain[2])
            );
            */
            break;
    }
}

// parse known control packets
void handleCTL(int t, String d) {
    switch (t) {
        case 31:
            // Stick Val ( A[val]E[val]R[val]Q )
            aerMain[0] = d.substring(1, d.indexOf("E")).toInt();
            aerMain[1] = d.substring((d.indexOf("E") + 1), d.indexOf("R")).toInt();
            aerMain[2] = d.substring((d.indexOf("R") + 1), d.indexOf("Q")).toInt();
            ++pktCnt;
            /*
            srlInfo("lTRX", "Ail: "
                + String(aerMain[0]) + " Elv: "
                + String(aerMain[1]) + " Rud: "
                + String(aerMain[2])
            );
            */
            break;
        case 32:
            // Button Vals ( SR[val]SL[val]Q )
            btnMain[0] = d.substring(2, d.indexOf("SL")).toInt();
            btnMain[1] = d.substring((d.indexOf("SL") + 2), d.indexOf("Q")).toInt();
            /*
            srlInfo("lTRX", "SR: "
                + String(btnMain[0]) + " SL "
                + String(btnMain[1])
            );
            */
            ++pktCnt;
            break;
        case 33:
            // Button Vals ( PX[val]PS[val]PT[val]PC[val]Q )
            btnMain[2] = d.substring(2, d.indexOf("PS")).toInt();
            btnMain[3] = d.substring((d.indexOf("PS") + 2), d.indexOf("PT")).toInt();
            btnMain[4] = d.substring((d.indexOf("PT") + 2), d.indexOf("PC")).toInt();
            btnMain[5] = d.substring((d.indexOf("PC") + 2), d.indexOf("Q")).toInt();
            /*
            srlInfo("lTRX", "PX: "
                + String(btnMain[2]) + " PS "
                + String(btnMain[3]) + " PT "
                + String(btnMain[4]) + " PC "
                + String(btnMain[5])
            );
            */
            ++pktCnt;
            break;
    }
}

// decoder function for lTRX packets
void declTRX(int msgType, String data, int pktRS, float pktSNR) {
    lastPacketRSSI = pktRS;
    lastPacketSNR = pktSNR;
    switch (msgType) {
        case 10 ... 19:
            handleLNK(msgType, data);
            break;
        /*
        case 20 ... 29:
            // GPS, @TODO, do nothing for now
            break;
        */
        case 30 ... 39:
            handleCTL(msgType, data);
            break;
    }
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
    crCL = millis();
    if (crCL - prCL > LTRX_DELAY) {
        prCL = crCL;
    } else return;
}
