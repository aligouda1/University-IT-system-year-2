#include "CancellationRecord.h"
CancellationRecord::CancellationRecord() {
    CT = 0;
    RID = 0;
}
CancellationRecord::CancellationRecord(int ct, int rid) {
    CT = ct;
    RID = rid;
}
int CancellationRecord::getCT() const {
    return CT;
}
int CancellationRecord::getRID() const {
    return RID;
}
void CancellationRecord::setCT(int ct) {
    CT = ct;
}
void CancellationRecord::setRID(int rid) {
    RID = rid;
}
