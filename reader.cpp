#include "reader.h"
#include "Classes/Station.h"

//7,PS_7,,
void Reader::readAndParsePS() {
    std::ifstream file("../Data/Stations.csv");
    std::string line;
    int id;

    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str;
        std::string code;

        getline(ss, id_str, ',');
        if (id_str.empty()) {
            break;
        }

        id = std::stoi(id_str);

        getline(ss, code, '\r');

        auto* PS = new Station(id,code);
        graph.addVertex(PS);
    }
    file.close();
}

void Reader::readAndParseDS() {
    std::ifstream file("../Data/Cities.csv");

    std::string line;

    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string city, id_str, code, demand_str, population_str;

        getline(ss, city, ',');
        getline(ss, id_str, ',');
        getline(ss, code, ',');
        getline(ss, demand_str, ',');
        getline(ss, population_str, '\n');

        population_str.erase(std::remove(population_str.begin(), population_str.end(), '"'), population_str.end());
        population_str.erase(std::remove(population_str.begin(), population_str.end(), ','), population_str.end());

        int id = std::stoi(id_str);
        double demand = std::stod(demand_str);
        int population = std::stoi(population_str);

        auto* DS = new DeliveryStation(id, code, city, demand, population);
        graph.addVertex(DS);

        // Add to codeMap and nameMap
        codeMap[code] = DS;
        nameMap[city] = DS;
        idMap[id] = DS;
    }

    file.close();
}


void Reader::readAndParseWR() {
    std::ifstream file("../Data/Reservoir.csv");

    std::string line;
    int id;
    int maxDelivery;

    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string reservoirName, municipality, id_str, code, maxDel;
        getline(ss, reservoirName, ',');
        getline(ss, municipality, ',');
        getline(ss, id_str, ',');

        id = std::stoi(id_str);

        getline(ss, code, ',');
        getline(ss, maxDel, ',');
        maxDelivery = std::stoi(maxDel);

        WaterReservoir* WR = new WaterReservoir(id, code, reservoirName, municipality, maxDelivery);

        graph.addVertex(WR);

        // Add to wrIdMap, wrCodeMap, and wrNameMap
        wrIdMap[id] = WR;
        wrCodeMap[code] = WR;
        wrNameMap[reservoirName] = WR;
    }
    file.close();
}


void Reader::readAndParsePipes() {
    std::ifstream file("../Data/Pipes.csv");
    std::string line;
    int capacity;
    bool direction;
    size_t aux;

    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string servicePointA, servicePointB, cap, dir;
        getline(ss, servicePointA, ',');
        getline(ss, servicePointB, ',');
        getline(ss, cap, ',');

        capacity = std::stoi(cap);

        getline(ss, dir, '\n');
        if ((aux = dir.find_first_not_of("0123456789")) != std::string::npos) { //Check
            dir.erase(aux);
        }
        direction = std::stoi(dir);


        Station* a = getNode(servicePointA);
        Station* b = getNode(servicePointB);
        if(!a || !b){
            std::cerr << "Didnt find any servicePoint with that CODE." << std::endl;
            exit(1);
        }
        if(direction){
            graph.addEdge(a,b,capacity);
        }else{
            graph.addBidirectionalEdge(a,b,capacity);
        }
    }
    file.close();
}

void Reader::addSuperSourceAndSink() {
    // Create super source and super sink vertices
    Station* superSource = new Station(-1, "SuperSource");
    Station* superSink = new Station(-2, "SuperSink");

    // Add super source and super sink vertices to the graph
    graph.addVertex(superSource);
    graph.addVertex(superSink);

    // Connect super source to all water reservoirs
    for (auto v : graph.getVertexSet()) {
        WaterReservoir* waterReservoir = dynamic_cast<WaterReservoir*>(v->getInfo());
        if (waterReservoir) {
            // Assuming the maximum delivery capacity is stored in m3/sec
            double capacity = waterReservoir->getMaxDelivery();
            graph.addEdge(superSource, waterReservoir, capacity);
        }
    }

    // Connect super sink to all delivery stations with edge capacities equal to their demands
    for (auto v : graph.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double demand = deliveryStation->getDemand();
            graph.addEdge(deliveryStation, superSink, demand);
        }
    }
}

Station* Reader::getNode(const std::string& servicePoint){
    for(auto v: graph.getVertexSet()){
        if(v->getInfo()->getCode() == servicePoint){
            return v->getInfo();
        }
    }
    return nullptr;
}

DeliveryStation* Reader::getDeliveryStationById(int id, const std::unordered_map<int, DeliveryStation*>& idMap) {
    auto it = idMap.find(id);
    return (it != idMap.end()) ? it->second : nullptr;
}

DeliveryStation* Reader::getDeliveryStationByCode(const std::string& code, const std::unordered_map<std::string, DeliveryStation*>& codeMap) {
    auto it = codeMap.find(code);
    return (it != codeMap.end()) ? it->second : nullptr;
}

DeliveryStation* Reader::getDeliveryStationByName(const std::string& name, const std::unordered_map<std::string, DeliveryStation*>& nameMap) {
    auto it = nameMap.find(name);
    return (it != nameMap.end()) ? it->second : nullptr;
}

WaterReservoir* Reader::getWaterReservoirById(int id, const std::unordered_map<int, WaterReservoir*>& wrIdMap) {
    auto it = wrIdMap.find(id);
    return (it != wrIdMap.end()) ? it->second : nullptr;
}

WaterReservoir* Reader::getWaterReservoirByCode(const std::string& code, const std::unordered_map<std::string, WaterReservoir*>& wrCodeMap) {
    auto it = wrCodeMap.find(code);
    return (it != wrCodeMap.end()) ? it->second : nullptr;
}

WaterReservoir* Reader::getWaterReservoirByName(const std::string& name, const std::unordered_map<std::string, WaterReservoir*>& wrNameMap) {
    auto it = wrNameMap.find(name);
    return (it != wrNameMap.end()) ? it->second : nullptr;
}


Reader::Reader() = default;