#ifndef NODE
#define NODE

#include "Tile.h"

class Node {
public:
    Node(Tile::Colour tile);
    ~Node();
    const Tile::Colour getTile();
    Node getNext();
    void setNext(Node node);

private:
    Tile::Colour tile;
    Node* mNext;
};

#endif // NODE