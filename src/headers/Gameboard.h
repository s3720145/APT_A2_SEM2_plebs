#ifndef GAMEBOARD
#define GAMEBOARD

#include "SinglyLinkedList.h"
#include "Player.h"
#include <vector>

using std::vector;

class Gameboard {

public:
    Gameboard();
    ~Gameboard();

private:
    SinglyLinkedList* tileBag;

    Player* player1;
    Player* player2;
};

#endif // GAMEBOARD