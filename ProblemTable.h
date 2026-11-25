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

    ProblemCode* getByIndex(int pc);   
    char getCategory(int pc);          // 'B' / 'H'   (or '?')
    int getDuration(int pc);           

    void print();       
    void clearAll();   
};

#endif
