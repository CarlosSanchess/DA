#include "reader.h"

//Need to handle stoi convertion
//7,PS_7,,
void Reader::readAndParsePS() {
    std::ifstream file("../Data/Stations_Madeira.csv");
    std::string line;

    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        int id;
        std::string code;

        ss >> id;
        std::getline(ss >> std::ws, code, ',');

        Airport newAirport(code, name, city, country, latitude, longitude);
        graph.addVertex(newAirport);
        Vertex<Airport>* newAirportVertex = graph.findVertex(newAirport);
        airportMap[code] = newAirportVertex;
        cityToAirportsMap[city].push_back(newAirportVertex);

    }
}


//Ribeiro Frio,Santana,4,R_4,385,,
void Reader::readAndParseWR() {
    std::ifstream file("../Data/Reservoirs_Madeira.csv");
    std::string line;

    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string reservoirName, municipality, id, code, maxDelivery;
        getline(ss, reservoirName, ',');
        getline(ss, municipality, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, maxDelivery, ',');

        airlineMap.emplace(code, Airline(code, name, callsign, country));

    }
}

//R_1,PS_1,100,1
void Reader::readAndParsePipes() {
    std::ifstream file("../Data/Pipes_Madeira.csv");
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string servicePointA, servicePointB, capacity, direction;
        getline(ss, servicePointA, ',');
        getline(ss, servicePointB, ',');
        getline(ss, capacity, ',');
        getline(ss, direction, ',');

        auto airlineIt = airlineMap.find(airlineCode);
        if (airlineIt != airlineMap.end()) {
            graph.addEdge(airportMap[sourceCode]->getInfo(), airportMap[targetCode]->getInfo(), airlineIt->second);
        }
    }
}

//Porto Moniz,1,C_1,18.00,"2,517"
void Reader::readAndParseDS(){
    std::ifstream file("../Data/Cities_Madeira.csv");
    std::string line;
    double demand;

    while(getline(file,line)){
        std::stringstream ss(line);
        std::string city, code, dmnd, population;
        getline(ss, city, ',');
        getline(ss, code, ',');
        getline(ss, dmnd, ',');
        getline(ss, population, ',');
        demand = std::stod(dmnd); // Double Convertion
    }

}

Reader::Reader() = default;