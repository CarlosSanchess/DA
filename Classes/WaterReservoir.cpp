#include "WaterReservoir.h"

WaterReservoir::WaterReservoir(int id, std::string code,std::string name, std::string municipality,int maxDel) :
        Station(id, std::move(code)), reservoirName(std::move(name)), municipality(std::move(municipality)), maxDelivery(maxDel) {}

std::string WaterReservoir::getReservoirName() const { return reservoirName; }
std::string WaterReservoir::getMunicipality() const { return municipality; }
int WaterReservoir::getMaxDelivery() const { return maxDelivery; }

void WaterReservoir::setReservoirName(const std::string &name) { reservoirName = name; }
void WaterReservoir::setMunicipality(const std::string &municipality) { this->municipality = municipality; }
void WaterReservoir::setMaxDelivery(int maxDelivery) { this->maxDelivery = maxDelivery; }