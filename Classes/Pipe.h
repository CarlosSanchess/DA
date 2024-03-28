#ifndef PROJ1_PIPE_H
#define PROJ1_PIPE_H

#include <string>

/**
 * @brief The Pipe class represents a pipe connecting two service points.
 */
class Pipe {

private:
    std::string servicePointA; ///< The code of the first service point connected by the pipe.
    std::string servicePointB; ///< The code of the second service point connected by the pipe.
    int capacity; ///< The capacity of the pipe.
    bool direction; ///< The direction of flow through the pipe.

public:
    Pipe(std::string servicePointA, std::string servicePointB, int capacity, bool direction);

    std::string getServicePointA() const;

    std::string getServicePointB() const;

    int getCapacity() const;

    bool getDirection() const;
};

#endif //PROJ1_PIPE_H
