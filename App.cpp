/*
#include <iostream>
#include "reader.h"
#include "App.h"

using namespace std;

void display4_1menu(Graph<Station*>& graph);
void display4_2menu(Graph<Station*>& graph);
void maxFlowSubMenu(Graph<Station*>& graph);
void determineMaxFlowForEachCity(Graph<Station*>& graph);
void determineMaxFlowForSpecificCity(Graph<Station*>& graph);

int mainMenu(){
    cout << "Loading...";

    Reader reader;
    reader.readAndParsePS();
    reader.readAndParseWR();
    reader.readAndParseDS();
    reader.readAndParsePipes();
    reader.addSuperSourceAndSink();

    Graph<Station*>  graph = reader.getGraph();

    string choice;
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "\n-----------------------------\n";
        cout << "     Welcome to Main Menu       \n";
        cout << "-----------------------------\n";
        cout << "Enter the number of the option that suits your needs:\n";
        cout << "1. Basic Service Metrics\n";
        cout << "2. Reliability and Sensitivity to Failures\n";
        cout << "e. Exit\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {
            case '1':
                display4_1menu(graph);
                break;
            case '2':
                display4_2menu(graph);
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

void display4_1menu(Graph<Station*>& graph) {
    string choice;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n-----------------------------\n";
        cout << "       Basic Service Metrics       \n";
        cout << "-----------------------------\n";
        cout << "Select an option:\n";
        cout << "1. Maximum amount of water to reach each or a specific city (4.1.1)\n";
        cout << "2. Verify if the network configuration meets water needs (4.1.2)\n";
        cout << "3. Balance the load across the network (4.1.3)\n";
        cout << "b. Back to Main Menu\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {
            case '1':
                maxFlowSubMenu(graph);
                break;
            case '2':
                // Call function for 4.1.2
                cout << "You selected Verify if the network configuration meets water needs (4.1.2)\n";
                // Call function for 4.1.2 here
                break;
            case '3':
                // Call function for 4.1.3
                cout << "You selected Balance the load across the network (4.1.3)\n";
                // Call function for 4.1.3 here
                break;
            case 'b':
                cout << "Returning to Main Menu...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }
}

void maxFlowSubMenu(Graph<Station*>& graph) {
    string choice;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n-----------------------------\n";
        cout << "   Maximum Amount of Water    \n";
        cout << "-----------------------------\n";
        cout << "Select an option:\n";
        cout << "1. Max flow for each city\n";
        cout << "2. Max flow for a specific city\n";
        cout << "b. Back to Previous Menu\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {
            case '1':
                determineMaxFlowForEachCity(graph);
                break;
            case '2':
                determineMaxFlowForSpecificCity(graph);
                break;
            case 'b':
                cout << "Returning to Previous Menu...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }
}

void determineMaxFlowForEachCity(Graph<Station*>& graph) {

}

void determineMaxFlowForSpecificCity(Graph<Station*>& graph) {
}

void display4_2menu(Graph<Station*>& graph){

}

void App::run() {
    mainMenu();
}
*/