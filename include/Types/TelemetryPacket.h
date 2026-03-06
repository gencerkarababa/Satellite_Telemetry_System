#pragma once

class TelemetryPacket {
public:
    // kimlik bilgileri
    int packetID;       
    long timestamp;     // (Zaman damgasý)

    // sensör verileri
    float batteryVoltage;
    float solarPanelCurrent;

    float internalTemp;
    float externalTemp;

    float gyroX;
    float gyroY;
    float gyroZ;

    float radiationLevel;
    float signalRSSI;

    // CONSTRUCTOR
    TelemetryPacket(int _packetID, long _timestamp, float _batteryVoltage, float _solarPanelCurrent, float _internalTemp, float _externalTemp,
        float _gyroX, float _gyroY, float _gyroZ, float _radiationLevel, float _signalRSSI);
};