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
void balanceLoad(Graph<Station*>& graph);

void fillMap(Graph<Station*>& g, std::unordered_map<Vertex<Station*>*, double>& flowMap);
void removeWR(Graph<Station*>& g, Vertex<Station*>* wrVertex);

Vertex<Station*>* findWrId (Graph<Station*> &g, const std::string &wrIdentifier,
                            std::unordered_map<int, WaterReservoir*> &wrIdMap,
                            std::unordered_map<std::string, WaterReservoir*> &wrCodeMap,
                            std::unordered_map<std::string, WaterReservoir*> &wrNameMap);
void showDifference(Graph<Station*> g, std::unordered_map<Vertex<Station*>*, double>& flowMap, std::unordered_map<std::string, DeliveryStation*>& codeMap);
void restoreGraph(Graph<Station*> *g, std::unordered_map<std::string, double> initialWeights);
void pipelineFailure(Graph<Station*> &g, std::unordered_map<Vertex<Station*>*, double>& flowMap);
vector<Edge<Station *>*> getAllEdges(const Graph<Station*> &g);
void examinePumpingStations(Graph<Station*>& g);
void resetGraph(Graph<Station*>& graph);

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
                maxFlowSubMenu(graph, IdMap, CodeMap, NameMap);
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
                resetGraph(graph);
                examinePumpingStations(graph);
                break;
            case '3':
                resetGraph(graph);
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
    resetGraph(graph);
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

    MaxFlowAlgo(graph);

    std::cout << "Computing initial metrics...\n";
    computeInitialMetrics(graph);

    std::cout << "Balancing the load across the network...\n";
    balanceLoad(graph);

    std::cout << "Showing improved metrics after load balancing...\n";
    showImprovedMetrics(graph);

    std::cout << "Load balancing completed.\n";

    resetGraph(graph);

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

    Vertex<Station*>* superSource = nullptr;
    Vertex<Station*>* superSink = nullptr;

    findSuperSourceAndSuperSink(g,superSource,superSink);

    if (!superSource || !superSink) {
        std::cerr << "Error: Super source or super sink not found." << std::endl;
        return 0;
    }

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
    for (auto v : graph.getVertexSet()) {
        auto* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
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

    outputFile.close();
    std::cout << "Results saved to ../max_flow.txt" << std::endl;
}

void checkWaterCity(Graph<Station*> g, const std::string& cityIdentifier,
                    const std::unordered_map<int, DeliveryStation*>& idMap,
                    const std::unordered_map<std::string, DeliveryStation*>& codeMap,
                    const std::unordered_map<std::string, DeliveryStation*>& nameMap) {
    Vertex<Station*>* target = nullptr;
    DeliveryStation* deliveryStation = nullptr;

    if (isdigit(cityIdentifier[0])) {
        int id = std::stoi(cityIdentifier);
        deliveryStation = Reader::getDeliveryStationById(id, idMap);
    }
    else if (codeMap.find(cityIdentifier) != codeMap.end()) {
        deliveryStation = Reader::getDeliveryStationByCode(cityIdentifier, codeMap);
    }
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
        auto* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
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

    if (maxDiffEdge) {
        std::cout << "Edge with maximum difference:" << std::endl;
        std::cout << "From: " << maxDiffEdge->getOrig()->getInfo()->getCode() << " to "
                  << maxDiffEdge->getDest()->getInfo()->getCode() << std::endl;
        std::cout << "Capacity: " << maxDiffEdge->getWeight() << std::endl;
        std::cout << "Flow: " << maxDiffEdge->getFlow() << std::endl;
    }
}

void showImprovedMetrics(Graph<Station*>& graph) {
    computeInitialMetrics(graph);
}


void balanceLoad(Graph<Station*>& graph) {
    double totalDifference = 0.0;
    int pipeCount = 0;
    double sumSquaredDifferences = 0.0;

    // Step 1: Calculate initial metrics
    for (auto vertex : graph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            double capacity = edge->getWeight();
            double flow = edge->getFlow();
            double difference = capacity - flow;
            totalDifference += difference;
            sumSquaredDifferences += difference * difference;
            pipeCount++;
        }
    }

    // Calculate average difference and variance
    double averageDifference = totalDifference / pipeCount;
    double variance = sumSquaredDifferences / pipeCount - (averageDifference * averageDifference);

    // Step 2: Identify pipes with flow less than capacity
    std::vector<Edge<Station*>*> underflowPipes;
    for (auto vertex : graph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            double capacity = edge->getWeight();
            double flow = edge->getFlow();
            if (capacity > flow) {
                underflowPipes.push_back(edge);
            }
        }
    }

    // Step 3: Sort underflow pipes by the difference between capacity and flow
    std::sort(underflowPipes.begin(), underflowPipes.end(), [](Edge<Station*>* a, Edge<Station*>* b) {
        return (a->getWeight() - a->getFlow()) > (b->getWeight() - b->getFlow());
    });

    // Step 4: Redistribute flow
    for (auto edge : underflowPipes) {
        double currentDifference = edge->getWeight() - edge->getFlow();
        if (currentDifference > averageDifference) {
            double adjustmentFactor = sqrt(variance / (2 * pipeCount)); // Adjust according to variance
            double targetFlow = edge->getWeight() - (averageDifference + adjustmentFactor);
            // Set flow to the target value
            edge->setFlow(targetFlow);
        }
    }
    
    // Step 6: Calculate total flow incoming to delivery stations after balancing
    double totalFlowToDeliveryStations = 0.0;
    for (auto vertex : graph.getVertexSet()) {
        if (auto deliveryStation = dynamic_cast<DeliveryStation*>(vertex->getInfo())) {
            totalFlowToDeliveryStations += getFlowToCity(graph, vertex);
        }
    }

    // Output total flow incoming to delivery stations
    std::cout << "Total flow incoming to delivery stations after balancing: " << totalFlowToDeliveryStations << std::endl;
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
    else if (wrCodeMap.find(wrIdentifier) != wrCodeMap.end()) {
        waterReservoir = Reader::getWaterReservoirByCode(wrIdentifier, wrCodeMap);
    }
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
        auto* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(g, v);
            flowMap[v] = cityFlow;
        }
    }
}
void showDifference(Graph<Station*> g, std::unordered_map<Vertex<Station*>*, double>& flowMap, std::unordered_map<std::string, DeliveryStation*>& codeMap){
    int affectedCities = 0;
    std::vector<std::string> affectedCityCodes;

    for (auto v : g.getVertexSet()) {
        auto* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double originalValue = flowMap[v];
            double newValue = getFlowToCity(g, v);

            if (newValue < originalValue) { // Check for deficit
                DeliveryStation* station = Reader::getDeliveryStationByCode(v->getInfo()->getCode(), codeMap);
                std::string stationName = (station != nullptr) ? (station->getCity() + " (" + station->getCode() + ")") : "Unknown";

                std::cout << stationName << std::endl;
                std::cout << "Old Flow: "<< originalValue << std::endl;
                std::cout << "New Flow: " << newValue << std::endl;
                std::cout << "Deficit: " << originalValue - newValue << std::endl;
                std::cout << "\n";
                flowMap[v] = newValue;

                affectedCities++;
                affectedCityCodes.push_back(station->getCode());
            }
        }
    }

    std::cout << "Total affected cities: " << affectedCities << std::endl;

    std::cout << "Affected city codes: (";
    for (size_t i = 0; i < affectedCityCodes.size(); ++i) {
        std::cout << affectedCityCodes[i];
        if (i < affectedCityCodes.size() - 1) {
            std::cout << ", ";
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

void resetGraph(Graph<Station*>& graph) {
    for(auto v : graph.getVertexSet()){
        v->getInfo()->setActive(true);
        for(auto e : v->getAdj()){
            e->setFlow(0.0);
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
    double initialWeight;

    for(auto e : allEdges) {

        initialWeight = e->getWeight();
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
                    cout << "Pipe:(" << e->getOrig()->getInfo()->getCode() << "," << e->getDest()->getInfo()->getCode() << ")" << endl;
                    cout << "We cant deliver the desired amount, to City:" << deliveryStation->getCity() << endl;
                    cout << "Flow Before:" << oldFlow << " Flow After:" << newFlow << " Deficit:" << oldFlow - newFlow << endl;
                }
            }
        }
        e->setWeight(initialWeight);
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

    fillMap(g, initialFlowMap);

    std::unordered_map<Vertex<Station*>*, std::unordered_map<Edge<Station*>*, double>> originalWeights;

    for (auto v : g.getVertexSet()) {
        if (v == superSource || v == superSink) {
            continue;
        }

        if (!dynamic_cast<DeliveryStation*>(v->getInfo()) && !dynamic_cast<WaterReservoir*>(v->getInfo())) {
            std::unordered_map<Edge<Station*>*, double> stationOriginalWeights;
            for (auto edge : v->getIncoming()) {
                stationOriginalWeights[edge] = edge->getWeight();
            }
            originalWeights[v] = std::move(stationOriginalWeights);
        }
    }

    int pumpsWithoutDeficit = 0;
    std::string pumpsWithoutDeficitCodes;
    for (auto pumpingStation : originalWeights) {
        for (auto& entry : pumpingStation.second) {
            entry.first->setWeight(0);
        }

        std::unordered_map<Vertex<Station*>*, double> stationFlowMap;
        fillMap(g, stationFlowMap);

        std::unordered_map<Vertex<Station*>*, double> stationDifferenceMap;
        bool deficitFound = false;
        for (auto& entry : stationFlowMap) {
            auto* deliveryStation = dynamic_cast<DeliveryStation*>(entry.first->getInfo());
            if (deliveryStation) {
                double deficit = initialFlowMap[entry.first] - entry.second;
                if (deficit > 0) {
                    deficitFound = true;
                    stationDifferenceMap[entry.first] = deficit;
                }
            }
        }

        if (deficitFound) {
            std::cout << "Pumping Station: " << pumpingStation.first->getInfo()->getCode() << std::endl;
            for (auto& entry : stationDifferenceMap) {
                Vertex<Station*>* stationVertex = entry.first;
                auto* station = dynamic_cast<DeliveryStation*>(stationVertex->getInfo());
                if (station) {
                    std::string cityName = station->getCity();
                    std::cout << "City Name: " << cityName << " (" << station->getCode() << "), Water Supply Deficit: " << entry.second << std::endl;
                    std::cout << "Old Flow: " << initialFlowMap[entry.first] << ", New Flow: " << stationFlowMap[entry.first] << std::endl;
                }
            }
            std::cout << "----------------------------------------" << std::endl;
        }

        for (auto& entry : pumpingStation.second) {
            entry.first->setWeight(entry.second);
        }

        if (!deficitFound) {
            pumpsWithoutDeficit++;
            pumpsWithoutDeficitCodes += (pumpsWithoutDeficitCodes.empty() ? "" : ", ") + pumpingStation.first->getInfo()->getCode();
        }
    }

    std::cout << "Number of pumping stations that can be removed without any water deficit: " << pumpsWithoutDeficit << " (" << pumpsWithoutDeficitCodes << ")" << std::endl;
}


void App::run() {
    mainMenu();
}