// UI.h - all console input / output (Mohamed Hamdy)
#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include "Defs.h"
using namespace std;

class UI {
    SimMode mode;

    // prints one line like:  UR (2): 3 7
    template <typename List>
    void printList(string title, List& list) {
        cout << title << " (" << list.getCount() << "): ";
        list.print();
        cout << endl;
    }

public:
    UI();

    SimMode selectMode();          // asks the user: 1 = Interactive, 2 = Silent
    string getInputFileName();     // asks for the input file name
    bool isInteractive();

    void printSilentStart();
    void printSilentEnd(bool outputFileCreated = false);
    void waitForEnter();           // "Press Enter to advance to the next minute."

    // Shows the state of the current minute (Phase 1.2: no technician info).
    // Does nothing in Silent mode, so the simulator can always call it.
    // Works with any list class that has print() and getCount().
    template <typename URList, typename SRList, typename NRList,
              typename DoneList, typename CancelList>
    void printMinuteState(int minute, URList& waitingUR, SRList& waitingSR,
                          NRList& waitingNR, DoneList& completed,
                          CancelList& cancelled) {
        if (mode == SILENT)
            return;

        cout << "==============================" << endl;
        cout << "Current Minute: " << minute << endl;
        cout << "------ Waiting tickets ------" << endl;
        printList("UR", waitingUR);
        printList("SR", waitingSR);
        printList("NR", waitingNR);
        cout << "------ Completed tickets ------" << endl;
        printList("Completed", completed);
        cout << "------ Cancelled tickets ------" << endl;
        printList("Cancelled", cancelled);

        waitForEnter();
    }
};

#endif
