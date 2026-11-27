// University IT Support Management System
// Phase 1.2 - Standalone discussion/demo simulator
// This file is intentionally separate from the GitHub project files.
// It demonstrates the Phase 1.2 random list movements using the Phase 1.1 DS choices.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

enum TicketType { NR, SR, UR };
enum TechType { ST, GT };
enum TicketStatus { WAITING, COMPLETED, CANCELLED };

struct Ticket {
    int RID;
    int QT;
    int LID;
    TicketType type;
    int PC;
    int PR;
    TicketStatus status;

    Ticket(int rid, int qt, int lid, TicketType t, int pc, int pr = 0)
        : RID(rid), QT(qt), LID(lid), type(t), PC(pc), PR(pr), status(WAITING) {}
};

struct Technician {
    int TID;
    TechType type;
    int simulatedFinishTime;

    Technician(int id, TechType t)
        : TID(id), type(t), simulatedFinishTime(0) {}
};

struct CancellationRecord {
    int CT;
    int RID;
};

struct ProblemCode {
    int PC;
    char category;
    int duration;
};

struct Location {
    int LID;
    string name;
};

// Display overloads used by the generic Queue and Priority Queue classes.
void printItem(Ticket* t) {
    if (!t) { cout << "NULL"; return; }
    cout << t->RID << "(";
    if (t->type == NR) cout << "NR";
    else if (t->type == SR) cout << "SR";
    else cout << "UR,PR=" << t->PR;
    cout << ")";
}

void printItem(Technician* t) {
    if (!t) { cout << "NULL"; return; }
    cout << (t->type == ST ? "ST" : "GT") << "-" << t->TID;
}

void printItem(CancellationRecord* c) {
    if (!c) { cout << "NULL"; return; }
    cout << "(CT=" << c->CT << ",RID=" << c->RID << ")";
}

void printItem(ProblemCode* p) {
    if (!p) { cout << "NULL"; return; }
    cout << "PC" << p->PC << "(" << p->category << "," << p->duration << " min)";
}

template <typename T>
class Node {
private:
    T item;
    Node<T>* next;
public:
    explicit Node(const T& value) : item(value), next(nullptr) {}
    T getItem() const { return item; }
    Node<T>* getNext() const { return next; }
    void setNext(Node<T>* n) { next = n; }
};

template <typename T>
class PriNode {
private:
    T data;
    int priority;
    PriNode<T>* next;
public:
    PriNode(const T& value, int p) : data(value), priority(p), next(nullptr) {}
    T getData() const { return data; }
    int getPriority() const { return priority; }
    PriNode<T>* getNext() const { return next; }
    void setNext(PriNode<T>* n) { next = n; }
};

template <typename T>
class Queue {
protected:
    Node<T>* front;
    Node<T>* back;
    int count;
public:
    Queue() : front(nullptr), back(nullptr), count(0) {}
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    virtual ~Queue() { clear(); }

    bool isEmpty() const { return front == nullptr; }
    int getCount() const { return count; }

    void enqueue(const T& value) {
        Node<T>* n = new Node<T>(value);
        if (isEmpty()) front = back = n;
        else { back->setNext(n); back = n; }
        ++count;
    }

    bool dequeue(T& value) {
        if (isEmpty()) return false;
        Node<T>* old = front;
        value = old->getItem();
        front = front->getNext();
        if (!front) back = nullptr;
        delete old;
        --count;
        return true;
    }

    bool peek(T& value) const {
        if (isEmpty()) return false;
        value = front->getItem();
        return true;
    }

    void print() const {
        Node<T>* cur = front;
        while (cur) {
            printItem(cur->getItem());
            if (cur->getNext()) cout << " -> ";
            cur = cur->getNext();
        }
        if (isEmpty()) cout << "(empty)";
    }

    void clear() {
        while (front) {
            Node<T>* old = front;
            front = front->getNext();
            delete old;
        }
        back = nullptr;
        count = 0;
    }
};

template <typename T>
class PriQueue {
protected:
    PriNode<T>* head;
    int count;
public:
    PriQueue() : head(nullptr), count(0) {}
    PriQueue(const PriQueue&) = delete;
    PriQueue& operator=(const PriQueue&) = delete;
    virtual ~PriQueue() { clear(); }

    bool isEmpty() const { return head == nullptr; }
    int getCount() const { return count; }

    // Smaller numeric key is removed first. Equal keys preserve insertion order.
    void enqueue(const T& value, int priority) {
        PriNode<T>* n = new PriNode<T>(value, priority);
        if (isEmpty() || priority < head->getPriority()) {
            n->setNext(head);
            head = n;
        } else {
            PriNode<T>* cur = head;
            while (cur->getNext() && cur->getNext()->getPriority() <= priority)
                cur = cur->getNext();
            n->setNext(cur->getNext());
            cur->setNext(n);
        }
        ++count;
    }

    bool dequeue(T& value, int& priority) {
        if (isEmpty()) return false;
        PriNode<T>* old = head;
        value = old->getData();
        priority = old->getPriority();
        head = head->getNext();
        delete old;
        --count;
        return true;
    }

    bool peek(T& value, int& priority) const {
        if (isEmpty()) return false;
        value = head->getData();
        priority = head->getPriority();
        return true;
    }

    void print() const {
        PriNode<T>* cur = head;
        while (cur) {
            printItem(cur->getData());
            if (cur->getNext()) cout << " -> ";
            cur = cur->getNext();
        }
        if (isEmpty()) cout << "(empty)";
    }

    void clear() {
        while (head) {
            PriNode<T>* old = head;
            head = head->getNext();
            delete old;
        }
        count = 0;
    }
};

class UrgentPQ : public PriQueue<Ticket*> {
private:
    bool hasHigherPriority(Ticket* a, Ticket* b) const {
        if (a->PR != b->PR) return a->PR > b->PR; // higher PR first
        if (a->QT != b->QT) return a->QT < b->QT; // earlier request first
        return a->RID < b->RID;                   // smaller RID first
    }
public:
    void enqueueUrgent(Ticket* t) {
        if (!t) return;
        PriNode<Ticket*>* n = new PriNode<Ticket*>(t, -t->PR);
        if (!head || hasHigherPriority(t, head->getData())) {
            n->setNext(head);
            head = n;
        } else {
            PriNode<Ticket*>* cur = head;
            while (cur->getNext() && !hasHigherPriority(t, cur->getNext()->getData()))
                cur = cur->getNext();
            n->setNext(cur->getNext());
            cur->setNext(n);
        }
        ++count;
    }
};

class NRQueue : public Queue<Ticket*> {
public:
    Ticket* removeByRID(int rid) {
        Node<Ticket*>* previous = nullptr;
        Node<Ticket*>* current = front;
        while (current) {
            Ticket* t = current->getItem();
            if (t && t->RID == rid) {
                if (!previous) front = current->getNext();
                else previous->setNext(current->getNext());
                if (current == back) back = previous;
                delete current;
                --count;
                return t;
            }
            previous = current;
            current = current->getNext();
        }
        return nullptr;
    }

    // For the Phase 1.2 demo, cancel the second waiting NR when possible.
    // This deliberately exercises removeByRID from the middle of the linked queue.
    Ticket* removeOneForDemo() {
        if (!front) return nullptr;
        Node<Ticket*>* target = (count >= 3) ? front->getNext() : front;
        if (!target || !target->getItem()) return nullptr;
        return removeByRID(target->getItem()->RID);
    }
};

class BusyList : public PriQueue<Technician*> {
private:
    bool finishesBefore(Technician* a, Technician* b) const {
        if (a->simulatedFinishTime != b->simulatedFinishTime)
            return a->simulatedFinishTime < b->simulatedFinishTime;
        // No real ticket assignment is done in Phase 1.2. TID is used as a
        // deterministic demo tie-breaker when there is no ticket RID available.
        return a->TID < b->TID;
    }
public:
    void enqueueBusy(Technician* tech) {
        if (!tech) return;
        PriNode<Technician*>* n = new PriNode<Technician*>(tech, tech->simulatedFinishTime);
        if (!head || finishesBefore(tech, head->getData())) {
            n->setNext(head);
            head = n;
        } else {
            PriNode<Technician*>* cur = head;
            while (cur->getNext() && !finishesBefore(tech, cur->getNext()->getData()))
                cur = cur->getNext();
            n->setNext(cur->getNext());
            cur->setNext(n);
        }
        ++count;
    }

    bool dequeueEarliest(Technician*& tech) {
        int ignoredPriority = 0;
        return PriQueue<Technician*>::dequeue(tech, ignoredPriority);
    }
};

class ProblemTable : public Queue<ProblemCode*> {};

class LocationsArray {
private:
    Location* data;
    int count;
public:
    LocationsArray() : data(nullptr), count(0) {}
    LocationsArray(const LocationsArray&) = delete;
    LocationsArray& operator=(const LocationsArray&) = delete;
    ~LocationsArray() { delete[] data; }

    bool initialize(int n) {
        if (n < 0) return false;
        delete[] data;
        data = new Location[n + 1];
        count = n;
        return true;
    }

    void set(int id, const string& name) {
        if (id >= 1 && id <= count) {
            data[id].LID = id;
            data[id].name = name;
        }
    }

    void print() const {
        for (int i = 1; i <= count; ++i)
            cout << "LID=" << data[i].LID << " " << data[i].name << "\n";
    }
};

class UI {
private:
    bool interactive;
public:
    UI() : interactive(true) {}

    void selectMode() {
        int choice = 1;
        cout << "Choose mode: 1-Interactive, 2-Silent: ";
        if (!(cin >> choice)) {
            cin.clear();
            choice = 1;
        }
        cin.ignore(10000, '\n');
        interactive = (choice != 2);
        if (interactive) cout << "Interactive mode selected.\n";
        else cout << "Silent mode selected. Simulation is running...\n";
    }

    bool isInteractive() const { return interactive; }

    void printMinute(int minute, int randomNumber, const string& action,
                     const UrgentPQ& ur, const Queue<Ticket*>& sr,
                     const NRQueue& nr, const Queue<Ticket*>& completed,
                     const Queue<Ticket*>& cancelled) const {
        if (!interactive) return;
        cout << "\n==================================================\n";
        cout << "Minute: " << minute << " | Random number: " << randomNumber << "\n";
        cout << "Action: " << action << "\n";
        cout << "Waiting UR (" << ur.getCount() << "): "; ur.print(); cout << "\n";
        cout << "Waiting SR (" << sr.getCount() << "): "; sr.print(); cout << "\n";
        cout << "Waiting NR (" << nr.getCount() << "): "; nr.print(); cout << "\n";
        cout << "Completed (" << completed.getCount() << "): "; completed.print(); cout << "\n";
        cout << "Cancelled (" << cancelled.getCount() << "): "; cancelled.print(); cout << "\n";
        cout << "Press Enter for the next minute...";
        string line;
        getline(cin, line);
    }
};

class Phase12Simulation {
private:
    Queue<Ticket*> All_Requests;
    Queue<CancellationRecord*> All_Cancellations;
    UrgentPQ Waiting_UR;
    Queue<Ticket*> Waiting_SR;
    NRQueue Waiting_NR;
    PriQueue<Technician*> Free_ST;
    PriQueue<Technician*> Free_GT;
    BusyList Busy_Technicians;
    Queue<Ticket*> Completed_Tickets;
    Queue<Ticket*> Cancelled_Tickets;
    ProblemTable Problem_Codes;
    LocationsArray Locations;
    UI ui;
    int totalTickets;
    unsigned int randomSeed;

    bool allTicketsMoved() const {
        return All_Requests.isEmpty() && Waiting_UR.isEmpty() &&
               Waiting_SR.isEmpty() && Waiting_NR.isEmpty();
    }

    void distributeAllRequestsToWaitingLists() {
        Ticket* t = nullptr;
        while (All_Requests.dequeue(t)) {
            if (!t) continue;
            t->status = WAITING;
            if (t->type == UR) Waiting_UR.enqueueUrgent(t);
            else if (t->type == SR) Waiting_SR.enqueue(t);
            else Waiting_NR.enqueue(t);
        }
    }

    void printLoadedData() const {
        cout << "\n--- Loaded configuration ---\n";
        cout << "Locations:\n";
        Locations.print();
        cout << "Problem codes (Queue): ";
        Problem_Codes.print();
        cout << "\nAll requests before distribution (Queue): ";
        All_Requests.print();
        cout << "\nCancellation records (Queue): ";
        All_Cancellations.print();
        cout << "\nTotal tickets loaded: " << totalTickets << "\n";
    }

    void cleanupOwnedObjects() {
        Ticket* ticket = nullptr;
        int priority = 0;
        Technician* tech = nullptr;
        CancellationRecord* cancelRecord = nullptr;
        ProblemCode* problem = nullptr;

        while (All_Requests.dequeue(ticket)) delete ticket;
        while (Waiting_UR.dequeue(ticket, priority)) delete ticket;
        while (Waiting_SR.dequeue(ticket)) delete ticket;
        while (Waiting_NR.dequeue(ticket)) delete ticket;
        while (Completed_Tickets.dequeue(ticket)) delete ticket;
        while (Cancelled_Tickets.dequeue(ticket)) delete ticket;

        while (Free_ST.dequeue(tech, priority)) delete tech;
        while (Free_GT.dequeue(tech, priority)) delete tech;
        while (Busy_Technicians.dequeueEarliest(tech)) delete tech;

        while (All_Cancellations.dequeue(cancelRecord)) delete cancelRecord;
        while (Problem_Codes.dequeue(problem)) delete problem;
    }

public:
    Phase12Simulation() : totalTickets(0), randomSeed(2) {}
    ~Phase12Simulation() { cleanupOwnedObjects(); }

    bool loadInput(const string& filename) {
        ifstream input(filename.c_str());
        if (!input.is_open()) {
            cout << "Cannot open input file: " << filename << "\n";
            return false;
        }

        int locationCount = 0;
        if (!(input >> locationCount) || locationCount < 0) return inputError();
        if (!Locations.initialize(locationCount)) return inputError();
        for (int i = 1; i <= locationCount; ++i) {
            string name;
            if (!(input >> name)) return inputError();
            Locations.set(i, name);
        }

        int problemCount = 0;
        if (!(input >> problemCount) || problemCount < 0) return inputError();
        for (int i = 1; i <= problemCount; ++i) {
            ProblemCode* p = new ProblemCode;
            p->PC = i;
            if (!(input >> p->category >> p->duration)) { delete p; return inputError(); }
            Problem_Codes.enqueue(p);
        }

        int numberST = 0, numberGT = 0;
        if (!(input >> numberST >> numberGT) || numberST < 0 || numberGT < 0)
            return inputError();
        int nextTechnicianID = 1;
        for (int i = 0; i < numberST; ++i) {
            Technician* tech = new Technician(nextTechnicianID++, ST);
            Free_ST.enqueue(tech, tech->TID);
        }
        for (int i = 0; i < numberGT; ++i) {
            Technician* tech = new Technician(nextTechnicianID++, GT);
            Free_GT.enqueue(tech, tech->TID);
        }

        if (!(input >> totalTickets) || totalTickets < 0) return inputError();
        for (int i = 0; i < totalTickets; ++i) {
            string typeText;
            int qt = 0, rid = 0, lid = 0, pc = 0, pr = 0;
            if (!(input >> typeText >> qt >> rid >> lid >> pc)) return inputError();
            TicketType type;
            if (typeText == "NR") type = NR;
            else if (typeText == "SR") type = SR;
            else if (typeText == "UR") {
                type = UR;
                if (!(input >> pr)) return inputError();
            } else return inputError();
            All_Requests.enqueue(new Ticket(rid, qt, lid, type, pc, pr));
        }

        int cancellationCount = 0;
        if (!(input >> cancellationCount) || cancellationCount < 0) return inputError();
        for (int i = 0; i < cancellationCount; ++i) {
            CancellationRecord* c = new CancellationRecord;
            if (!(input >> c->CT >> c->RID)) { delete c; return inputError(); }
            All_Cancellations.enqueue(c);
        }

        input.close();
        printLoadedData();
        distributeAllRequestsToWaitingLists();
        cout << "\nAfter distribution: All_Requests = " << All_Requests.getCount()
             << ", Waiting_UR = " << Waiting_UR.getCount()
             << ", Waiting_SR = " << Waiting_SR.getCount()
             << ", Waiting_NR = " << Waiting_NR.getCount() << "\n";
        return true;
    }

    bool inputError() {
        cout << "Input file has an invalid or incomplete format.\n";
        return false;
    }

    void run() {
        ui.selectMode();
        cout << "Random seed used for repeatable discussion demo: " << randomSeed << "\n";
        srand(randomSeed);
        int minute = 0;

        while (!allTicketsMoved()) {
            ++minute;
            const int number = rand() % 100 + 1;
            string action = "No list movement for this random number.";
            Ticket* ticket = nullptr;
            Technician* tech = nullptr;
            int priority = 0;

            if (number >= 10 && number < 20) {
                if (Waiting_UR.dequeue(ticket, priority)) {
                    ticket->status = COMPLETED;
                    Completed_Tickets.enqueue(ticket);
                    action = "Moved highest-priority UR ticket " + to_string(ticket->RID) +
                             " from Waiting_UR to Completed_Tickets.";
                } else action = "UR action selected, but Waiting_UR is empty.";
            } else if (number >= 20 && number < 30) {
                if (Waiting_SR.dequeue(ticket)) {
                    ticket->status = COMPLETED;
                    Completed_Tickets.enqueue(ticket);
                    action = "Moved front SR ticket " + to_string(ticket->RID) +
                             " from Waiting_SR to Completed_Tickets.";
                } else action = "SR action selected, but Waiting_SR is empty.";
            } else if (number >= 30 && number < 45) {
                if (Waiting_NR.dequeue(ticket)) {
                    ticket->status = COMPLETED;
                    Completed_Tickets.enqueue(ticket);
                    action = "Moved front NR ticket " + to_string(ticket->RID) +
                             " from Waiting_NR to Completed_Tickets.";
                } else action = "NR action selected, but Waiting_NR is empty.";
            } else if (number >= 45 && number < 50) {
                ticket = Waiting_NR.removeOneForDemo();
                if (ticket) {
                    ticket->status = CANCELLED;
                    Cancelled_Tickets.enqueue(ticket);
                    action = "Removed NR ticket " + to_string(ticket->RID) +
                             " by ID from Waiting_NR and moved it to Cancelled_Tickets.";
                } else action = "Cancellation selected, but Waiting_NR is empty.";
            } else if (number >= 50 && number < 60) {
                if (Free_ST.dequeue(tech, priority)) {
                    // A synthetic finish key is used only to test BusyList ordering.
                    // Phase 1.2 does not require assigning a real ticket to this technician.
                    tech->simulatedFinishTime = minute + 5;
                    Busy_Technicians.enqueueBusy(tech);
                    action = "Moved one ST technician from Free_ST to Busy_Technicians.";
                } else action = "ST movement selected, but Free_ST is empty.";
            } else if (number >= 60 && number < 70) {
                if (Free_GT.dequeue(tech, priority)) {
                    tech->simulatedFinishTime = minute + 5;
                    Busy_Technicians.enqueueBusy(tech);
                    action = "Moved one GT technician from Free_GT to Busy_Technicians.";
                } else action = "GT movement selected, but Free_GT is empty.";
            } else if (number >= 70 && number < 85) {
                if (Busy_Technicians.dequeueEarliest(tech)) {
                    tech->simulatedFinishTime = 0;
                    if (tech->type == ST) Free_ST.enqueue(tech, tech->TID);
                    else Free_GT.enqueue(tech, tech->TID);
                    action = string("Moved one ") + (tech->type == ST ? "ST" : "GT") +
                             " technician from Busy_Technicians back to its Free list.";
                } else action = "Busy-to-free movement selected, but Busy_Technicians is empty.";
            }

            ui.printMinute(minute, number, action, Waiting_UR, Waiting_SR,
                           Waiting_NR, Completed_Tickets, Cancelled_Tickets);
        }

        cout << "\n================ SIMULATION FINISHED ================\n";
        cout << "Total tickets loaded: " << totalTickets << "\n";
        cout << "Completed tickets: " << Completed_Tickets.getCount() << "\n";
        cout << "Cancelled tickets: " << Cancelled_Tickets.getCount() << "\n";
        cout << "Remaining waiting tickets: 0\n";
        cout << "No output file was created (Phase 1 requirement).\n";
    }
};

int main() {
    cout << "University IT Support Management System\n";
    cout << "Phase 1.2 - Discussion Simulation\n\n";
    cout << "Enter input file name (example: phase12_demo_input.txt): ";
    string filename;
    getline(cin, filename);
    if (filename.empty()) filename = "phase12_demo_input.txt";

    Phase12Simulation simulation;
    if (!simulation.loadInput(filename)) return 1;
    simulation.run();
    return 0;
}
