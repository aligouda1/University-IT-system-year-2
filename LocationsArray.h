#ifndef LOCATIONS_ARRAY_H
#define LOCATIONS_ARRAY_H

#include "Defs.h"
#include <string>

class LocationsArray {
private:
    Location* locArray;
    int numLocations;

public:
    LocationsArray();
    ~LocationsArray();

    void initLocations(int L);
    void setLocation(int lid, std::string name);
    std::string getLocationName(int lid) const;
    void printLocations() const;
    void clearLocations();
};

#endif
