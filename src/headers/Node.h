#ifndef NODE
#define NODE

#include "Tile.h"

class Node {
public:
    Node();
    ~Node();
    const Tile::Colour getTile();
    const Node* getNext();
    void setNext(const Node* node);

private:
    Tile::Colour tile;
    Node* mNext;
};

#endif // NODE