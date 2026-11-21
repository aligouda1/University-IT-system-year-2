#ifndef PRIQUEUE_H
#define PRIQUEUE_H
#include "PriNode.h"
#include <iostream>
using namespace std;

template <typename PQ>
class PriQueue
{
protected:
    PriNode<PQ>* head;
	int count;

public:
    PriQueue() : head(nullptr), count(0) {}
	PriQueue(const PriQueue&) = delete;
    PriQueue& operator=(const PriQueue&) = delete;
    virtual ~PriQueue() { clear(); }

	bool isEmpty() const { return head == nullptr; }
    void enqueue(const PQ& newData, int newPriority) {
		PriNode<PQ>* newNode = new PriNode<PQ>(newData, newPriority);
		if (isEmpty() || newPriority < head->getPriority()) {
			newNode->setNext(head);
			head = newNode;
		}
		else {
			PriNode<PQ>* current = head;
			while (current->getNext() != nullptr && current->getNext()->getPriority() <= newPriority) {
				current = current->getNext();
			}
			newNode->setNext(current->getNext());
			current->setNext(newNode);
		}
		count++;
    }
	bool dequeue(PQ& item, int& pri) {
		if (isEmpty()) {return false;}
		else {
			PriNode<PQ>* temp = head;
			item = temp->getData();
			head = head->getNext();
			pri = temp->getPriority();
			delete temp;
			count--;
			return true;
		}
	}
	bool peek(PQ& data, int& pri) const {
		if (isEmpty()) {
			return false;
		}
		data = head->getData();
		pri = head->getPriority();
		return true;
	}
	int getCount() const { return count; }
	void print() const {
		PriNode<PQ>* current = head;
		while (current != nullptr) {
			cout << current->getPriority();
			if (current->getNext() != nullptr)
				cout << ", ";
			current = current->getNext();
		}
	}
	void clear() {
		while (!isEmpty()) {
			PriNode<PQ>* temp = head;
			head = head->getNext();
			delete temp;
		}
		count = 0;
	}

};

#endif // PRIQUEUE_H
