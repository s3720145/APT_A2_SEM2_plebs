#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H

#include "GenericNode.h"

template <typename T> 
class GenericLinkedList {
public:
    GenericLinkedList();
    ~GenericLinkedList();
    void addToBack(T value);
    GenericNode<T>* getHead();
    // returns value stored within node
    T removeHead();

private:
    GenericNode<T>* mHead;
    GenericNode<T>* mTail;
};

#endif // GENERICLINKEDLIST_H