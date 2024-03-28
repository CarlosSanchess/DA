#ifndef PROJ1_WATERRESERVOIR_H
#define PROJ1_WATERRESERVOIR_H

#include <string>
#include "Station.h"

/**
 * @brief The WaterReservoir class represents a water reservoir station.
 *
 * It inherits from the Station class and adds attributes specific to water reservoirs,
 * such as reservoir name, municipality, and maximum delivery capacity.
 */
class WaterReservoir : public Station {
private:
    std::string reservoirName; ///< The name of the water reservoir.
    std::string municipality;  ///< The municipality where the water reservoir is located.
    int maxDelivery;            ///< The maximum delivery capacity of the water reservoir.
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