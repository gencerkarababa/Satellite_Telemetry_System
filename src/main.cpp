#include "Management/SatelliteControlUnit.h"
#include "Types/TelemetryPacket.h"
#include <iostream>

using namespace std;

int main() {
    cout << "--- Satellite Initialization Sequence ---" << endl;

    SatelliteControlUnit scu("TURKSAT-6A");

    cout << "\n[1] SIMULATING SENSOR DATA ACQUISITION..." << endl;

    // Sensörden veri gelmiþ gibi 3 adet paket oluþturuyoruz
    for (int i = 1; i <= 3; i++) {
        TelemetryPacket* newPacket = new TelemetryPacket(
            100 + i,            // packetID
            1715000000L + i,    // timestamp
            12.5f,              // batteryVoltage
            0.5f * i,           // solarPanelCurrent
            22.0f + i,          // internalTemp
            -15.0f - i,         // externalTemp
            0.1f * i,           // gyroX
            0.2f * i,           // gyroY
            0.3f * i,           // gyroZ
            0.01f * i,          // radiationLevel
            -60.0f - i          // signalRSSI
        );
        scu.readSensors(newPacket); // paket kuyruga gidiyor
    }

    cout << "\n[2] STARTING TELEMETRY TRANSMISSION TO EARTH..." << endl;
    scu.sendToEarth();

    cout << "\n[3] GENERATING MISSION REPORTS..." << endl;

    scu.displayLatestSummary();

    scu.displayFullHistory();

    cout << "\n--- Mission Simulation Completed Successfully ---" << endl;

    return 0;
}