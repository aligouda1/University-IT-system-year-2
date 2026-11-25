#ifndef PROBLEMTABLE_H
#define PROBLEMTABLE_H

#include <iostream>
#include "Queue.h"
#include "Defs.h"
using namespace std;


ostream& operator<<(ostream& out, ProblemCode* p);

class ProblemTable : public Queue<ProblemCode*> {
public:
    ~ProblemTable();

    ProblemCode* getByIndex(int pc);   
    char getCategory(int pc);          
    int getDuration(int pc);           

    void print();       
    void clearAll();   
};

#endif
