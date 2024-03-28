#include "Pipe.h"

/**
 * @brief Constructor for the Pipe class.
 * @param servicePointA The code of the first service point connected by the pipe.
 * @param servicePointB The code of the second service point connected by the pipe.
 * @param capacity The capacity of the pipe.
 * @param direction The direction of flow through the pipe.
 */
Pipe::Pipe(std::string servicePointA, std::string servicePointB, int capacity, bool direction)
        : servicePointA(std::move(servicePointA)), servicePointB(std::move(servicePointB)), capacity(capacity), direction(direction) {}

/**
 * @brief Get the code of the first service point connected by the pipe.
 * @return The code of the first service point connected by the pipe.
 */
std::string Pipe::getServicePointA() const {
    return servicePointA;
}

/**
 * @brief Get the code of the second service point connected by the pipe.
 * @return The code of the second service point connected by the pipe.
 */
std::string Pipe::getServicePointB() const {
    return servicePointB;
}

/**
 * @brief Get the capacity of the pipe.
 * @return The capacity of the pipe.
 */
int Pipe::getCapacity() const {
    return capacity;
}

/**
 * @brief Get the direction of flow through the pipe.
 * @return The direction of flow through the pipe.
 *         True if the flow is from servicePointA to servicePointB, false otherwise.
 */
bool Pipe::getDirection() const {
    return direction;
}
