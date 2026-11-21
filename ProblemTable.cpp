// ProblemTable.cpp
#include "ProblemTable.h"

ostream& operator<<(ostream& out, ProblemCode* p) {
    out << "PC=" << p->PC << " " << p->category << " " << p->duration;
    return out;
}

ProblemTable::~ProblemTable() {
    clearAll();
}

ProblemCode* ProblemTable::getByIndex(int pc) {
    if (pc < 1 || pc > count)
        return nullptr;

    Node<ProblemCode*>* cur = front;
    for (int i = 1; i < pc; i++)       // move forward pc-1 times
        cur = cur->getNext();
    return cur->getItem();
}

char ProblemTable::getCategory(int pc) {
    ProblemCode* p = getByIndex(pc);
    if (p == nullptr)
        return '?';
    return p->category;
}

int ProblemTable::getDuration(int pc) {
    ProblemCode* p = getByIndex(pc);
    if (p == nullptr)
        return 0;
    return p->duration;
}

void ProblemTable::print() {
    Node<ProblemCode*>* cur = front;
    while (cur != nullptr) {
        cout << cur->getItem() << endl;
        cur = cur->getNext();
    }
}

void ProblemTable::clearAll() {
    ProblemCode* p;
    while (dequeue(p))      // dequeue frees the node, we free the row
        delete p;
}
