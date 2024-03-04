#ifndef READER_H_
#define READER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>


class Reader {
private:

    Graph<Airport> graph;


    unordered_map<string, Airline> airlineMap;


    unordered_map<string, Vertex<Airport>*> airportMap;


    unordered_map<string, vector<Vertex<Airport>*>> cityToAirportsMap;


public:
    Reader();

    void readAndParseDS();

    void readAndParsePS();

    void readAndParseWR();

    void readAndParsePipes();

    const Graph<Airport>& getGraph() const {
        return graph;
    }

    const unordered_map<string, Airline>& getAirlineMap() const {
        return airlineMap;
    }

    const unordered_map<string, vector<Vertex<Airport>*>>& getCityToAirportsMap() const {
        return cityToAirportsMap;
    }

    const unordered_map<string, Vertex<Airport>*>& getAirportMap() const {
        return airportMap;
    }

};

#endif /* READER_H_ */