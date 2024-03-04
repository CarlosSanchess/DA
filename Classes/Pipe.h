#ifndef PROJ1_PIPE_H
#define PROJ1_PIPE_H

#include <string>


class Pipe {

private:
    std::string servicePointA;
    std::string servicePointB;
    int capacity;
    bool direction;

public:
    Pipe(std::string  servicePointA, std::string  servicePointB, int capacity, bool direction);

    std::string getServicePointA() const;
    std::string getServicePointB() const;
    int getCapacity() const;
    bool getDirection() const;
};

#endif //PROJ1_PIPE_H