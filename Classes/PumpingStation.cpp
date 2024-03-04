#include "PumpingStation.h"

PumpingStation::PumpingStation(int id, string  code)
        : id(id), code(std::move(code)) {}

int PumpingStation::getId() const {
    return id;
}

string PumpingStation::getCode() const {
    return code;
}