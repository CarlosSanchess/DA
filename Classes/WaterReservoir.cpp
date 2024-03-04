#include "WaterReservoir.h"

WaterReservoir::WaterReservoir(std::string  name, std::string  municipality, int reservoirId, std::string  reservoirCode, int maxDel) :
        reservoirName(std::move(name)), municipality(std::move(municipality)), id(reservoirId), code(std::move(reservoirCode)), maxDelivery(maxDel) {}

std::string WaterReservoir::getReservoirName() const { return reservoirName; }
std::string WaterReservoir::getMunicipality() const { return municipality; }
int WaterReservoir::getId() const { return id; }
std::string WaterReservoir::getCode() const { return code; }
int WaterReservoir::getMaxDelivery() const { return maxDelivery; }

void WaterReservoir::setReservoirName(const std::string &name) { reservoirName = name; }
void WaterReservoir::setMunicipality(const std::string &municipality) { this->municipality = municipality; }
void WaterReservoir::setId(int id) { this->id = id; }
void WaterReservoir::setCode(const std::string &code) { this->code = code; }
void WaterReservoir::setMaxDelivery(int maxDelivery) { this->maxDelivery = maxDelivery; }