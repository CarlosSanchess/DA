#include "reader.h"
#include "Classes/Station.h"
#include "Classes/Graph.h"


//
// Created by David Ferreira on 11/03/2024.
//




template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {

    if (! w->isVisited() && residual > 0) {

        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {

    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    s->setVisited(true);
    std::queue<Vertex<T> *> q;
    q.push(s);

    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();

        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }

        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }

    return t->isVisited();
}

template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;

    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }

    return f;
}

template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {

    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}
template <class T>
double initEdmondsKarp(Graph<T> *g, Station * source, Station * target) {

    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    for (auto v : g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    double optimalFlow = 0.0;
    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
        optimalFlow += f;
    }

    for (auto v : g->getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(*g, v);
            if (cityFlow > deliveryStation->getDemand()) {
                // Reduce flow to match city demand
                double excessFlow = cityFlow - deliveryStation->getDemand();
                // Find outgoing edges and reduce their flow proportionally
                double reductionFactor = excessFlow / cityFlow;
                for (auto outgoingEdge : v->getAdj()) {
                    double edgeFlow = outgoingEdge->getFlow();
                    double reducedFlow = edgeFlow * (1 - reductionFactor);
                    outgoingEdge->setFlow(reducedFlow);
                }
            }
        }
    }
    for (auto v : g->getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = getFlowToCity(*g, v);
            if (cityFlow > deliveryStation->getDemand()) {
                // Reduce flow to match city demand
                double excessFlow = cityFlow - deliveryStation->getDemand();
                // Find outgoing edges and reduce their flow proportionally
                double reductionFactor = excessFlow / cityFlow;
                for (auto outgoingEdge : v->getAdj()) {
                    double edgeFlow = outgoingEdge->getFlow();
                    double reducedFlow = edgeFlow * (1 - reductionFactor);
                    outgoingEdge->setFlow(reducedFlow);
                }
            }
        }
    }

    return optimalFlow;
}

double getFlowToCity(Graph<Station*>& g, Vertex<Station*>* deliveryStation) {
    double flowToCity = 0.0;
    // Sum the incoming flow to the delivery station
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
        if (deliveryStation && cityFlow > deliveryStation->getDemand()) {
            cityFlow = deliveryStation->getDemand(); // Set flow equal to demand
        }
        std::cout << "Flow to city " << deliveryStation->getCity() << " (" << cityCode << "): " << cityFlow << std::endl;
    } else {
        std::cout << "City with code " << cityCode << " not found." << std::endl;
    }
}




void checkWaterCity_each(Graph<Station*> g) {
    // Output file to save results
    std::ofstream outputFile("../max_flow.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }

    std::cout << "Calculating maximum water flow for each city..." << std::endl;

    // Add super source and super sink to the graph
    Reader reader; // Assuming Reader is properly defined and accessible
    reader.addSuperSourceAndSink();

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
        outputFile.close();
        return;
    }

    // Run the Max Flow Algorithm on the Entire Graph
    double totalFlow = initEdmondsKarp(&g, superSource->getInfo(), superSink->getInfo());

    // Output total flow from super source to super sink
    std::cout << "Total maximum flow of the network : " << totalFlow << std::endl;
    outputFile << "Total maximum flow of the network : " << totalFlow << std::endl;

    // Check flow for each city
    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation) {
            double cityFlow = 0.0;
            // Sum the incoming flow to the delivery station
            for (auto incomingEdge : v->getIncoming()) {
                cityFlow += incomingEdge->getFlow();
            }
            // Ensure the flow does not surpass the demand for the city
            if (cityFlow > deliveryStation->getDemand()) {
                cityFlow = deliveryStation->getDemand(); // Set flow equal to demand
            }
            // Output flow for the city
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


void checkWaterSupply(Graph<Station*> g) {
    for (auto v : g.getVertexSet()) {
        DeliveryStation* deliveryStation = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (deliveryStation != nullptr) {
            double capacityDelivered = 0.0;
            for (auto incomingEdge : v->getIncoming()) {
                capacityDelivered += incomingEdge->getFlow();
            }
            double deficit = deliveryStation->getDemand() - capacityDelivered;
            std::cout << "Cidade: " << deliveryStation->getCity() << std::endl;
            std::cout << "Quantidade de água disponível: " << capacityDelivered << " m³" << std::endl;
            std::cout << "Diferença entre a água disponível e a demanda: " << deficit << " m³" << std::endl;
            std::cout << std::endl;
        }
    }
}



int main() {
    Reader r;
    r.readAndParsePS();
    r.readAndParseWR();
    r.readAndParseDS();
    r.readAndParsePipes();
    r.addSuperSourceAndSink();

    Graph<Station*> g = r.getGraph();

    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Determine the maximum amount of water" << std::endl;
    std::cout << "2. Check water supply for each city" << std::endl;

    int option = 0;
    std::cin >> option;

    if (option == 1) {
        // Run the maximum flow algorithm
        checkWaterCity_each(g);

        // Ask the user for a specific city to check
        std::string cityCode;
        std::cout << "Enter the code of the city you want to check: ";
        std::cin >> cityCode;

        // Check water flow for the specified city
        checkWaterCity(g, cityCode);
    } else if (option == 2) {
        // Check water supply for each city
        checkWaterSupply(g);
    } else {
        std::cout << "Invalid option. Please choose either 1 or 2." << std::endl;
    }

    return 0;
}









