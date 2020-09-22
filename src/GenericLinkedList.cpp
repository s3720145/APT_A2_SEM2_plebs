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
    GenericNode<T>* newNode = new GenericNode<T>(value);

    // if empty list
    if(mHead == nullptr) {
        mHead = newNode;
        mTail = newNode;
    } else {
        mTail->setNext(newNode);
        mTail = mTail->getNext();
    }
}

template <typename T>
GenericNode<T>* GenericLinkedList<T>::getHead() {
    return mHead;
}

template <typename T>
GenericNode<T>* GenericLinkedList<T>::removeHead() {
    GenericNode<T>* removedNode = mHead;

    if(mHead != nullptr) {
        mHead = removedNode->getNext();
        removedNode->setNext(nullptr);
    }

    return removedNode;
}