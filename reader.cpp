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

void Reader::readAndParseDS() {
    std::ifstream file("../Data/Cities_Madeira.csv");
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


Reader::Reader() = default;