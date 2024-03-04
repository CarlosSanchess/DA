#ifndef PROJ1_DELIVERYSTATION_H
#define PROJ1_DELIVERYSTATION_H

#include "Station.h"

class DeliveryStation : public Station {
private:
    std::string city;
    double demand;
    int population;
public:
    DeliveryStation(int id, std::string code, std::string city, double demand, int population);

    std::string getCity() const;
    double getDemand() const;
    int getPopulation() const;
};

#endif //PROJ1_DELIVERYSTATION_H