#include "reader.h"
#include "Classes/Station.h"

/**
 * @brief Read and parse data from the Stations.csv file to create Station objects.
 *
 * This function reads data from the Stations.csv file, creates Station objects, and adds them to the graph.
 */
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


/**
 * @brief Read and parse data from the Cities.csv file to create DeliveryStation objects.
 *
 * This function reads data from the Cities.csv file, creates DeliveryStation objects, and adds them to the graph.
 */
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

        codeMap[code] = DS;
        nameMap[city] = DS;
        idMap[id] = DS;
    }

    file.close();
}

/**
 * @brief Read and parse data from the Reservoir.csv file to create WaterReservoir objects.
 *
 * This function reads data from the Reservoir.csv file, creates WaterReservoir objects, and adds them to the graph.
 */
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

        wrIdMap[id] = WR;
        wrCodeMap[code] = WR;
        wrNameMap[reservoirName] = WR;
    }
    file.close();
}

/**
 * @brief Read and parse data from the Pipes.csv file to create edges between stations in the graph.
 *
 * This function reads data from the Pipes.csv file and creates edges between stations in the graph based on the data.
 */
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
        pipeWeighVector.emplace_back(std::make_pair(a->getCode(), b->getCode()), capacity);

    }
    file.close();
}

/**
 * @brief Add super source and super sink vertices to the graph.
 *
 * This function creates super source and super sink vertices and connects them to appropriate vertices in the graph.
 */
void Reader::addSuperSourceAndSink() {
    Station* superSource = new Station(-1, "SuperSource");
    Station* superSink = new Station(-2, "SuperSink");

    graph.addVertex(superSource);
    graph.addVertex(superSink);

    for (auto v : graph.getVertexSet()) {
        WaterReservoir* waterReservoir = dynamic_cast<WaterReservoir*>(v->getInfo());
        if (waterReservoir) {
            double capacity = waterReservoir->getMaxDelivery();
            graph.addEdge(superSource, waterReservoir, capacity);
        }
    }

    for (auto v : graph.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double demand = deliveryStation->getDemand();
            graph.addEdge(deliveryStation, superSink, demand);
        }
    }

    for (auto vertex : graph.getVertexSet()) {
        if (vertex->getInfo()->getCode() == "SuperSource") {
            for (auto edge : vertex->getAdj()) {
                WaterReservoir* targetReservoir = dynamic_cast<WaterReservoir*>(edge->getDest()->getInfo());
                if (targetReservoir) {
                    double edgeWeight = edge->getWeight();

                    edgeWeightMap[targetReservoir->getCode()] = edgeWeight;
                }
            }
        }
    }
}

/**
 * @brief Get a Station object from the graph by its code.
 *
 * @param servicePoint The code of the Station to search for.
 * @return A pointer to the Station object if found, nullptr otherwise.
 */
Station* Reader::getNode(const std::string& servicePoint){
    for(auto v: graph.getVertexSet()){
        if(v->getInfo()->getCode() == servicePoint){
            return v->getInfo();
        }
    }
    return nullptr;
}

/**
 * @brief Get a DeliveryStation object by its ID from a provided map.
 *
 * @param id The ID of the DeliveryStation to search for.
 * @param idMap The map containing DeliveryStation objects keyed by their IDs.
 * @return A pointer to the DeliveryStation object if found, nullptr otherwise.
 */
DeliveryStation* Reader::getDeliveryStationById(int id, const std::unordered_map<int, DeliveryStation*>& idMap) {
    auto it = idMap.find(id);
    return (it != idMap.end()) ? it->second : nullptr;
}

/**
 * @brief Get a DeliveryStation object by its code from a provided map.
 *
 * @param code The code of the DeliveryStation to search for.
 * @param codeMap The map containing DeliveryStation objects keyed by their codes.
 * @return A pointer to the DeliveryStation object if found, nullptr otherwise.
 */
DeliveryStation* Reader::getDeliveryStationByCode(const std::string& code, const std::unordered_map<std::string, DeliveryStation*>& codeMap) {
    auto it = codeMap.find(code);
    return (it != codeMap.end()) ? it->second : nullptr;
}

/**
 * @brief Get a DeliveryStation object by its name from a provided map.
 *
 * @param name The name of the DeliveryStation to search for.
 * @param nameMap The map containing DeliveryStation objects keyed by their names.
 * @return A pointer to the DeliveryStation object if found, nullptr otherwise.
 */
DeliveryStation* Reader::getDeliveryStationByName(const std::string& name, const std::unordered_map<std::string, DeliveryStation*>& nameMap) {
    auto it = nameMap.find(name);
    return (it != nameMap.end()) ? it->second : nullptr;
}

/**
 * @brief Get a WaterReservoir object by its ID from a provided map.
 *
 * @param id The ID of the WaterReservoir to search for.
 * @param wrIdMap The map containing WaterReservoir objects keyed by their IDs.
 * @return A pointer to the WaterReservoir object if found, nullptr otherwise.
 */
WaterReservoir* Reader::getWaterReservoirById(int id, const std::unordered_map<int, WaterReservoir*>& wrIdMap) {
    auto it = wrIdMap.find(id);
    return (it != wrIdMap.end()) ? it->second : nullptr;
}

/**
 * @brief Get a WaterReservoir object by its code from a provided map.
 *
 * @param code The code of the WaterReservoir to search for.
 * @param wrCodeMap The map containing WaterReservoir objects keyed by their codes.
 * @return A pointer to the WaterReservoir object if found, nullptr otherwise.
 */
WaterReservoir* Reader::getWaterReservoirByCode(const std::string& code, const std::unordered_map<std::string, WaterReservoir*>& wrCodeMap) {
    auto it = wrCodeMap.find(code);
    return (it != wrCodeMap.end()) ? it->second : nullptr;
}

/**
 * @brief Get a WaterReservoir object by its name from a provided map.
 *
 * @param name The name of the WaterReservoir to search for.
 * @param wrNameMap The map containing WaterReservoir objects keyed by their names.
 * @return A pointer to the WaterReservoir object if found, nullptr otherwise.
 */
WaterReservoir* Reader::getWaterReservoirByName(const std::string& name, const std::unordered_map<std::string, WaterReservoir*>& wrNameMap) {
    auto it = wrNameMap.find(name);
    return (it != wrNameMap.end()) ? it->second : nullptr;
}

/**
 * @brief Constructor for the Reader class.
 *
 * Initializes a new Reader object.
 */
Reader::Reader() = default;