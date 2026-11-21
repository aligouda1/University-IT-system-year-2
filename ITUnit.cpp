#include "ITUnit.h"


void ITUnit::addWaitingTicket(Ticket* t) {
	if (t == nullptr) { return; }
	switch (t->getType()) {
	case UR:
		Waiting_UR.enqueue(t);
		break;
	case SR:
		Waiting_SR.enqueue(t);
		break;
	case NR:
		Waiting_NR.enqueue(t);
		break;
	}
}
void ITUnit::addFreeTechnician(Technician * tech) {
	if (tech == nullptr) { return; }
	if (tech->getType() == ST) {
		Free_ST.enqueue(tech, tech->getTID());
	}
	else {
		Free_GT.enqueue(tech, tech->getTID());
	}
}
bool ITUnit::areWaitingListsEmpty() const {
	return Waiting_UR.isEmpty() && Waiting_SR.isEmpty() && Waiting_NR.isEmpty();
}
const UrgentPQ& ITUnit::getWaitingUR() const { return Waiting_UR; }
const Queue<Ticket*>& ITUnit::getWaitingSR() const { return Waiting_SR; }
const NRQueue& ITUnit::getWaitingNR() const { return Waiting_NR; }
const PriQueue<Technician*>& ITUnit::getFreeST() const { return Free_ST; }
const PriQueue<Technician*>& ITUnit::getFreeGT() const { return Free_GT; }
const BusyList& ITUnit::getBusyTechnicians() const { return Busy_Technicians; }