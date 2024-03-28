#ifndef PROJ1_DELIVERYSTATION_H
#define PROJ1_DELIVERYSTATION_H

#include "Station.h"

/**
 * @brief A class representing a delivery station.
 *
 * This class extends the functionality of the Station class to include information
 * specific to delivery stations, such as the city served, demand, and population.
 */
class DeliveryStation : public Station {
private:
    std::string city; /**< The city served by the delivery station.*/
    double demand;    /**< The demand for water in the city served by the delivery station.*/
    int population;   /**< The population of the city served by the delivery station.*/
public:
    DeliveryStation(int id, std::string code, std::string city, double demand, int population);

    std::string getCity() const;

    double getDemand() const;

    int getPopulation() const;
};

#endif //PROJ1_DELIVERYSTATION_H
