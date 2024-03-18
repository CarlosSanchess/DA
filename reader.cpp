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


Station* Reader::getNode(const std::string& servicePoint){
    for(auto v: graph.getVertexSet()){
        if(v->getInfo()->getCode() == servicePoint){
            return v->getInfo();
        }
    }
    return nullptr;
}
Reader::Reader() = default;