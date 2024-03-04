#ifndef PROJ1_DELIVERYSTATION_H
#define PROJ1_DELIVERYSTATION_H

#include <string>

class DeliveryStation {

private:
    std::string city;
    int id;
    std::string code;
    double demand;
    int population;

public:
    DeliveryStation(std::string  city, int id, std::string  code, double demand, int population);

    std::string getCity() const;
    int getId() const;
    std::string getCode() const;
    double getDemand() const;
    int getPopulation() const;
};

#endif //PROJ1_DELIVERYSTATION_H