#ifndef URGENTPQ_H
#define URGENTPQ_H
#include "Ticket.h"
#include "PriNode.h"
class UrgentPQ {
private:
    PriNode<Ticket*>* head = nullptr;
    bool Priority(Ticket* a, Ticket* b);
public:
    ~UrgentPQ();
    bool is_empty();
    void enqueue(Ticket* t);
    Ticket* dequeue();
};
#endif
