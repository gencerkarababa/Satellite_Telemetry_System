#include "DataStructures/TelemetryQueue.h"
#include "Exceptions/SatelliteException.h"

// CONSTRUCTOR
TelemetryQueue::TelemetryQueue() {
    front = 0;
    rear = 0;
    currentSize = 0;
    for (int i = 0; i < capacity; i++) {
		buffer[i] = nullptr;
    }
}

// DESTRUCTOR
TelemetryQueue::~TelemetryQueue() {
    while (!isEmpty()) {
        delete dequeue();
    }
}

void TelemetryQueue::enqueue(TelemetryPacket* _packet) {
    if (isFull()) {
        delete dequeue();
    }

    buffer[rear] = _packet; 
    rear = (rear + 1) % capacity; // Dairesel ilerle
    currentSize++;
}

TelemetryPacket* TelemetryQueue::dequeue() {
    if (isEmpty()) {
        throw SatelliteException("CRITICAL WARNING: Launch pad (Queue) is empty!");
    }

    TelemetryPacket* temp = buffer[front];
    buffer[front] = nullptr; 
    front = (front + 1) % capacity; // Dairesel ilerle
    currentSize--;

    return temp;
}

bool TelemetryQueue::isEmpty() {
    return currentSize == 0;
}

bool TelemetryQueue::isFull() {
    return currentSize >= capacity;
}