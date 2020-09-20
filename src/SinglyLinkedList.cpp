#include "SinglyLinkedList.h"
SinglyLinkedList::SinglyLinkedList(){
    this->mHead = nullptr;
    this->mTail = nullptr;
}
SinglyLinkedList::~SinglyLinkedList(){
}
void SinglyLinkedList::initializeBag(int arrayDim){
    Node* currNode = mHead;
    for(int i=0; i<20; i++){
        for(int j=0; j<arrayDim; j++){
            Node* newNode = new Node(static_cast<Tile::Colour>(j));
            if(mHead == nullptr){
                mHead = newNode; 
                mTail = newNode;
            }
            else{
                mTail = newNode;
                currNode->setNext(newNode);
                currNode = currNode->getNext();
            }
        }
    }
}
void SinglyLinkedList::addToBack(Tile::Colour tile){
    Node* newTile = new Node(tile);
    mTail->setNext(newTile);
    mTail = this->mTail->getNext();

}
Node* SinglyLinkedList::removeHead(){
    Node* newHead = this->mHead->getNext();
    Node* oldHead = this->mHead;
    this->mHead = newHead;
    return oldHead;
}
string SinglyLinkedList::toString(){
    Node* currNode = this->mHead;
    string output;
    while(currNode != this->mTail){
        output.push_back(currNode->getTile());
        currNode = currNode->getNext();
    }
    output.push_back(this->mTail->getTile());
    return output;
}