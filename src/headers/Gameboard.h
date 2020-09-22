#ifndef GAMEBOARD
#define GAMEBOARD

#include "GenericLinkedList.h"
#include "Player.h"
#include <fstream>
#include <sstream>

#define NUM_PER_TILE    20
#define FACTORY_WIDTH   4

using std::vector;

class Gameboard {

public:
    Gameboard();
    ~Gameboard();

    void setTileBag();
    void setFactories();

    void addNewPlayer(string playerName, int score);
    Player* getCurrentPlayer();
    void setNextCurrentPlayer();

    const string tileBagToString();
    const string centreFactoryToString();
    const string factoriesToString();

private:
    GenericLinkedList<Tile*>* tileBag;
    GenericLinkedList<Player*>* players;

    int centreFactorySize;
    vector<Tile*> centreFactory;
    Tile* factories[ARRAY_DIM][FACTORY_WIDTH];

    Player* currentPlayer;
};

#endif // GAMEBOARD