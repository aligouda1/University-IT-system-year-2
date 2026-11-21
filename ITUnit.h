#ifndef ITUNIT_H
#define ITUNIT_H

#include "Defs.h"
#include "Ticket.h"
#include "Technician.h"
#include "Queue.h"        // Ali: Queue<T>
#include "PriQueue.h"   
#include "UrgentPQ.h"     // Abdelrahman
#include "NRQueue.h"      // Abdelrahman
#include "BusyList.h"     // Abdelrahman


class ITUnit{
private:
    UrgentPQ Waiting_UR;               // urgent tickets waiting for a technician
    Queue<Ticket*> Waiting_SR;         // specialist tickets waiting for an ST
    NRQueue Waiting_NR;                // normal tickets waiting for a GT
    PriQueue<Technician*> Free_ST;     // free specialist technicians (key = TID)
    PriQueue<Technician*> Free_GT;     // free general technicians (key = TID)
    BusyList Busy_Technicians;         // technicians currently serving a ticket

public:
    void addWaitingTicket(Ticket* t);
    void addFreeTechnician(Technician* tech);
    bool areWaitingListsEmpty() const;

    const UrgentPQ& getWaitingUR() const;
    const Queue<Ticket*>& getWaitingSR() const;
    const NRQueue& getWaitingNR() const;
    const PriQueue<Technician*>& getFreeST() const;
    const PriQueue<Technician*>& getFreeGT() const;
    const BusyList& getBusyTechnicians() const;
};

#endif