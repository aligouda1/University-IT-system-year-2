#include "Organizer.h"
Organizer::Organizer(){
    locations = nullptr;
    locationCount = 0;
    problemCodes = nullptr;
    pcCount = 0;
}
void Organizer::moveToCompleted(Ticket* t){
    if (t ==nullptr) {
        return;
    }
    t->setStatus(COMPLETED);
    Completed_Tickets.enqueue(t);
}
void Organizer::moveToCancelled(Ticket* t){
    if (t == nullptr) {
        return;
    }
    t->setStatus(CANCELLED);
    Cancelled_Tickets.enqueue(t);
}
void Organizer::assignTicketToTech(Technician* tech,Ticket* t,int finishTime){
    t->setStatus(IN_SERVICE);
    tech->setAssignedTicket(t);
    tech->setFinishTime(finishTime);
    Busy_Technicians.enqueueBusy(tech);
}
void Organizer::releaseTechnician(Technician* tech){
    tech->setAssignedTicket(nullptr);
    itUnit.returnTechnician(tech);
}
Organizer::~Organizer() {
    Ticket* t =nullptr;
    CancellationRecord*c=nullptr;
    Technician*tech =nullptr;
    while(Completed_Tickets.dequeue(t)){
        delete t;
    }
    while(Cancelled_Tickets.dequeue(t)){
        delete t;
    }
    while(All_Requests.dequeue(t)){
        delete t;
    }
    while(All_Cancellations.dequeue(c)){
        delete c;
    }
    while(Busy_Technicians.dequeue(tech)){
        delete tech->getAssignedTicket();
        delete tech;
    }
    for(int i = 0; i < pcCount; i++){
        delete problemCodes[i];
    }
    delete[] problemCodes;
    delete[] locations;
}
