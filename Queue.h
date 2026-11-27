// Queue.h
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
    int count;

public:
    // initialize empty queue
    Queue() {
        front = nullptr;
        back = nullptr;
        count = 0;
    }

    // check if queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // return number of items
    int getCount() {
        return count;
    }

    // add item to the back
    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (isEmpty()) {
            front = newNode;
            back = newNode;
        }
        else {
            back->setNext(newNode);
            back = newNode;
        }
        count++;
    }

    // remove item from the front
    bool dequeue(T& value) {
        if (isEmpty())
            return false;

        Node<T>* temp = front;
        value = front->getItem();
        front = front->getNext();

        if (front == nullptr)
            back = nullptr;

        delete temp;
        count--;
        return true;
    }

    // get front item without removing it
    bool peek(T& value) {
        if (isEmpty())
            return false;

        value = front->getItem();
        return true;
    }

    // print all items in the queue
    void print() {
        Node<T>* cur = front;
        while (cur != nullptr) {
            cout << cur->getItem() << " ";
            cur = cur->getNext();
        }
    }

    // remove all nodes from the queue
    void clear() {
        T dummy;
        while (dequeue(dummy));
    }
};

#endif
