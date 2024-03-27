#include "Station.h"

Station::Station(int id, std::string code) : id(id), code(std::move(code)), active(true) {}

Station::~Station() = default;

int Station::getId() const {
    return id;
}

std::string Station::getCode() const {
    return code;
}
void Station::setActive(bool status){
    Station::active = status;
}
bool Station::isActive() const {
    return active;
}