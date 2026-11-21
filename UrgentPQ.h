#ifndef URGENTPQ_H
#define URGENTPQ_H
#include "PriQueue.h"
#include "Ticket.h"
using namespace std;
class UrgentPQ : public PriQueue<Ticket*> {
public:
    bool Priority(Ticket* a, Ticket* b);
    void enqueue(Ticket* t);
};
#endif
