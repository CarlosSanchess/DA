#ifndef PROJ1_STATION_H
#define PROJ1_STATION_H

#include <string>

class Station {
protected:
    int id;
    std::string code;
    bool active;
public:
    Station(int id, std::string code);
    virtual ~Station();

    int getId() const;
    std::string getCode() const;
    void setActive(bool active);
    bool isActive() const;
};


#endif //PROJ1_STATION_H