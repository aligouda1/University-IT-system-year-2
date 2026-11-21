#ifndef BUSYLIST_H
#define BUSYLIST_H
#include "PriQueue.h"
#include "Technician.h"
using namespace std;
class BusyList : public PriQueue<Technician*> {
public:
    bool finishesBefore(Technician* a, Technician* b);
    void enqueueBusy(Technician* tech);
    Technician* removeByTicketID(int rid);
};
#endif
