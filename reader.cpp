#include "reader.h"
#include "Classes/Station.h"

//7,PS_7,,
void Reader::readAndParsePS() {
    std::ifstream file("../Data/Stations_Madeira.csv");
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

        getline(ss, code, ',');

        auto* PS = new Station(id,code);
        graph.addVertex(PS);
    }
    file.close();
}


void Reader::readAndParseWR() {
    std::ifstream file("../Data/Reservoirs_Madeira.csv");
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
    std::ifstream file("../Data/Pipes_Madeira.csv");
    std::string line;
    int capacity;
    bool direction;

    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string servicePointA, servicePointB, cap, dir;
        getline(ss, servicePointA, ',');
        getline(ss, servicePointB, ',');
        getline(ss, cap, ',');

        capacity = std::stoi(cap);

        getline(ss, dir, '\n');

        direction = std::stoi(dir);

        auto *p = new Pipe(servicePointA, servicePointB, capacity, direction);


        Station* a = getNode(servicePointA);
        Station* b = getNode(servicePointB);
        if(!a || !b){
            std::cerr << "Didnt find any servicePoint with that CODE." << std::endl;
        }
        if(direction){
            graph.addEdge(a,b,capacity);
        }else{
            graph.addBidirectionalEdge(a,b,capacity);
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