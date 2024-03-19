#include "reader.h"
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
    return optimalFlow;
}



void exercicio4_2(Graph<Station*> g){
    for(auto v: g.getVertexSet()){
        auto ptr = dynamic_cast<DeliveryStation*>(v->getInfo());
        if (ptr != nullptr) {
            double aux = 0;
            for(auto p : v->getIncoming()) {
                aux += p->getWeight();
            }
            aux = aux - ptr->getDemand();
            if(aux < 0){
                std::cout << "(" << ptr->getCode() << "," << aux << ")" << std::endl;
            }
        }
    }
}
int main() {

    Reader r;
    r.readAndParsePS();
    r.readAndParseWR();
    r.readAndParseDS();
    r.readAndParsePipes();

    Graph<Station*> g = r.getGraph();
    bool play =true;

    while(play) {

        std::cout << "Print the city you want : ";
        std::string city;
        std::cin >> city;
        if(city == "exit"){
            play = false;
            break;
        }


        int max = -999;
        Vertex<Station *> src = Vertex<Station *>(nullptr);


        // ver o reservatorio que necessita mais de agua ( para tornar a soluçao mais otima )

        // Falta a garantir que o flow não é superior ao capacity do src



        Vertex<Station *> target = Vertex<Station *>(nullptr);

        for (auto v: g.getVertexSet()) {
            DeliveryStation *deliveryStation = dynamic_cast<DeliveryStation *>(v->getInfo());
            if (deliveryStation != nullptr) {
                if (deliveryStation->getCity() == city) {
                    target = *v;
                }
            }
        }
        double optimalFlow = 0.0;


        for (auto v: g.getVertexSet()) {
            if (v->getInfo()->getCode() == "R_" + std::to_string(v->getInfo()->getId())) {
                optimalFlow = initEdmondsKarp(&g, v->getInfo(), target.getInfo());
                if (optimalFlow > max) {
                    max = optimalFlow;
                    src = *v;

                }
            }
        }

        std::cout << "Optimal Flow is " << max << std::endl;


    }

    return 0;
}


