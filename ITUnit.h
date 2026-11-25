#ifndef ITUNIT_H
#define ITUNIT_H

#include "Defs.h"
#include "Ticket.h"
#include "Technician.h"
#include "Queue.h"        // Ali
#include "PriQueue.h"   
#include "UrgentPQ.h"     // Abdelrahman
#include "NRQueue.h"      // Abdelrahman
#include "BusyList.h"     // Abdelrahman


class ITUnit{
private:
    UrgentPQ Waiting_UR;               
    Queue<Ticket*> Waiting_SR;         
    NRQueue Waiting_NR;                
    PriQueue<Technician*> Free_ST;    
    PriQueue<Technician*> Free_GT;    
    BusyList Busy_Technicians;         

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
