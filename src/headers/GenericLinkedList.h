#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H

template <typename T> 
struct GNode {
    T value;
    GNode<T>* mNext;

    GNode(T value) {
        value = value;
        mNext = nullptr;
    }
};

template <typename T> 
class GenericLinkedList {
public:
    GenericLinkedList();
    ~GenericLinkedList();
    void addToBack(T value);
    GNode<T>* removeHead();

private:
    GNode<T>* mHead;
    GNode<T>* mTail;
};

#endif // GENERICLINKEDLIST_H