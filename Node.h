// Node.h - one node of a linked list
#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    T item;
    Node<T>* next;

public:
    Node(T value) {
        item = value;
        next = nullptr;
    }

    void setNext(Node<T>* n) { next = n; }
    Node<T>* getNext() { return next; }
    T getItem() { return item; }
};

#endif
