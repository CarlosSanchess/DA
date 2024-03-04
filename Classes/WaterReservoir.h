#ifndef PROJ1_WATERRESERVOIR_H
#define PROJ1_WATERRESERVOIR_H

#include <string>
using namespace std;

class WaterReservoir {
private:
    string reservoirName;
    string municipality;
    int id;
    string code;
    int maxDelivery;
public:
    WaterReservoir(string  name, string  municipality, int reservoirId, string  reservoirCode, int maxDel);

    string getReservoirName() const;
    string getMunicipality() const;
    int getId() const;
    string getCode() const;
    int getMaxDelivery() const;

    void setReservoirName(const string &name);
    void setMunicipality(const string &municipality);
    void setId(int id);
    void setCode(const string &code);
    void setMaxDelivery(int maxDelivery);
};

#endif //PROJ1_WATERRESERVOIR_H