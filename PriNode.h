#ifndef PRINODE_H
#define PRINODE_H

template <typename PN>
class PriNode
{
private:
    PN  data;
    int priority;
    PriNode<PN>* next;

public:
    PriNode() : data(), priority(0), next(nullptr) {}

    PriNode(const PN& newData, int newPriority):
        data(newData), priority(newPriority), next(nullptr) {
    }

    PN getData() const { 
        return data;
    }
    int getPriority() const {
        return priority; 
    }
    PriNode<PN>* getNext() const { 
        return next;
    }

    void setData(const PN & newData) {
        data = newData;
    }
    void setPriority(int newPriority) {
        priority = newPriority;
    }
    void setNext(PriNode<PN>* newNext) {
        next = newNext;
    }
};

#endif 
