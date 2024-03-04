#include "DeliveryStation.h"

#include <utility>

DeliveryStation::DeliveryStation(int id, std::string code, std::string city, double demand, int population)
        : Station(id, std::move(code)), city(std::move(city)), demand(demand), population(population) {}

std::string DeliveryStation::getCity() const {
    return city;
}

double DeliveryStation::getDemand() const {
    return demand;
}

int DeliveryStation::getPopulation() const {
    return population;
}