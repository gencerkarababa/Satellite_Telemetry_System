#pragma once

#include "Types/TelemetryPacket.h"

class TelemetryQueue {
private:
	int front;
	int rear;
	static const int capacity = 25;
	TelemetryPacket* buffer[capacity];
	int currentSize;

public:
	// CONSTRUCTOR
	TelemetryQueue();

	// DESTRUCTOR
	~TelemetryQueue();

	void enqueue(TelemetryPacket* _packet);
	TelemetryPacket* dequeue();
	bool isEmpty();
	bool isFull();
};


