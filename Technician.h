#ifndef TECHNICIAN_H
#define TECHNICIAN_H
#include "Defs.h"

class Ticket;

class Technician
{
private:

	TechType type;
	int TID;// technician 
	int finishTime; //Finish Time
	int busyTime; // Busy time
	Ticket* assignedTicket;

public:

	Technician(int tid, TechType t);

	int getTID() const;
	int getBusyTime() const;
	int getFinishTime() const;
	TechType getType() const;
	Ticket* getAssignedTicket() const;
	void assignTicket(Ticket* t, int ft);
	void releaseTicket();
	void incrementBusyTime(int minutes);
};

#endif // TECHNICIAN_H