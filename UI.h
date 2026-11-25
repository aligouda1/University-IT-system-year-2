#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include "Defs.h"
using namespace std;

class UI {
    SimMode mode;

    // UR (2): 3 7
    template <typename List>
    void printList(string title, List& list) {
        cout << title << " (" << list.getCount() << "): ";
        list.print();
        cout << endl;
    }

public:
    UI();

    SimMode selectMode();          
    string getInputFileName();    
    bool isInteractive();

    void printSilentStart();
    void printSilentEnd(bool outputFileCreated = false);
    void waitForEnter();           


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
