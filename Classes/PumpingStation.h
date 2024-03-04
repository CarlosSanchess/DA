#ifndef PROJ1_PUMPINGSTATION_H
#define PROJ1_PUMPINGSTATION_H

#include <string>
using namespace std;

class PumpingStation {
public:
    PumpingStation(int id, string  code);

    int getId() const;
    string getCode() const;

private:
    int id;
    string code;
};

#endif //PROJ1_PUMPINGSTATION_H