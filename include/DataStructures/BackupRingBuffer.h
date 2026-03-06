#pragma once

#include "Types/TelemetryPacket.h"

class BackupRingBuffer {
private:
	int head;
	int count;
	static const int capacity = 25;
	TelemetryPacket* buffer[capacity];

public:
	// CONSTRUCTOR
	BackupRingBuffer();

	// DESTRUCTOR
	~BackupRingBuffer();
	
	void addRecord(TelemetryPacket* _packet);
	TelemetryPacket* getLastRecord();
	void displayLastArchiveDetails();
	void displayAllArchivesDetails();
};