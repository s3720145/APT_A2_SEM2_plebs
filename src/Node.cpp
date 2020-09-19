#include "Node.h"

Node::Node(Tile::Colour tile){
    this->tile=tile;
}
Node::~Node(){
}
const Tile::Colour Node::getTile(){
    return this->tile;
}
Node Node::getNext(){
    Node outputNode = *mNext;
    return outputNode;
}
void Node::setNext(Node node){
    this->mNext = &node;
}