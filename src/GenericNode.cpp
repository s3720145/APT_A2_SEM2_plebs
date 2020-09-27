#include "GenericNode.h"

template <typename T> 
GenericNode<T>::GenericNode(T value) {
    this->value = value;
    this->mNext = nullptr;
}

template <typename T> 
GenericNode<T>::~GenericNode() {

}

template <typename T> 
T GenericNode<T>::getValue() {
    return value;
}

template <typename T> 
GenericNode<T>* GenericNode<T>::getNext() {
    return mNext;
}

template <typename T> 
void GenericNode<T>::setNext(GenericNode<T>* genericNode) {
    mNext = genericNode;
}