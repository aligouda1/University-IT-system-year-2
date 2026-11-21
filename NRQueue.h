#ifndef NRQUEUE_H
#define NRQUEUE_H
#include "Queue.h"
#include "Ticket.h"
using namespace std;
class NRQueue: public Queue<Ticket*> {
public:
    Ticket*removeByID(int rid);
    Ticket*getWaitingTicket();
};
#endif
