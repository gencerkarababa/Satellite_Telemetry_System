#include "Management/SatelliteControlUnit.h"
#include <iostream>

using namespace std;

// CONSTRUCTOR
SatelliteControlUnit::SatelliteControlUnit(std::string name) : satelliteName(name) {}

// DESTRUCTOR
SatelliteControlUnit::~SatelliteControlUnit() {
    cout << "[SYSTEM] " << satelliteName << " all sub-systems have been safely shut down.\n";
}

void SatelliteControlUnit::readSensors(TelemetryPacket* packet) {
    try {
        if (packet == nullptr) return;

        if (launchPad.isFull()) {
            cout << "\n[AUTO-SYSTEM] Launch pad is FULL! Triggering autonomous transmission...\n";
            sendToEarth();
            cout << "[AUTO-SYSTEM] Transmission complete. Space is now available for new data.\n\n";
        }

        launchPad.enqueue(packet);

        cout << "[SENSOR] Packet ID [" << packet->packetID << "] received and loaded into Queue.\n";
    }
    catch (const SatelliteException& e) {
        cout << "[ERROR] Sensor data could not be processed: " << e.what() << "\n";
        delete packet;
    }
}

void SatelliteControlUnit::sendToEarth() {
    cout << "[SCU] Communication channel established. Transmitting data for " << satelliteName << "...\n";

    int sentCount = 0;
    while (!launchPad.isEmpty()) {
        try {
            TelemetryPacket* p = launchPad.dequeue();

            cout << ">> Packet ID [" << p->packetID << "] transmitted via high-gain antenna!\n";

            // Paketin bir kopyasýný arþive gönder (Arþiv kendi içinde 'new' yapacak)
            backupMemory.addRecord(p);

            delete p;

            sentCount++;
        }
        catch (const SatelliteException& e) {
            cout << "[CRITICAL] Transmission failed: " << e.what() << "\n";
            break;
        }
    }
    cout << "-> Operation Complete: " << sentCount << " packets transmitted and archived.\n";
}

void SatelliteControlUnit::displayLatestSummary() {
    cout << "\n>>> LATEST TELEMETRY SUMMARY FOR " << satelliteName << " <<<" << endl;
    backupMemory.displayLastArchiveDetails();
}

void SatelliteControlUnit::displayFullHistory() {
    cout << "\n>>> FULL MISSION HISTORY REPORT (" << satelliteName << ") <<<" << endl;
    backupMemory.displayAllArchivesDetails();
}