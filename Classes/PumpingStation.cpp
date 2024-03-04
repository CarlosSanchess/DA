#include "PumpingStation.h"

PumpingStation::PumpingStation(int id, std::string  code)
        : id(id), code(std::move(code)) {}

int PumpingStation::getId() const {
    return id;
}

std::string PumpingStation::getCode() const {
    return code;
}