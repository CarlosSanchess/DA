#ifndef PROJ1_PIPE_H
#define PROJ1_PIPE_H

#include <string>
using namespace std;

class Pipe {

private:
    string servicePointA;
    string servicePointB;
    int capacity;
    bool direction;

public:
    Pipe(string  servicePointA, string  servicePointB, int capacity, bool direction);

    string getServicePointA() const;
    string getServicePointB() const;
    int getCapacity() const;
    bool getDirection() const;
};

#endif //PROJ1_PIPE_H