#include "reader.h"


void Reader::readAndParseAirports() {
    ifstream file("../resources/airports.csv");
    string line;

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string code, name, city, country, lat, lon;
        double latitude, longitude;

        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        getline(ss, lat, ',');
        getline(ss, lon, ',');
        latitude = stod(lat);
        longitude = stod(lon);

        Airport newAirport(code, name, city, country, latitude, longitude);
        graph.addVertex(newAirport);
        Vertex<Airport>* newAirportVertex = graph.findVertex(newAirport);
        airportMap[code] = newAirportVertex;
        cityToAirportsMap[city].push_back(newAirportVertex);
    }
}


void Reader::readAndParseAirlines() {
    ifstream file("../resources/airlines.csv");
    string line;

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string code, name, callsign, country;
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country, ',');

        airlineMap.emplace(code, Airline(code, name, callsign, country));
    }
}


void Reader::readAndParseFlights() {
    ifstream file("../resources/flights.csv");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string sourceCode, targetCode, airlineCode;
        getline(ss, sourceCode, ',');
        getline(ss, targetCode, ',');
        getline(ss, airlineCode, ',');

        auto airlineIt = airlineMap.find(airlineCode);
        if (airlineIt != airlineMap.end()) {
            graph.addEdge(airportMap[sourceCode]->getInfo(), airportMap[targetCode]->getInfo(), airlineIt->second);
        }
    }
}


Reader::Reader() = default;