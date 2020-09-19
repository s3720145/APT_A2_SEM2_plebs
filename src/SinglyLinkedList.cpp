#include "SinglyLinkedList.h"
SinglyLinkedList::SinglyLinkedList(){
    this->mHead = nullptr;
    this->mTail = nullptr;
}
SinglyLinkedList::~SinglyLinkedList(){
}
void SinglyLinkedList::initializeBag(){
    //todo add a 100 tile bag
}
void SinglyLinkedList::addToBack(Tile::Colour tile){
    Node newTile = Node(tile);
    mTail->setNext(newTile);
    mTail = &this->mTail->getNext();

}
Node* SinglyLinkedList::removeHead(){
    Node* newHead = &this->mHead->getNext();
    Node* oldHead = this->mHead;
    this->mHead = newHead;
    return oldHead;
}
string SinglyLinkedList::toString(){
    Node* currNode = this->mHead;
    string output;
    while(currNode != this->mTail){
        output.push_back(currNode->getTile());
        currNode = &currNode->getNext();
    }
    output.push_back(this->mTail->getTile());
    return output;
}