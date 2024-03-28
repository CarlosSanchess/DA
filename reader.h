#ifndef READERH
#define READERH

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "Classes/DeliveryStation.h"
#include "Classes/Station.h"
#include "Classes/Graph.h"
#include "Classes/WaterReservoir.h"
#include "Classes/Pipe.h"

class Reader {
private:
    Graph<Station*> graph;
    std::unordered_map<int, DeliveryStation*> idMap;  // Map from ID to Station
    std::unordered_map<std::string, DeliveryStation*> codeMap;  // Map from code to Station
    std::unordered_map<std::string, DeliveryStation*> nameMap;  // Map from name to Station

    std::unordered_map<int, WaterReservoir*> wrIdMap;  // Map from ID to Water Reservoir
    std::unordered_map<std::string, WaterReservoir*> wrCodeMap;  // Map from code to Water Reservoir
    std::unordered_map<std::string, WaterReservoir*> wrNameMap;  // Map from name to Water Reservoir

    std::unordered_map<std::string, double> edgeWeightMap; // New map to store edge weights

public:
    Reader();

    void readAndParseDS();

    void readAndParsePS();

    void readAndParseWR();

    void readAndParsePipes();

    Station* getNode(const std::string& servicePoint);

    Graph<Station*> getGraph(){
        return graph;
    }

    void addSuperSourceAndSink();

    static DeliveryStation* getDeliveryStationById(int id, const std::unordered_map<int, DeliveryStation*>& idMap);
    static DeliveryStation* getDeliveryStationByCode(const std::string& code, const std::unordered_map<std::string, DeliveryStation*>& codeMap);
    static DeliveryStation* getDeliveryStationByName(const std::string& name, const std::unordered_map<std::string, DeliveryStation*>& nameMap);

    static WaterReservoir* getWaterReservoirById(int id, const std::unordered_map<int, WaterReservoir*>& wrIdMap);
    static WaterReservoir* getWaterReservoirByCode(const std::string& code, const std::unordered_map<std::string, WaterReservoir*>& wrCodeMap);
    static WaterReservoir* getWaterReservoirByName(const std::string& name, const std::unordered_map<std::string, WaterReservoir*>& wrNameMap);

    std::unordered_map<std::string, DeliveryStation*> getCodeMap() const {
        return codeMap;
    }

    std::unordered_map<std::string, DeliveryStation*> getNameMap() const {
        return nameMap;
    }

    std::unordered_map<int, DeliveryStation*> getIdMap() const {
        return idMap;
    }

    std::unordered_map<int, WaterReservoir*> getWrIdMap() const {
        return wrIdMap;
    }

    std::unordered_map<std::string, WaterReservoir*> getWrCodeMap() const {
        return wrCodeMap;
    }

    std::unordered_map<std::string, WaterReservoir*> getWrNameMap() const {
        return wrNameMap;
    }

    std::unordered_map<std::string, double> getEdgeWeightMap() const {
        return edgeWeightMap;
    }
};

#endif /* READER_H */