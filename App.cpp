#include <iostream>
#include <cmath>
#include "reader.h"
#include "App.h"

using namespace std;

void display4_1menu(Graph<Station*>& graph,
                    const std::unordered_map<int, DeliveryStation*>& IdMap,
                    const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& NameMap);

void display4_2menu(Graph<Station*> graph,
                    std::unordered_map<int, WaterReservoir*> &wrIdMap,
                    std::unordered_map<std::string, WaterReservoir*> &wrCodeMap,
                    std::unordered_map<std::string, WaterReservoir*> &wrNameMap);

void maxFlowSubMenu(Graph<Station*>& graph,
                    const std::unordered_map<int, DeliveryStation*>& IdMap,
                    const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& NameMap);
void loadBalancingMenu(Graph<Station*>& graph,
                       const std::unordered_map<int, DeliveryStation*>& IdMap,
                       const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                       const std::unordered_map<std::string, DeliveryStation*>& NameMap);


double MaxFlowAlgo(Graph<Station*>& g);
bool hasFlows(Graph<Station*> g);
double getFlowToCity(Graph<Station*>& g, Vertex<Station*>* deliveryStation);
void PrintMaxFlowForCities(Graph<Station*>& graph, double totalFlow);


void checkWaterCity(Graph<Station*> g, const std::string& cityIdentifier,
                    const std::unordered_map<int, DeliveryStation*>& IdMap,
                    const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& NameMap);


void checkWaterSupply(Graph<Station*> g, const std::unordered_map<std::string, DeliveryStation*>& codeMap);

void computeInitialMetrics(Graph<Station*>& graph);
void showImprovedMetrics(Graph<Station*>& graph);
double calculateMaxDifference(Graph<Station*>& graph);
void balanceLoad(Graph<Station*>& graph);

void fillMap(Graph<Station*>& g, std::unordered_map<Vertex<Station*>*, double>& flowMap);
void removeWR(Graph<Station*>& g, std::unordered_map< Vertex<Station*>*, double>  &flowMap, Vertex<Station*> *wrVertex);

Vertex<Station*>* findWrId (Graph<Station*> &g, const std::string &wrIdentifier,
                            std::unordered_map<int, WaterReservoir*> &wrIdMap,
                            std::unordered_map<std::string, WaterReservoir*> &wrCodeMap,
                            std::unordered_map<std::string, WaterReservoir*> &wrNameMap);


int mainMenu(){
    cout << "Loading...";

    Reader reader;
    reader.readAndParsePS();
    reader.readAndParseWR();
    reader.readAndParseDS();
    reader.readAndParsePipes();
    reader.addSuperSourceAndSink();

    auto IdMap = reader.getIdMap();
    auto CodeMap = reader.getCodeMap();
    auto NameMap = reader.getNameMap();

    auto WrIdMap = reader.getWrIdMap();
    auto WrCodeMap = reader.getWrCodeMap();
    auto WrNameMap = reader.getWrNameMap();

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
                display4_1menu(graph,IdMap,CodeMap,NameMap);
                break;
            case '2':
                display4_2menu(graph, WrIdMap, WrCodeMap, WrNameMap);
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

void display4_1menu(Graph<Station*>& graph,
                    const std::unordered_map<int, DeliveryStation*>& IdMap,
                    const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& NameMap) {
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
                maxFlowSubMenu(graph, IdMap, CodeMap, NameMap); // pass maps to sub-menu
                break;
            case '2':
                checkWaterSupply(graph,CodeMap);
                break;
            case '3':
                loadBalancingMenu(graph,IdMap,CodeMap,NameMap);
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

void display4_2menu(Graph<Station*> graph,
                    std::unordered_map<int, WaterReservoir*> &wrIdMap,
                    std::unordered_map<std::string, WaterReservoir*> &wrCodeMap,
                    std::unordered_map<std::string, WaterReservoir*> &wrNameMap) {
    string choice;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n----------------------------------------------\n";
        cout << "    Reliability and Sensitivity to Failures       \n";
        cout << "----------------------------------------------\n";
        cout << "Select an option:\n";
        cout << "1. Verify Network's resiliency, water reservoir fails. (4.2.1)\n";
        cout << "2.  (4.2.2)\n";
        cout << "3.  (4.2.3)\n";
        cout << "b. Back to Main Menu\n";
        cout << "----------------------------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }
        string wrId;
        std::unordered_map< Vertex<Station*>*, double> flowMap;
        Vertex<Station*> * vertex = nullptr;
        switch (choice[0]) {
            case '1':
                cout << "Enter the Water Reservoir identifier (wrId,wrCode or wrName) ('b' to go back): ";
                cin >> wrId;
                if (wrId == "b") {
                    exitMenu = true;
                    break;
                }

                vertex = findWrId(graph,wrId,wrIdMap,wrCodeMap,wrNameMap);
                if(!vertex)
                {
                    cout << "Doesnt exist a node with that id";
                    break;
                }
                if(!vertex->getInfo()->isActive()){
                    cout << "Doesnt exist in graph";
                    break;
                }
                fillMap(graph, flowMap);
                removeWR(graph,flowMap,vertex);

                break;
            case '2':
                break;
            case '3':
                break;
            case 'b':
                cout << "Returning to Main Menu...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }
    for(auto v : graph.getVertexSet()){
        v->getInfo()->setActive(true);
    }
}

void maxFlowSubMenu(Graph<Station*>& graph,
                    const std::unordered_map<int, DeliveryStation*>& IdMap,
                    const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& NameMap) {
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
                cout << "Enter the city identifier (Id,Code or name) ('b' to go back): ";
                cin >> cityCode;
                if (cityCode == "b") {
                    exitMenu = true;
                    break;
                }
                checkWaterCity(graph, cityCode,IdMap,CodeMap,NameMap);
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

void loadBalancingMenu(Graph<Station*>& graph,
                       const std::unordered_map<int, DeliveryStation*>& IdMap,
                       const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                       const std::unordered_map<std::string, DeliveryStation*>& NameMap) {
    std::cout << "\n-----------------------------\n";
    std::cout << "   Load Balancing Algorithm    \n";
    std::cout << "-----------------------------\n";

    if(!hasFlows(graph)){
        MaxFlowAlgo(graph);
    }

    std::cout << "Computing initial metrics...\n";
    computeInitialMetrics(graph);

    std::cout << "Balancing the load across the network...\n";
    balanceLoad(graph);

    std::cout << "Showing improved metrics after load balancing...\n";
    showImprovedMetrics(graph);

    std::cout << "Load balancing completed.\n";

    display4_1menu(graph,IdMap,CodeMap,NameMap);
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

bool hasFlows(Graph<Station*> g){
    for(auto v : g.getVertexSet()){
        auto* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation){
            double flow = getFlowToCity(g,v);

            return !flow ? false : true;
        }
    }
    return false;
}

double getFlowToCity(Graph<Station*>& g, Vertex<Station*>* deliveryStation){
    double flowToCity = 0.0;
    for (auto incomingEdge : deliveryStation->getIncoming()) {
        flowToCity += incomingEdge->getFlow();
    }
    return flowToCity;
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

    int number_full_cities = 0;
    int number_unfilled_cities = 0;
    // Check flow for each city
    for (auto v : graph.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(graph, v);

            std::string cityName = deliveryStation->getCity();
            std::string cityCode = deliveryStation->getCode();
            std::cout << "Flow to city " << cityName << " (" << cityCode << "): " << cityFlow << std::endl;
            outputFile << "Flow to city " << cityName << " (" << cityCode << "): " << cityFlow << std::endl;
            if(cityFlow == deliveryStation->getDemand()) {
                number_full_cities++;
            }
            else{number_unfilled_cities++;}
        }
    }

    cout << "Full " << number_full_cities << endl;
    cout << "NOT FULL "<< number_unfilled_cities << endl;

    // Close the output file
    outputFile.close();
    std::cout << "Results saved to ../max_flow.txt" << std::endl;
}

void checkWaterCity(Graph<Station*> g, const std::string& cityIdentifier,
                    const std::unordered_map<int, DeliveryStation*>& idMap,
                    const std::unordered_map<std::string, DeliveryStation*>& codeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& nameMap) {
    // Find the delivery station corresponding to the input city identifier
    Vertex<Station*>* target = nullptr;
    DeliveryStation* deliveryStation = nullptr;

    // Check if the city identifier is an ID
    if (isdigit(cityIdentifier[0])) {
        int id = std::stoi(cityIdentifier);
        deliveryStation = Reader::getDeliveryStationById(id, idMap);
    }
        // Check if the city identifier is a code
    else if (codeMap.find(cityIdentifier) != codeMap.end()) {
        deliveryStation = Reader::getDeliveryStationByCode(cityIdentifier, codeMap);
    }
        // Check if the city identifier is a name
    else if (nameMap.find(cityIdentifier) != nameMap.end()) {
        deliveryStation = Reader::getDeliveryStationByName(cityIdentifier, nameMap);
    }

    if (deliveryStation) {
        double cityFlow = 0.0;
        for (auto v : g.getVertexSet()) {
            if (v->getInfo() == deliveryStation) {
                target = v;
                break;
            }
        }

        if (target) {
            for (auto incomingEdge : target->getIncoming()) {
                cityFlow += incomingEdge->getFlow();
            }
            std::cout << "Flow to city " << deliveryStation->getCity() << " (" << cityIdentifier << "): " << cityFlow << std::endl;
            return;
        }
    }
    std::cout << "City with identifier " << cityIdentifier << " not found." << std::endl;
}

void checkWaterSupply(Graph<Station*> g, const std::unordered_map<std::string, DeliveryStation*>& codeMap) {
    if (!hasFlows(g)) {
        MaxFlowAlgo(g);
    }

    int citiesWithEnoughWater = 0;
    std::vector<std::tuple<std::string, std::string, double>> citiesWithoutEnoughWater;

    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(g, v);
            std::string cityName = deliveryStation->getCity();
            std::string cityCode = deliveryStation->getCode();
            int cityDemand = deliveryStation->getDemand();
            if (cityDemand > cityFlow) {
                double deficit = cityDemand - cityFlow;
                citiesWithoutEnoughWater.push_back(std::make_tuple(cityName, cityCode, deficit));
            } else {
                citiesWithEnoughWater++;
            }
        }
    }
    std::cout << "Cities that don't fulfill their demand:\n";
    for(const auto& city : citiesWithoutEnoughWater) {
        std::string cityName = std::get<0>(city);
        std::string cityCode = std::get<1>(city);
        double deficit = std::get<2>(city);
        std::cout << "City: " << cityName << ", Code: " << cityCode << ", Deficit: " << deficit << " m3/sec\n";
    }

    std::cout << '\n';
    std::cout << "Number of cities that fulfill their demand: " << citiesWithEnoughWater << '\n';
    std::cout << "Number of cities that don't fulfill their demand: " << citiesWithoutEnoughWater.size() << '\n';
}

void computeInitialMetrics(Graph<Station*>& graph) {
    double totalDifference = 0.0;
    double maxDifference = std::numeric_limits<double>::min();
    Edge<Station*>* maxDiffEdge = nullptr;
    int pipeCount = 0;

    for (auto vertex : graph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            double capacity = edge->getWeight();
            double flow = edge->getFlow();

            double difference = capacity - flow;
            totalDifference += difference;

            if (difference > maxDifference) {
                maxDifference = difference;
                maxDiffEdge = edge;
            }

            pipeCount++;

            std::cout << "Pipe " << pipeCount << ": From " << edge->getOrig()->getInfo()->getCode()
                      << " to " << edge->getDest()->getInfo()->getCode() << ", Flow: " << flow << std::endl;
        }
    }

    double averageDifference = totalDifference / pipeCount;
    double variance = 0.0;

    for (auto vertex : graph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            double capacity = edge->getWeight();
            double flow = edge->getFlow();
            double difference = capacity - flow;
            variance += std::pow(difference - averageDifference, 2);
        }
    }

    variance /= pipeCount;

    std::cout << "Initial Metrics:" << std::endl;
    std::cout << "Average difference: " << averageDifference << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Maximum difference: " << maxDifference << std::endl;

    // Print information about the edge with maximum difference
    if (maxDiffEdge) {
        std::cout << "Edge with maximum difference:" << std::endl;
        std::cout << "From: " << maxDiffEdge->getOrig()->getInfo()->getCode() << " to "
                  << maxDiffEdge->getDest()->getInfo()->getCode() << std::endl;
        std::cout << "Capacity: " << maxDiffEdge->getWeight() << std::endl;
        std::cout << "Flow: " << maxDiffEdge->getFlow() << std::endl;
    }
}

void balanceLoad(Graph<Station*>& graph) {

}


void showImprovedMetrics(Graph<Station*>& graph) {
    computeInitialMetrics(graph);
}

Vertex<Station*>* findWrId (Graph<Station*> &g, const std::string &wrIdentifier,
                          std::unordered_map<int, WaterReservoir*> &wrIdMap,
                          std::unordered_map<std::string, WaterReservoir*> &wrCodeMap,
                          std::unordered_map<std::string, WaterReservoir*> &wrNameMap){

    WaterReservoir* waterReservoir = nullptr;
    if (isdigit(wrIdentifier[0])) {
        int id = std::stoi(wrIdentifier);
        waterReservoir = Reader::getWaterReservoirById(id, wrIdMap);
    }
        // Check if the waterReservoir identifier is a code
    else if (wrCodeMap.find(wrIdentifier) != wrCodeMap.end()) {
        waterReservoir = Reader::getWaterReservoirByCode(wrIdentifier, wrCodeMap);
    }
        // Check if the waterReservoir identifier is a name
    else if (wrNameMap.find(wrIdentifier) != wrNameMap.end()) {
        waterReservoir = Reader::getWaterReservoirByName(wrIdentifier, wrNameMap);
    }

    Vertex<Station*> *wrVertex = g.findVertex(waterReservoir);

    return wrVertex;

}
void fillMap(Graph<Station*>& g, std::unordered_map<Vertex<Station*>*, double>& flowMap) {
    if (!hasFlows(g)) {
        MaxFlowAlgo(g);
        for(auto vertex : g.getVertexSet()){
            vertex->setVisited(false);
        }
    }
    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(g, v);
            flowMap[v] = cityFlow;
        }
    }
}

void removeWR(Graph<Station*>& g, std::unordered_map<Vertex<Station*>*, double>& flowMap, Vertex<Station*>* wrVertex) {
    // Mark the vertex as visited to indicate removal

    // Use a set to track affected subset
    auto affectedSubset = findAffectedSubset(&g,wrVertex);

    Vertex<Station*>* superSink = nullptr;
    for (auto v : g.getVertexSet()) {
        if (v->getInfo()->getCode() == "SuperSink") {
            superSink = v;
            break; // No need to continue searching once found
        }
    }

    if (!superSink) {
        std::cerr << "Error: super sink not found." << std::endl;
        return;
    }

    double optimalLocal = initEdmondsKarp(&g, wrVertex->getInfo(), superSink->getInfo());

    for (auto v : affectedSubset) {
        if (flowMap.find(v) != flowMap.end()) {
            double originalValue = flowMap[v];
            double difference = originalValue - optimalLocal;
            flowMap[v] = difference;

            std::cout << "Node: " << v->getInfo()->getCode() << ", Flow Loss: " << difference;

            // Check if the vertex is a delivery station and if it meets demand after removal
            DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
            if (deliveryStation && difference < deliveryStation->getDemand()) {
                std::cout << " (Does not meet demand)";
            }

            std::cout << std::endl;
        }
    }

    wrVertex->getInfo()->setActive(false);
    flowMap.erase(wrVertex);
}




void App::run() {
    mainMenu();
}