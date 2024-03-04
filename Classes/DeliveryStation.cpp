#include "DeliveryStation.h"

#include <utility>

DeliveryStation::DeliveryStation(std::string  city, int id, std::string  code, double demand, int population)
        : city(std::move(city)), id(id), code(std::move(code)), demand(demand), population(population) {}

std::string DeliveryStation::getCity() const {
    return city;
}

int DeliveryStation::getId() const {
    return id;
}

std::string DeliveryStation::getCode() const {
    return code;
}

double DeliveryStation::getDemand() const {
    return demand;
}

int DeliveryStation::getPopulation() const {
    return population;
}