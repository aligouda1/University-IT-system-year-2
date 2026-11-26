#ifndef CANCELLATIONRECORD_H
#define CANCELLATIONRECORD_H

class CancellationRecord {
private:
    int CT;    //cancellation time
    int RID;   //request ID 
public:
    CancellationRecord();
    CancellationRecord(int ct, int rid);
    int getCT() const;
    int getRID() const;
    void setCT(int ct);
    void setRID(int rid);
};
#endif
