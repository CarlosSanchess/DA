#ifndef PROJ1_WATERRESERVOIR_H
#define PROJ1_WATERRESERVOIR_H

#include <string>
#include "Station.h"

class WaterReservoir : public Station{
private:
    std::string reservoirName;
    std::string municipality;
    int maxDelivery;
public:
    WaterReservoir(int id, std::string code,std::string  name, std::string  municipality, int maxDel);

    std::string getReservoirName() const;
    std::string getMunicipality() const;
    int getMaxDelivery() const;

    void setReservoirName(const std::string &name);
    void setMunicipality(const std::string &municipality);
    void setMaxDelivery(int maxDelivery);
};

#endif //PROJ1_WATERRESERVOIR_H