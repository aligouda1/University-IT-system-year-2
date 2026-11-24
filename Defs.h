#ifndef DEFS_H
#define DEFS_H
#include <string>



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



struct Location {
    int LID;
    std::string name;
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
