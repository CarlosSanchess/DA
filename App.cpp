#include <iostream>
#include <limits>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <cmath>
#include "reader.h"
#include "App.h"


using namespace std;

/**
 * @brief This function represents the main menu of the flight system application.
 *
 * The mainMenu function performs the following tasks:
 * 1. Loads data related to airports, airlines, and flights using the Reader class.
 * 2. Displays a user interface with multiple options for the user to choose from.
 * 3. Based on the user's choice, it either:
 *      - Directs the user to a statistics menu.
 *      - Displays a filter menu to find the best flight option.
 *      - Exits the main menu.
 *
 * @return int Returns 0 upon successful execution of the menu system.
 */
int mainMenu(){
    cout << "Loading...";

    Reader reader;
    reader.readAndParseAirports();
    reader.readAndParseAirlines();
    reader.readAndParseFlights();
    Graph graph = reader.getGraph();
    unordered_map<string, Vertex<Airport>*> airportMap = reader.getAirportMap();
    unordered_map<string, Airline> airlineMap = reader.getAirlineMap();
    unordered_map<string, vector<Vertex<Airport>*>> cityToAirportsMap = reader.getCityToAirportsMap();

    string choice;
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "\n-----------------------------\n";
        cout << "     Welcome to Main Menu       \n";
        cout << "-----------------------------\n";
        cout << "Enter the number of the option that suits your needs:\n";
        cout << "1. Search for flight/airport statistics\n";
        cout << "2. Find the best flight option for you\n";
        cout << "e. Exit\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {
            case '1':
                StatisticsMenu(graph);
                break;
            case '2':
                displayFilterMenu(graph, cityToAirportsMap, airportMap);
                break;
            case 'e':
                cout << "Exiting menu system...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }

    return 0;
}


/**
 * @brief This function represents the statistics menu of the flight system application.
 *
 * @param graph The Graph object.
 *
 * The menu options available in this function are as follows:
 * 1. Display global airport and flight availability statistics.
 * 2. Show flights from an airport and the airlines operating there.
 * 3. Explore flights per city/airline.
 * 4. Count countries served by a specific airport/city.
 * 5. View destinations available from a chosen airport (airports, cities, or countries).
 * 6. Find reachable destinations from an airport with a maximum number of layovers.
 * 7. Find the trip(s) with the greatest number of stops in between.
 * 8. Identify the top airport(s) with the greatest air traffic capacity.
 * 9. Identify essential airports for network circulation.
 * b. Go back to the previous menu.
 *
 * @return void This function does not return any value upon completion as it is a menu-based system.
 */
void StatisticsMenu(Graph<Airport> graph) {

    string choice;
    bool back = false;

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "            Statistics Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Display global airport and flight availability statistics\n";
        cout << "2. Show flights from an airport and the airlines operating there\n";
        cout << "3. Explore flights per city/airline\n";
        cout << "4. Count countries served by a specific airport/city\n";
        cout << "5. View destinations available from a chosen airport (airports, cities, or countries)\n";
        cout << "6. Find reachable destinations from an airport with a max number of layovers (airports, cities, or countries)\n";
        cout << "7. Find the trip(s) with the greatest number of stops in between\n";
        cout << "8. Identify the top airport(s) with the greatest air traffic capacity\n";
        cout << "9. Identify essential airports for network circulation\n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "(Note : The chosen source airport/city/airline is always included in searches)" << endl;
        cout << "Your choice: ";

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                displayGlobalNumbers(graph);
                break;
            case '2':
                displayFlightsFromAirport(graph);
                break;
            case '3':
                calculateFlights(graph);
                break;
            case '4':
                displayCountriesFromAirportCity(graph);
                break;
            case '5':
                displayDestinations(graph);
                break;
            case '6':
                displayReachableDestinationsXStops(graph);
                break;
            case '7':
                displayMaxStopsTrip(graph);
                break;
            case '8':
                displayTopKAirTraffic(graph);
                break;
            case '9':
                displayEssentialAirports(graph);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

/**
 * @brief Displays the filter menu to the user and handles the user's filter choice.
 *
 * This function displays a menu of filter options to the user, reads the user's choice,
 * and calls the appropriate function based on the user's choice. The user can choose to
 * apply no filters, filter by preferred airlines, filter by least number of airline changes,
 * or filter to specific countries/cities. The user can also choose to go back to the previous step.
 *
 * @param graph The graph of airports.
 * @param airportMap A map from airport codes to vertices in the graph.
 * @param cityToAirportMap A map from city names to its airports.
 */
void displayFilterMenu(const Graph<Airport> &graph, const unordered_map<string, vector<Vertex<Airport> *>> &airportMap,
                       const unordered_map<string, Vertex<Airport> *> &cityToAirportMap) {

    string filterOptionForCase1 = "NoFilter";
    string filterOptionForCase2 = "Filter1";
    string filterOptionForCase3 = "Filter2";
    string filterOptionForCase4 = "Filter3";

    while(true) {
        cout << "\n----------------------------------\n";
        cout << "          " << "Filter" << " Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose a " << "Filter" << " option:\n";
        cout << "1. No filters\n";
        cout << "2. Filter by preferred Airlines\n";
        cout << "3. Filter by least number of Airline changes\n";
        cout << "4. Filter to avoid certain Airlines\n";
        cout << "b. Go back to the previous step\n";
        cout << "----------------------------------\n";
        cout << "Your choice: ";

        string filterOption;
        cin >> filterOption;

        if (filterOption == "b" || filterOption == "B") {
            return;
        }

        if(filterOption.length() != 1){
            filterOption = "0";
        }

        switch (filterOption[0]) {
            case '1':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase1);
                break;
            case '2':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase2);
                break;
            case '3':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase3);
                break;
            case '4':
                displaySourceMenu(graph, airportMap, cityToAirportMap, filterOptionForCase4);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
