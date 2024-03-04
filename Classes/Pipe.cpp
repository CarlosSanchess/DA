#include "Pipe.h"

#include <utility>

Pipe::Pipe(std::string  servicePointA, std::string  servicePointB, int capacity, bool direction)
        : servicePointA(std::move(servicePointA)), servicePointB(std::move(servicePointB)), capacity(capacity), direction(direction) {}

std::string Pipe::getServicePointA() const {
    return servicePointA;
}

std::string Pipe::getServicePointB() const {
    return servicePointB;
}

int Pipe::getCapacity() const {
    return capacity;
}

bool Pipe::getDirection() const {
    return direction;
}