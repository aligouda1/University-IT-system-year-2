#ifndef DEFS_H
#define DEFS_H
using namespace std;
#include <string>

// 1. Shared Enumerations (Enums)
// These define the standard options for types and modes across the whole project.

enum TicketType { 
    NR, // Normal Request
    SR, // Specialist Request
    UR  // Urgent Request
};

enum TechType { 
    ST, // Specialist Technician
    GT  // General Technician
};

enum TicketStatus { 
    WAITING, 
    IN_SERVICE, 
    COMPLETED, 
    CANCELLED 
};

enum SimMode { 
    INTERACTIVE, 
    SILENT 
};

// 2. Shared Basic Structs
// These are simple containers for the data entities you are responsible for managing.

struct Location {
    int LID;
    string name;
};

struct ProblemCode {
    int PC;
    char category; // 'B' (hardware) or 'H' (software/other)
    int duration;
};

struct CancellationRecord {
    int CT;  // Cancellation Time
    int RID; // Request ID
};
#endif // DEFS_H
