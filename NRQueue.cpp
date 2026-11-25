#include "NRQueue.h"
using namespace std;
Ticket* NRQueue::removeByID(int rid) {
    Node<Ticket*>* prev = nullptr;
    Node<Ticket*>* curr = frontPtr;
    while (curr != nullptr) {
        if (curr->getItem()->getRID() == rid) {
            Ticket* t = curr->getItem();
            if (prev == nullptr)               
                frontPtr = curr->getNext();
            else                               
                prev->setNext(curr->getNext());
            if (curr == backPtr)               
                backPtr = prev;
            delete curr;
            count--;
            return t;
        }
        prev = curr;
        curr = curr->getNext();
    }
    return nullptr;                            
}

Ticket* NRQueue::getAnyWaitingTicket() {
    if (frontPtr == nullptr)
        return nullptr;
    return frontPtr->getItem();
}
