// ProblemTable.h - the problem-code table (derived from Queue)
#ifndef PROBLEMTABLE_H
#define PROBLEMTABLE_H

#include <iostream>
#include "Queue.h"
#include "Defs.h"
using namespace std;

// cout << problemCode*   prints  "PC=1 B 3"
ostream& operator<<(ostream& out, ProblemCode* p);

class ProblemTable : public Queue<ProblemCode*> {
public:
    ~ProblemTable();

    ProblemCode* getByIndex(int pc);   // O(K)  walks to row pc, nullptr if not found
    char getCategory(int pc);          // 'B' / 'H'   (or '?' if pc is wrong)
    int getDuration(int pc);           // minutes     (or 0 if pc is wrong)

    void print();       // O(K)  one row per line
    void clearAll();    // O(K)  deletes the rows AND the nodes
};

#endif
