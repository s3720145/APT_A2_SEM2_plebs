#ifndef GAMEBOARD
#define GAMEBOARD

#include "SinglyLinkedList.h"
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
    SinglyLinkedList* players;

    int centreFactorySize;
    int numPlayers;
    vector<Tile::Colour> centreFactory;
    Tile::Colour factories[ARRAY_DIM][ARRAY_DIM];

    Player* players[MAX_PLAYERS];
    Player* currentPlayer;
};

#endif // GAMEBOARD