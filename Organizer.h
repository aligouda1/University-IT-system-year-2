#ifndef ORGANIZER_H
#define ORGANIZER_H
#include "Defs.h"
#include "Queue.h"
#include "Ticket.h"
#include "Technician.h"
#include "NRQueue.h"
#include "UrgentPQ.h"
#include "BusyList.h"
#include "ITUnit.h"
class Organizer {
private:
    Queue<Ticket*> All_Requests;
    Queue<CancellationRecord*> All_Cancellations;
    Queue<Ticket*> Completed_Tickets;
    Queue<Ticket*> Cancelled_Tickets;
    BusyList Busy_Technicians;
    ITUnit itUnit;
    Location* locations;
    int locationCount;
    ProblemCode** problemCodes;
    int pcCount;
public:
    Organizer();
    ~Organizer();
    void moveToCompleted(Ticket* t);
    void moveToCancelled(Ticket* t);
    void assignTicketToTech(Technician* tech, Ticket* t, int finishTime);
    void releaseTechnician(Technician* tech);
};
#endif
