#include "LocationsArray.h"
#include <iostream>

using namespace std;

LocationsArray::LocationsArray() {
    locArray = nullptr;
    numLocations = 0;
}

LocationsArray::~LocationsArray() {
    clearLocations();
}

void LocationsArray::initLocations(int L) {
    numLocations = L;
    locArray = new Location[L + 1]; 
}

void LocationsArray::setLocation(int lid, string name) {
    if (lid >= 1 && lid <= numLocations) {
        locArray[lid].LID = lid;
        locArray[lid].name = name;
    }
}

string LocationsArray::getLocationName(int lid) const {
    if (lid >= 1 && lid <= numLocations) {
        return locArray[lid].name;
    }
    return "Unknown";
}

void LocationsArray::printLocations() const {
    for (int i = 1; i <= numLocations; i++) {
        cout << "LID: " << locArray[i].LID 
             << " | Name: " << locArray[i].name << "\n";
    }
}

void LocationsArray::clearLocations() {
    if (locArray != nullptr) {
        delete[] locArray;
        locArray = nullptr;
        numLocations = 0;
    }
}
