// Organizer_LoadInput.cpp
#include <fstream>
#include <iostream>
#include <string>
#include "Organizer.h"
using namespace std;

bool Organizer::loadInputFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return false;
    }

    // read locations
    file >> numLocations;
    locations.initLocations(numLocations);
    for (int i = 1; i <= numLocations; i++) {
        string name;
        file >> name;
        locations.setLocation(i, name);
    }

    // read problem codes
    file >> numProblemCodes;
    for (int i = 1; i <= numProblemCodes; i++) {
        ProblemCode* p = new ProblemCode;
        p->PC = i;
        file >> p->category >> p->duration;
        problemTable.enqueue(p);
    }

    // read technicians (ST then GT)
    file >> numST >> numGT;
    int id = 1;
    for (int i = 0; i < numST; i++) {
        itUnit.addFreeTechnician(new Technician(id++, ST));
    }
    for (int i = 0; i < numGT; i++) {
        itUnit.addFreeTechnician(new Technician(id++, GT));
    }

    // read requests
    int R;
    file >> R;
    for (int i = 0; i < R; i++) {
        string typeStr;
        int qt, rid, lid, pc, pr = 0;
        file >> typeStr >> qt >> rid >> lid >> pc;

        TicketType type;
        if (typeStr == "NR") {
            type = NR;
            numNR++;
        }
        else if (typeStr == "SR") {
            type = SR;
            numSR++;
        }
        else {
            type = UR;
            numUR++;
            file >> pr;
        }

        Ticket* t = new Ticket(rid, qt, lid, type, pc, pr);
        t->setStatus(WAITING);
        itUnit.addWaitingTicket(t);
    }

    // read cancellations
    int C;
    file >> C;
    for (int i = 0; i < C; i++) {
        CancellationRecord* c = new CancellationRecord;
        file >> c->CT >> c->RID;
        allCancellations.enqueue(c);
    }

    if (file.fail()) {
        cout << "Input file has a wrong format" << endl;
        return false;
    }

    file.close();
    return true;
}
