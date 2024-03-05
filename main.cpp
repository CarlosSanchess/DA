#include "reader.h"
#include "Classes/Graph.h"

int main() {

    Reader r;
    r.readAndParsePS();
    r.readAndParseWR();
    r.readAndParseDS();
    r.readAndParsePipes();

    Graph<Station*> g = r.getGraph();
/*
        for(auto v: g.getVertexSet()){
            if(v->getInfo()->getCode() == "PS_4"){
                v->getAdj();
                v->getIncoming();
            }
        }
        */
    return 0;
}