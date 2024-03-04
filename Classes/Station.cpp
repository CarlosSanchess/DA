#include "Station.h"

Station::Station(int id, std::string code) : id(id), code(std::move(code)) {}

Station::~Station() = default;

int Station::getId() const {
    return id;
}

std::string Station::getCode() const {
    return code;
}