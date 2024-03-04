#ifndef READER_H_
#define READER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>

/**
 * @brief Represents a reader utility for parsing airlines, airports, and flights.
 *
 * This class provides functionalities to read and parse data related to airlines,
 * airports, and flights.
 */
class Reader {
private:
    /**
     * @brief Graph structure that represents airports and their connections.
     */
    Graph<Airport> graph;

    /**
     * @brief Map to store airlines based on their unique identifiers.
     */
    unordered_map<string, Airline> airlineMap;

    /**
     * @brief Map to store airports based on their unique identifiers.
     */
    unordered_map<string, Vertex<Airport>*> airportMap;

    /**
     * @brief Map that associates city with a vector of airports.
     */
    unordered_map<string, vector<Vertex<Airport>*>> cityToAirportsMap;


public:
    Reader();

    void readAndParseAirlines();

    void readAndParseAirports();

    void readAndParseFlights();

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