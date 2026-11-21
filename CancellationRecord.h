class CancellationRecord {
private:
    int CT;   
    int RID;   
public:   
    CancellationRecord() {
        CT = 0;
        RID = 0;
    }   
    CancellationRecord(int ct, int rid) {
        CT = ct;
        RID = rid;
    }    
    int getCT() {
        return CT;
    }   
    int getRID() {
        return RID;
    }
};
