#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include "Defs.h"
using namespace std;

class UI {
private:
    SimMode mode;

public:
    UI();

    SimMode selectMode();
    string getInputFileName();
    bool isInteractive();

    void printSilentStart();
    void printSilentEnd(bool outputFileCreated = false);
    void waitForEnter();

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    void printMinuteState(int minute, T1& waitingUR, T2& waitingSR,
                          T3& waitingNR, T4& completed, T5& cancelled) {
        if (mode == SILENT)
            return;

        cout << "==============================" << endl;
        cout << "Current Minute: " << minute << endl;

        cout << "------ Waiting tickets ------" << endl;
        cout << "UR (" << waitingUR.getCount() << "): ";
        waitingUR.print();
        cout << endl;

        cout << "SR (" << waitingSR.getCount() << "): ";
        waitingSR.print();
        cout << endl;

        cout << "NR (" << waitingNR.getCount() << "): ";
        waitingNR.print();
        cout << endl;

        cout << "------ Completed tickets ------" << endl;
        cout << "Completed (" << completed.getCount() << "): ";
        completed.print();
        cout << endl;

        cout << "------ Cancelled tickets ------" << endl;
        cout << "Cancelled (" << cancelled.getCount() << "): ";
        cancelled.print();
        cout << endl;

        waitForEnter();
    }
};

#endif
