#ifndef SINGLYLINKEDLIST
#define SINGLYLINKEDLIST

#include "Node.h"
#include <string>

using std::string;

class SinglyLinkedList {
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void initializeBag();
    void addToBack(Tile::Colour tile);
    Node* removeHead();
    string toString();

private:
    Node* mHead;
    Node* mTail;

};

#endif // SINGLYLINKEDLIST