#ifndef PROJ1_STATION_H
#define PROJ1_STATION_H

#include <string>

/**
 * @brief The Station class represents a generic station in the network.
 */
class Station {
protected:
    int id; /**< The unique identifier of the station. */
    std::string code; /**< The code identifying the station. */
    bool active; /**< Indicates whether the station is active or not. */

public:
    Station(int id, std::string code);
    virtual ~Station();

    int getId() const;
    std::string getCode() const;
    void setActive(bool active);
    bool isActive() const;
};


#endif //PROJ1_STATION_H