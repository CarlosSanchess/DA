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
#include "Classes/WaterReservoir.h"
#include "Classes/Pipe.h"

class Reader {
private:
    Graph<Station*> graph;

public:
    Reader();

    void readAndParseDS();

    void readAndParsePS();

    void readAndParseWR();

    void readAndParsePipes();

    Station* getNode(const std::string& servicePoint);

};

#endif /* READER_H */