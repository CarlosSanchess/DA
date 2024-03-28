#include <iostream>
#include <cmath>
#include <utility>
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
                    std::unordered_map<std::string, WaterReservoir*> &wrNameMap,
                    std::unordered_map<std::string, double> initialWeights,std::unordered_map<std::string, DeliveryStation*>& CodeMap);

void maxFlowSubMenu(Graph<Station*>& graph,
                    const std::unordered_map<int, DeliveryStation*>& IdMap,
                    const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& NameMap);
void loadBalancingMenu(Graph<Station*>& graph,
                       const std::unordered_map<int, DeliveryStation*>& IdMap,
                       const std::unordered_map<std::string, DeliveryStation*>& CodeMap,
                       const std::unordered_map<std::string, DeliveryStation*>& NameMap);


void findSuperSourceAndSuperSink(Graph<Station*>& graph, Vertex<Station*>*& superSource, Vertex<Station*>*& superSink);
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
void removeWR(Graph<Station*>& g, Vertex<Station*>* wrVertex);

Vertex<Station*>* findWrId (Graph<Station*> &g, const std::string &wrIdentifier,
                            std::unordered_map<int, WaterReservoir*> &wrIdMap,
                            std::unordered_map<std::string, WaterReservoir*> &wrCodeMap,
                            std::unordered_map<std::string, WaterReservoir*> &wrNameMap);
void showDifference(Graph<Station*> g, std::unordered_map<Vertex<Station*>*, double>& flowMap, std::unordered_map<std::string, DeliveryStation*>& codeMap);
void restoreGraph(Graph<Station*> *g, std::unordered_map<std::string, double> initialWeights);
<<<<<<< HEAD
void pipelineFailure(Graph<Station*> &g, std::unordered_map<Vertex<Station*>*, double>& flowMap);
vector<Edge<Station *>*> getAllEdges(const Graph<Station*> &g);

=======
void examinePumpingStations(Graph<Station*>& g);
>>>>>>> 88cc37284e64acefcc042a4b448469156e8fd73f

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

    auto EdgeWeightMap = reader.getEdgeWeightMap();
    auto PipeWeightVector = reader.getpipeWeighVector();

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
                display4_2menu(graph, WrIdMap, WrCodeMap, WrNameMap, EdgeWeightMap,CodeMap);
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
                    std::unordered_map<std::string, WaterReservoir*> &wrNameMap,
                    std::unordered_map<std::string, double> initialWeights,std::unordered_map<std::string, DeliveryStation*>& CodeMap){
    string choice;
    bool exitMenu = false;

    for(auto v : graph.getVertexSet()){
        for(auto e : v->getAdj()){
            e->setFlow(0.0);
        }
    }

    Vertex<Station*>* superSource = nullptr;
    Vertex<Station*>* superSink = nullptr;

    findSuperSourceAndSuperSink(graph,superSource,superSink);
    std::unordered_map<Vertex<Station*>*, double> flowBefore;
    fillMap(graph,flowBefore);

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
                if(!vertex->getInfo()->isActive()) {
                    cout << "Doesnt exist in graph";
                    break;
                }
                removeWR(graph,vertex);
                initEdmondsKarp(&graph,superSource->getInfo(),superSink->getInfo());
                showDifference(graph, flowBefore,CodeMap);
                break;
            case '2':
                examinePumpingStations(graph);
                break;
            case '3':
                pipelineFailure(graph, flowBefore);
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
        for(auto e : v->getAdj()){
            e->setFlow(0.0);
        }
    }
    restoreGraph(&graph, std::move(initialWeights));
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

void findSuperSourceAndSuperSink(Graph<Station*>& graph, Vertex<Station*>*& superSource, Vertex<Station*>*& superSink) {
    for (auto v : graph.getVertexSet()) {
        if (v->getInfo()->getCode() == "SuperSource") {
            superSource = v;
        } else if (v->getInfo()->getCode() == "SuperSink") {
            superSink = v;
        }
    }
}


double MaxFlowAlgo(Graph<Station*>& g) {

    // Find super source and super sink
    Vertex<Station*>* superSource = nullptr;
    Vertex<Station*>* superSink = nullptr;

    findSuperSourceAndSuperSink(g,superSource,superSink);

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

    MaxFlowAlgo(g);

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

    for(auto v:graph.getVertexSet()){
        int n=0;
        int sumflow=0;
        for (auto e:v->getAdj()){
            n++;
            sumflow+=e->getFlow();
        }
        for(auto e:v->getAdj()){
            e->setFlow(sumflow/n);
        }
    }
}


void showImprovedMetrics(Graph<Station*>& graph) {

    std::cout << "Improve Metrics:" << std::endl;
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

    std::cout << "Improve Metrics:" << std::endl;
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

void removeWR(Graph<Station*>& g, Vertex<Station*>* wrVertex){

    Vertex<Station*>* superSource = nullptr;

    for (auto v : g.getVertexSet()) {
        if (v->getInfo()->getCode() == "SuperSource") {
            superSource = v;
        }
    }
    if(!superSource){
        std::cerr << "Didn't find the superSource \n";
        return;
    }
    for (auto edge : superSource->getAdj()) {
        if (edge->getDest() == wrVertex) {
            edge->setWeight(0);
        }
    }
}
void fillMap(Graph<Station*>& g, std::unordered_map<Vertex<Station*>*, double>& flowMap) {

    MaxFlowAlgo(g);

    for(auto vertex : g.getVertexSet()){
        vertex->setVisited(false);
    }
    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(g, v);
            flowMap[v] = cityFlow;
        }
    }
}
void showDifference(Graph<Station*> g, std::unordered_map<Vertex<Station*>*, double>& flowMap, std::unordered_map<std::string, DeliveryStation*>& codeMap){
    int affectedCities = 0; // Counter for affected cities
    std::vector<std::string> affectedCityCodes; // Vector to store affected city codes
    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double originalValue = flowMap[v];
            double newValue = getFlowToCity(g, v);

            DeliveryStation* station = Reader::getDeliveryStationByCode(v->getInfo()->getCode(), codeMap);
            std::string stationName = (station != nullptr) ? station->getCity() : "Unknown";

            std::cout << stationName << std::endl;
            std::cout << "Current Flow: "<< originalValue << std::endl;
            std::cout << "Loss after removal: " << originalValue - newValue << std::endl;
            std::cout << "\n";
            flowMap[v] = newValue;

            // Check if flow is affected (difference is non-zero)
            if (newValue != originalValue) {
                affectedCities++; // Increment affected cities counter
                affectedCityCodes.push_back(station->getCode()); // Store affected city code
            }
        }
    }

    // Print total affected cities
    std::cout << "Total affected cities: " << affectedCities << std::endl;

    // Print affected city codes inside parentheses
    std::cout << "Affected city codes: (";
    for (size_t i = 0; i < affectedCityCodes.size(); ++i) {
        std::cout << affectedCityCodes[i];
        if (i < affectedCityCodes.size() - 1) {
            std::cout << ", "; // Add comma if not the last element
        }
    }
    std::cout << ")" << std::endl;
}
void restoreGraph(Graph<Station*> *g, std::unordered_map<std::string, double> initialWeights){
    Vertex<Station*>* superSource = nullptr;
    for (auto v : g->getVertexSet()) {
        if (v->getInfo()->getCode() == "SuperSource") {
            superSource = v;
        }
    }
    if(!superSource){
        std::cerr << "Didn't find the superSource \n";
        return;
    }
    for (auto edge : superSource->getAdj()) {
        std::string code = edge->getDest()->getInfo()->getCode();
        if (initialWeights.find(code) != initialWeights.end()){
            edge->setWeight(initialWeights[code]);
        }
    }
}

void pipelineFailure(Graph<Station*> &g, std::unordered_map<Vertex<Station*>*, double>& flowMap){
    std::vector<std::pair<Pipe, std::pair<std::string ,double>>> dataStructure;

    Vertex<Station*>* superSource = nullptr;
    Vertex<Station*>* superSink = nullptr;
    findSuperSourceAndSuperSink(g,superSource, superSink);
    fillMap(g, flowMap);

    vector<Edge<Station *>*> allEdges = getAllEdges(g);
    double initalWeight;

    for(auto e : allEdges) {

        initalWeight = e->getWeight();
        if(e->getDest()->getInfo()->getCode() == "C_17"){
            int a = 0;
        }
        e->setWeight(0);
        initEdmondsKarp(&g, superSource->getInfo(), superSink->getInfo());

        for(auto v : g.getVertexSet()) {
            auto *deliveryStation = dynamic_cast<DeliveryStation *>(v->getInfo());

            if(deliveryStation) {
                double demand = deliveryStation->getDemand();
                double oldFlow = flowMap[v];
                if (demand > oldFlow) {
                    continue;
                }
                double newFlow = getFlowToCity(g, v);
                if( demand > newFlow) {
                    cout << "---------------------------\n";
                    cout << "City:" << deliveryStation->getCity() << endl;
                    cout << "We cant deliver the desired amount, when we remove Pipes:\n";
                    cout << "(" << e->getOrig()->getInfo()->getCode() << "," << e->getDest()->getInfo()->getCode()  << ") old: " << oldFlow << " New Flow:" << newFlow << " Loss:" << oldFlow - newFlow << endl;

                }
            }
        }
        e->setWeight(initalWeight);
    }
}

vector<Edge<Station *>*> getAllEdges(const Graph<Station*>& g){

    vector<Edge<Station *>*> vector;

    for(auto v : g.getVertexSet()){
        for(auto e : v->getAdj()){
            if(!e->isSelected() && e->getOrig()->getInfo()->getId() != -1 && e->getDest()->getInfo()->getId() != -2){
                vector.push_back(e);
                e->setSelected(true);
            }
        }
    }
    return vector;
}

void examinePumpingStations(Graph<Station*>& g) {
    Vertex<Station*>* superSource = nullptr;
    Vertex<Station*>* superSink = nullptr;

    findSuperSourceAndSuperSink(g, superSource, superSink);

    std::unordered_map<Vertex<Station*>*, double> initialFlowMap;

    // Fill initial flow map before modifying weights
    fillMap(g, initialFlowMap);

    std::unordered_map<Vertex<Station*>*, std::unordered_map<Edge<Station*>*, double>> originalWeights;

    // Store original weights of incoming edges for each pumping station
    for (auto v : g.getVertexSet()) {
        if (v == superSource || v == superSink) {
            continue;
        }

        if (!dynamic_cast<DeliveryStation*>(v->getInfo()) && !dynamic_cast<WaterReservoir*>(v->getInfo())) {
            // If the vertex is not a delivery station or water reservoir, it's a pumping station
            std::unordered_map<Edge<Station*>*, double> stationOriginalWeights;
            for (auto edge : v->getIncoming()) {
                stationOriginalWeights[edge] = edge->getWeight();
            }
            originalWeights[v] = std::move(stationOriginalWeights);
        }
    }

    // Iterate over pumping stations
    int pumpsWithoutDeficit = 0; // Counter for pumping stations without any water deficit
    std::string pumpsWithoutDeficitCodes; // String to store the codes of pumping stations without deficit
    for (auto pumpingStation : originalWeights) {
        // Set weights of incoming edges to 0 for the pumping station
        for (auto& entry : pumpingStation.second) {
            entry.first->setWeight(0);
        }

        // Fill the flowMap after setting weights to 0 for the pumping station
        std::unordered_map<Vertex<Station*>*, double> stationFlowMap;
        fillMap(g, stationFlowMap);

        // Calculate water supply deficits for delivery stations
        std::unordered_map<Vertex<Station*>*, double> stationDifferenceMap;
        bool deficitFound = false; // Flag to indicate if any water deficit is found
        for (auto& entry : stationFlowMap) {
            DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(entry.first->getInfo());
            if (deliveryStation) {
                // Calculate water supply deficit for the delivery station using initial and station flow maps
                double deficit = initialFlowMap[entry.first] - entry.second;
                stationDifferenceMap[entry.first] = deficit;
                if (deficit > 0) {
                    deficitFound = true;
                }
            }
        }

        // Print affected cities and their water supply deficits
        std::cout << "Pumping Station: " << pumpingStation.first->getInfo()->getCode() << std::endl;
        for (auto& entry : stationDifferenceMap) {
            Vertex<Station*>* stationVertex = entry.first;
            DeliveryStation* station = dynamic_cast<DeliveryStation*>(stationVertex->getInfo());
            if (station) {
                std::string cityName = station->getCity(); // Assuming DeliveryStation has a getCode() method
                std::cout << "City Name: " << cityName << ", Water Supply Deficit: " << entry.second << std::endl;
            }
        }

        // Restore original weights of incoming edges for the pumping station
        for (auto& entry : pumpingStation.second) {
            entry.first->setWeight(entry.second);
        }

        // Separate each new pumping station with a line of dashes
        std::cout << "----------------------------------------" << std::endl;

        // Increment the counter if no water deficit is found and append the code to the string
        if (!deficitFound) {
            pumpsWithoutDeficit++;
            pumpsWithoutDeficitCodes += (pumpsWithoutDeficitCodes.empty() ? "" : ", ") + pumpingStation.first->getInfo()->getCode();
        }
    }

    // Print the number of pumping stations without any water deficit and their codes
    std::cout << "Number of pumping stations that can be removed without any water deficit: " << pumpsWithoutDeficit << " (" << pumpsWithoutDeficitCodes << ")" << std::endl;
}


void App::run() {
    mainMenu();
}