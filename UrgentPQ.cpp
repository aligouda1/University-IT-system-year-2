#include "UrgentPQ.h"
using namespace std;
bool UrgentPQ::Priority(Ticket* a, Ticket* b) {
    if (a->getPR() != b->getPR())
        return a->getPR() > b->getPR();     
    if (a->getQT() != b->getQT())
        return a->getQT() < b->getQT();     
    return a->getRID() < b->getRID();      
void UrgentPQ::enqueue(Ticket* t) {
    PriNode<Ticket*>* newNode = new PriNode<Ticket*>(t);    
    if (head == nullptr || Priority(t, head->getItem())) {
        newNode->setNext(head);
        head = newNode;
        count++;
        return;
    }
    PriNode<Ticket*>* curr = head;
    while (curr->getNext() != nullptr &&
           !Priority(t, curr->getNext()->getItem())) {
        curr = curr->getNext();
    }
    newNode->setNext(curr->getNext());   
    curr->setNext(newNode);             
    count++;
}
