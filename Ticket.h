// Ticket.h
#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <string>
#include "Defs.h"
using namespace std;

class Ticket {
    int RID;            // request ID
    int QT;             // request time
    int LID;            // location ID
    TicketType type;    // NR, SR or UR
    int PC;             // problem code
    int PR;             // priority (only for UR, otherwise 0)
    int AT;             // assignment time (-1 until assigned)
    int ST;             // service start time (-1 until started)
    int FT;             // finish time (-1 until finished)
    TicketStatus status;

public:
    Ticket(int rid, int qt, int lid, TicketType t, int pc, int pr = 0);

    int getRID() { return RID; }
    int getQT() { return QT; }
    int getLID() { return LID; }
    TicketType getType() { return type; }
    int getPC() { return PC; }
    int getPR() { return PR; }
    int getAT() { return AT; }
    int getST() { return ST; }
    int getFT() { return FT; }
    TicketStatus getStatus() { return status; }

    void setAT(int at) { AT = at; }
    void setST(int st) { ST = st; }
    void setFT(int ft) { FT = ft; }
    void setStatus(TicketStatus s) { status = s; }

    int getWaitingTime() { return ST - QT; }
    int getResolutionTime() { return FT - QT; }
    string getTypeString();
    void printTicket();
};

// cout << ticket   prints the RID only
ostream& operator<<(ostream& out, Ticket* t);

#endif
