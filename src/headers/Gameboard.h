#ifndef GAMEBOARD
#define GAMEBOARD

#include "SinglyLinkedList.h"
#include "GenericLinkedList.h"
#include "Player.h"

#define MAX_PLAYERS 2

using std::vector;

class Gameboard {

public:
    Gameboard();
    ~Gameboard();

    void initialiseTileBag();
    void initialiseFactories();

    void addNewPlayer(string playerName, int score);
    const Player* getCurrentPlayer();
    void setNextCurrentPlayer();

    const string tileBagToString();
    const string centreFactoryToString();
    const string factoriesToString();

private:
    SinglyLinkedList* tileBag;
    GenericLinkedList<Player*>* players;

    int centreFactorySize;
    vector<Tile::Colour> centreFactory;
    Tile::Colour factories[ARRAY_DIM][ARRAY_DIM];

    Player* currentPlayer;
};

#endif // GAMEBOARD