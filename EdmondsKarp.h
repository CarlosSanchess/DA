//
// Created by David Ferreira on 11/03/2024.
//

#ifndef PROJ1_EDMONDSKARP_H
#define PROJ1_EDMONDSKARP_H
#include "Classes/Graph.h"
using namespace std;
template<class T>
class EdmondsKarp {
private:

public:
    EdmondsKarp();
    void testAndVisit(queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);
    bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t);
    double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);
    void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);
    void initEdmondsKarp(Graph<T> *g, int source, int target);

};


#endif //PROJ1_EDMONDSKARP_H
