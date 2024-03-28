#include "DeliveryStation.h"

/**
 * @brief Constructor for the DeliveryStation class.
 * @param id The ID of the delivery station.
 * @param code The code of the delivery station.
 * @param city The city where the delivery station is located.
 * @param demand The demand of the delivery station.
 * @param population The population served by the delivery station.
 */
DeliveryStation::DeliveryStation(int id, std::string code, std::string city, double demand, int population)
        : Station(id, std::move(code)), city(std::move(city)), demand(demand), population(population) {}

/**
 * @brief Get the city where the delivery station is located.
 * @return The city where the delivery station is located.
 */
std::string DeliveryStation::getCity() const {
    return city;
}

/**
 * @brief Get the demand of the delivery station.
 * @return The demand of the delivery station.
 */
double DeliveryStation::getDemand() const {
    return demand;
}

/**
 * @brief Get the population served by the delivery station.
 * @return The population served by the delivery station.
 */
int DeliveryStation::getPopulation() const {
    return population;
}
