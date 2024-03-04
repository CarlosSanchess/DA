#ifndef PROJ1_DELIVERYSTATION_H
#define PROJ1_DELIVERYSTATION_H

#include <string>
using namespace std;

class DeliveryStation {

private:
    string city;
    int id;
    string code;
    double demand;
    int population;

public:
    DeliveryStation(string  city, int id, string  code, double demand, int population);

    string getCity() const;
    int getId() const;
    string getCode() const;
    double getDemand() const;
    int getPopulation() const;
};

#endif //PROJ1_DELIVERYSTATION_H