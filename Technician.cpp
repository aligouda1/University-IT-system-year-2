#include "Technician.h"


Technician::Technician(int tid, TechType t) :
    type(t),
    TID(tid),
    finishTime(0),
    busyTime(0),
    assignedTicket(nullptr) {
}
int Technician::getTID() const { return TID; }
int Technician::getBusyTime() const { return busyTime; }
int Technician::getFinishTime() const { return finishTime; }
TechType Technician::getType() const { return type; }
Ticket* Technician::getAssignedTicket() const { return assignedTicket; }
void Technician::assignTicket(Ticket* t, int ft) {
	assignedTicket = t;
	finishTime = ft;
}
void Technician::releaseTicket() {
	assignedTicket = nullptr;
	finishTime = 0;
}
void Technician::incrementBusyTime(int minutes) {busyTime += minutes;}


