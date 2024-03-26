#include <iostream>
#include "reader.h"
#include "App.h"

using namespace std;

void display4_1menu(Graph<Station*>& graph);
void maxFlowSubMenu(Graph<Station*>& graph);
double getFlowToCity(Graph<Station*>& g, Vertex<Station*>* deliveryStation);
void checkWaterCity(Graph<Station*> g, const std::string& cityCode);
double MaxFlowAlgo(Graph<Station*>& g);
void PrintMaxFlowForCities(Graph<Station*>& graph, double totalFlow);
void checkWaterSupply(Graph<Station*> g);


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
                maxFlowSubMenu(graph); // menu for 4.1.1
                break;
            case '2':
                checkWaterSupply(graph);
                break;
            case '3':
                // Call function for 4.1.3
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

    double totalFlow = MaxFlowAlgo(graph);

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
                PrintMaxFlowForCities(graph, totalFlow);
                break;
            case '2':
            {
                string cityCode;
                cout << "Enter the city code ('b' to go back): ";
                cin >> cityCode;
                if (cityCode == "b") {
                    exitMenu = true;
                    break;
                }
                checkWaterCity(graph, cityCode);
                break;
            }
            case 'b':
                cout << "Returning to Previous Menu...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }
}

double MaxFlowAlgo(Graph<Station*>& g) {

    // Find super source and super sink
    Vertex<Station*>* superSource = nullptr;
    Vertex<Station*>* superSink = nullptr;

    for (auto v : g.getVertexSet()) {
        if (v->getInfo()->getCode() == "SuperSource") {
            superSource = v;
        } else if (v->getInfo()->getCode() == "SuperSink") {
            superSink = v;
        }
    }

    if (!superSource || !superSink) {
        std::cerr << "Error: Super source or super sink not found." << std::endl;
        return 0;
    }

    // Run the Max Flow Algorithm on the Entire Graph
    return initEdmondsKarp(&g, superSource->getInfo(), superSink->getInfo());
}

void PrintMaxFlowForCities(Graph<Station*>& graph, double totalFlow) {
    // Output file to save results
    std::ofstream outputFile("../max_flow.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }

    std::cout << "Calculating maximum water flow for each city..." << std::endl;
    std::cout << "Total maximum flow of the network : " << totalFlow << std::endl;
    outputFile << "Total maximum flow of the network : " << totalFlow << std::endl;

    // Check flow for each city
    for (auto v : graph.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(graph, v);

            std::string cityName = deliveryStation->getCity();
            std::string cityCode = deliveryStation->getCode();
            std::cout << "Flow to city " << cityName << " (" << cityCode << "): " << cityFlow << std::endl;
            outputFile << "Flow to city " << cityName << " (" << cityCode << "): " << cityFlow << std::endl;
        }
    }

    // Close the output file
    outputFile.close();
    std::cout << "Results saved to ../max_flow.txt" << std::endl;
}

double getFlowToCity(Graph<Station*>& g, Vertex<Station*>* deliveryStation) {
    double flowToCity = 0.0;
    for (auto incomingEdge : deliveryStation->getIncoming()) {
        flowToCity += incomingEdge->getFlow();
    }
    return flowToCity;
}


void checkWaterCity(Graph<Station*> g, const std::string& cityCode) {
    // Find the delivery station corresponding to the input city code
    Vertex<Station*>* target = nullptr;
    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation && deliveryStation->getCode() == cityCode) {
            target = v;
            break;
        }
    }

    // If the target delivery station is found, consult the flow
    if (target) {
        double cityFlow = 0.0;
        // Sum the incoming flow to the delivery station
        for (auto incomingEdge : target->getIncoming()) {
            cityFlow += incomingEdge->getFlow();
        }
        // Ensure the flow does not surpass the demand for the city
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(target->getInfo());

        std::cout << "Flow to city " << deliveryStation->getCity() << " (" << cityCode << "): " << cityFlow << std::endl;
    } else {
        std::cout << "City with code " << cityCode << " not found." << std::endl;
    }
}

void checkWaterSupply(Graph<Station*> g) {

    MaxFlowAlgo(g);
    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(g, v);

            std::string cityName = deliveryStation->getCity();
            std::string cityCode = deliveryStation->getCode();
            int cityDemand= deliveryStation->getDemand();
            std::cout << "Flow to city " << cityName << " (" << cityCode << "): " << cityFlow << std::endl;
            std::cout << "Demand to city " << cityName << " (" << cityCode << "): " << cityDemand << std::endl;
            if(cityDemand>cityFlow){
                std::cout << "The city of  " << cityName << " (" << cityCode << ") doesn't have enough water because : " << cityDemand - cityFlow << " m3/sec of water are missing." << std::endl;

            }
            else if (cityDemand>=cityFlow) {
                std::cout << "The city of  " << cityName << " (" << cityCode << ") has enough water because it has : " << cityDemand - cityFlow << " m3/sec more than it needs." << std::endl;

            }
        }
        std::cout << "\n" << std::endl;
    }

}

void App::run() {
    mainMenu();
}