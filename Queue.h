// Queue.h - simple linked FIFO queue
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Node.h"
using namespace std;

template <typename T>
class Queue {
protected:
    Node<T>* front;
    Node<T>* back;
    int cont;

public:
    Queue() {
        front = nullptr;
        back = nullptr;
        cont = 0;
    }

  

    // no copying (it would delete the same nodes twice)
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    // add at the back - O(1)
    void enqueue(T value) {
        Node<T>* n = new Node<T>(value);
        if (front == nullptr)
            front = n;
        else
            back->setNext(n);
        back = n;
        cont++;
    }

    // remove from the front - O(1)
    bool dequeue(T& value) {
        if (front == nullptr)
            return false;

        Node<T>* temp = front;
        value = temp->getItem();
        front = front->getNext();
        if (front == nullptr)
            back = nullptr;   // queue is empty now
        delete temp;
        cont--;
        return true;
    }

    // look at the front without removing it - O(1)
    bool peek(T& value) {
        if (front == nullptr)
            return false;
        value = front->getItem();
        return true;
    }

    bool isEmpty() { return front == nullptr; }
    int getCount() { return count; }

    // print all items from front to back - O(n)
    void print() {
        Node<T>* cur = front;
        while (cur != nullptr) {
            cout << cur->getItem();
            if (cur->getNext() != nullptr)
                cout << " ";
            cur = cur->getNext();
        }
    }

    // delete all nodes - O(n)
    // (the objects the pointers point to are deleted by the Organizer destructor)
    void clear() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->getNext();
            delete temp;
        }
        back = nullptr;
        cont = 0;
    }
};

#endif
