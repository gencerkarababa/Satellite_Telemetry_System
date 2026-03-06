#include "Types/TelemetryPacket.h"
#include "Exceptions/SatelliteException.h"

// CONSTRUCTOR
TelemetryPacket::TelemetryPacket(int _packetID, long _timestamp, float _batteryVoltage, float _solarPanelCurrent, float _internalTemp, float _externalTemp,
    float _gyroX, float _gyroY, float _gyroZ, float _radiationLevel, float _signalRSSI) {

    if (_packetID <= 0) {
        throw SatelliteException("ERROR: Invalid Packet ID! ID value cannot be zero or negative.");
    }

    packetID = _packetID;
    timestamp = _timestamp;

    batteryVoltage = _batteryVoltage;
    solarPanelCurrent = _solarPanelCurrent;

    internalTemp = _internalTemp;
    externalTemp = _externalTemp;

    gyroX = _gyroX;
    gyroY = _gyroY;
    gyroZ = _gyroZ;

    radiationLevel = _radiationLevel;
    signalRSSI = _signalRSSI;
}