#ifndef READERH
#define READERH

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "Classes/DeliveryStation.h"
#include "Classes/Station.h"
#include "Classes/Graph.h"

class Reader {
private:
    Graph<Station*> graph;

public:
    Reader();

    void readAndParseDS();

    void readAndParsePS();

    void readAndParseWR();

    void readAndParsePipes();

};

#endif /* READER_H */