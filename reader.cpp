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

        Station* PS = new Station(id,code);
        graph.addVertex(PS);
    }
    file.close();
}

/*
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
*/

Reader::Reader() = default;