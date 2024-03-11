//
// Created by David Ferreira on 11/03/2024.
//

#include "EdmondsKarp.h"


template <class T>
void EdmondsKarp<T>::testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {

    if (! w->isVisited() && residual > 0) {

        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

template <class T>
bool EdmondsKarp<T>::findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {

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
double EdmondsKarp<T>::findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
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
void EdmondsKarp<T>::augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {

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
void EdmondsKarp<T>::initEdmondsKarp(Graph<T> *g, int source, int target) {

    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    for (auto v : g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}
