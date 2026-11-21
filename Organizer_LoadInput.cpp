// Organizer_LoadInput.cpp - reads the input file (Ali Mostafa)
#include <fstream>
#include <iostream>
#include <string>
#include "Organizer.h"
using namespace std;

bool Organizer::loadInputFile (string filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return false;
    }

    // ----- locations -----
    int L;
    in >> L;
    locations.initLocations(L);
    for (int i = 1; i <= L; i++) {
        string name;
        in >> name;
        locations.setLocation(i, name);
    }
    numLocations = L;

    // ----- problem codes (row number = problem code, starts at 1) -----
    int K;
    in >> K;
    for (int i = 1; i <= K; i++) {
        ProblemCode* p = new ProblemCode;
        p->PC = i;
        in >> p->category >> p->duration;
        problemTable.enqueue(p);
    }
    numProblemCodes = K;

    // ----- technicians (ST first, then GT, IDs increase) -----
    int stCount, gtCount;
    in >> stCount >> gtCount;
    int id = 1;
    for (int i = 0; i < stCount; i++) {
        itUnit.addFreeTechnician(new Technician(id, ST));
        id++;
    }
    for (int i = 0; i < gtCount; i++) {
        itUnit.addFreeTechnician(new Technician(id, GT));
        id++;
    }
    numST = stCount;
    numGT = gtCount;

    // ----- requests (Phase 1.2: go directly to the waiting lists) -----
    int R;
    in >> R;
    for (int i = 0; i < R; i++) {
        string typeStr;
        int qt, rid, lid, pc;
        int pr = 0;
        in >> typeStr >> qt >> rid >> lid >> pc;

        TicketType type;
        if (typeStr == "NR") {
            type = NR;
            numNR++;
        } else if (typeStr == "SR") {
            type = SR;
            numSR++;
        } else {
            type = UR;
            numUR++;
            in >> pr;   // only UR has a priority
        }

        Ticket* t = new Ticket(rid, qt, lid, type, pc, pr);
        t->setStatus(WAITING);
        itUnit.addWaitingTicket(t);   // ITUnit chooses the right list
    }

    // ----- cancellations -----
    int C;
    in >> C;
    for (int i = 0; i < C; i++) {
        CancellationRecord* c = new CancellationRecord;
        in >> c->CT >> c->RID;
        allCancellations.enqueue(c);
    }

    if (in.fail()) {
        cout << "Input file has a wrong format" << endl;
        return false;
    }

    in.close();
    return true;
}
