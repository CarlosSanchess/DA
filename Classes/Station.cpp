#include "Station.h"

/**
 * @brief Constructor for the Station class.
 * @param id The unique identifier of the station.
 * @param code The code identifying the station.
 */
Station::Station(int id, std::string code) : id(id), code(std::move(code)), active(true) {}

/**
 * @brief Destructor for the Station class.
 */
Station::~Station() = default;

/**
 * @brief Get the unique identifier of the station.
 * @return The unique identifier of the station.
 */
int Station::getId() const {
    return id;
}

/**
 * @brief Get the code identifying the station.
 * @return The code identifying the station.
 */
std::string Station::getCode() const {
    return code;
}

/**
 * @brief Set the activity status of the station.
 * @param status True if the station is active, false otherwise.
 */
void Station::setActive(bool status) {
    active = status;
}

/**
 * @brief Check if the station is active.
 * @return True if the station is active, false otherwise.
 */
bool Station::isActive() const {
    return active;
}
