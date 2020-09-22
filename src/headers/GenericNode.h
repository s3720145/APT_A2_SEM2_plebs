#ifndef GENERICNODE_H
#define GENERICNODE_H

template <typename T> 
class GenericNode {
public:
    GenericNode(T value);
    ~GenericNode();
    T getValue();
    GenericNode<T>* getNext();
    void setNext(GenericNode<T>* genericNode);

private:
    T value;
    GenericNode<T>* mNext;
};

#endif // GENERICNODE_H