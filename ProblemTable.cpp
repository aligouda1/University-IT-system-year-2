#include "ProblemTable.h"

ProblemTable::~ProblemTable() {
    clearAll();
}

ProblemCode* ProblemTable::getByIndex(int pc) {
    if (pc < 1 || pc > count)
        return nullptr;

    Node<ProblemCode*>* cur = front;
    for (int i = 1; i < pc; i++) {
        cur = cur->getNext();
    }
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
        ProblemCode* p = cur->getItem();
        cout << "PC=" << p->PC << " " << p->category << " " << p->duration << endl;
        cur = cur->getNext();
    }
}

void ProblemTable::clearAll() {
    ProblemCode* p;
    while (dequeue(p)) {
        delete p;
    }
}
