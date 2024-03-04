#include "WaterReservoir.h"

WaterReservoir::WaterReservoir(string  name, string  municipality, int reservoirId, string  reservoirCode, int maxDel) :
        reservoirName(std::move(name)), municipality(std::move(municipality)), id(reservoirId), code(std::move(reservoirCode)), maxDelivery(maxDel) {}

string WaterReservoir::getReservoirName() const { return reservoirName; }
string WaterReservoir::getMunicipality() const { return municipality; }
int WaterReservoir::getId() const { return id; }
string WaterReservoir::getCode() const { return code; }
int WaterReservoir::getMaxDelivery() const { return maxDelivery; }

void WaterReservoir::setReservoirName(const string &name) { reservoirName = name; }
void WaterReservoir::setMunicipality(const string &municipality) { this->municipality = municipality; }
void WaterReservoir::setId(int id) { this->id = id; }
void WaterReservoir::setCode(const string &code) { this->code = code; }
void WaterReservoir::setMaxDelivery(int maxDelivery) { this->maxDelivery = maxDelivery; }