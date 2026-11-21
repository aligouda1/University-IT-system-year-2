#include "BusyList.h"
#include "Ticket.h"
using namespace std;
bool BusyList::finishesBefore(Technician* a, Technician* b) {
    if (a->getFinishTime() != b->getFinishTime())
        return a->getFinishTime() < b->getFinishTime();
    return a->getAssignedTicket()->getRID() < b->getAssignedTicket()->getRID();
}
void BusyList::enqueueBusy(Technician* tech) {
    PriNode<Technician*>* newNode = new PriNode<Technician*>(tech);
    if (head == nullptr || finishesBefore(tech, head->getItem())) {
        newNode->setNext(head);
        head = newNode;
        count++;
        return;
    }
    PriNode<Technician*>* curr = head;
    while (curr->getNext() != nullptr &&
           !finishesBefore(tech, curr->getNext()->getItem())) {
        curr = curr->getNext();
    }
    newNode->setNext(curr->getNext());
    curr->setNext(newNode);
    count++;
}
Technician* BusyList::removeByTicketID(int rid) {
    PriNode<Technician*>* prev = nullptr;
    PriNode<Technician*>* curr = head;
    while (curr != nullptr) {
        Technician* tech = curr->getItem();
        Ticket* t = tech->getAssignedTicket();
        if (t != nullptr && t->getRID() == rid) {
            if (prev == nullptr)               
                head = curr->getNext();
            else                               
                prev->setNext(curr->getNext());
            delete curr;                       
            count--;
            return tech;
        }
        prev = curr;
        curr = curr->getNext();
    }
    return nullptr;                            
}
