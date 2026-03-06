#pragma once

#include "DataStructures/TelemetryQueue.h"
#include "DataStructures/BackupRingBuffer.h"
#include "Exceptions/SatelliteException.h"
#include <string>

using namespace std;

class SatelliteControlUnit {
private:
    TelemetryQueue launchPad;
    BackupRingBuffer backupMemory;
    string satelliteName;

public:
    // CONSTRUCTOR
    SatelliteControlUnit(string name);

	// DESTRUCTOR
    ~SatelliteControlUnit();

    // AKIÞ FONKSÝYONLARI
    void readSensors(TelemetryPacket* packet); // Sensörden veriyi alýp DÝREKT kuyruða ekler
    void sendToEarth(); // Kuyruktaki veriyi dünyaya fýrlatýr ve 'kopyasýný' yedekler
    void displayLatestSummary();
    void displayFullHistory();
};