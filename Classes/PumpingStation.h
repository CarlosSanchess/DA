#ifndef PROJ1_PUMPINGSTATION_H
#define PROJ1_PUMPINGSTATION_H

#include <string>

class PumpingStation {
public:
    PumpingStation(int id, std::string  code);

    int getId() const;
    std::string getCode() const;

private:
    int id;
    std::string code;
};

#endif //PROJ1_PUMPINGSTATION_H