#include "UrgentPQ.h"
bool UrgentPQ::hasHigherPriority(Ticket* a, Ticket* b) const {
    if (a->getPR() != b->getPR())
        return a->getPR() > b->getPR();   
    if (a->getQT() != b->getQT())
        return a->getQT() < b->getQT();   
    return a->getRID() < b->getRID();     
}
void UrgentPQ::enqueueUrgent(Ticket* t) {
    PriNode<Ticket*>* newNode = new PriNode<Ticket*>(t, t->getPR());    
    if (head == nullptr || hasHigherPriority(t, head->getItem())) {
        newNode->setNext(head);
        head = newNode;
        count++;
        return;
    }   
    PriNode<Ticket*>* curr = head;
    while (curr->getNext() != nullptr && !hasHigherPriority(t, curr->getNext()->getItem())) {
        curr = curr->getNext();
    }
    newNode->setNext(curr->getNext());
    curr->setNext(newNode);
    count++;
}
