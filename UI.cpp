// UI.cpp
#include "UI.h"

UI::UI() {
    mode = INTERACTIVE;
}

SimMode UI::selectMode() {
    string answer;
    while (true) {
        cout << "Choose the mode:" << endl;
        cout << "  1 - Interactive" << endl;
        cout << "  2 - Silent" << endl;
        cout << "Your choice: ";
        getline(cin, answer);

        if (answer == "1") {
            mode = INTERACTIVE;
            break;
        }
        if (answer == "2") {
            mode = SILENT;
            break;
        }
        cout << "Wrong choice, please enter 1 or 2." << endl;
    }
    return mode;
}

string UI::getInputFileName() {
    string name;
    cout << "Enter the input file name: ";
    getline(cin, name);
    return name;
}

bool UI::isInteractive() {
    return mode == INTERACTIVE;
}

void UI::printSilentStart() {
    cout << "Silent Mode" << endl;
    cout << "Simulation Starts..." << endl;
}

void UI::printSilentEnd(bool outputFileCreated) {
    cout << "Simulation ends";
    if (outputFileCreated){
        cout << ", Output file created";
    }
    cout << endl;
}

void UI::waitForEnter() {
    string dummy;
    cout << "Press Enter to advance to the next minute." << endl;
    getline(cin, dummy);
}
