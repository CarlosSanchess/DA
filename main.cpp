#include "reader.h"
#include "Classes/Graph.h"

int main() {

    Reader r;
    r.readAndParsePS();
    r.readAndParseWR();
    r.readAndParseDS();
    r.readAndParsePipes();

    Graph<Station*> g = r.getGraph();


    return 0;
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
