#include "UI.h"

UI::UI() {
    mode = INTERACTIVE;
}

SimMode UI::selectMode() {
    string choice;
    while (true) {
        cout << "Choose the mode:\n1 - Interactive\n2 - Silent\nYour choice: ";
        getline(cin, choice);

        if (choice == "1") {
            mode = INTERACTIVE;
            break;
        } else if (choice == "2") {
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
    return (mode == INTERACTIVE);
}

void UI::printSilentStart() {
    cout << "Silent Mode\nSimulation Starts..." << endl;
}

void UI::printSilentEnd(bool outputFileCreated) {
    cout << "Simulation ends";
    if (outputFileCreated)
        cout << ", Output file created";
    cout << endl;
}

void UI::waitForEnter() {
    string temp;
    cout << "Press Enter to advance to the next minute." << endl;
    getline(cin, temp);
}
