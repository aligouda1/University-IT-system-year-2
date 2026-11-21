// Ticket.cpp
#include "Ticket.h"

Ticket::Ticket(int rid, int qt, int lid, TicketType t, int pc, int pr) {
    RID = rid;
    QT = qt;
    LID = lid;
    type = t;
    PC = pc;
    PR = pr;
    AT = -1;
    ST = -1;
    FT = -1;
    status = PENDING;
}

string Ticket::getTypeString() {
    if (type == NR){
        return "NR"; 
    }
    if (type == SR) {
        return "SR";
    }
    return "UR";
}

void Ticket::printTicket() {
    cout << getTypeString() << " RID=" << RID << " QT=" << QT
         << " LID=" << LID << " PC=" << PC;
    if (type == UR)
        cout << " PR=" << PR;
    cout << endl;
}

ostream& operator<<(ostream& out, Ticket* t) {
    out << t->getRID();
    return out;
}
