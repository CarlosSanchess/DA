#include "WaterReservoir.h"

/**
 * @brief Constructor for the WaterReservoir class.
 * @param id The unique identifier of the water reservoir.
 * @param code The code identifying the water reservoir.
 * @param name The name of the water reservoir.
 * @param municipality The municipality where the water reservoir is located.
 * @param maxDel The maximum delivery capacity of the water reservoir.
 */
WaterReservoir::WaterReservoir(int id, std::string code, std::string name, std::string municipality, int maxDel) :
        Station(id, std::move(code)), reservoirName(std::move(name)), municipality(std::move(municipality)), maxDelivery(maxDel) {}

/**
 * @brief Get the name of the water reservoir.
 * @return The name of the water reservoir.
 */
std::string WaterReservoir::getReservoirName() const {
    return reservoirName;
}

/**
 * @brief Get the municipality where the water reservoir is located.
 * @return The municipality where the water reservoir is located.
 */
std::string WaterReservoir::getMunicipality() const {
    return municipality;
}

/**
 * @brief Get the maximum delivery capacity of the water reservoir.
 * @return The maximum delivery capacity of the water reservoir.
 */
int WaterReservoir::getMaxDelivery() const {
    return maxDelivery;
}

/**
 * @brief Set the name of the water reservoir.
 * @param name The new name of the water reservoir.
 */
void WaterReservoir::setReservoirName(const std::string &name) {
    reservoirName = name;
}

/**
 * @brief Set the municipality where the water reservoir is located.
 * @param municipality The new municipality where the water reservoir is located.
 */
void WaterReservoir::setMunicipality(const std::string &municipality) {
    this->municipality = municipality;
}

/**
 * @brief Set the maximum delivery capacity of the water reservoir.
 * @param maxDelivery The new maximum delivery capacity of the water reservoir.
 */
void WaterReservoir::setMaxDelivery(int maxDelivery) {
    this->maxDelivery = maxDelivery;
}
