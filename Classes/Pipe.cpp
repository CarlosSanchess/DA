#include "Pipe.h"

#include <utility>

Pipe::Pipe(string  servicePointA, string  servicePointB, int capacity, bool direction)
        : servicePointA(std::move(servicePointA)), servicePointB(std::move(servicePointB)), capacity(capacity), direction(direction) {}

string Pipe::getServicePointA() const {
    return servicePointA;
}

string Pipe::getServicePointB() const {
    return servicePointB;
}

int Pipe::getCapacity() const {
    return capacity;
}

bool Pipe::getDirection() const {
    return direction;
}