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

        Station* WR = new WaterReservoir(id, code, reservoirName, municipality, maxDelivery);

        graph.addVertex(WR);
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

    // Connect super sink to all delivery stations
    for (auto v : graph.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            graph.addEdge(deliveryStation, superSink, INF); // Assuming INF represents unlimited capacity
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
Reader::Reader() = default;