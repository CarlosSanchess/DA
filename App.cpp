/* #include <iostream>
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
    //Complete
        cout << "e. Exit\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {

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



void StatisticsMenu() {

    string choice;
    bool back = false;

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "            Statistics Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: ";

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}


void displayFilterMenu() {

    string filterOptionForCase1 = "NoFilter";
    string filterOptionForCase2 = "Filter1";
    string filterOptionForCase3 = "Filter2";
    string filterOptionForCase4 = "Filter3";

    while(true) {
        cout << "\n----------------------------------\n";
        cout << "          " << "Filter" << " Menu          \n";
        cout << "----------------------------------\n";
        cout << "Choose a " << "Filter" << " option:\n";
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
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
*/