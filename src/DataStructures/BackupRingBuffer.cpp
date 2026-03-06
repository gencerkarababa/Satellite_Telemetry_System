#include "DataStructures/BackupRingBuffer.h"
#include "Exceptions/SatelliteException.h"
#include <iostream>

using namespace std;

// CONSTRUCTOR
BackupRingBuffer::BackupRingBuffer() {
    head = 0;
    count = 0;
    for (int i = 0; i < capacity; i++) {
        buffer[i] = nullptr;
    }
}

// DESTRUCTOR
BackupRingBuffer::~BackupRingBuffer() {
    for (int i = 0; i < capacity; i++) {
        if (buffer[i] != nullptr) {
            delete buffer[i];
        }
    }
}

void BackupRingBuffer::addRecord(TelemetryPacket* _packet) {
    if (_packet == nullptr) return;

    if (buffer[head] != nullptr) {
        delete buffer[head];
    }

    // _packet'ýn adresini deðil, içeriðini yeni bir nesneye kopyalýyoruz (fotokopi)
    buffer[head] = new TelemetryPacket(*_packet);

    if (count < capacity) {
        count++;
    }

    head = (head + 1) % capacity;
}

TelemetryPacket* BackupRingBuffer::getLastRecord() {
    if (count == 0) {
        return nullptr;
    }

    int lastIndex = (head - 1 + capacity) % capacity;
    return buffer[lastIndex];
}

void BackupRingBuffer::displayLastArchiveDetails() {
    TelemetryPacket* last = getLastRecord(); // En son yedeklenen kopyayý al

    if (last == nullptr) {
        std::cout << "[ARCHIVE] No telemetry data found in backup storage.\n";
        return;
    }

    cout << "\n----------- FINAL TELEMETRY ARCHIVE RECORD -----------\n";
    cout << "Packet ID  : " << last->packetID << "\n";
    cout << "Timestamp  : " << last->timestamp << "\n";
    cout << "Power      : " << last->batteryVoltage << "V | Solar: " << last->solarPanelCurrent << "A\n";
    cout << "Thermal    : Internal: " << last->internalTemp << "C | External: " << last->externalTemp << "C\n";
    cout << "Attitude   : X: " << last->gyroX << " | Y: " << last->gyroY << " | Z: " << last->gyroZ << "\n";
    cout << "Environment: Radiation: " << last->radiationLevel << " | RSSI: " << last->signalRSSI << " dBm\n";
    cout << "------------------------------------------------------\n";
}

void BackupRingBuffer::displayAllArchivesDetails() {
    if (count == 0) {
        std::cout << "[ARCHIVE] No telemetry data found in backup storage.\n";
        return;
    }
    cout << "\n=========== ALL TELEMETRY ARCHIVES IN BACKUP STORAGE ===========\n";
    for (int i = 0; i < count; i++) {
        int index = (head - 1 - i + capacity) % capacity;
        TelemetryPacket* p = buffer[index];
        cout << "\n--- Archive Record " << (i + 1) << " ---\n";
        cout << "Packet ID  : " << p->packetID << "\n";
        cout << "Timestamp  : " << p->timestamp << "\n";
        cout << "Power      : " << p->batteryVoltage << "V | Solar: " << p->solarPanelCurrent << "A\n";
        cout << "Thermal    : Internal: " << p->internalTemp << "C | External: " << p->externalTemp << "C\n";
        cout << "Attitude   : X: " << p->gyroX << " | Y: " << p->gyroY << " | Z: " << p->gyroZ << "\n";
        cout << "Environment: Radiation: " << p->radiationLevel << " | RSSI: " << p->signalRSSI << " dBm\n";
    }
    cout << "\n===============================================================\n";
}