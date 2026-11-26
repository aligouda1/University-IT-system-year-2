#ifndef URGENTPQ_H
#define URGENTPQ_H
#include "PriQueue.h"
#include "Ticket.h"
class UrgentPQ : public PriQueue<Ticket*> {
public:
    bool hasHigherPriority(Ticket* a, Ticket* b) const;
    void enqueueUrgent(Ticket* t);   
};

