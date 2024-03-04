#ifndef PROJ1_WATERRESERVOIR_H
#define PROJ1_WATERRESERVOIR_H

#include <string>

class WaterReservoir {
private:
    std::string reservoirName;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery;
public:
    WaterReservoir(std::string  name, std::string  municipality, int reservoirId, std::string  reservoirCode, int maxDel);

    std::string getReservoirName() const;
    std::string getMunicipality() const;
    int getId() const;
    std::string getCode() const;
    int getMaxDelivery() const;

    void setReservoirName(const std::string &name);
    void setMunicipality(const std::string &municipality);
    void setId(int id);
    void setCode(const std::string &code);
    void setMaxDelivery(int maxDelivery);
};

#endif //PROJ1_WATERRESERVOIR_H