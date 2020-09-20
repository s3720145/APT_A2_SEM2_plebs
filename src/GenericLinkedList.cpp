#include "GenericLinkedList.h"
#include <iostream>

template <typename T> 
GenericLinkedList<T>::GenericLinkedList() {
    this->mHead = nullptr;
    this->mTail = nullptr;
}

template <typename T>
GenericLinkedList<T>::~GenericLinkedList() {

}

template <typename T>
void GenericLinkedList<T>::addToBack(T value) {
    std::cout << "test" << std::flush << std::endl;
    std::cout << "test" << std::flush;
    if(mHead == nullptr) {
        GNode<T>* newNode = new GNode<T>(value);
        mHead = newNode;
        mTail = newNode;
    } else {
        GNode<T>* newNode = new GNode<T>(value);
        mTail->mNext = newNode;
        newNode = mTail;
    }
}

template <typename T>
GNode<T>* GenericLinkedList<T>::removeHead() {
    GNode<T>* oldNode = mHead;

    if(mHead != nullptr) {
        mHead->mNext = nullptr;
    }

    return oldNode;
}