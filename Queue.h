
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

  

    
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

   
    void enqueue(T value) {
        Node<T>* n = new Node<T>(value);
        if (front == nullptr)
            front = n;
        else
            back->setNext(n);
        back = n;
        cont++;
    }

    
    bool dequeue(T& value) {
        if (front == nullptr)
            return false;

        Node<T>* temp = front;
        value = temp->getItem();
        front = front->getNext();
        if (front == nullptr)
            back = nullptr;   
        delete temp;
        cont--;
        return true;
    }

    
    bool peek(T& value) {
        if (front == nullptr)
            return false;
        value = front->getItem();
        return true;
    }

    bool isEmpty() { return front == nullptr; }
    int getCount() { return count; }

    
    void print() {
        Node<T>* cur = front;
        while (cur != nullptr) {
            cout << cur->getItem();
            if (cur->getNext() != nullptr)
                cout << " ";
            cur = cur->getNext();
        }
    }

    
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
